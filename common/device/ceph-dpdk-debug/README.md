```c
void DPDKWorker::initialize()
{
  static enum {
    WAIT_DEVICE_STAGE,
    WAIT_PORT_FIN_STAGE,
    DONE
  } create_stage = WAIT_DEVICE_STAGE;
  static Mutex lock("DPDKStack::lock");
  static Cond cond;
  static unsigned queue_init_done = 0;
  static unsigned cores = 0;
  static std::shared_ptr<DPDKDevice> sdev;

  unsigned i = center.get_id();
  ldout(cct, 10) << __func__ << " id = " << i << dendl;
  if (i == 0) {
    cores = cct->_conf->ms_async_op_threads;
    uint8_t port_idx = cct->_conf->ms_dpdk_port_id;

    ldout(cct, 5) << __func__ << " using " << cores << " cores and port "
        << port_idx << dendl;

    std::unique_ptr<DPDKDevice> dev = create_dpdk_net_device(
        cct, cores, port_idx,
        cct->_conf->ms_dpdk_lro,
        cct->_conf->ms_dpdk_hw_flow_control);
    sdev = std::shared_ptr<DPDKDevice>(dev.release());
    sdev->workers.resize(cores);

    Mutex::Locker l(lock);
    create_stage = WAIT_PORT_FIN_STAGE;
    cond.Signal();
  } else {
    Mutex::Locker l(lock);
    while (create_stage <= WAIT_DEVICE_STAGE)
      cond.Wait(lock);
  }
  assert(sdev);
  ldout(cct, 10) << __func__ << " event_id " << i << " hw_queues_count =  "
      << sdev->hw_queues_count() << dendl;
  if (i < sdev->hw_queues_count()) {
    auto qp = sdev->init_local_queue(cct, &center, cct->_conf->ms_dpdk_hugepages, i);
    std::map<unsigned, float> cpu_weights;
    for (unsigned j = sdev->hw_queues_count() + i % sdev->hw_queues_count();
         j < cores; j+= sdev->hw_queues_count())
      cpu_weights[i] = 1;
    cpu_weights[i] = cct->_conf->ms_dpdk_hw_queue_weight;
    qp->configure_proxies(cpu_weights);
    sdev->set_local_queue(i, std::move(qp));
    Mutex::Locker l(lock);
    ++queue_init_done;
    cond.Signal();
  } else {
    // auto master = qid % sdev->hw_queues_count();
    // sdev->set_local_queue(create_proxy_net_device(master, sdev.get()));
    ceph_abort();
  }
  if (i == 0) {
    {
      ldout(cct, 10) << __func__ << " === Wait queue_init_done=" <<
          queue_init_done  << " < cores=" << cores << dendl;
      Mutex::Locker l(lock);
      while (queue_init_done < cores)
        cond.Wait(lock);
      ldout(cct, 10) << __func__ << " >>> End  queue_init_done=" <<
          queue_init_done  << " >= cores=" << cores << dendl;
    }

    if (sdev->init_port_fini() < 0) {
      lderr(cct) << __func__ << " init_port_fini failed " << dendl;
      ceph_abort();
    }
    Mutex::Locker l(lock);
    create_stage = DONE;
    cond.Signal();
  } else {
    Mutex::Locker l(lock);
    while (create_stage <= WAIT_PORT_FIN_STAGE)
      cond.Wait(lock);
  }

  sdev->workers[i] = this;
  _impl = std::unique_ptr<DPDKWorker::Impl>(
          new DPDKWorker::Impl(cct, i, &center, sdev));
  {
    Mutex::Locker l(lock);
    if (!--queue_init_done) {
      create_stage = WAIT_DEVICE_STAGE;
      sdev.reset();
    }
  }
}


```

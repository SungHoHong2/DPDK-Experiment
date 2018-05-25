found out that hydra is one of the process managers
Hydra is the default process management framework that uses existing
daemons on nodes (e.g., ssh, pbs, slurm, sge) to start MPI
and the rdma interface part is unaccessible.

However IMB benchmark is only compatible in MPICH
MPICH is a high-performance and widely portable implementation of the Message Passing Interface (MPI)
standard (MPI-1, MPI-2 and MPI-3).

(1) to provide an MPI implementation that efficiently supports different computation
(2) communication platforms including commodity clusters (desktop systems, shared-memory systems, multicore architectures), high-speed networks (10 Gigabit Ethernet, InfiniBand, Myrinet, Quadrics)

MVAPICH2
Open-MPI
MPICH





mpirun -np 128 --hostfile filename ./IMB-MPI1 pingpong -msglog 10

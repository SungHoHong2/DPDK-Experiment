### RING EXPERIMENT

- **load balancing example running code**

```
./build/load_balancer -l 3-7 -n 4 -d librte_pmd_e1000.so -d librte_mempool_ring.so -- --rx "(0,0,3),(1,0,3)" --tx "(0,3),(1,3)" --w "4,5,6,7" --lpm "1.0.0.0/24=>0; 1.0.1.0/24=>1;" --pos-lb 29
```


<br>

- [debugging files from load balance](load_balancing/debug)
- **the files related ring**

```c
// buffer struct
struct buf_ring {
        volatile uint32_t       br_prod_head;
        volatile uint32_t       br_prod_tail;
        int                     br_prod_size;
        int                     br_prod_mask;
        uint64_t                br_drops;
        uint64_t                br_prod_bufs;
        uint64_t                br_prod_bytes;

        uint64_t                pad0[11];

        volatile uint32_t       br_cons_head;
        volatile uint32_t       br_cons_tail;
        int                     br_cons_size;
        int                     br_cons_mask;

        uint64_t                pad1[14];
#ifdef DEBUG_BUFRING
        struct mtx              * br_lock;
#endif
        void                    * br_ring[0];
};


// buffer ring allocation
struct buf_ring * buf_ring_alloc(int count, struct malloc_type *type, int flags, struct mtx *lock);

// free ring
void buf_ring_free(struct buf_ring *br, struct malloc_type *type);

// multi-producer safe lock-free ring buffer enqueue
static __inline int buf_ring_enqueue_bytes(struct buf_ring *br, void *buf, int nbytes)
static __inline int
buf_ring_enqueue(struct buf_ring *br, void *buf){
        return (buf_ring_enqueue_bytes(br, buf, 0));
}

// multi-consumer safe dequeue
static __inline void *buf_ring_dequeue_mc(struct buf_ring *br);

// single-consumer dequeue
static __inline void *buf_ring_dequeue_sc(struct buf_ring *br);

// return a pointer to the first entry in the ring
static __inline void *buf_ring_peek(struct buf_ring *br);

static __inline int buf_ring_full(struct buf_ring *br);

static __inline int buf_ring_empty(struct buf_ring *br);

static __inline int buf_ring_count(struct buf_ring *br);

struct buf_ring *buf_ring_alloc(int count, struct malloc_type *type, int flags, struct mtx *);

void buf_ring_free(struct buf_ring *br, struct malloc_type *type);
```

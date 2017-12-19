#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");


#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
#include <sys/ktr.h>
#include <sys/buf_ring.h>


struct buf_ring * buf_ring_alloc(int count, struct malloc_type *type, int flags, struct mtx *lock){
        struct buf_ring *br;

        KASSERT(powerof2(count), ("buf ring must be size power of 2"));

        br = malloc(sizeof(struct buf_ring) + count*sizeof(caddr_t),
            type, flags|M_ZERO);
        if (br == NULL)
                return (NULL);
#ifdef DEBUG_BUFRING
        br->br_lock = lock;
#endif
        br->br_prod_size = br->br_cons_size = count;
        br->br_prod_mask = br->br_cons_mask = count-1;
        br->br_prod_head = br->br_cons_head = 0;
        br->br_prod_tail = br->br_cons_tail = 0;
        return (br);
}

void
buf_ring_free(struct buf_ring *br, struct malloc_type *type){
        free(br, type);
}

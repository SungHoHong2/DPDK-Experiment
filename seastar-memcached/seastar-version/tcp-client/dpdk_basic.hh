#define	LIBMEMCACHED_MEMCACHED_SET_START()
#define	LIBMEMCACHED_MEMCACHED_SET_END()
#define memcached2Memcached(__obj) (__obj)

typedef struct memcached_st Memcached;

enum memcached_storage_action_t {
    SET_OP,
    REPLACE_OP,
    ADD_OP,
    PREPEND_OP,
    APPEND_OP,
    CAS_OP
};

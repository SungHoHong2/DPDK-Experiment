#define MAX_ERROR_LENGTH 2048
struct memcached_error_t
{
    Memcached *root;
    uint64_t query_id;
    struct memcached_error_t *next;
    memcached_return_t rc;
    int local_errno;
    size_t size;
    char message[MAX_ERROR_LENGTH];
};

static inline void libmemcached_free(const memcached_st *self, void *mem)
{
    if (self)
    {
        self->allocators.free(self, mem, self->allocators.context);
    }
    else if (mem)
    {
#ifdef __cplusplus
        std::free(mem);
#else
        free(mem);
#endif
    }
}


static void _error_free(memcached_error_t *error)
{
    if (error)
    {
        _error_free(error->next);

        libmemcached_free(error->root, error);
    }
}


void memcached_error_free(Memcached& self)
{
    _error_free(self.error_messages);
    self.error_messages= NULL;
}


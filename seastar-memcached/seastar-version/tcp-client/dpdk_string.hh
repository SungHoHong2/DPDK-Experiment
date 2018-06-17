#define HASHKIT_BLOCK_SIZE 1024

struct hashkit_string_st {
    char *end;
    size_t current_size;
    char *string;
};

size_t hashkit_string_length(const hashkit_string_st *self)
{
    return size_t(self->end -self->string);
}

char *hashkit_string_c_str_mutable(hashkit_string_st *self)
{
    assert(self);
    if (self == NULL)
    {
        return NULL;
    }
    return self->string;
}

const char *hashkit_string_c_str(const hashkit_string_st* self)
{
    assert(self);
    if (self == NULL)
    {
        return NULL;
    }
    return self->string;
}


hashkit_string_st *hashkit_string_create(size_t initial_size);

bool hashkit_string_append_character(hashkit_string_st *string, char character);

bool hashkit_string_append(hashkit_string_st *string, const char *value, size_t length);

char *hashkit_string_c_copy(hashkit_string_st *string);

void hashkit_string_reset(hashkit_string_st *string);

bool hashkit_string_resize(hashkit_string_st& string, const size_t need);

size_t hashkit_string_max_size(const hashkit_string_st *self);

char *hashkit_string_take(hashkit_string_st *self);

char *hashkit_string_c_str_mutable(hashkit_string_st *self);

void hashkit_string_set_length(hashkit_string_st *self, size_t length);

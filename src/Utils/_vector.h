#ifndef _VECTOR_H_
#define _VECTOR_H_

// https://www.daniweb.com/software-development/c/threads/377149/how-could-i-implement-a-vector-like-container-by-pure-c


#include <stddef.h>
/**
 * @brief Returns the value of an item at the specified index
 * @remarks This is a convenience wrapper around vector_at() for the average use case
 */
#define VECTOR_AT(T,v,i) *((T*)_vector_at((v), (i)))
/**
 * @brief Inserts a value of type T into a vector at the specified index
 * @remarks This is a convenience wrapper to support rvalues.
 *          Note that VECTOR_INSERT() cannot be used as an expression
 */
#define VECTOR_INSERT(T, v, x, i) do {        \
    T __anon_var19781111 = x;                 \
    _vector_insert(v, &__anon_var19781111, i); \
} while (0)
/**
 * @brief A structure representing the vector object
 */
typedef struct _vector {
    void   *base;      /**< Raw memory for items */
    size_t  size;      /**< The number of inserted items */
    size_t  capacity;  /**< The number of potential items before a resize */
    size_t  item_size; /**< The number of bytes occupied by an item */
} _vector;

extern _vector *_vector_create(size_t item_size, size_t capacity);
extern _vector *_vector_clone(_vector *v);
extern void     _vector_clear(_vector *v);
extern int      _vector_resize(_vector *v, size_t capacity);
extern size_t   _vector_size(_vector *v);
extern void   * _vector_at(_vector *v, size_t index);
extern int      _vector_insert(_vector *v, void *item, size_t index);
extern int      _vector_remove(_vector *v, size_t index);
extern int      _vector_remove_if(_vector *v, int (*pred)(void *item));
extern size_t   _vector_find(_vector *v, void *value);
extern size_t   _vector_find_if(_vector *v, int (*pred)(void *item));


#endif// _VECTOR_H_

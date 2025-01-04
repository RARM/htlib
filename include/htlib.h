#ifndef _HTLIB_H_
#define _HTLIB_H_

#include <stdbool.h>
#include <stddef.h>

// Type of the hashmap key
typedef enum {
  HT_KEY_TYPE_INT,
  HT_KEY_TYPE_UINT,
  HT_KEY_TYPE_DOUBLE,
  HT_KEY_TYPE_STRING,
} ht_key_type_t;

// Type of the hashmap value
typedef enum {
  HT_VALUE_TYPE_INT,
  HT_VALUE_TYPE_UINT,
  HT_VALUE_TYPE_DOUBLE,
  HT_VALUE_TYPE_STRING,
  HT_VALUE_TYPE_PTR
} ht_value_type_t;

// Hashmap structure
typedef struct ht_hashmap ht_hashmap_t;

/**
 * @brief Creates a new hashmap.
 *
 * @param key_type The type of the keys in the hashmap.
 * @param value_type The type of the values in the hashmap.
 * @param initial_capacity The initial capacity of the hashmap.
 * @return A pointer to the new hashmap, or NULL if an error occurred.
 */
ht_hashmap_t *ht_new(ht_key_type_t key_type, ht_value_type_t value_type,
                     size_t initial_capacity);

/**
 * @brief Inserts a key-value pair into the hashmap.
 *
 * @param ht The hashmap to insert into.
 * @param key The key to insert.
 * @param value The value to insert.
 * @return True if the insertion was successful, false otherwise.
 */
bool ht_insert(ht_hashmap_t *ht, const void *key, const void *value);

/**
 * @brief Gets the value associated with a key.
 *
 * @param ht The hashmap to search.
 * @param key The key to search for.
 * @param value_out A pointer to a variable to store the value in.
 * @return True if the key was found, false otherwise.
 */
bool ht_get(ht_hashmap_t *ht, const void *key, void *value_out);

/**
 * @brief Removes a key-value pair from the hashmap.
 *
 * @param ht The hashmap to remove from.
 * @param key The key to remove.
 * @return True if the removal was successful, false otherwise.
 */
bool ht_remove(ht_hashmap_t *ht, const void *key);

/**
 * @brief Gets the number of elements in the hashmap.
 *
 * @param ht The hashmap to get the size of.
 * @return The number of elements in the hashmap.
 */
size_t ht_size(ht_hashmap_t *ht);

/**
 * @brief Checks if the hashmap is empty.
 *
 * @param ht The hashmap to check.
 * @return True if the hashmap is empty, false otherwise.
 */
bool ht_is_empty(ht_hashmap_t *ht);

/**
 * @brief Clears all elements from the hashmap.
 *
 * @param ht The hashmap to clear.
 */
void ht_clear(ht_hashmap_t *ht);

/**
 * @brief Destroys the hashmap.
 *
 * @param ht The hashmap to destroy.
 */
void ht_destroy(ht_hashmap_t *ht);

#endif  // _HTLIB_H_
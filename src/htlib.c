#include "htlib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the load factor threshold for rehashing
#define HT_LOAD_FACTOR_THRESHOLD 0.75

// Define the initial capacity of the hashmap
#define HT_INITIAL_CAPACITY 16

static size_t ht_key_size(ht_key_type_t key_type);
static size_t ht_value_size(ht_value_type_t value_type, const void *value);

// Structure for a key-value pair
typedef struct ht_entry {
  void *key;
  void *value;
  struct ht_entry *next;  // For handling collisions with separate chaining
} ht_entry_t;

// Structure for the hashmap
struct ht_hashmap {
  ht_key_type_t key_type;
  ht_value_type_t value_type;
  size_t size;         // Number of elements in the hashmap
  size_t capacity;     // Capacity of the hash table
  ht_entry_t **table;  // Hash table array
};

// Hash function (FNV-1a hash algorithm)
static unsigned int ht_hash(const void *key, ht_key_type_t key_type,
                            size_t capacity) {
  unsigned int hash = 2166136261u;
  switch (key_type) {
    case HT_KEY_TYPE_INT: {
      int int_key = *(int *)key;
      for (size_t i = 0; i < sizeof(int); i++) {
        hash ^= (unsigned char)(int_key >> (i * 8));
        hash *= 16777619u;
      }
      break;
    }
    case HT_KEY_TYPE_UINT: {
      unsigned int uint_key = *(unsigned int *)key;
      for (size_t i = 0; i < sizeof(unsigned int); i++) {
        hash ^= (unsigned char)(uint_key >> (i * 8));
        hash *= 16777619u;
      }
      break;
    }
    case HT_KEY_TYPE_DOUBLE: {
      double double_key = *(double *)key;
      for (size_t i = 0; i < sizeof(double); i++) {
        hash ^= ((unsigned char *)&double_key)[i];
        hash *= 16777619u;
      }
      break;
    }
    case HT_KEY_TYPE_STRING: {
      const char *str_key = (const char *)key;
      for (size_t i = 0; str_key[i] != '\0'; i++) {
        hash ^= (unsigned char)str_key[i];
        hash *= 16777619u;
      }
      break;
    }
    default:
      // Handle invalid key type
      break;
  }
  return hash % capacity;
}

// Comparison function for keys
static bool ht_compare_keys(const void *key1, const void *key2,
                            ht_key_type_t key_type) {
  switch (key_type) {
    case HT_KEY_TYPE_INT:
      return *(int *)key1 == *(int *)key2;
    case HT_KEY_TYPE_UINT:
      return *(unsigned int *)key1 == *(unsigned int *)key2;
    case HT_KEY_TYPE_DOUBLE:
      return *(double *)key1 == *(double *)key2;
    case HT_KEY_TYPE_STRING:
      return strcmp((const char *)key1, (const char *)key2) == 0;
    default:
      // Handle invalid key type
      return false;
  }
}

// Creates a new hashmap
ht_hashmap_t *ht_new(ht_key_type_t key_type, ht_value_type_t value_type,
                     size_t initial_capacity) {
  if (initial_capacity == 0) {
    initial_capacity = HT_INITIAL_CAPACITY;
  }

  ht_hashmap_t *ht = (ht_hashmap_t *)malloc(sizeof(ht_hashmap_t));
  if (ht == NULL) {
    return NULL;
  }

  ht->key_type = key_type;
  ht->value_type = value_type;
  ht->size = 0;
  ht->capacity = initial_capacity;
  ht->table = (ht_entry_t **)calloc(ht->capacity, sizeof(ht_entry_t *));
  if (ht->table == NULL) {
    free(ht);
    return NULL;
  }

  return ht;
}

// Inserts a key-value pair into the hashmap
bool ht_insert(ht_hashmap_t *ht, const void *key, const void *value) {
  if (ht == NULL || key == NULL || value == NULL) {
    return false;
  }

  // Calculate the load factor
  double load_factor = (double)ht->size / ht->capacity;

  // Rehash if the load factor exceeds the threshold
  if (load_factor >= HT_LOAD_FACTOR_THRESHOLD) {
    // ... (Rehashing logic - to be implemented)
  }

  // Calculate the hash index
  unsigned int index = ht_hash(key, ht->key_type, ht->capacity);

  // Create a new entry
  ht_entry_t *new_entry = (ht_entry_t *)malloc(sizeof(ht_entry_t));
  if (new_entry == NULL) {
    return false;
  }
  new_entry->key = malloc(ht_key_size(ht->key_type));
  if (new_entry->key == NULL) {
    free(new_entry);
    return false;
  }
  memcpy(new_entry->key, key, ht_key_size(ht->key_type));
  new_entry->value = malloc(ht_value_size(ht->value_type, value));
  if (new_entry->value == NULL) {
    free(new_entry->key);
    free(new_entry);
    return false;
  }
  memcpy(new_entry->value, value, ht_value_size(ht->value_type, value));
  new_entry->next = NULL;

  // Insert the entry into the hash table (separate chaining)
  if (ht->table[index] == NULL) {
    ht->table[index] = new_entry;
  } else {
    ht_entry_t *current = ht->table[index];
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_entry;
  }

  ht->size++;
  return true;
}

// Gets the value associated with a key
bool ht_get(ht_hashmap_t *ht, const void *key, void *value_out) {
  if (ht == NULL || key == NULL || value_out == NULL) {
    return false;
  }

  // Calculate the hash index
  unsigned int index = ht_hash(key, ht->key_type, ht->capacity);

  // Search for the key in the linked list
  ht_entry_t *current = ht->table[index];
  while (current != NULL) {
    if (ht_compare_keys(current->key, key, ht->key_type)) {
      memcpy(value_out, current->value,
             ht_value_size(ht->value_type, current->value));
      return true;
    }
    current = current->next;
  }

  return false;  // Key not found
}

// Removes a key-value pair from the hashmap
bool ht_remove(ht_hashmap_t *ht, const void *key) {
  if (ht == NULL || key == NULL) {
    return false;
  }

  // Calculate the hash index
  unsigned int index = ht_hash(key, ht->key_type, ht->capacity);

  // Search for the key in the linked list
  ht_entry_t *current = ht->table[index];
  ht_entry_t *previous = NULL;
  while (current != NULL) {
    if (ht_compare_keys(current->key, key, ht->key_type)) {
      // Remove the entry from the linked list
      if (previous == NULL) {
        ht->table[index] = current->next;
      } else {
        previous->next = current->next;
      }

      // Free the entry's memory
      free(current->key);
      free(current->value);
      free(current);

      ht->size--;
      return true;
    }
    previous = current;
    current = current->next;
  }

  return false;  // Key not found
}

// Gets the number of elements in the hashmap
size_t ht_size(ht_hashmap_t *ht) {
  if (ht == NULL) {
    return 0;
  }
  return ht->size;
}

// Checks if the hashmap is empty
bool ht_is_empty(ht_hashmap_t *ht) {
  if (ht == NULL) {
    return true;
  }
  return ht->size == 0;
}

// Clears all elements from the hashmap
void ht_clear(ht_hashmap_t *ht) {
  if (ht == NULL) {
    return;
  }

  for (size_t i = 0; i < ht->capacity; i++) {
    ht_entry_t *current = ht->table[i];
    while (current != NULL) {
      ht_entry_t *next = current->next;
      free(current->key);
      free(current->value);
      free(current);
      current = next;
    }
    ht->table[i] = NULL;
  }
  ht->size = 0;
}

// Destroys the hashmap
void ht_destroy(ht_hashmap_t *ht) {
  if (ht == NULL) {
    return;
  }

  ht_clear(ht);
  free(ht->table);
  free(ht);
}

// Helper function to get the size of a key based on its type
static size_t ht_key_size(ht_key_type_t key_type) {
  switch (key_type) {
    case HT_KEY_TYPE_INT:
      return sizeof(int);
    case HT_KEY_TYPE_UINT:
      return sizeof(unsigned int);
    case HT_KEY_TYPE_DOUBLE:
      return sizeof(double);
    case HT_KEY_TYPE_STRING:
      // Note: This assumes the string is passed as a pointer to a
      // null-terminated string. The actual size might vary.
      return sizeof(char *);
    default:
      return 0;
  }
}

// Helper function to get the size of a value based on its type
static size_t ht_value_size(ht_value_type_t value_type, const void *value) {
  switch (value_type) {
    case HT_VALUE_TYPE_INT:
      return sizeof(int);
    case HT_VALUE_TYPE_UINT:
      return sizeof(unsigned int);
    case HT_VALUE_TYPE_DOUBLE:
      return sizeof(double);
    case HT_VALUE_TYPE_STRING:
      // Note: This assumes the string is passed as a pointer to a
      // null-terminated string. The actual size might vary.
      return sizeof(char *);
    case HT_VALUE_TYPE_PTR:
      return sizeof(void *);
    default:
      return 0;
  }
}
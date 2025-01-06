# htlib: A Lightweight C Hashmap Library

## Overview
htlib is a lightweight, cross-platform C library that provides a simple and efficient hashmap implementation. It supports various key and value types, including integers, unsigned integers, doubles, strings, and pointers, making it suitable for a wide range of applications.

## Features

> [!caution]
> The library is not ready. It is still missing features for automatic resizing and there is an issue with tables using integer keys and string values.

*   **Support for various key and value types:**
    *   Signed/unsigned integers
    *   Doubles
    *   C strings
    *   Pointers to custom data structures
*   **No external dependencies:** htlib relies only on standard C libraries, ensuring portability across different platforms.
*   **Efficient hash function:** Uses the FNV-1a hash algorithm for good distribution and performance.
*   **Collision handling:** Implements separate chaining for efficient handling of collisions.
*   **Dynamic resizing:** Automatically resizes the hashmap as needed to maintain performance. (To be implemented)
*   **Memory management:** Provides functions for clearing and destroying the hashmap, ensuring proper memory deallocation.

## Example Operations
### Including the library
```c
#include "htlib.h"
```

### Creating a hashmap
```c
ht_hashmap_t *ht = ht_new(HT_KEY_TYPE_INT, HT_VALUE_TYPE_STRING, 16);
```

This creates a new hashmap with an initial capacity of 16. The key type is set to `HT_KEY_TYPE_INT`, and the value type is set to `HT_VALUE_TYPE_STRING`.

### Inserting key-value pairs
```c
int key = 1;
const char *value = "value1";
ht_insert(ht, &key, value);
```

### Retrieving values
```c
char retrieved_value[100];
ht_get(ht, &key, retrieved_value);
```

### Removing key-value pairs
```c
ht_remove(ht, &key);
```

### Other operations
* `ht_size(ht)`: Returns the number of elements in the hashmap.
* `ht_is_empty(ht)`: Checks if the hashmap is empty.
* `ht_clear(ht)`: Removes all elements from the hashmap.
* `ht_destroy(ht)`: Destroys the hashmap and frees the allocated memory.
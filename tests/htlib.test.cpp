#include "htlib.h"
#include <gtest/gtest.h>

TEST(HtLibTest, IntInt) {
  ht_hashmap_t *ht = ht_new(HT_KEY_TYPE_INT, HT_VALUE_TYPE_INT, 16);
  ASSERT_NE(ht, nullptr);

  int key1 = 1;
  int value1 = 10;
  ASSERT_TRUE(ht_insert(ht, &key1, &value1));

  int key2 = 2;
  int value2 = 20;
  ASSERT_TRUE(ht_insert(ht, &key2, &value2));

  int retrieved_value1;
  int retrieved_value2;
  ASSERT_TRUE(ht_get(ht, &key1, &retrieved_value1));
  ASSERT_EQ(retrieved_value1, value1);
  ASSERT_TRUE(ht_get(ht, &key2, &retrieved_value2));
  ASSERT_EQ(retrieved_value2, value2);

  ASSERT_EQ(ht_size(ht), 2);

  ASSERT_TRUE(ht_remove(ht, &key1));
  ASSERT_EQ(ht_size(ht), 1);

  ht_destroy(ht);
}

TEST(HtLibTest, IntUint) {
  ht_hashmap_t *ht = ht_new(HT_KEY_TYPE_INT, HT_VALUE_TYPE_UINT, 16);
  ASSERT_NE(ht, nullptr);

  int key1 = 1;
  unsigned int value1 = 10;
  ASSERT_TRUE(ht_insert(ht, &key1, &value1));

  int key2 = 2;
  unsigned int value2 = 20;
  ASSERT_TRUE(ht_insert(ht, &key2, &value2));

  unsigned int retrieved_value1;
  unsigned int retrieved_value2;
  ASSERT_TRUE(ht_get(ht, &key1, &retrieved_value1));
  ASSERT_EQ(retrieved_value1, value1);
  ASSERT_TRUE(ht_get(ht, &key2, &retrieved_value2));
  ASSERT_EQ(retrieved_value2, value2);

  ASSERT_EQ(ht_size(ht), 2);

  ASSERT_TRUE(ht_remove(ht, &key1));
  ASSERT_EQ(ht_size(ht), 1);

  ht_destroy(ht);
}

TEST(HtLibTest, IntDouble) {
  ht_hashmap_t *ht = ht_new(HT_KEY_TYPE_INT, HT_VALUE_TYPE_DOUBLE, 16);
  ASSERT_NE(ht, nullptr);

  int key1 = 1;
  double value1 = 10.5;
  ASSERT_TRUE(ht_insert(ht, &key1, &value1));

  int key2 = 2;
  double value2 = 20.5;
  ASSERT_TRUE(ht_insert(ht, &key2, &value2));

  double retrieved_value1;
  double retrieved_value2;
  ASSERT_TRUE(ht_get(ht, &key1, &retrieved_value1));
  ASSERT_EQ(retrieved_value1, value1);
  ASSERT_TRUE(ht_get(ht, &key2, &retrieved_value2));
  ASSERT_EQ(retrieved_value2, value2);

  ASSERT_EQ(ht_size(ht), 2);

  ASSERT_TRUE(ht_remove(ht, &key1));
  ASSERT_EQ(ht_size(ht), 1);

  ht_destroy(ht);
}

TEST(HtLibTest, IntString) {
  ht_hashmap_t *ht = ht_new(HT_KEY_TYPE_INT, HT_VALUE_TYPE_STRING, 16);
  ASSERT_NE(ht, nullptr);

  int key1 = 1;
  const char *value1 = "value1";
  ASSERT_TRUE(ht_insert(ht, &key1, &value1));

  int key2 = 2;
  const char *value2 = "value2";
  ASSERT_TRUE(ht_insert(ht, &key2, &value2));

  char *retrieved_value1 = (char *)malloc(100);
  char *retrieved_value2 = (char *)malloc(100);
  ASSERT_TRUE(ht_get(ht, &key1, retrieved_value1));
  ASSERT_STREQ(retrieved_value1, value1);
  ASSERT_TRUE(ht_get(ht, &key2, retrieved_value2));
  ASSERT_STREQ(retrieved_value2, value2);

  ASSERT_EQ(ht_size(ht), 2);

  ASSERT_TRUE(ht_remove(ht, &key1));
  ASSERT_EQ(ht_size(ht), 1);

  free(retrieved_value1);
  free(retrieved_value2);
  ht_destroy(ht);
}

TEST(HtLibTest, IntPtr) {
  ht_hashmap_t *ht = ht_new(HT_KEY_TYPE_INT, HT_VALUE_TYPE_PTR, 16);
  ASSERT_NE(ht, nullptr);

  int key1 = 1;
  int value1 = 10;
  ASSERT_TRUE(ht_insert(ht, &key1, &value1));

  int key2 = 2;
  int value2 = 20;
  ASSERT_TRUE(ht_insert(ht, &key2, &value2));

  int *retrieved_value1 = (int *)malloc(sizeof(int));
  int *retrieved_value2 = (int *)malloc(sizeof(int));
  ASSERT_TRUE(ht_get(ht, &key1, retrieved_value1));
  ASSERT_EQ(*retrieved_value1, value1);
  ASSERT_TRUE(ht_get(ht, &key2, retrieved_value2));
  ASSERT_EQ(*retrieved_value2, value2);

  ASSERT_EQ(ht_size(ht), 2);

  ASSERT_TRUE(ht_remove(ht, &key1));
  ASSERT_EQ(ht_size(ht), 1);

  free(retrieved_value1);
  free(retrieved_value2);
  ht_destroy(ht);
}

// ... (Similar tests for other key types: UINT, DOUBLE, STRING)

TEST(HtLibTest, RemoveNonExistingKey) {
  ht_hashmap_t *ht = ht_new(HT_KEY_TYPE_INT, HT_VALUE_TYPE_INT, 16);
  ASSERT_NE(ht, nullptr);

  int key1 = 1;
  int value1 = 10;
  ASSERT_TRUE(ht_insert(ht, &key1, &value1));

  int key2 = 2;
  ASSERT_FALSE(ht_remove(ht, &key2));

  ht_destroy(ht);
}

TEST(HtLibTest, GetNonExistingKey) {
  ht_hashmap_t *ht = ht_new(HT_KEY_TYPE_INT, HT_VALUE_TYPE_INT, 16);
  ASSERT_NE(ht, nullptr);

  int key1 = 1;
  int value1 = 10;
  ASSERT_TRUE(ht_insert(ht, &key1, &value1));

  int key2 = 2;
  int retrieved_value;
  ASSERT_FALSE(ht_get(ht, &key2, &retrieved_value));

  ht_destroy(ht);
}

TEST(HtLibTest, Clear) {
  ht_hashmap_t *ht = ht_new(HT_KEY_TYPE_INT, HT_VALUE_TYPE_INT, 16);
  ASSERT_NE(ht, nullptr);

  int key1 = 1;
  int value1 = 10;
  ASSERT_TRUE(ht_insert(ht, &key1, &value1));

  int key2 = 2;
  int value2 = 20;
  ASSERT_TRUE(ht_insert(ht, &key2, &value2));

  ASSERT_EQ(ht_size(ht), 2);

  ht_clear(ht);
  ASSERT_EQ(ht_size(ht), 0);

  ht_destroy(ht);
}

TEST(HtLibTest, IsEmpty) {
  ht_hashmap_t *ht = ht_new(HT_KEY_TYPE_INT, HT_VALUE_TYPE_INT, 16);
  ASSERT_NE(ht, nullptr);

  ASSERT_TRUE(ht_is_empty(ht));

  int key1 = 1;
  int value1 = 10;
  ASSERT_TRUE(ht_insert(ht, &key1, &value1));

  ASSERT_FALSE(ht_is_empty(ht));

  ht_destroy(ht);
}

// ... (Add more tests for other scenarios and edge cases)
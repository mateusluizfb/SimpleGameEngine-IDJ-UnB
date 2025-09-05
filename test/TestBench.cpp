#include <gtest/gtest.h>

TEST(TestBench, TestBench)
{
  std::unordered_map<std::string, std::string> testMap;

  // add key:
  testMap["key1"] = "value1";

  // get unexisting key:
  std::string value = testMap["key2"]; // This will create a new entry with default value (empty string)
  printf("Value for 'key2': '%s'\n", value.c_str()); // Should print an empty string
}

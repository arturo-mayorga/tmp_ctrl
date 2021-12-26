#include <gtest/gtest.h>
#include "../message-reader.h"

// Demonstrate some basic assertions.
TEST(MessageReaderTest, MessageNullAfterConstruction) {
  MessageReader *reader = new MessageReader();
  EXPECT_TRUE(reader != NULL);
  EXPECT_TRUE(reader->getMessage() == NULL);  
}
#include <gtest/gtest.h>
#include "../message-reader.h"
#include "logger-test-impl.h"

void sendString(MessageReader *reader, const char *str, bool expectMessageAtEnd)
{
  int i = 0;
  for (i = 0; i < strlen(str) - 1; i++)
  {
    EXPECT_FALSE(reader->addByte(str[i]));
  }
  EXPECT_EQ(reader->addByte(str[i]), expectMessageAtEnd);
}

TEST(MessageReader, MessageNullAfterConstruction)
{
  LoggerTestImpl logger;
  MessageReader *reader = new MessageReader(&logger);
  EXPECT_TRUE(reader != NULL);
  EXPECT_TRUE(reader->getMessage() == NULL);
}

TEST(MessageReader, SimpleMessage)
{
  LoggerTestImpl logger;
  MessageReader *reader = new MessageReader(&logger);
  sendString(reader, "{K:12345}", true);

  Message *msg = reader->getMessage();
  EXPECT_TRUE(msg != NULL);
  EXPECT_EQ(msg->numParams, 1);
  EXPECT_EQ(msg->type, MSG_TYPE_SET_KNOB);
  EXPECT_EQ(msg->params[0], 12345);
}

TEST(MessageReader, MessageWithMutipleParams)
{
  LoggerTestImpl logger;
  MessageReader *reader = new MessageReader(&logger);
  sendString(reader, "{S:12345:98765:10101}", true);

  Message *msg = reader->getMessage();
  EXPECT_TRUE(msg != NULL);
  EXPECT_EQ(msg->numParams, 3);
  EXPECT_EQ(msg->type, MSG_TYPE_STATUS);
  EXPECT_EQ(msg->params[0], 12345);
  EXPECT_EQ(msg->params[1], 98765);
  EXPECT_EQ(msg->params[2], 10101);
}

TEST(MessageReader, InvalidMessageReturnsFalse)
{
  LoggerTestImpl logger;
  MessageReader *reader = new MessageReader(&logger);
  sendString(reader, "{K:}", false);
}

TEST(MessageReader, MessagesIgnoreNonsenseBeforeValidMessage)
{
  LoggerTestImpl logger;
  MessageReader *reader = new MessageReader(&logger);
  sendString(reader, "AB{{:}}{K:1}", true);

  Message *msg = reader->getMessage();
  EXPECT_TRUE(msg != NULL);
  EXPECT_EQ(msg->numParams, 1);
  EXPECT_EQ(msg->type, MSG_TYPE_SET_KNOB);
  EXPECT_EQ(msg->params[0], 1);
}

TEST(MessageReader, ParametersMustBeLessThan50CharsLong)
{
  LoggerTestImpl logger;
  MessageReader *reader = new MessageReader(&logger);
  sendString(reader, "{K:0123456789012345678901234567890123456789012345678}", true);
  sendString(reader, "{K:01234567890123456789012345678901234567890123456789}", false);
}

TEST(MessageReader, TotalMessageLengthMustBeUnder100)
{
  LoggerTestImpl logger;
  MessageReader *reader = new MessageReader(&logger);
  sendString(reader, "{K:12345:12345:12345:12345:12345:12345:12345:12345:12345:12345:12345:12345:12345:12345:12345:123450}", true);
  sendString(reader, "{K:12345:12345:12345:12345:12345:12345:12345:12345:12345:12345:12345:12345:12345:12345:12345:1234500}", false);
}
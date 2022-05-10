#include "test-framework/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_the_first(void)
{
   /* TEST_IGNORE_MESSAGE("Implement me"); */
   TEST_ASSERT_EQUAL(1, 2);
}

static void test_the_second(void)
{
   TEST_ASSERT_EQUAL(2, 2);
}

static void test_the_third(void)
{
   TEST_ASSERT_EQUAL_FLOAT(1.1, 1.2);
}

int main(void)
{
   UnityBegin("test/test_hello_world.c");

   RUN_TEST(test_the_first);
   RUN_TEST(test_the_second);
   RUN_TEST(test_the_third);

   return UnityEnd();
}

/*
* TEST_ASSERT(1 == 1);
* TEST_ASSERT_TRUE(3 <= 3);
* TEST_ASSERT_FALSE(2 == 2);

* TEST_ASSERT_EQUAL_INT32( -1, 0xFFFFFFFF );  -> TRUE
* TEST_ASSERT_EQUAL(4, 2 + 2);                -> TRUE
* TEST_ASSERT_EQUAL(1.1, 1);                  -> TRUE
* TEST_ASSERT_EQUAL_INT(2, 2);                -> TRUE
* TEST_ASSERT_EQUAL_FLOAT(1.1, 1.2);          -> FALSE
*/

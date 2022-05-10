#include "test-framework/unity.h"
#include "../src/fib.h"
#include <limits.h>

#define DIMENSION_OF(a) (sizeof(a) / sizeof(a[0]))

void setUp(void)
{
}

void tearDown(void)
{
}

/* TESTS for Fibonacci_GetElement */
static void test_element0_should_return_1(void)
{
	TEST_ASSERT_EQUAL_INT(1, Fibonacci_GetElement(0));
}

static void test_element1_should_return_1(void)
{
	TEST_ASSERT_EQUAL_INT(1, Fibonacci_GetElement(1));
}

static void test_element2_should_return_2(void)
{
	TEST_ASSERT_EQUAL_INT(2, Fibonacci_GetElement(2));
}

static void test_part_of_the_sequence(void)
{
	unsigned char expected[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};

	for (unsigned char i = 0; i < DIMENSION_OF(expected); i++)
	{
		TEST_ASSERT_EQUAL_INT(expected[i], Fibonacci_GetElement(i));
	}
}

static void test_that_negative_elements_return_negative_1(void)
{
	TEST_ASSERT_EQUAL_INT(-1, Fibonacci_GetElement(-1));
	TEST_ASSERT_EQUAL_INT(-1, Fibonacci_GetElement(-3));
	TEST_ASSERT_EQUAL_INT(-1, Fibonacci_GetElement(-555));
	TEST_ASSERT_EQUAL_INT(-1, Fibonacci_GetElement(INT_MIN));
}

static void test_that_overrun_values_return_negative_1(void)
{
	const int first_bad_element = 46;
	const int last_good_element = first_bad_element - 1;
	int last_good_value = Fibonacci_GetElement(last_good_element);

	TEST_ASSERT_EQUAL_INT_MESSAGE(4, sizeof(int),
								  "Constants first_bad_element and FIB_MAX_ELEMENT must be changed");
	TEST_ASSERT_MESSAGE(last_good_value > 1, "This value should not have been a rollover");
	TEST_ASSERT_EQUAL_INT(-1, Fibonacci_GetElement(first_bad_element));
	TEST_ASSERT_EQUAL_INT(-1, Fibonacci_GetElement(INT_MAX));
}

/* TEST for Fibonacci_IsInSequence */
static void test_first_10_numbers_in_sequence_return_1(void)
{
	unsigned char numbers_in_sequence[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};

	for (unsigned char i = 0; i < DIMENSION_OF(numbers_in_sequence); i++)
	{
		TEST_ASSERT_EQUAL_INT(1, Fibonacci_IsInSequence(numbers_in_sequence[i]));
	}
}

static void test_max_int_in_sequence_should_return_1()
{
	TEST_ASSERT_EQUAL_INT(1, Fibonacci_IsInSequence(1836311903));
}

static void test_limit_int_in_sequence_should_return_0()
{
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_IsInSequence(INT_MAX));
}

static void test_first_10_numbers_not_in_sequence_return_0(void)
{
	unsigned char numbers_not_in_sequence[] = {0, 4, 6, 7, 9, 10, 11, 12, 14, 15};

	for (unsigned char i = 0; i < DIMENSION_OF(numbers_not_in_sequence); i++)
	{
		TEST_ASSERT_EQUAL_INT(0, Fibonacci_IsInSequence(numbers_not_in_sequence[i]));
	}
}

static void test_negative_in_sequence_should_return_0()
{
    TEST_ASSERT_EQUAL_INT(Fibonacci_IsInSequence(-1),0);
    TEST_ASSERT_EQUAL_INT(Fibonacci_IsInSequence(-100),0);
    TEST_ASSERT_EQUAL_INT(Fibonacci_IsInSequence(-500),0);
    TEST_ASSERT_EQUAL_INT(Fibonacci_IsInSequence(-15000),0);
}

static void test_negative_limit_in_sequence_should_return_0()
{
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_IsInSequence(INT_MIN));
}

int main(void)
{
	UnityBegin("test/test_fib.c");

	/* TEST for Fibonacci_GetElement */
	RUN_TEST(test_element0_should_return_1);
	RUN_TEST(test_element1_should_return_1);
	RUN_TEST(test_element2_should_return_2);
	RUN_TEST(test_part_of_the_sequence);
	RUN_TEST(test_that_negative_elements_return_negative_1);
	RUN_TEST(test_that_overrun_values_return_negative_1);

	/* TEST for Fibonacci_IsInSequence */
	RUN_TEST(test_first_10_numbers_in_sequence_return_1);
	RUN_TEST(test_max_int_in_sequence_should_return_1);
	RUN_TEST(test_limit_int_in_sequence_should_return_0);
	RUN_TEST(test_first_10_numbers_not_in_sequence_return_0);
	RUN_TEST(test_negative_in_sequence_should_return_0);
	RUN_TEST(test_negative_limit_in_sequence_should_return_0);

	return UnityEnd();
}

/*
What we learned?
* Test the expected normal behavior
* Test the outliers
* Test the handling of error conditions
* Unity tests are just C code, so we can make loops and other such things to
help us.
*/

/*
Challlenge
Write tests for the other function in fib.c, Fibonacci_IsInSequence.
* It should return 1 when the number you give it is in the sequence.
* It should return 0 when it is not.
* Edit the function as needed.
* The tests should go in test_fib.c too!
*/

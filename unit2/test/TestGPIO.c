#include "unity.h"
#include "../src/GPIO.h"
#include "../inc/MK20DX256.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void Test_SetPinAsOuput_Should_ConfigurePinDirection(void)
{
	PORTC.PDDR = 0;

	TEST_ASSERT_EQUAL(0, GPIO_SetPinAsOutput(0));
	TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0), PORTC.PDDR);

	TEST_ASSERT_EQUAL(0, GPIO_SetPinAsOutput(22));
	TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0) | BIT_TO_MASK(22), PORTC.PDDR);

	TEST_ASSERT_EQUAL(0, GPIO_SetPinAsOutput(31));
	TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0) | BIT_TO_MASK(22) | BIT_TO_MASK(31),
							PORTC.PDDR);
}

static void Test_SetPinAsOutput_Should_NotUpdatePinDirection_When_PinIsNotValid(void)
{
	PORTC.PDDR = 0;

	TEST_ASSERT_NOT_EQUAL(0, GPIO_SetPinAsOutput(32));
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PDDR);
}

static void Test_SetPinAsInput_Should_ConfigurePinDirection(void)
{
	PORTC.PDDR = 0xFFFFFFFF; /* All pins configured as outputs */

	TEST_ASSERT_EQUAL(0, GPIO_SetPinAsInput(0));
	TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0)), PORTC.PDDR);

	TEST_ASSERT_EQUAL(0, GPIO_SetPinAsInput(16));
	TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0) | BIT_TO_MASK(16)), PORTC.PDDR);

	TEST_ASSERT_EQUAL(0, GPIO_SetPinAsInput(31));
	TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0) | BIT_TO_MASK(16) | BIT_TO_MASK(31)),
							PORTC.PDDR);
}

static void Test_SetPinAsInput_Should_NotUpdatePinDirection_When_PinIsNotValid(void)
{
	PORTC.PDDR = 0xFFFFFFFF; /* All pins configured as outputs */

	TEST_ASSERT_NOT_EQUAL(0, GPIO_SetPinAsInput(32));
	TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, PORTC.PDDR);
}

int main(void)
{
	UnityBegin("TestGPIO.c");

	RUN_TEST(Test_SetPinAsOuput_Should_ConfigurePinDirection);
	RUN_TEST(Test_SetPinAsOutput_Should_NotUpdatePinDirection_When_PinIsNotValid);
	RUN_TEST(Test_SetPinAsInput_Should_ConfigurePinDirection);
	RUN_TEST(Test_SetPinAsInput_Should_NotUpdatePinDirection_When_PinIsNotValid);

	return UnityEnd();
}

/**
 * Notes:
 * 
 * Simple Test Pattern
 * - Set up starting conditions
 * - Run function under test
 * - Verify effect
 * 
 * What we learned?
 * - How to write source and test together.
 * - How do we interface with registers in tests?
 * - A nice naming convention for naming tests.
 * 
 * A few thoughts on the subject:
 * - When working with registers during a unit test, do we want to remap them to
 * RAM? Yes, we want to be able to simulate and verify any register conditions.
 * 
 * - It's best if we write a source module, and then write the tests for it?
 * False
 * 
 * - A common simple test flow for unit under test (UUT) is:
 * setup, run UUT, verify results
 * 
 */

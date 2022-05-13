#include "unity.h"
#include "../src/GPIO.h"
#include "../inc/MK20DX256.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/* Tests for GPIO_SetPinAsOutput */
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

/* Tests for GPIO_SetPinAsInput */
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

/* Tests for GPIO_SetPin */
static void Test_SetPin_Should_SetOutputHigh(void)
{
	PORTC.PSOR = 0;
	PORTC.PCOR = 0;

	TEST_ASSERT_EQUAL(0, GPIO_SetPin(0));
	TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0), PORTC.PSOR);
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR);

	TEST_ASSERT_EQUAL(0, GPIO_SetPin(31));
	TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(31), PORTC.PSOR);
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR);
}

static void Test_SetPin_Should_ForceToOutput_When_ConfigureAsInput(void)
{
	PORTC.PSOR = 0;
	PORTC.PCOR = 0;
	PORTC.PDDR = 0x50000000;

	TEST_ASSERT_EQUAL(0, GPIO_SetPin(0)); /* Checking return value */
	TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0), PORTC.PSOR); /* Checking PSOR change*/
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR); /* Unchanged */
	TEST_ASSERT_EQUAL_HEX32(0x50000001, PORTC.PDDR); /* Pin 0 force to output*/
}

static void Test_SetPin_Should_NotSetOutputs_When_PinIsNotValid(void)
{
	PORTC.PSOR = 0;
	PORTC.PCOR = 0;
	PORTC.PDDR = 0;

	TEST_ASSERT_NOT_EQUAL(0, GPIO_SetPinAsOutput(32));
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PSOR);
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR);
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PDDR);
}

/* Tests for GPIO_ClearPin */
static void Test_ClearPin_Should_SetOutputLow(void)
{
	PORTC.PSOR = 0; /* Port Set Output Register */
	PORTC.PCOR = 0; /* Port Clear Output Register */

	TEST_ASSERT_EQUAL(0, GPIO_ClearPin(0)); /* Checking return value is 0 */
	TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0), PORTC.PCOR);
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PSOR); /* Unchanged */

	TEST_ASSERT_EQUAL(0, GPIO_ClearPin(31)); /* Checking return value is 0 */
	TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(31), PORTC.PCOR);
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PSOR); /* Unchanged */
}

static void Test_ClearPin_Should_ForceToOutput_When_ConfigureAsInput(void)
{
	PORTC.PSOR = 0;
	PORTC.PCOR = 0;
	PORTC.PDDR = 0x50000000;

	TEST_ASSERT_EQUAL(0, GPIO_ClearPin(0)); /* Checking return value */
	TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0), PORTC.PCOR); /* Checking PCOR change*/
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PSOR); /* Unchanged */
	TEST_ASSERT_EQUAL_HEX32(0x50000001, PORTC.PDDR); /* Pin 0 force to output*/
}

static void Test_ClearPin_Should_NotClearOutputs_When_PinIsNotValid(void)
{
	PORTC.PSOR = 0;
	PORTC.PCOR = 0;
	PORTC.PDDR = 0;

	TEST_ASSERT_NOT_EQUAL(0, GPIO_SetPinAsOutput(32)); /* Checking return value */
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PSOR);
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR); /* Checking PCOR change*/
	TEST_ASSERT_EQUAL_HEX32(0, PORTC.PDDR);
}

int main(void)
{
	UnityBegin("TestGPIO.c");

	RUN_TEST(Test_SetPinAsOuput_Should_ConfigurePinDirection);
	RUN_TEST(Test_SetPinAsOutput_Should_NotUpdatePinDirection_When_PinIsNotValid);

	RUN_TEST(Test_SetPinAsInput_Should_ConfigurePinDirection);
	RUN_TEST(Test_SetPinAsInput_Should_NotUpdatePinDirection_When_PinIsNotValid);

	RUN_TEST(Test_SetPin_Should_SetOutputHigh);
	RUN_TEST(Test_SetPin_Should_ForceToOutput_When_ConfigureAsInput);
	RUN_TEST(Test_SetPin_Should_NotSetOutputs_When_PinIsNotValid);

	RUN_TEST(Test_ClearPin_Should_SetOutputLow);
	RUN_TEST(Test_ClearPin_Should_ForceToOutput_When_ConfigureAsInput);
	RUN_TEST(Test_ClearPin_Should_NotClearOutputs_When_PinIsNotValid);

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
 * 17. A Second Helping
 *
 * [X] Each pin can be set as input/output
 * [X] Each pin can be set high or low
 * [X] Each pin can be read
 * [X] Each pin can be read in one word
 * [ ] Has init function to config defaults by pin
 * [ ] Each pin can have its active polarity reversed
 *
 * What we learned?
 * - Practice our TDD and BDD skills.
 * - Return illegal or failing values from unimplemented tests.
 * - Test passing & failing conditions.
 *
 * Challenge:
 * - Implement GPIO_ClearPin
 * - Implement GPIO_ReadPin
 * - Implement GPIO_ReadPort
 *
 * 18. Your Turn

Now it’s your turn! Use the techniques we’ve worked on to finish the set output
feature and develop the next features:

	- each pin can be set low
	- each pin can be read individually.
	- read an entire port at once.

Hint: For the read pin function, you are going to be left with a classic puzzle.
How do you handle errors and return values at the same time? We’re going to look
at different options for this later… for now, let’s assume it’s okay to return 0
and 1 for low and high, and -1 when there is a problem.
 *
 */

#include "unity.h"
#include "sum.h"

// Funções setUp e tearDown são chamadas antes e depois de cada teste (podem ficar vazias)
void setUp(void) {}
void tearDown(void) {}


void test_AddPositiveNumbers(void) {
    TEST_ASSERT_EQUAL_INT(5, add(2, 3));
}

void test_AddNegativeNumbers(void) {
    TEST_ASSERT_EQUAL_INT(-5, add(-2, -3));
}

void test_AddMixedNumbers(void) {
    TEST_ASSERT_EQUAL_INT(0, add(5, -5));
}

void test_AddZero(void) {
    TEST_ASSERT_EQUAL_INT(10, add(10, 0));
}

void test_AddLargeNumbers(void) {
    TEST_ASSERT_EQUAL_INT(1000000, add(500000, 500000));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_AddPositiveNumbers);
    RUN_TEST(test_AddNegativeNumbers);
    RUN_TEST(test_AddMixedNumbers);
    RUN_TEST(test_AddZero);
    RUN_TEST(test_AddLargeNumbers);
    return UNITY_END();
}

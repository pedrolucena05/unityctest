#include <stdio.h>
#include <assert.h>
#include "sum.h"
#include "unity.h"


void setUp (void) {

}

void tearDown () {

}

void test_add(void) {

    TEST_ASSERT_EQUAL_INT(10, add(4,6));
}

void test_add_2 (void) {
    int res = add(8,4);
    if (res != 11) {
        
        TEST_FAIL();
        
    }
}

int main () {
    UNITY_BEGIN();
    RUN_TEST(test_add);
    RUN_TEST(test_add_2);
    return UNITY_END();
}
#include <UnitTest++/UnitTest++.h>
#include "../Calculator.h"

SUITE(CalculatorTest) {
    TEST(AddTest) {
        Calculator calc;
        CHECK_EQUAL(5, calc.add(2, 3));
    }

    TEST(SubtractTest) {
        Calculator calc;
        CHECK_EQUAL(1, calc.subtract(3, 2));
    }

    TEST(DivideByZero) {
        Calculator calc;
        CHECK_THROW(calc.divide(5, 0), std::invalid_argument);
    }
}
#include <gtest/gtest.h>

extern "C" {
    #include "calculator.h"
}

// Тесты
TEST(CalculatorTest, ModeTest)
{
    set_mode(INT_MODE);
    EXPECT_EQ(get_mode(), INT_MODE);

    set_mode(FLOAT_MODE);
    EXPECT_EQ(get_mode(), FLOAT_MODE);
}

TEST(CalculatorTest, ValidCharTest)
{
    EXPECT_TRUE(is_valid_char('3'));
    EXPECT_TRUE(is_valid_char('+'));
    EXPECT_FALSE(is_valid_char('x'));
}

TEST(CalculatorTest, InputValidation)
{
    char buffer[] = " 3 + 4 ";
    validate_and_strip_input(buffer);
    EXPECT_STREQ(buffer, "3+4");
}

TEST(CalculatorTest, GetOperand)
{
    char buffer[] = "42";
    set_mode(INT_MODE);
    EXPECT_EQ(get_operand(buffer).intValue, 42);
}

TEST(CalculatorTest, ExpressionTest)
{
    char buffer[] = "(5+4)*5";
    set_mode(INT_MODE);
    set_global_pos(0);
    EXPECT_EQ(calculate_expression(buffer).intValue, 45);
}
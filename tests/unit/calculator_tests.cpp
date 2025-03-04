#include <gtest/gtest.h>

extern "C" {
#include "../src/main.c"
}

// Тест установки и получения режима
TEST(CalculatorTest, ModeTest)
{
    set_mode(INT_MODE);
    EXPECT_EQ(get_mode(), INT_MODE);

    set_mode(FLOAT_MODE);
    EXPECT_EQ(get_mode(), FLOAT_MODE);
}

// Тест установки и получения глобальной позиции
TEST(CalculatorTest, GlobalPosTest)
{
    set_global_pos(15);
    EXPECT_EQ(get_global_pos(), 15);
}

// Тест валидации символов
TEST(CalculatorTest, ValidCharTest)
{
    EXPECT_TRUE(is_valid_char('3'));
    EXPECT_TRUE(is_valid_char('+'));
    EXPECT_FALSE(is_valid_char('x'));
}

// Тест обработки корректного ввода
TEST(CalculatorTest, InputValidation)
{
    char buffer[] = " 3 + 4 ";
    validate_and_strip_input(buffer);
    EXPECT_STREQ(buffer, "3+4");
}

// Тест получения числа
TEST(CalculatorTest, GetOperand)
{
    char buffer[] = "42";
    set_global_pos(0);
    set_mode(INT_MODE);
    EXPECT_EQ(get_operand(buffer).intValue, 42);
}

// Тест вычисления выражения
TEST(CalculatorTest, ExpressionTest)
{
    char buffer[] = "(5+5)*2";
    set_global_pos(0);
    set_mode(INT_MODE);
    EXPECT_EQ(calculate_expression(buffer).intValue, 20);
}

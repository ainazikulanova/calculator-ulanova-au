#include "calculator.h"

// Глобальные переменные
static int global_pos = 0;
static Mode currentMode = INT_MODE;

// Реализация функций
Mode set_mode(Mode new_mode) {
    currentMode = new_mode;
    return currentMode;
}

Mode get_mode() { 
    return currentMode; 
}

int set_global_pos(int new_pos) {
    global_pos = new_pos;
    return global_pos;
}

int get_global_pos() { 
    return global_pos; 
}

int is_valid_char(char c) {
    return isdigit(c) || strchr("()*+-/", c) || isspace(c);
}

void validate_and_strip_input(char* buffer) {
    char* old = buffer;
    char* new_buffer = buffer;
    int parenthesis = 0;
    int operation = 0;
    int prev_char_was_digit = 0;
    int space_count = 0;

    for (; *old != 0; ++old) {
        if (!is_valid_char(*old)) exit(3);

        if (isspace(*old)) {
            space_count++;
            continue;
        }

        if (isdigit(*old)) {
            if (prev_char_was_digit && space_count > 0) exit(3);
            prev_char_was_digit = 1;
        } else {
            prev_char_was_digit = 0;
        }
        space_count = 0;

        if (*old == '(') ++parenthesis;
        if (*old == ')') --parenthesis;

        if (strchr("+-*/", *old)) {
            if (operation == 1) exit(3);
            operation = 1;
        } else {
            operation = 0;
        }

        *new_buffer = *old;
        ++new_buffer;
    }
    *new_buffer = 0;

    if (parenthesis != 0) exit(4);
}

NumberType get_operand(char* buffer) {
    NumberType num;
    if (buffer[global_pos] == ')') exit(4);  // Закрывающая скобка без открывающей
    if (buffer[global_pos] == '(') {
        global_pos++;  // Пропускаем открывающую скобку
        num = calculate_expression(buffer);  // Вычисляем выражение внутри скобок
        if (buffer[global_pos] != ')') exit(4);  // Проверяем закрывающую скобку
        global_pos++;  // Пропускаем закрывающую скобку
        return num;
    }
    if (currentMode == INT_MODE) {
        num.intValue = 0;
        while (isdigit(buffer[global_pos])) {
            num.intValue = num.intValue * 10 + (buffer[global_pos++] - '0');
        }
    } else {
        num.floatValue = 0.0;
        while (isdigit(buffer[global_pos])) {
            num.floatValue = num.floatValue * 10 + (buffer[global_pos++] - '0');
        }
    }
    return num;
}

NumberType get_product(char* buffer) {
    NumberType res = get_operand(buffer);
    while (buffer[global_pos] == '*' || buffer[global_pos] == '/') {
        char operation = buffer[global_pos];
        ++global_pos;
        NumberType x = get_operand(buffer);

        if (operation == '*') {
            if (currentMode == INT_MODE) {
                res.intValue *= x.intValue;
            } else {
                res.floatValue *= x.floatValue;
            }
        } else {
            if (currentMode == INT_MODE) {
                if (x.intValue == 0) exit(1);
                res.intValue = res.intValue / x.intValue;
                if ((res.intValue * x.intValue != res.intValue) && ((res.intValue < 0) != (x.intValue < 0))) {
                    res.intValue -= 1;
                }
            } else {
                if (fabs(x.floatValue) < FLOAT_PRECISION) exit(2);
                res.floatValue /= x.floatValue;
            }
        }
    }
    return res;
}

NumberType calculate_expression(char* buffer) {
    NumberType res = get_product(buffer);  // Получаем первый операнд
    while (buffer[global_pos] == '+' || buffer[global_pos] == '-') {
        char operation = buffer[global_pos];
        global_pos++;  // Пропускаем оператор
        NumberType x = get_product(buffer);  // Получаем следующий операнд

        if (operation == '+') {
            if (currentMode == INT_MODE) {
                res.intValue += x.intValue;
            } else {
                res.floatValue += x.floatValue;
            }
        } else {
            if (currentMode == INT_MODE) {
                res.intValue -= x.intValue;
            } else {
                res.floatValue -= x.floatValue;
            }
        }
    }
    return res;
}
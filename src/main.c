#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_BUFFER_SIZE 1024
#define FLOAT_PRECISION 1e-4

typedef enum { INT_MODE, FLOAT_MODE } Mode;

typedef union {
    long intValue;
    double floatValue;
} NumberType;

NumberType calculate_expression(char* buffer);

static int global_pos = 0;
static Mode currentMode = INT_MODE;

int set_global_pos(int new_pos) {
    global_pos = new_pos;
    return global_pos;
}

int get_global_pos() { return global_pos; }

Mode set_mode(Mode new_mode) {
    currentMode = new_mode;
    return currentMode;
}

Mode get_mode() { return currentMode; }

int is_valid_char(char c) { return isdigit(c)  strchr("()*+-/", c)  isspace(c); }

void validate_and_strip_input(char* buffer) {
    char* old = buffer;
    char* new = buffer;
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

        *new = *old;
        ++new;
    }
    *new = 0;

    if (parenthesis != 0) exit(4);
}

NumberType get_operand(char* buffer) {
    NumberType num;
    if (buffer[global_pos] == ')') exit(4);
    if (buffer[global_pos] == '(') {
        global_pos++;
        num = calculate_expression(buffer);
        global_pos++;
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
                // Округление вниз при делении (в сторону -inf)
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
    NumberType res = get_product(buffer);
    while (buffer[global_pos] == '+' || buffer[global_pos] == '-') {
        char operation = buffer[global_pos];
        ++global_pos;
        NumberType x = get_product(buffer);

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

int main(int argc, char* argv[]) {
    char buffer[MAX_BUFFER_SIZE];
    int len = 0;
    int space_left = sizeof(buffer);

    if (argc > 1 && strcmp(argv[1], "--float") == 0) {
        set_mode(FLOAT_MODE);
    }

    while (fgets(buffer + len, space_left, stdin)) {
        len += strlen(buffer + len);
        space_left -= len;
    }
    validate_and_strip_input(buffer);

    NumberType result = calculate_expression(buffer);

    if (get_mode() == FLOAT_MODE) {
        printf("=%.4f\n", result.floatValue);
    } else {
        printf("=%ld\n", result.intValue);
    }

    return 0;
}

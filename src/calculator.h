#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_BUFFER_SIZE 1024
#define FLOAT_PRECISION 1e-4

// Объявления типов
typedef enum { INT_MODE, FLOAT_MODE } Mode;

typedef union {
    long intValue;
    double floatValue;
} NumberType;

// Прототипы функций
Mode set_mode(Mode new_mode);
Mode get_mode();
int set_global_pos(int new_pos);
int get_global_pos();
int is_valid_char(char c);
void validate_and_strip_input(char* buffer);
NumberType calculate_expression(char* buffer);
NumberType get_operand(char* buffer);
NumberType get_product(char* buffer);
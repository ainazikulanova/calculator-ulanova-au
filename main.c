#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int number = 0;

int calculate();

void esc(char *buffer) {
    char *before = buffer;
    char *after = buffer;
    while (*before) {
        if (!isspace(*before)) {
            *after = *before;
            ++after;
        }
        ++before;
    }
    *after = 0;
}

int get(char *buffer) {
    if (buffer[number] == '(') {
        ++number;
        int res = calculate(buffer);
        ++number;
        return res;
    }
    int num = 0;
    char current_digit;
    while (isdigit(buffer[number])) {
        current_digit = buffer[number];
        ++number;
        num = num * 10 + (current_digit - '0');
    }
    return num;
}

int get_object(char *buffer) {
    int res = get(buffer);
    while (buffer[number] == '*' || buffer[number] == '/') {
        char operation = buffer[number];
        ++number;
        int x = get(buffer);
        switch (operation) {
            case '*': res *= x; break;
            case '/': res /= x; break;
        }
    }
    return res;
}

int calculate(char *buffer) {
    int res = get_object(buffer);
    while (buffer[number] == '+' || buffer[number] == '-') {
        char operation = buffer[number];
        ++number;
        int x = get_object(buffer);
        res = (operation == '+') ? (res + x) : (res - x);
    }
    return res;
}

int main() {
    char buffer[1024];
    int len = 0;
    int space_left = sizeof(buffer);

    while (fgets(buffer + len, space_left, stdin)) {
        len += strlen(buffer + len);
        space_left -= len;
    }
    
    esc(buffer);
    printf("=%d\n", calculate(buffer));
    return 0;
}

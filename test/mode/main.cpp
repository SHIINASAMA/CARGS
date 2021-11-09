//a.out
//a.out hello
//a.out hello world

#include "CArgs.h"
#include <cstdio>

void mode_help(char **argv) {
    puts("no args");
}

void mode_1(char **argv) {
    printf("%s\n", argv[1]);
}

void mode_2(char **argv) {
    printf("%s,%s\n", argv[1], argv[2]);
}

int main(int argc, char **argv) {
    CARGS_SET_MODE_CALLBACK_FUNC(0, mode_help);
    CARGS_SET_MODE_CALLBACK_FUNC(1, mode_1);
    CARGS_SET_MODE_CALLBACK_FUNC(2, mode_2);
    CARGS_INIT(argc, argv);
    return 0;
}

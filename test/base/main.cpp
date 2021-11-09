//a.out -d hello -f 1 -s 2

#include "CArgs.h"
#include <cstdio>

void check(const char *key) {
    const char *temp = nullptr;
    if (CARGS_GET_VALUE_BY_KEY(key, &temp)) {
        printf("参数 \"%s\": %s\n", key, temp);
    } else {
        printf("参数 \"%s\" 不存在\n", key);
    }
}

int main(int argc, char **argv) {
    CARGS_INIT(argc, argv);
    CARGS_REQUEST("d");
    CARGS_REQUEST("f");
    CARGS_REQUEST("s");
    CARGS_NOT_ESSENTIAL("o", "default value");

    check("d");
    check("f");
    check("s");
    check("o");
    return 0;
}
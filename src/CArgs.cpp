#include "CArgs.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>

#define CARGS_MARK '-'

struct str_cmp {
    bool operator()(char const *a, char const *b) {
        return std::strcmp(a, b) < 0;
    }
};

bool has_mark(int argc, char **argv) {
    if (argc == 1) {
        return false;
    }
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == CARGS_MARK) {
            return true;
        }
    }
    return false;
}

static std::map<const char *, const char *, str_cmp> kv_map;
static std::map<int, CARGS_MODE_CALLBACK_FUNC> cb_func_map;

void CARGS_INIT(int argc, char **argv) {
    if (has_mark(argc, argv)) {
        if (argc % 2 == 1) {
            for (int i = 1; i < argc; i++) {
                if (argv[i][0] == CARGS_MARK && strlen(argv[i]) > 1) {
                    kv_map[argv[i + 0] + 1] = argv[i + 1];
                    i++;
                } else {
                    printf("参数错误，在 \"%s\" 附近\n", argv[i]);
                    exit(-1);
                }
            }
        } else {
            puts("参数个数错误\n");
            exit(-1);
        }
    } else {
        auto itor = cb_func_map.find(argc - 1);
        if (itor == cb_func_map.end()) {
            puts("没有找到匹配的模式\n");
            exit(-1);
        } else {
            itor->second(argv);
        }
    }
}

void CARGS_REQUEST(const char *key) {
    if (kv_map.find(key) == kv_map.end()) {
        printf("缺少必要参数 \"%s\"\n", key);
        exit(-1);
    }
}

void CARGS_NOT_ESSENTIAL(const char *key, const char *default_value) {
    if (kv_map.find(key) == kv_map.end()) {
        kv_map[key] = default_value;
    }
}

bool CARGS_GET_VALUE_BY_KEY(const char *key, const char **value) {
    auto itor = kv_map.find(key);
    if (itor == kv_map.end()) {
        return false;
    } else {
        *value = itor->second;
        return true;
    }
}

void CARGS_SET_MODE_CALLBACK_FUNC(int argc, CARGS_MODE_CALLBACK_FUNC func) {
    cb_func_map[argc] = func;
}
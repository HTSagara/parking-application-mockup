#include "Utils.h"

namespace sdds {
    void strcpy(char* des, const char* src, int len) {
        int i;
        for (i = 0; src[i] && (len < 0 || i < len); i++) {
            des[i] = src[i];
        }
        des[i] = 0;
    }
    int strlen(const char* str) {
        int len = 0;
        while (str[len]) {
            len++;
        }
        return len;
    }
    char* alcpy(const char* cstr) {
        char* newStr{};
        if (cstr) {
            newStr = new char[strlen(cstr) + 1];
            strcpy(newStr, cstr);
        }
        return newStr;
    }
}
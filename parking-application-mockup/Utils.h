#ifndef SDDS_UTILS_H__
#define SDDS_UTILS_H__
#include <iostream>
namespace sdds {
	void strcpy(char* des, const char* src, int len = -1);
	int strlen(const char* str);
	char* alcpy(const char* cstr);
}
#endif
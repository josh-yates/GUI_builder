#ifndef INTERFACEFUNCTIONS_H
#define INTERFACEFUNCTIONS_H

//General interface related functions

//TODO try to make wstring to string converter

#define TEST_BUTTON 0

#include <Windows.h>
#include <algorithm>
#include <string>

namespace Interface {
	std::wstring StringToWstring(const std::string StringIn);
}

#endif
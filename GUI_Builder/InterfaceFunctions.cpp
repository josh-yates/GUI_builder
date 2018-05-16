#include "InterfaceFunctions.h"

std::wstring Interface::StringToWstring(const std::string StringIn) {
	std::wstring Converted(StringIn.length(), L' ');
	std::copy(StringIn.begin(), StringIn.end(), Converted.begin());
	return Converted;
}
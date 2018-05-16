//GUI_BUILDER
//personal project: interface builder for simple gui applications

//EXTERNAL INCLUDES
#include <Windows.h>
#include <stdexcept>

//INTERNAL INCLUDES
#include "GlobalVariables.h"
#include "MainWindowFunctions.h"
#include "GenericWindow.h"

//MAIN PROGRAM
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	try {
		//REGISTER WINDOW CLASSES
		mwns::RegisterMainWindow(hInst);
		
		//DISPLAY MAIN WINDOW
		mwns::DisplayMainWindow();

		//MESSAGE LOOP
		MSG Message{ 0 };
		while (GetMessage(&Message, NULL, NULL, NULL)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	//CATCH ERRORS SENT BY PROGRAM
	catch (std::invalid_argument& inval_arg) {
		//copy string to wstring
		std::string temp_string(inval_arg.what());
		std::wstring errmsg(temp_string.length(), L' ');
		std::copy(temp_string.begin(), temp_string.end(), errmsg.begin());
		MessageBox(mwns::hMainWindow, errmsg.c_str(), L"Programming error", MB_ICONERROR);
	}
	//CATCH OTHER ERRORS
	catch (...) {
		MessageBox(mwns::hMainWindow, L"Unknown error", L"Programming error", MB_ICONERROR);
	}
	return 0;
}


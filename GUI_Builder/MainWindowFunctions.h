#ifndef MAINWINDOWFUNCTIONS_H
#define MAINWINDOWFUNCTIONS_H

#include <Windows.h>
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>

#include "GenericWindow.h"

//Main window holds editing tools and has multiple screens. mwns (main window namespace) stores everything main window related

namespace mwns {

	//-----DATA-----
	//MAIN WINDOW DATA
	extern std::wstring MainWindowClassName;
	extern HWND hMainWindow;
	extern int HeightMainWindow;
	extern int WidthMainWindow;
	extern int XPosMainWindow;
	extern int YPosMainWindow;
	extern std::vector<HWND*> ChildrenShowingPtrs;

	extern Interface::Button testButton;
	extern Interface::TextBox testText;
	extern Interface::InputBox testInput;

	//-----PROCEDURE-----
	LRESULT WINAPI MainWindowProcedure(HWND hWindow, UINT Message, WPARAM wP, LPARAM lP);

	//-----FUNCTIONS-----
	//MAIN WINDOW FUNCTIONS
	void RegisterMainWindow(HINSTANCE hInstance);
	void DisplayMainWindow();
	void ClearWindowContents();

	//SCREEN SHOWING FUNCTIONS
	void ShowStartScreen();
}
#endif
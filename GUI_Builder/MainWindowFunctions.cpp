#include "MainWindowFunctions.h"

//-----DATA-----
//MAIN WINDOW DATA
std::wstring mwns::MainWindowClassName{ L"MainWindowClass" };
HWND mwns::hMainWindow;
int mwns::HeightMainWindow{ 400 };
int mwns::WidthMainWindow{ 400 };
int mwns::XPosMainWindow{ 100 };
int mwns::YPosMainWindow{ 100 };
std::vector<HWND*> mwns::ChildrenShowingPtrs;

//START SCREEN DATA
HWND mwns::hNewButton;

//-----PROCEDURE-----
LRESULT WINAPI mwns::MainWindowProcedure(HWND hWindow, UINT Message, WPARAM wP, LPARAM lP) {
	switch (Message) {
	case WM_CREATE: {
		//TEST BUTTON CLASS
		Interface::Button MyButton(50, 100, 20, 100, hWindow, "Beans please");
		MyButton.CreateAndShow();
		Interface::Button MyButton2(50, 100, 170, 100, hWindow, "More beans!!");
		MyButton2.CreateAndShow();
		Interface::TextBox MyTextBox(40, 100, 20, 20, hWindow, "Would you like beans?");
		MyTextBox.CreateAndShow();
		Interface::TextBox StorageBox(100, 100, 150, 20, hWindow, "");
		StorageBox.CreateAndShow();
		Interface::Button TestButton(20, 20, 10, 10, *StorageBox.GetHandle(), "a");
		TestButton.CreateAndShow();
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWindow, Message, wP, lP);
		break;
	}
	return 0;
}

//-----FUNCTIONS-----
//MAIN WINDOW FUNCTIONS
void mwns::RegisterMainWindow(HINSTANCE hInstance) {
	//CREATE WINDOW CLASS
	WNDCLASSW MainWindowClass{ 0 };
	MainWindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;				//paint background colour
	MainWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);				//set cursor type
	MainWindowClass.hInstance = hInstance;								//current instance of this window, provided by OS
	MainWindowClass.lpszClassName = mwns::MainWindowClassName.c_str();	//window class identifier
	MainWindowClass.lpfnWndProc = mwns::MainWindowProcedure;			//provide a message handler

	//REGISTER WINDOW CLASS WITH OS
	if (!RegisterClassW(&MainWindowClass)) {
		//throw error if unable to register class
		throw std::invalid_argument("Failed to register MainWindowClass");
	}
}

void mwns::DisplayMainWindow() {
	mwns::hMainWindow = CreateWindowW(mwns::MainWindowClassName.c_str(), L"GUI Builder", WS_SYSMENU | WS_VISIBLE,
		mwns::XPosMainWindow, mwns::YPosMainWindow, 
		mwns::WidthMainWindow, mwns::HeightMainWindow, 
		NULL, NULL, NULL, NULL);
}

void mwns::ClearWindowContents() {
	for (auto child{ mwns::ChildrenShowingPtrs.begin() }; child != mwns::ChildrenShowingPtrs.end(); child++) {
		DestroyWindow(**child);		//destroy all child windows currently on display
	}
	ChildrenShowingPtrs.clear();
}

//SCREEN SHOWING FUNCTIONS
void mwns::ShowStartScreen() {
	mwns::ClearWindowContents();
}
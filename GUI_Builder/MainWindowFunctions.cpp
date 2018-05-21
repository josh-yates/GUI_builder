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
Interface::Button mwns::MyButton(50, 100, 20, 100, mwns::hMainWindow, "Beans please");
Interface::TextBox mwns::MyText(50, 100, 10, 10, mwns::hMainWindow, "Text box");

bool mwns::DraggingText{ false };

//-----PROCEDURE-----
LRESULT WINAPI mwns::MainWindowProcedure(HWND hWindow, UINT Message, WPARAM wP, LPARAM lP) {
	switch (Message) {
	case WM_CREATE: {
		//TEST BUTTON CLASS
		mwns::MyButton.SetParentWindowPtr(hWindow);
		mwns::MyButton.CreateAndShow();
		mwns::MyText.SetParentWindowPtr(hWindow);
		mwns::MyText.CreateAndShow();
		break;
	}
	case WM_SETCURSOR: {
		if ((HWND)wP == *mwns::MyButton.GetHandle()) {
			SetCursor(LoadCursor(NULL, IDC_HAND));
		}
		else if (DraggingText) {
			SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		}
		else {
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		return(TRUE);
		break;
	}
	case WM_LBUTTONDOWN: {
		POINT pos;
		pos.x = LOWORD(lP);
		pos.y = HIWORD(lP);
		if (pos.x >= mwns::MyText.GetXPos() && pos.x <= mwns::MyText.GetXPos() + mwns::MyText.GetWidth() &&
			pos.y >= mwns::MyText.GetYPos() && pos.y <= mwns::MyText.GetYPos() + mwns::MyText.GetHeight()) {
			DraggingText = true;
		}
		break;
	}
	case WM_LBUTTONUP:
		DraggingText = false;
		break;
	case WM_MOUSEMOVE: {
		POINT pos;
		pos.x = LOWORD(lP);
		pos.y = HIWORD(lP);
		if (DraggingText) {
			mwns::MyText.SetXPos(pos.x);
			mwns::MyText.SetYPos(pos.y);
			SetWindowPos(*mwns::MyText.GetHandle(), NULL, pos.x, pos.y, mwns::MyText.GetWidth(), mwns::MyText.GetHeight(), NULL);
		}
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
#include "GenericWindow.h"

Interface::GenericWindow::GenericWindow(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn) :
	Height(HeightIn), Width(WidthIn), XPos(XPosIn), YPos(YPosIn), ParentWindowPtr(&ParentWindowIn), HandlePtr(new HWND), WindowShowing(false) {};

Interface::GenericWindow::~GenericWindow() {}

HWND* Interface::GenericWindow::GetHandle()const {
	return HandlePtr.get();
}

int Interface::GenericWindow::GetHeight()const {
	return Height;
}

int Interface::GenericWindow::GetWidth()const {
	return Width;
}

int Interface::GenericWindow::GetXPos()const {
	return XPos;
}

int Interface::GenericWindow::GetYPos()const {
	return YPos;
}

bool Interface::GenericWindow::IsWindowShowing()const {
	return WindowShowing;
}

void Interface::GenericWindow::SetHeight(const int HeightIn) {
	Height = HeightIn;
}

void Interface::GenericWindow::SetWidth(const int WidthIn) {
	Width = WidthIn;
}

void Interface::GenericWindow::SetXPos(const int XPosIn) {
	XPos = XPosIn;
}

void Interface::GenericWindow::SetYPos(const int YPosIn) {
	YPos = YPosIn;
}

void Interface::GenericWindow::SetParentWindowPtr(HWND& ParentWindowIn) {
	ParentWindowPtr = &ParentWindowIn;
}

void Interface::GenericWindow::Resize(const int HeightIn, const int WidthIn) {
	Hide();
	SetHeight(HeightIn);
	SetWidth(WidthIn);
	Show();
}

void Interface::GenericWindow::Move(const int XPosIn, const int YPosIn) {
	SetXPos(XPosIn);
	SetYPos(YPosIn);
	SetWindowPos(*GetHandle(), NULL, XPosIn, YPosIn, GetWidth(), GetHeight(), NULL);
}

void Interface::GenericWindow::Hide() {
	DestroyWindow(*HandlePtr);
	WindowShowing = false;
}

void Interface::GenericWindow::Redraw() {
	Hide();
	Show();
}

//STATIC WINDOW CLASS
Interface::StaticWindow::StaticWindow(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, const std::wstring WindowTextIn) :
	GenericWindow(HeightIn, WidthIn, XPosIn, YPosIn, ParentWindowIn), WindowText(WindowTextIn) {};

Interface::StaticWindow::~StaticWindow() {};

void Interface::StaticWindow::StaticWindow::Show() {
	*HandlePtr = CreateWindow(ClassName.c_str(), WindowText.c_str(), WS_VISIBLE | WS_CHILD,
		XPos, YPos, Width, Height, *ParentWindowPtr, NULL, NULL, NULL);
	WindowShowing = true;
}

std::wstring Interface::StaticWindow::GetText()const {
	return WindowText;
}

void Interface::StaticWindow::SetText(const std::wstring WindowTextIn) {
	WindowText = WindowTextIn;
}

//BUTTON CLASS
Interface::Button::Button(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::wstring ButtonTextIn, const int ButtonMessageIn) :
	StaticWindow(HeightIn, WidthIn, XPosIn, YPosIn, ParentWindowIn, ButtonTextIn) {
	ButtonMessage = ButtonMessageIn;
	ClassName = L"Button";
}

void Interface::Button::Show() {
	*HandlePtr = CreateWindow(ClassName.c_str(), WindowText.c_str(), WS_VISIBLE | WS_CHILD,
		XPos, YPos, Width, Height, *ParentWindowPtr, (HMENU)ButtonMessage, NULL, NULL);
	WindowShowing = true;
}

//TEXTBOX CLASS
Interface::TextBox::TextBox(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::wstring TextIn) :
	StaticWindow(HeightIn, WidthIn, XPosIn, YPosIn, ParentWindowIn, TextIn) {
	ClassName = L"Static";
}

//INPUT BOX CLASS
Interface::InputBox::InputBox(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::wstring DefaultTextIn) :
	GenericWindow(HeightIn, WidthIn, XPosIn, YPosIn, ParentWindowIn), DefaultText(DefaultTextIn) {
	ClassName = L"Edit";
};

void Interface::InputBox::Show() {
	*HandlePtr = CreateWindow(ClassName.c_str(), DefaultText.c_str(), WS_VISIBLE | WS_CHILD,
		XPos, YPos, Width, Height, *ParentWindowPtr, NULL, NULL, NULL);
	WindowShowing = true;
}

std::wstring Interface::InputBox::GetDefaultText()const {
	return DefaultText;
}

std::wstring Interface::InputBox::Read()const {
	//TODO make this not hardcoded
	wchar_t BoxText[100000];
	GetWindowTextW(*HandlePtr, BoxText, 100000);
	std::wstring ReturnWString(BoxText);
	return ReturnWString;
}
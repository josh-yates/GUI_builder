#include "GenericWindow.h"

Interface::GenericWindow::GenericWindow(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::string WindowTextIn) :
	Height(HeightIn), Width(WidthIn), XPos(XPosIn), YPos(YPosIn), ParentWindowPtr(&ParentWindowIn), HandlePtr(new HWND), WindowText(Interface::StringToWstring(WindowTextIn)) {};

Interface::GenericWindow::~GenericWindow(){}

HWND* Interface::GenericWindow::GetHandle() {
	return HandlePtr.get();
}

int Interface::GenericWindow::GetHeight() {
	return Height;
}

int Interface::GenericWindow::GetWidth() {
	return Width;
}

int Interface::GenericWindow::GetXPos() {
	return XPos;
}

int Interface::GenericWindow::GetYPos() {
	return YPos;
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

void Interface::GenericWindow::CreateAndShow() {
	*HandlePtr = CreateWindow(ClassName.c_str(), WindowText.c_str(), WS_VISIBLE | WS_CHILD, 
		XPos, YPos, Width, Height, *ParentWindowPtr, NULL, NULL, NULL);
}

//BUTTON CLASS
Interface::Button::Button(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::string ButtonTextIn):
	GenericWindow(HeightIn, WidthIn, XPosIn, YPosIn, ParentWindowIn, ButtonTextIn) {
	ClassName = L"Button";
}

//TEXTBOX CLASS
Interface::TextBox::TextBox(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::string TextIn) :
	GenericWindow(HeightIn, WidthIn, XPosIn, YPosIn, ParentWindowIn, TextIn) {
	ClassName = L"Static";
}
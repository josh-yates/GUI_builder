#include "GenericWindow.h"

Interface::GenericWindow::GenericWindow(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn) :
	Height(HeightIn), Width(WidthIn), XPos(XPosIn), YPos(YPosIn), ParentWindowPtr(&ParentWindowIn), HandlePtr(new HWND) {};

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

void Interface::GenericWindow::CreateAndShow() {
	*HandlePtr = CreateWindow(ClassName.c_str(), L"Test", WS_VISIBLE | WS_CHILD, 
		XPos, YPos, Width, Height, *ParentWindowPtr, NULL, NULL, NULL);
}

//BUTTON CLASS
Interface::Button::Button(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn):
	GenericWindow(HeightIn, WidthIn, XPosIn, YPosIn, ParentWindowIn) {
	ClassName = L"Button";
}
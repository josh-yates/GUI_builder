#ifndef GENERICWINDOW_H
#define GENERICWINDOW_H

//Abstract base class for window type

#include <Windows.h>
#include <memory>
#include <string>

#include "InterfaceFunctions.h"

namespace Interface {
	class GenericWindow {
	protected:
		std::wstring ClassName;
		std::wstring WindowText;		//TODO add in constructor input for window text - use string and convert
		std::unique_ptr<HWND> HandlePtr;
		HWND* ParentWindowPtr;	//TODO make this part of derived child window classes if making a parent window derived class
		int Height, Width, XPos, YPos;
	public:
		GenericWindow(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::string WindowTextIn);
		virtual ~GenericWindow() = 0;
		//GETTERS
		HWND* GetHandle();
		int GetHeight();
		int GetWidth();
		int GetXPos();
		int GetYPos();
		//SETTERS
		void SetHeight(const int HeightIn);
		void SetWidth(const int WidthIn);
		void SetXPos(const int XPosIn);
		void SetYPos(const int YPosIn);
		//DISPLAY CHILD WINDOW IN PARENT WINDOW
		void CreateAndShow();
	};

	//TODO move derived window classes to separate header
	class Button : public Interface::GenericWindow {
	public:
		Button(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::string ButtonTextIn);
	};
}
#endif
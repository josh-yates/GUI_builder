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
		std::unique_ptr<HWND> HandlePtr;
		HWND* ParentWindowPtr;	//TODO make this part of derived child window classes if making a parent window derived class
		int Height, Width, XPos, YPos;
		bool WindowShowing;
	public:
		GenericWindow(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn);
		virtual ~GenericWindow() = 0;
		//GETTERS
		HWND* GetHandle()const;
		int GetHeight()const;
		int GetWidth()const;
		int GetXPos()const;
		int GetYPos()const;
		bool IsWindowShowing()const;

		//SETTERS
		void SetHeight(const int HeightIn);
		void SetWidth(const int WidthIn);
		void SetXPos(const int XPosIn);
		void SetYPos(const int YPosIn);
		void SetParentWindowPtr(HWND& ParentWindowIn);

		//CHANGING HOW WINDOW IS DISPLAYED
		virtual void Show() = 0;
		void Resize(const int HeightIn, const int WidthIn);
		void Move(const int XPosIn, const int YPosIn);
		void Hide();
	};

	//TODO move derived window classes to separate header
	class StaticWindow :public Interface::GenericWindow {
	protected:
		std::wstring WindowText;
		std::string WindowTextString;
	public:
		StaticWindow(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, const std::string WindowTextIn);
		virtual ~StaticWindow() = 0;

		//SHOW - OVERRIDDEN
		void Show();

		//TEXT RELATED FUNCTIONS
		std::string GetText()const;
		void SetText(const std::string WindowTextIn);
	};

	class Button : public Interface::StaticWindow {
	public:
		Button(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::string ButtonTextIn);
	};

	class TextBox : public Interface::StaticWindow {
	public:
		TextBox(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::string TextIn);
	};

	class InputBox : public Interface::GenericWindow {
	private:
		std::wstring DefaultText;
	public:
		InputBox(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::string DefaultTextIn);
		void Show();
	};
}
#endif
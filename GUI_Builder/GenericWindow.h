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
		void Redraw();
	};

	//TODO move derived window classes to separate header
	class StaticWindow :public Interface::GenericWindow {
	protected:
		std::wstring WindowText;
	public:
		StaticWindow(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, const std::wstring WindowTextIn);
		virtual ~StaticWindow() = 0;

		//SHOW - OVERRIDDEN
		void Show();

		//TEXT RELATED FUNCTIONS
		std::wstring GetText()const;
		void SetText(const std::wstring WindowTextIn);
	};

	class Button : public Interface::StaticWindow {
	private:
		int ButtonMessage;
	public:
		Button(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::wstring ButtonTextIn, const int ButtonMessageIn);
		void Show();
	};

	class TextBox : public Interface::StaticWindow {
	public:
		TextBox(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::wstring TextIn);
	};

	class InputBox : public Interface::GenericWindow {
	private:
		std::wstring DefaultText;
	public:
		InputBox(const int HeightIn, const int WidthIn, const int XPosIn, const int YPosIn, HWND& ParentWindowIn, std::wstring DefaultTextIn);
		
		//SHOW- OVERIDDEN
		void Show();

		//TEXT RELATED FUNCTIONS
		std::wstring GetDefaultText()const;
		std::wstring Read()const;
	};
}
#endif
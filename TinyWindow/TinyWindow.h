#ifndef TINYWINDOW_H
#define TINYWINDOW_H

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
#define CURRENT_OS_WINDOWS
#include <Windows.h>
#include <gl/GL.h>
#include <io.h>
#include <fcntl.h>
#include "../dependencies/wglext.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//this automatically loads the OpenGL library if you are using Visual studio 
#pragma comment (lib, "opengl32.lib")
//this makes sure that the entry point of your program is main(). not Winmain()
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#if defined(__linux__) || defined(__GNUG__) || defined(__GNUC__) || defined(__clang__)
#define CURRENT_OS_LINUX
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include "../dependencies/glext.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <limits.h>
#include <string.h>

#define KEYSTATE_DOWN 1
#define KEYSTATE_UP 0
#define KEYSTATE_IDLE 2

#define KEY_ERROR -1

#define KEY_FIRST 256 + 1
#define KEY_F1 KEY_FIRST 
#define KEY_F2 KEY_FIRST + 1
#define KEY_F3 KEY_FIRST + 2
#define KEY_F4 KEY_FIRST + 3
#define KEY_F5 KEY_FIRST + 4
#define KEY_F6 KEY_FIRST + 5
#define KEY_F7 KEY_FIRST + 6
#define KEY_F8 KEY_FIRST + 7
#define KEY_F9 KEY_FIRST + 8
#define KEY_F10 KEY_FIRST + 9
#define KEY_F11 KEY_FIRST + 10
#define KEY_F12 KEY_FIRST + 11
#define KEY_CAPSLOCK KEY_FIRST + 12
#define KEY_LEFTSHIFT KEY_FIRST + 13
#define KEY_RIGHTSHIFT KEY_FIRST + 14
#define KEY_LEFTCONTROL KEY_FIRST + 15
#define KEY_RIGHTCONTROL KEY_FIRST + 16
#define KEY_LEFTWINDOW KEY_FIRST + 17
#define KEY_RIGHTWINDOW KEY_FIRST + 18
#define KEY_LEFTALT KEY_FIRST + 19
#define KEY_RIGHTALT KEY_FIRST + 20
#define KEY_ENTER KEY_FIRST + 21
#define KEY_PRINTSCREEN KEY_FIRST + 22
#define KEY_SCROLLLOCK KEY_FIRST + 23
#define KEY_NUMLOCK KEY_FIRST + 24
#define KEY_PAUSE KEY_FIRST + 25
#define KEY_INSERT KEY_FIRST + 26
#define KEY_HOME KEY_FIRST + 27
#define KEY_END KEY_FIRST + 28
#define KEY_PAGEUP KEY_FIRST + 28 
#define KEY_PAGEDOWN KEY_FIRST + 30 
#define KEY_ARROW_DOWN KEY_FIRST + 31
#define KEY_ARROW_UP KEY_FIRST + 32
#define KEY_ARROW_LEFT KEY_FIRST + 33
#define KEY_ARROW_RIGHT KEY_FIRST + 34
#define KEY_KEYPAD_DIVIDE KEY_FIRST + 35
#define KEY_KEYPAD_MULTIPLY KEY_FIRST + 36
#define KEY_KEYPAD_SUBTRACT KEY_FIRST + 37
#define KEY_KEYPAD_ADD KEY_FIRST + 38
#define KEY_KEYPAD_ENTER KEY_FIRST + 39
#define KEY_KEYPAD_PERIOD KEY_FIRST + 40
#define KEY_KEYPAD_0 KEY_FIRST + 41
#define KEY_KEYPAD_1 KEY_FIRST + 42
#define KEY_KEYPAD_2 KEY_FIRST + 43
#define KEY_KEYPAD_3 KEY_FIRST + 44
#define KEY_KEYPAD_4 KEY_FIRST + 45
#define KEY_KEYPAD_5 KEY_FIRST + 46
#define KEY_KEYPAD_6 KEY_FIRST + 47
#define KEY_KEYPAD_7 KEY_FIRST + 48
#define KEY_KEYPAD_8 KEY_FIRST + 49
#define KEY_KEYPAD_9 KEY_FIRST + 50
#define KEY_BACKSPACE KEY_FIRST + 51
#define KEY_TAB KEY_FIRST + 52
#define KEY_DELETE KEY_FIRST + 53
#define KEY_ESCAPE KEY_FIRST + 54
#define KEY_WINDOW_LEFT KEY_FIRST + 55
#define KEY_WINDOW_RIGHT KEY_FIRST + 56
#define KEY_LAST KEY_WINDOW_RIGHT

#define MOUSE_BUTTONUP 0
#define MOUSE_BUTTONDOWN 1
#define MOUSE_BUTTONIDLE 2

#define MOUSE_LEFTBUTTON 0
#define MOUSE_RIGHTBUTTON 1
#define MOUSE_MIDDLEBUTTON 2
#define MOUSE_LAST MOUSE_MIDDLEBUTTON + 1

#define MOUSE_SCROLL_DOWN 0
#define MOUSE_SCROLL_UP 1

#define WINDOWSTYLE_BARE 1
#define WINDOWSTYLE_DEFAULT 2
#define WINDOWSTYLE_POPUP 3

#define WINDOWSTATE_NORMAL 0
#define WINDOWSTATE_MAXIMIZED 1
#define WINDOWSTATE_MINIMIZED 2
#define WINDOWSTATE_FULLSCREEN 3

typedef void(*OnKeyEvent)(GLuint Key, GLboolean KeyState);/**<To be called when a key event has occured*/
typedef void(*OnMouseButtonEvent)(GLuint Button, GLboolean ButtonState);/**<To be called when a Mouse button event has occurred*/
typedef void(*OnMouseWheelEvent)(GLuint WheelDirection);/**<To be called when a mouse wheel event has occured.
NOTE: this is currently the only way of recieveing mouse wheel events.*/
typedef void(*OnDestroyedEvent)();/**<To be called when the window is being destroyed*/
typedef void(*OnMaximizedEvent)();/**<To be called when the window has been maximized*/
typedef void(*OnMinimizedEvent)();/**<To be called when the window has been minimized*/
typedef void(*OnFocusEvent)(GLboolean InFocus);/**<To be called when the window has gained event focus*/
typedef void(*OnMovedEvent)(GLuint X, GLuint Y);/**<To be called when the window has been moved*/
typedef void(*OnResizeEvent)(GLuint Width, GLuint Height);/**<To be called when the window has been resized*/
typedef void(*OnMouseMoveEvent)(GLuint WindowX, GLuint WindowY, GLuint ScreenX, GLuint ScreenY);/**<To be called when the mouse has been moved within the window*/ 

class WindowManager
{
public:

	WindowManager(){}

	/**
	 * shutdown and delete all windows in the manager
	 */
	~WindowManager()
	{
		if (!GetInstance()->Windows.empty())
		{
			for (GLuint l_Iter = 0; l_Iter <= GetInstance()->Windows.size() - 1; l_Iter++)
			{
				delete GetWindowInList(l_Iter);
			}
			GetInstance()->Windows.clear();
		}
	}

	/**
	 * use this to shutdown the window manager when your program is finished
	*/
	 static void ShutDown()
	{
		for (GLuint l_CurrentWindow = 0; l_CurrentWindow < GetInstance()->Windows.size() - 1; l_CurrentWindow++)
		{
			delete GetWindowInList(l_CurrentWindow);
		}

		GetInstance()->Windows.clear();

#if defined(CURRENT_OS_WINDOWS)
#endif
		//apparently Win32 doesnt need a shut down procedure?
#if defined(CURRENT_OS_LINUX)
		XCloseDisplay(GetInstance()->CurrentDisplay);
#endif

		delete Instance;
	}

	/**
	 *use this to add a window to the manager. returns a pointer to the manager which allows for the easy creation of multiple windows
	 */
	static WindowManager* AddWindow(const char*  WindowName, GLuint Width = 1280, GLuint Height = 720, GLuint ColourBits = 32,
		GLuint DepthBits = 8, GLuint StencilBits = 8)
	{
		if (IsValid(WindowName))
		{
			TWindow* NewWindow = new TWindow;
			NewWindow->Name = WindowName;
			NewWindow->Resolution[0] = Width;
			NewWindow->Resolution[1] = Height;
			NewWindow->ColourBits = ColourBits;
			NewWindow->DepthBits = DepthBits;
			NewWindow->StencilBits = StencilBits;

			GetInstance()->Windows.push_back(NewWindow);
			NewWindow->ID = GetNumWindows() - 1;

			InitializeWindow(NewWindow);
			
			return GetInstance();
		}

		/**
		 *if a valid window name was not given the function will return 0;
		 */
		return nullptr;
	}

	/**
	 * return the total amount of windows the manager has
	 */
	static GLuint GetNumWindows()
	{
		return GetInstance()->Windows.size();
	}

	/**
	 * return the mouse position in screen co-ordinates
	 */
	static void GetMousePositionInScreen(GLuint& X, GLuint& Y)
	{
		X = GetInstance()->ScreenMousePosition[0];
		Y = GetInstance()->ScreenMousePosition[1];
	}
	/**
	 * return the mouse position in screen co-ordinates
	 */
	static GLuint* GetMousePositionInScreen()
	{
		return GetInstance()->ScreenMousePosition;
	}
	/**
	 * set the position of the mouse cursor relative to screen co-ordinates
	 */
	static void SetMousePositionInScreen(GLuint X, GLuint Y)
	{
		GetInstance()->ScreenMousePosition[0] = X;
		GetInstance()->ScreenMousePosition[1] = Y;

#if defined(CURRENT_OS_WINDOWS)
		Windows_SetMousePositionInScreen();
#endif

#if defined(CURRENT_OS_LINUX)
		Linux_SetMousePositionInScreen(X, Y);
#endif
	}

	/**
	 * return the Reolution of the current screen
	 */
	static GLuint* GetScreenResolution()
	{
#if defined(CURRENT_OS_WINDOWS)
		RECT l_Screen;
		HWND m_Desktop = GetDesktopWindow();
		GetWindowRect(m_Desktop, &l_Screen);

		GetInstance()->ScreenResolution[0] = l_Screen.right;
		GetInstance()->ScreenResolution[1] = l_Screen.bottom;
		return GetInstance()->ScreenResolution;

#endif

#if defined(CURRENT_OS_LINUX)
		GetInstance()->ScreenResolution[0] = WidthOfScreen(XDefaultScreenOfDisplay(GetInstance()->CurrentDisplay));
		GetInstance()->ScreenResolution[1] = HeightOfScreen(XDefaultScreenOfDisplay(GetInstance()->CurrentDisplay));

		return GetInstance()->ScreenResolution;
#endif
	}
	/**
	 * return the Resolution of the current screen
	 */
	static void GetScreenResolution(GLuint& Width, GLuint& Height)
	{
#if defined(CURRENT_OS_WINDOWS)
		RECT l_Screen;
		HWND m_Desktop = GetDesktopWindow();
		GetWindowRect(m_Desktop, &l_Screen);
		Width = l_Screen.right;
		Height = l_Screen.bottom;
#endif

#if defined(CURRENT_OS_LINUX)
		Width = WidthOfScreen(XDefaultScreenOfDisplay(GetInstance()->CurrentDisplay));
		Height = HeightOfScreen(XDefaultScreenOfDisplay(GetInstance()->CurrentDisplay));

		GetInstance()->ScreenResolution[0] = Width;
		GetInstance()->ScreenResolution[1] = Height;
#endif
	}

	/**
	 * return the Resolution of the given window by setting width and height
	 */
	static void GetWindowResolution(const char* WindowName, GLuint& Width, GLuint& Height)
	{
		if (IsValid(WindowName))
		{
			Width = GetWindowByName(WindowName)->Resolution[0];
			Height = GetWindowByName(WindowName)->Resolution[1];
		}
	}
	/**
	 * return the Resolution of the given window by setting width and height
	 */
	static void GetWindowResolution(GLuint WindowIndex, GLuint& Width, GLuint& Height)
	{
		if (WindowExists(WindowIndex))
		{
			Width = GetWindowByIndex(WindowIndex)->Resolution[0];
			Height = GetWindowByIndex(WindowIndex)->Resolution[1];
		}
	}
	/**
	 * return the Resolution of the given Window as an array of unsigned ints
	 */
	static GLuint* GetWindowResolution(const char* WindowName)
	{
		if (IsValid(WindowName))
		{
			return GetWindowByName(WindowName)->Resolution;
		}
		return nullptr;
	}
	/**
	 * return the Resolution of the Given Window as an array of unsigned ints
	 */
	static GLuint* GetWindowResolution(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
			return GetWindowByIndex(WindowIndex)->Resolution;
		}
		return nullptr;
	}
	/**
	 * set the Size/Resolution of the given window
	 */
	static void SetWindowResolution(const char* WindowName, GLuint Width, GLuint Height)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->Resolution[0] = Width;
			GetWindowByName(WindowName)->Resolution[1] = Height;
#if defined(CURRENT_OS_WINDOWS)
			Windows_SetWindowResolution(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_SetWindowResolution(GetWindowByName(WindowName));
#endif
		}
	}
	/**
	 * set the Size/Resolution of the given window
	 */
	static void SetWindowResolution(GLuint WindowIndex, GLuint Width, GLuint Height)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->Resolution[0] = Width;
			GetWindowByIndex(WindowIndex)->Resolution[1] = Height;

#if defined(CURRENT_OS_WINDOWS)
			Windows_SetWindowResolution(GetWindowByIndex(WindowIndex));
#endif
#if defined(CURRENT_OS_LINUX)
			Linux_SetWindowResolution(GetWindowByIndex(WindowIndex));
#endif
		}
	}

	/**
	 * return the Position of the given window relative to screen co-ordinates by setting X and Y
	 */ 
	static void GetWindowPosition(const char* WindowName, GLuint& X, GLuint& Y)
	{
		if (IsValid(WindowName))
		{
			X = GetWindowByName(WindowName)->Position[0];
			Y = GetWindowByName(WindowName)->Position[1];
		}
	}
	/**
	 * return the Position of the given window relative to screen co-ordinates by setting X and Y
	 */
	static void GetWindowPosition(GLuint WindowIndex, GLuint& X, GLuint& Y)
	{
		if (WindowExists(WindowIndex))
		{
			X = GetWindowByIndex(WindowIndex)->Position[0];
			Y = GetWindowByIndex(WindowIndex)->Position[1];
		}
	}
	/**
	 * return the Position of the given window relative to screen co-ordinates as an array
	 */
	static GLuint* GetWindowPosition(const char* WindowName)
	{
		if (IsValid(WindowName))
		{
			return GetWindowByName(WindowName)->Position;
		}

		return nullptr;
	}
	/**
	 * return the Position of the given window relative to screen co-ordinates as an array
	 */
	static GLuint* GetWindowPosition(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
			return GetWindowByIndex(WindowIndex)->Position;
		}

		return nullptr;
	}
	/**
	 * set the Position of the given window relative to screen co-ordinates
	 */
	static void SetWindowPosition(const char* WindowName, GLuint X, GLuint Y)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->Position[0] = X;
			GetWindowByName(WindowName)->Position[1] = Y;
#if defined(CURRENT_OS_WINDOWS)
			Windows_SetWindowPosition(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_SetWindowPosition(GetWindowByName(WindowName));
#endif
		}
	}
	/**
	 * set the position of the given window relative to screen co-ordinates
	 */
	static void SetWindowPosition(GLuint WindowIndex, GLuint X, GLuint Y)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->Position[0] = X;
			GetWindowByIndex(WindowIndex)->Position[1] = Y;
#if defined(CURRENT_OS_WINDOWS)
			Windows_SetWindowPosition(GetWindowByIndex(WindowIndex));
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_SetWindowPosition(GetWindowByIndex(WindowIndex));
#endif
		}
	}

	/**
	 * return the mouse Position relative to the given window's co-ordinates by setting X and Y
	 */
	static void GetMousePositionInWindow(const char* WindowName, GLuint& X, GLuint& Y)
	{
		if (IsValid(WindowName))
		{
			X = GetWindowByName(WindowName)->MousePosition[0];
			Y = GetWindowByName(WindowName)->MousePosition[1];
		}
	}
	/**
	 * return the mouse position relative to the given window's co-ordinates by setting X and Y
	 */
	static void GetMousePositionInWindow(GLuint WindowIndex, GLuint& X, GLuint& Y)
	{
		if (WindowExists(WindowIndex))
		{
			X = GetWindowByIndex(WindowIndex)->MousePosition[0];
			Y = GetWindowByIndex(WindowIndex)->MousePosition[1];
		}
	}
	/**
	 * return the mouse Position relative to the given window's co-ordinates as an array
	 */
	static GLuint* GetMousePositionInWindow(const char* WindowName)
	{
		if (IsValid(WindowName))
		{
			return GetWindowByName(WindowName)->MousePosition;
		}

		return nullptr;
	}
	/**
	 * return the mouse Position relative to the given window's co-ordinates as an array
	 */
	static GLuint* GetMousePositionInWindow(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
			return GetWindowByIndex(WindowIndex)->MousePosition;
		}

		return nullptr;
	}
	/**
	 * set the mouse Position of the given window's co-ordinates
	 */
	static void SetMousePositionInWindow(const char* WindowName, GLuint X, GLuint Y)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->MousePosition[0] = X;
			GetWindowByName(WindowName)->MousePosition[1] = Y;
#if defined(CURRENT_OS_WINDOWS)
			Windows_SetMousePosition(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_SetMousePositionInWindow(GetWindowByName(WindowName));
#endif
		}
	}
	/**
	 * set the mouse Position of the given window's co-ordinates
	 */
	static void SetMousePositionInWindow(GLuint WindowIndex, GLuint X, GLuint Y)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->MousePosition[0] = X;
			GetWindowByIndex(WindowIndex)->MousePosition[1] = Y;
#if defined(CURRENT_OS_WINDOWS)
			Windows_SetMousePosition(GetWindowByIndex(WindowIndex));
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_SetMousePositionInWindow(GetWindowByIndex(WindowIndex));
#endif
		}
	}

	/**
	 * returns the current state of the given key relative to the given window
	 */
	static GLboolean WindowGetKey(const char* WindowName, GLuint Key)
	{
		if (IsValid(WindowName))
		{
			return GetWindowByName(WindowName)->Keys[Key];
		}

		return GL_FALSE;
	}
	/**
	 * returns the current state of the given key relative to the given window
	 */
	static GLboolean WindowGetKey(GLuint WindowIndex, GLuint Key)
	{
		if (WindowExists(WindowIndex))
		{
			return GetWindowByIndex(WindowIndex)->Keys[Key];
		}

		return GL_TRUE;
	}

	/**
	 * return whether the given window should be closing
	 */
	static GLboolean GetWindowShouldClose(const char* WindowName)
	{
		if (IsValid(WindowName))
		{
			return GetWindowByName(WindowName)->ShouldClose;
		}

		return GL_FALSE;
	}
	/**
	 * return whether the given window should be closing
	 */
	static GLboolean GetWindowShouldClose(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
			return GetWindowByIndex(WindowIndex)->ShouldClose;
		}

		return GL_FALSE;
	}

	/**
	 * swap the draw buffers of the given window
	 */
	static void WindowSwapBuffers(const char* WindowName)
	{
		if (IsValid(WindowName))
		{
#if defined(CURRENT_OS_WINDOWS)
			SwapBuffers(GetWindowByName(WindowName)->DeviceContextHandle);
#endif

#if defined(CURRENT_OS_LINUX)
			glXSwapBuffers(GetDisplay(), GetWindowByName(WindowName)->WindowHandle);
#endif
		}
	}

	/**
	 * swap the draw buffers of the given window
	 */
	static void WindowSwapBuffers(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
#if defined(CURRENT_OS_WINDOWS)
			SwapBuffers(GetWindowByIndex(WindowIndex)->DeviceContextHandle);
#endif 

#if defined(CURRENT_OS_LINUX)
			glXSwapBuffers(GetDisplay(), GetWindowByIndex(WindowIndex)->WindowHandle);
#endif
		}
	}

	/**
	 * make the given window be the current OpenGL Context to be drawn to
	 */
	static void MakeWindowCurrentContext(const char* WindowName)
	{
		if(IsValid(WindowName))
		{

#if defined(CURRENT_OS_WINDOWS)
			wglMakeCurrent(GetWindowByName(WindowName)->DeviceContextHandle, 
					GetWindowByName(WindowName)->GLRenderingContextHandle);		
#endif

#if defined(CURRENT_OS_LINUX)
			glXMakeCurrent(GetDisplay(), GetWindowByName(WindowName)->WindowHandle,
				   	GetWindowByName(WindowName)->Context); 
#endif
		}
	}

	/**
	 * make the given window be the current OpenGL Context to be drawn to
	 */
	static void MakeWindowCurrentContext(GLuint WindowIndex)
	{
		if(WindowExists(WindowIndex))
		{
#if defined(CURRENT_OS_WINDOWS)
			wglMakeCurrent(GetWindowByIndex(WindowIndex)->DeviceContextHandle,
					GetWindowByIndex(WindowIndex)->GLRenderingContextHandle);
#endif

#if defined(CURRENT_OS_LINUX)
			glXMakeCurrent(GetDisplay(), GetWindowByIndex(WindowIndex)->WindowHandle,
					GetWindowByIndex(WindowIndex)->Context);
#endif
		}
	}

	/**
	 * return whether the given window is in fullscreen mode
	 */
	static GLboolean GetWindowIsFullScreen(const char* WindowName)
	{
		if (IsValid(WindowName))
		{
			return (GetWindowByName(WindowName)->CurrentState == WINDOWSTATE_FULLSCREEN);
		}

		return GL_FALSE;
	}

	/**
	 * return whether the given window is in fullscreen mode
	 */
	static GLboolean GetWindowIsFullScreen(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
			return (GetWindowByIndex(WindowIndex)->CurrentState == WINDOWSTATE_FULLSCREEN);
		}

		return GL_FALSE;
	}	

	/**
	 * toggle the given window's fullscreen mode
	 */
	static void SetFullScreen(const char* WindowName, GLboolean NewState)
	{
		if (IsValid(WindowName))
		{
			if(NewState)
			{
				GetWindowByName(WindowName)->CurrentState = WINDOWSTATE_FULLSCREEN;
#if defined(CURRENT_OS_WINDOWS)
				Windows_FullScreen(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Fullscreen(GetWindowByName(WindowName));
#endif
			}

			else
			{
				GetWindowByName(WindowName)->CurrentState = WINDOWSTATE_NORMAL;
#if defined(CURRENT_OS_WINDOWS)
				Windows_FullScreen(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Fullscreen(GetWindowByName(WindowName));
#endif
			}
		}
	}

	/*
	 * toggle the given window's fullscreen mode
	 */
	static void SetFullScreen(GLuint WindowIndex, GLboolean NewState)
	{
		if (WindowExists(WindowIndex))
		{
			if(NewState)
			{
				GetWindowByIndex(WindowIndex)->CurrentState = WINDOWSTATE_FULLSCREEN;
#if defined(CURRENT_OS_WINDOWS)
				Windows_Fullscreen(GetWindowByIndex(WindowIndex));
#endif
#if defined(CURRENT_OS_LINUX)
				Linux_Fullscreen(GetWindowByIndex(WindowIndex));
#endif
			}

			else
			{
				GetWindowByIndex(WindowIndex)->CurrentState = WINDOWSTATE_NORMAL;
#if defined(CURRENT_OS_WINDOWS)
				Windows_FullScreen(GetWindowByIndex(WindowIndex), NewState);
#endif
#if defined(CURRENT_OS_LINUX)
				Linux_Fullscreen(GetWindowByIndex(WindowIndex));
#endif
			}
		}
	}

	/**
	 * returns whether the given window is minimized
	 */
	static GLboolean GetWindowIsMinimized(const char* WindowName)
	{
		if (IsValid(WindowName))
		{
			return (GetWindowByName(WindowName)->CurrentState == WINDOWSTATE_MINIMIZED);
		}
		return GL_FALSE;
	}

	/**
	 * returns whether the given window is minimized
	 */
	static GLboolean GetWindowIsMinimized(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
			return (GetWindowByIndex(WindowIndex)->CurrentState == WINDOWSTATE_MINIMIZED);
		}
		return GL_FALSE;
	}

	/**
	 * toggle the minimization state of the given window
	 */
	static void MinimizeWindow(const char* WindowName, GLboolean NewState)
	{
		if (IsValid(WindowName))
		{
			if(NewState)
			{
				GetWindowByName(WindowName)->CurrentState = WINDOWSTATE_MINIMIZED;

#if defined(CURRENT_OS_WINDOWS)
				Windows_Minimize(GetWindowBName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Minimize(GetWindowByName(WindowName));
#endif
			}

			else
			{
				GetWindowByName(WindowName)->CurrentState = WINDOWSTATE_NORMAL;
#if defined(CURRENT_OS_WINDOWS)
				Windows_Minimize(GetWindowByName(WindowName), NewState);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Minimize(GetWindowByName(WindowName));
#endif
			}
		}
	}

	/**
	 * toggle the minimization state of the window
	 */
	static void MinimizeWindow(GLuint WindowIndex, GLboolean NewState)
	{
		if (WindowExists(WindowIndex))
		{
			if(NewState)
			{
				GetWindowByIndex(WindowIndex)->CurrentState = WINDOWSTATE_MINIMIZED;
#if defined(CURRENT_OS_WINDOWS)
				Windows_Minimize(GetWindowByIndex(WindowIndex));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Minimize(GetWindowByIndex(WindowIndex));
#endif
			}

			else
			{
				GetWindowByIndex(WindowIndex)->CurrentState = WINDOWSTATE_NORMAL;
#if defined(CURRENT_OS_WINDOWS)
				Windows_Minimize(GetWindowByIndex(WindowIndex);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Minimize(GetWindowByIndex(WindowIndex));
#endif
			}
		}	
	}

	/**
	 * return whether the current window is currently maximized
	 */
	static GLboolean GetWindowIsMaximized(const char* WindowName)
	{
		if (IsValid(WindowName))
		{
			return (GetWindowByName(WindowName)->CurrentState == WINDOWSTATE_MAXIMIZED);
		}

		return GL_FALSE;
	}
	/**
	 * return whether the given window is currently maximized
	 */
	static GLboolean GetWindowIsMaximized(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
			return (GetWindowByIndex(WindowIndex)->CurrentState == WINDOWSTATE_MAXIMIZED);
		}

		return GL_FALSE;
	}
	/**
	 * toggle the maximization state of the current window
	 */
	static void MaximizeWindow(const char* WindowName, GLboolean NewState)
	{
		if (IsValid(WindowName))
		{
			if(NewState)
			{
				GetWindowByName(WindowName)->CurrentState = WINDOWSTATE_MAXIMIZED;
#if defined(CURRENT_OS_WINDOWS)
				Windows_Maximize(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Maximize(GetWindowByName(WindowName));
#endif
			}

			else
			{
				GetWindowByName(WindowName)->CurrentState = WINDOWSTATE_NORMAL;
#if defined(CURRENT_OS_WINDOWS)
				Windows_Maximize(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Maximize(GetWindowByName(WindowName));
#endif

			}
		}
	}
	/**
	 * toggle the maximization state of the current window
	 */
	static void MaximizeWindow(GLuint WindowIndex, GLboolean NewState)
	{
		if (WindowExists(WindowIndex))
		{
#if defined(CURRENT_OS_WINDOWS)
			Windows_Maximize(GetWindowByIndex(WindowIndex), NewState);
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_Maximize(GetWindowByIndex(WindowIndex));
#endif
		}
	}

	//gets and sets for window name and index
	static const char* GetWindowName(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
			return GetWindowByIndex(WindowIndex)->Name;
		}
	}

	static GLuint GetWindowIndex(const char*  WindowName)
	{
		if (IsValid(WindowName))
		{
			return GetWindowByName(WindowName)->ID;
		}
	}

	//set the window title bar?
	static void SetWindowTitleBar(const char* WindowName, const char* NewTitle)
	{
		if (IsValid(WindowName) && IsValid(NewTitle))
		{
#if defined(CURRENT_OS_WINDOWS)
			SetWindowText(GetWindowByName(WindowName)->WindowHandle, NewTitle);
#endif

#if defined(CURRENT_OS_LINUX)
			XStoreName(GetDisplay(), GetWindowByName(WindowName)->WindowHandle, NewTitle);
#endif
		}
	}
	static void SetWindowTitleBar(GLuint WindowIndex, const char* NewName)
	{
		if (WindowExists(WindowIndex) && IsValid(NewName))
		{
#if defined(CURRENT_OS_WINDOWS)
			SetWindowText(GetWindowByIndex(WindowIndex)->WindowHandle, NewName);
#endif

#if defined(CURRENT_OS_LINUX)
			XStoreName(GetDisplay(), GetWindowByIndex(WindowIndex)->WindowHandle, NewName);
#endif
		}
	}

	//gets and sets window is in focus
	static GLboolean GetWindowIsInFocus(const char* WindowName)
	{
		if (IsValid(WindowName))
		{
			return GetWindowByName(WindowName)->InFocus;
		}
	}
	static GLboolean GetWindowIsInFocus(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
			return GetWindowByIndex(WindowIndex)->InFocus;
		}
	}
	static void FocusWindow(const char* WindowName, GLboolean NewState)
	{
		if (IsValid(WindowName))
		{
#if defined(CURRENT_OS_WINDOWS)
			Windows_Focus(GetWindowByName(WindowName), NewState);
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_Focus(GetWindowByName(WindowName), NewState);
#endif
		}
	}
	static void FocusWindow(GLuint WindowIndex, GLboolean NewState)
	{
		if (WindowExists(WindowIndex))
		{
#if defined(CURRENT_OS_WINDOWS)
			Windows_Focus(GetWindowByIndex(WindowIndex), NewState);
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_Focus(GetWindowByIndex(WindowIndex), NewState);
#endif
		}
	}

	//gets and sets for restoring the window
	static void RestoreWindow(const char* WindowName)
	{
		if (IsValid(WindowName))
		{
#if defined(CURRENT_OS_WINDOWS)
			Windows_Restore(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_Restore(GetWindowByName(WindowName));
#endif
		}
	}
	static void RestoreWindow(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
#if defined(CURRENT_OS_WINDOWS)
			Windows_Restore(GetWindowByIndex(WindowIndex));
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_Restore(GetWindowByIndex(WindowIndex));
#endif
		}
	}

	//initialize the window manager
	static void Initialize()
	{
#if defined(CURRENT_OS_LINUX)
		Linux_Initialize();
#endif	

#if defined(CURRENT_OS_WINDOWS)
		Windows_Initialize();
#endif
	}

	//ask the window to poll for window events
	static void PollForEvents()
	{
#if defined(CURRENT_OS_WINDOWS)
		GetInstance()->Windows_PollForEvents();
#endif

#if defined (CURRENT_OS_LINUX)
		GetInstance()->Linux_PollForEvents();
#endif
	}

	//remove a window from the manager
	static void RemoveWindow(const char* WindowName)
	{
		if(IsValid(WindowName))
		{
			ShutdownWindow(GetWindowByName(WindowName));
		}
	}

	static void RemoveWindow(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
			ShutdownWindow(GetWindowByIndex(WindowIndex));
		}
	}

	//set callbacks for the selected window
	static void SetWindowOnKeyEvent(const char* WindowName, OnKeyEvent OnKey)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->KeyEvent = OnKey;
		}
	}
	static void SetWindowOnKeyEvent(GLuint WindowIndex, OnKeyEvent OnKey)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->KeyEvent = OnKey;
		}
	}

	static void SetWindowOnMouseButtonEvent(const char* WindowName, OnMouseButtonEvent OnMouseButton)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->MouseButtonEvent = OnMouseButton;
		}
	}
	static void SetWindowOnMouseButtonEvent(GLuint WindowIndex, OnMouseButtonEvent OnMouseButton)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->MouseButtonEvent = OnMouseButton;
		}
	}

	static void SetWindowOnMouseWheelEvent(const char* WindowName, OnMouseWheelEvent OnMouseWheel)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->MouseWheelEvent = OnMouseWheel;
		}
	}
	static void SetWindowOnMouseWheelEvent(GLuint WindowIndex, OnMouseWheelEvent OnMouseWheel)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->MouseWheelEvent = OnMouseWheel;
		}
	}

	static void SetWindowOnDestroyed(const char* WindowName, OnDestroyedEvent OnDestroyed)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->DestroyedEvent = OnDestroyed;
		}
	}
	static void SetWindowOnDestroyed(GLuint WindowIndex, OnDestroyedEvent OnDestroyed)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->DestroyedEvent = OnDestroyed;
		}
	}

	static void SetWindowOnMaximized(const char* WindowName, OnMaximizedEvent OnMaximized)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->MaximizedEvent = OnMaximized;
		}
	}
	static void SetWindowOnMaximized(GLuint WindowIndex, OnMaximizedEvent OnMaximized)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->MaximizedEvent = OnMaximized;
		}
	}

	static void SetWindowOnMinimized(const char* WindowName, OnMinimizedEvent OnMiniimzed)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->MinimizedEvent = OnMiniimzed;
		}
	}
	static void SetWindowOnMinimized(GLuint WindowIndex, OnMinimizedEvent OnMiniimzed)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->MinimizedEvent = OnMiniimzed;
		}
	}

	static void SetWindowOnFocus(const char* WindowName, OnFocusEvent OnFocus)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->FocusEvent = OnFocus;
		}
	}
	static void SetWindowOnFocus(GLuint WindowIndex, OnFocusEvent OnFocus)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->FocusEvent = OnFocus;
		}
	}

	static void SetWindowOnMoved(const char* WindowName, OnMovedEvent OnMoved)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->MovedEvent = OnMoved;
		}
	}
	static void SetWindowOnMoved(GLuint WindowIndex, OnMovedEvent OnMoved)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->MovedEvent = OnMoved;
		}
	}

	static void SetWindowOnResize(const char* WindowName, OnResizeEvent OnResize)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->ResizeEvent = OnResize;
		}
	}
	static void SetWindowOnResize(GLuint WindowIndex, OnResizeEvent OnResize)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->ResizeEvent = OnResize;
		}
	}

	static void SetWindowOnMouseMove(const char* WindowName, OnMouseMoveEvent OnMouseMove)
	{
		if (IsValid(WindowName))
		{
			GetWindowByName(WindowName)->MouseMoveEvent = OnMouseMove;
		}
	}
	static void SetWindowOnMouseMove(GLuint WindowIndex, OnMouseMoveEvent OnMouseMove)
	{
		if (WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->MouseMoveEvent = OnMouseMove;
		}
	}

	static GLint GetWindowCurrentSyncState(const char* WindowName)
	{
		if(IsValid(WindowName))
		{
			return GetWindowByName(WindowName)->CurrentSyncSetting;
		}

		return 0;
	}

	static GLint GetWindowCurrentSyncState(GLuint WindowIndex)
	{
		if(WindowExists(WindowIndex))
		{
			return GetWindowByIndex(WindowIndex)->CurrentSyncSetting;
		}

		return 0;
	}

	static void ToggleVerticalSync(const char* WindowName, GLint SyncSetting)
	{
		if(IsValid(WindowName))
		{
			GetWindowByName(WindowName)->CurrentSyncSetting = SyncSetting;

#if defined(CURRENT_OS_WINDOWS)
			Windows_ToggleVerticalSync(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_ToggleVerticalSync(GetWindowByName(WindowName));
#endif
		}
	}

	static void ToggleVerticalSync(GLuint WindowIndex, GLint SyncSetting)
	{
		if(WindowExists(WindowIndex))
		{
			GetWindowByIndex(WindowIndex)->CurrentSyncSetting = SyncSetting;
#if defined(CURRENT_OS_WINDOWS)
			Windows_ToggleVerticalSync(GetWindowByIndex(WindowIndex));
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_ToggleVerticalSync(GetWindowByIndex(WindowIndex));
#endif
		}
	}
	private:

	struct TWindow
		{
			TWindow()
			{
				Name = nullptr;
				ID = 0;
				ColourBits = 0;
				DepthBits = 0;
				StencilBits = 0;
				ShouldClose = GL_FALSE;
				CurrentState = WINDOWSTATE_NORMAL;
				
				KeyEvent = nullptr;
				MouseButtonEvent = nullptr;
				MouseWheelEvent = nullptr;
				DestroyedEvent = nullptr;
				MaximizedEvent = nullptr;
				MinimizedEvent = nullptr;
				FocusEvent = nullptr;
				MovedEvent = nullptr;
				ResizeEvent = nullptr;
				MouseMoveEvent = nullptr;
			}
			//Name of the window
			const char*  Name;
			//ID of the Window. (where it belongs in the window manager)
			GLuint ID;
			//Colour format of the window. (defaults to 32 bit Colour)
			GLuint ColourBits;
			//Size of the Depth buffer. (defaults to 8 bit depth)
			GLuint DepthBits;
			//Size of the stencil buffer, (defaults to 8 bit)
			GLuint StencilBits;
			//Record of keys that are either pressed or released in the respective window
			GLboolean Keys[KEY_LAST];
			//Record of mouse buttons that are either presses or released
			GLboolean MouseButton[MOUSE_LAST];
			//Resolution/Size of the window stored in an array
			GLuint Resolution[2];
			//Position of the Window relative to the screen co-ordinates
			GLuint Position[2];
			//Position of the Mouse cursor relative to the window co-ordinates
			GLuint MousePosition[2];
			//Whether the Window should be closing
			GLboolean ShouldClose;
			//Whether the Window is currently in focus(if it is the current window be used)
			GLboolean InFocus;
			//The current state of the window. these states include Normal, Minimized, Maximized and Full screen
			GLuint CurrentState;
			//The current swap interval of the window(V-Sync). a value of -1 enables adaptive V-Sync on supported systems
			GLuint CurrentSyncSetting;

			//this is the callback to be used when a key has been pressed
			OnKeyEvent KeyEvent;
			//this is the callback to be used when a mouse button has been pressed
			OnMouseButtonEvent MouseButtonEvent;
			//this is the callback to be used when the mouse wheel has been scrolled. 
			OnMouseWheelEvent MouseWheelEvent;
			//this is the callback to be used when the window has been closed in a non-programmatic fashion
			OnDestroyedEvent DestroyedEvent;
			//this is the callback to be used when the window has been maximized in a non-programmatic fashion
			OnMaximizedEvent MaximizedEvent;
			//this is the callback to be used when the window has been minimized in a non-programmatic fashion
			OnMinimizedEvent MinimizedEvent;
			//this is the callback to be used when the window has been given focus in a non-programmatic fashion
			OnFocusEvent FocusEvent;
			//this is the callback to be used the window has been moved in a non-programmatic fashion
			OnMovedEvent MovedEvent;
			//this is a callback to be used when the window has been resized in a non-programmatic fashion
			OnResizeEvent ResizeEvent;
			//this is a callback to be used when the mouse has been moved
			OnMouseMoveEvent MouseMoveEvent;

			GLboolean EXTSwapControlSupported;
			GLboolean SGISwapControlSupported;
			GLboolean MESASwapControlSupported;

#if defined(CURRENT_OS_WINDOWS)
			
			HDC DeviceContextHandle;
			HGLRC GLRenderingContextHandle;
			HPALETTE PaletteHandle;
			PIXELFORMATDESCRIPTOR PixelFormatDescriptor;

			WNDCLASS WindowClass;
			HWND WindowHandle;
			HINSTANCE InstanceHandle;	
			
			PFNWGLSWAPINTERVALEXTPROC SwapIntervalEXT;

#endif

#if defined(CURRENT_OS_LINUX)
			Window WindowHandle;
			GLXContext Context;
			XVisualInfo* VisualInfo;
			GLint* Attributes;

			XSetWindowAttributes SetAttributes;
	
			PFNGLXSWAPINTERVALMESAPROC SwapIntervalMESA;
			PFNGLXSWAPINTERVALEXTPROC SwapIntervalEXT;
			PFNGLXSWAPINTERVALSGIPROC SwapIntervalSGI;

			//these atomics are needed to change window states via the extended window manager
			Atom AtomState; //_NET_WM_STATE
			Atom AtomHidden;// _NET_WM_STATE_HIDDEN
			Atom AtomFullScreen; //NET_WM_STATE_FULLSCREEN
			Atom AtomMaxHorz; // _NET_WM_STATE_MAXIMIZED_HORZ
			Atom AtomMaxVert; // _NET_WM_STATE_MAXIMIZED_VERT
			Atom AtomClose; // _NET_WM_CLOSE_WINDOW
			Atom AtomActive; //_NET_ACTIVE_WINDOW
			Atom AtomDemandsAttention;//_NET_WM_STATE_DEMANDS_ATTENTION
			Atom AtomFocused;//_NET_WM_STATE_FOCUSED

#endif
		};

	static TWindow* GetWindowInList(const char* WindowName)
	{
		if (IsValid(WindowName))
		{
#if defined(CURRENT_OS_WINDOWS)
			for each (auto iter in GetInstance()->Windows)
			{
				if (iter->Name == WindowName)
				{
					return iter;
				}
			}
#endif

#if defined(CURRENT_OS_LINUX)
			for(auto iter : GetInstance()->Windows)
			{
				if(iter->Name == WindowName)
				{
					return iter;
				}
			}

			return nullptr;
#endif
		}

		return nullptr;
	}

	static TWindow* GetWindowInList(GLuint WindowIndex)
	{
		if (WindowExists(WindowIndex))
		{
#if defined(CURRENT_OS_WINDOWS)
			for each (auto iter in GetInstance()->Windows)
			{
				if (iter->ID == WindowIndex)
				{
					return iter;
				}
			}
#endif

#if defined(CURRENT_OS_LINUX)
			for (auto iter : GetInstance()->Windows)
			{
				if (iter->ID == WindowIndex)
				{
					return iter;
				}
			}

			return nullptr;
#endif
		}

		return nullptr;
	}


	static GLboolean IsValid(const char* String)
	{
		return (String != nullptr);
	}

	static GLboolean IsValid(OnKeyEvent OnKeyPressed)
	{
		return (OnKeyPressed != nullptr);
	}

	static GLboolean IsValid(OnMouseWheelEvent OnMouseWheelEvent)
	{
		return (OnMouseWheelEvent != nullptr);
	}

	static GLboolean IsValid(OnMaximizedEvent OnMaximized)
	{
		return (OnMaximized != nullptr);
	}

	static GLboolean IsValid(OnFocusEvent OnFocus)
	{
		return (OnFocus != nullptr);
	}

	static GLboolean IsValid(OnMovedEvent OnMoved)
	{
		return (OnMoved != nullptr);
	}

	static GLboolean IsValid(OnMouseMoveEvent OnMouseMove)
	{
		return (OnMouseMove != nullptr);
	}	

	static GLboolean WindowExists(GLuint WindowIndex)
	{
		return (WindowIndex <= GetInstance()->Windows.size() - 1);
	}

	//get a static reference to the window manager
	static WindowManager* GetInstance()
	{
		if (WindowManager::Instance == nullptr)
		{
			WindowManager::Instance = new WindowManager();
			return WindowManager::Instance;
		}

		else
		{
			return WindowManager::Instance;
		}
	}

	static void InitializeWindow(TWindow* SelectedWindow)
	{
#if defined(CURRENT_OS_WINDOWS)
		Windows_InitializeWindow(SelectedWindow);
#endif

#if defined(CURRENT_OS_LINUX)
		Linux_InitializeWindow(SelectedWindow);
#endif
	}

	static void InitializeGL(TWindow* SelectedWindow)
	{
#if defined(CURRENT_OS_WINDOWS)
		Windows_InitializeGL(SelectedWindow);
#endif

#if defined(CURRENT_OS_LINUX)
		Linux_InitializeGL(SelectedWindow);
#endif
	}

	static void InitializeGLExtensions(TWindow* SelectedWindow)
	{
#if defined(CURRENT_OS_WINDOWS)
		Windows_InitGLExtensions(SelectedWindow);
#endif

#if defined(CURRENT_OS_LINUX)
		Linux_InitGLExtensions(SelectedWindow);
#endif
	}

	static void ShutdownWindow(TWindow* SelectedWindow)
	{
#if defined(CURRENT_OS_WINDOWS)
		Windows_ShutdownWindow(SelectedWindow);
#endif

#if defined(CURRENT_OS_LINUX)
		Linux_ShutdownWindow(SelectedWindow);
#endif
	}


	static TWindow* GetWindowByName(const char* WindowName)
	{
		if (IsValid(WindowName))
		{
			for (GLuint l_Iter = 0; l_Iter <= GetInstance()->Windows.size() - 1; l_Iter++)
			{
				if (GetWindowInList(l_Iter)->Name == WindowName)
				{
					return GetWindowInList(l_Iter);
				}
			}
			return nullptr;
		}
		return nullptr;
	}

	static TWindow* GetWindowByIndex(GLuint WindowIndex)
	{
		if (WindowIndex <= GetInstance()->Windows.size() - 1)
		{
			return GetWindowInList(WindowIndex);
		}

		return nullptr;
	}

	std::list<TWindow*> Windows;
	static WindowManager* Instance;

	GLuint ScreenResolution[2];
	GLuint ScreenMousePosition[2];
	
#if defined(CURRENT_OS_WINDOWS)
	LRESULT CALLBACK WindowProcedure(HWND WindowHandle, GLuint Message, WPARAM WordParam, LPARAM LongParam)
	{
		TWindow* LocalWindow = GetWindowByHandle(WindowHandle);
		switch (Message)
		{
		case WM_CREATE:
		{
			GetWindowByIndex(Windows.size() - 1)->WindowHandle = WindowHandle;
			LocalWindow = GetWindowByHandle(WindowHandle);

			InitializeGL(LocalWindow);
			break;
		}

		case WM_DESTROY:
		{
			LocalWindow->ShouldClose = GL_TRUE;

			if (IsValid(LocalWindow->DestroyedEvent))
			{
				LocalWindow->DestroyedEvent();
			}

			ShutdownWindow(LocalWindow);
			break;
		}
		case WM_MOVE:
		{
			LocalWindow->Position[0] = LOWORD(LongParam);
			LocalWindow->Position[1] = HIWORD(LongParam);

			if (IsValid(LocalWindow->MovedEvent))
			{
				LocalWindow->MovedEvent(LocalWindow->Position[0], LocalWindow->Position[1]);
			}

			break;
		}

		case WM_MOVING:
		{
			LocalWindow->Position[0] = LOWORD(LongParam);
			LocalWindow->Position[1] = HIWORD(LongParam);

			if (IsValid(LocalWindow->MovedEvent))
			{
				LocalWindow->MovedEvent(LocalWindow->Position[0], LocalWindow->Position[1]);
			}
			break;
		}

		case WM_SIZE:
		{
			LocalWindow->Resolution[0] = (GLuint)LOWORD(LongParam);
			LocalWindow->Resolution[1] = (GLuint)HIWORD(LongParam);

			switch (WordParam)
			{
			case SIZE_MAXIMIZED:
			{
				if (IsValid(LocalWindow->MaximizedEvent))
				{
					LocalWindow->MaximizedEvent();
				}

				break;
			}

			case SIZE_MINIMIZED:
			{
				if (IsValid(LocalWindow->MinimizedEvent))
				{
					LocalWindow->MinimizedEvent();
				}
				break;
			}

			default:
			{
				if (IsValid(LocalWindow->ResizeEvent))
				{
					LocalWindow->ResizeEvent(LocalWindow->Resolution[0],
						LocalWindow->Resolution[1]);
				}

				break;
			}
			}
			break;
		}

		case WM_SIZING:
		{

			LocalWindow->Resolution[0] = (GLuint)LOWORD(LongParam);
			LocalWindow->Resolution[1] = (GLuint)HIWORD(LongParam);

			if (IsValid(LocalWindow->ResizeEvent))
			{
				LocalWindow->ResizeEvent(LocalWindow->Resolution[0],
					LocalWindow->Resolution[1]);
			}


			break;
		}

		case WM_KEYDOWN:
		{
			GLuint l_TranslatedKey = 0;

			switch (HIWORD(LongParam))
			{
			case 29:
			{
				LocalWindow->Keys[KEY_LEFTCONTROL] = KEYSTATE_DOWN;
				l_TranslatedKey = KEY_LEFTCONTROL;
				break;
			}

			case 285:
			{
				LocalWindow->Keys[KEY_RIGHTCONTROL] = KEYSTATE_DOWN;
				l_TranslatedKey = KEY_RIGHTCONTROL;
				break;
			}

			case 42:
			{
				LocalWindow->Keys[KEY_LEFTSHIFT] = KEYSTATE_DOWN;
				l_TranslatedKey = KEY_LEFTSHIFT;
				break;
			}

			case 54:
			{
				LocalWindow->Keys[KEY_RIGHTSHIFT] = KEYSTATE_DOWN;
				l_TranslatedKey = KEY_RIGHTSHIFT;
				break;
			}

			default:
			{
				l_TranslatedKey = Windows_TranslateKey(WordParam, LongParam);
				LocalWindow->Keys[l_TranslatedKey] = KEYSTATE_DOWN;
				break;
			}
			}

			if (IsValid(LocalWindow->KeyEvent))
			{
				LocalWindow->KeyEvent(l_TranslatedKey, KEYSTATE_DOWN);
			}
			break;
		}

		case WM_KEYUP:
		{
			GLuint l_TranslatedKey = 0;

			switch (HIWORD(LongParam))
			{
			case 49181:
			{
				LocalWindow->Keys[KEY_LEFTCONTROL] = KEYSTATE_UP;
				l_TranslatedKey = KEY_LEFTCONTROL;
				break;
			}

			case 49437:
			{
				LocalWindow->Keys[KEY_RIGHTCONTROL] = KEYSTATE_UP;
				l_TranslatedKey = KEY_RIGHTCONTROL;
				break;
			}

			case 49194:
			{
				LocalWindow->Keys[KEY_LEFTSHIFT] = KEYSTATE_UP;
				l_TranslatedKey = KEY_LEFTSHIFT;
				break;
			}

			case 49206:
			{
				LocalWindow->Keys[KEY_RIGHTSHIFT] = KEYSTATE_UP;
				l_TranslatedKey = KEY_RIGHTSHIFT;
				break;
			}

			default:
			{
				l_TranslatedKey = Windows_TranslateKey(WordParam, LongParam);
				LocalWindow->Keys[l_TranslatedKey] = KEYSTATE_UP;
				break;
			}
			}

			if (IsValid(LocalWindow->KeyEvent))
			{
				LocalWindow->KeyEvent(l_TranslatedKey, KEYSTATE_UP);
			}
			break;
		}

		case WM_SYSKEYDOWN:
		{
			GLuint l_TranslatedKey = 0;
			switch (HIWORD(LongParam))
			{
			case 8248:
			{
				LocalWindow->Keys[KEY_LEFTALT] = KEYSTATE_DOWN;
				l_TranslatedKey = KEY_LEFTALT;
				break;
			}


			case 8504:
			{
				LocalWindow->Keys[KEY_RIGHTALT] = KEYSTATE_DOWN;
				l_TranslatedKey = KEY_RIGHTALT;
			}

			default:
			{
				break;
			}
			}

			if (IsValid(LocalWindow->KeyEvent))
			{
				LocalWindow->KeyEvent(l_TranslatedKey, KEYSTATE_DOWN);
			}

			break;
		}

		case WM_SYSKEYUP:
		{
			GLuint l_TranslatedKey = 0;
			switch (HIWORD(LongParam))
			{
			case 49208:
			{
				LocalWindow->Keys[KEY_LEFTALT] = KEYSTATE_UP;
				l_TranslatedKey = KEY_LEFTALT;
				break;
			}


			case 49464:
			{
				LocalWindow->Keys[KEY_RIGHTALT] = KEYSTATE_UP;
				l_TranslatedKey = KEY_RIGHTALT;
				break;
			}

			default:
			{
				break;
			}
			}

			if (IsValid(LocalWindow->KeyEvent))
			{
				LocalWindow->KeyEvent(l_TranslatedKey, KEYSTATE_UP);
			}
			break;
		}

		case WM_MOUSEMOVE:
		{
			LocalWindow->MousePosition[0] = (GLuint)LOWORD(LongParam);
			LocalWindow->MousePosition[1] = (GLuint)HIWORD(LongParam);

			POINT l_Point;
			l_Point.x = LocalWindow->MousePosition[0];
			l_Point.y = LocalWindow->MousePosition[1];

			ClientToScreen(WindowHandle, &l_Point);

			if (IsValid(LocalWindow->MouseMoveEvent))
			{
				LocalWindow->MouseMoveEvent(LocalWindow->MousePosition[0],
					LocalWindow->MousePosition[1], l_Point.x, l_Point.y);
			}
			break;
		}

		case WM_LBUTTONDOWN:
		{
			LocalWindow->MouseButton[MOUSE_LEFTBUTTON] = MOUSE_BUTTONDOWN;

			if (IsValid(LocalWindow->MouseButtonEvent))
			{
				LocalWindow->MouseButtonEvent(MOUSE_LEFTBUTTON, MOUSE_BUTTONDOWN);
			}
			break;
		}

		case WM_LBUTTONUP:
		{
			LocalWindow->MouseButton[MOUSE_LEFTBUTTON] = MOUSE_BUTTONUP;

			if (IsValid(LocalWindow->MouseButtonEvent))
			{
				LocalWindow->MouseButtonEvent(MOUSE_LEFTBUTTON, MOUSE_BUTTONUP);
			}
			break;
		}

		case WM_RBUTTONDOWN:
		{
			LocalWindow->MouseButton[MOUSE_RIGHTBUTTON] = MOUSE_BUTTONDOWN;

			if (IsValid(LocalWindow->MouseButtonEvent))
			{
				LocalWindow->MouseButtonEvent(MOUSE_RIGHTBUTTON, MOUSE_BUTTONDOWN);
			}
			break;
		}

		case WM_RBUTTONUP:
		{
			LocalWindow->MouseButton[MOUSE_RIGHTBUTTON] = MOUSE_BUTTONUP;

			if (IsValid(LocalWindow->MouseButtonEvent))
			{
				LocalWindow->MouseButtonEvent(MOUSE_RIGHTBUTTON, MOUSE_BUTTONUP);
			}
			break;
		}

		case WM_MBUTTONDOWN:
		{
			LocalWindow->MouseButton[MOUSE_MIDDLEBUTTON] = MOUSE_BUTTONDOWN;

			if (IsValid(LocalWindow->MouseButtonEvent))
			{
				LocalWindow->MouseButtonEvent(MOUSE_MIDDLEBUTTON, MOUSE_BUTTONDOWN);
			}
			break;
		}

		case WM_MBUTTONUP:
		{
			LocalWindow->MouseButton[MOUSE_MIDDLEBUTTON] = MOUSE_BUTTONUP;

			if (IsValid(LocalWindow->MouseButtonEvent))
			{
				LocalWindow->MouseButtonEvent(MOUSE_MIDDLEBUTTON, MOUSE_BUTTONUP);
			}
			break;
		}

		case WM_MOUSEWHEEL:
		{
			if ((WordParam % WHEEL_DELTA) > 0)
			{
				if (IsValid(LocalWindow->MouseWheelEvent))
				{
					LocalWindow->MouseWheelEvent(MOUSE_SCROLL_DOWN);
				}
			}

			else
			{
				if (IsValid(LocalWindow->MouseWheelEvent))
				{
					LocalWindow->MouseWheelEvent(MOUSE_SCROLL_UP);
				}

			}
			break;
		}

		default:
		{
			return DefWindowProc(WindowHandle, Message, WordParam, LongParam);
		}
		}
		return 0;

	}

	static LRESULT CALLBACK StaticWindowProcedure(HWND WindowHandle, UINT Message, WPARAM WordParam, LPARAM LongParam)
	{
		return WindowManager::GetInstance()->WindowProcedure(WindowHandle, Message, WordParam, LongParam);
	}

	static TWindow* GetWindowByHandle(HWND WindowHandle)
	{
		for (GLuint l_Iter = 0; l_Iter < GetInstance()->Windows.size(); l_Iter++)
		{
			if (GetWindowInList(l_Iter)->WindowHandle == WindowHandle)
			{
				return GetWindowInList(l_Iter);
			}
		}

		return nullptr;
	}

	static void Windows_SetWindowResolution(TWindow* SelectedWindow)
	{
		SetWindowPos(SelectedWindow->WindowHandle, HWND_TOP,
			SelectedWindow->Position[0], SelectedWindow->Position[1],
			SelectedWindow->Resolution[0], SelectedWindow->Resolution[1],
			SWP_SHOWWINDOW | SWP_NOMOVE);
	}

	static void Windows_SetWindowPosition(TWindow* SelectedWindow)
	{
		SetWindowPos(SelectedWindow->WindowHandle, HWND_TOP,
			SelectedWindow->Position[0], SelectedWindow->Position[1],
			SelectedWindow->Resolution[0], SelectedWindow->Resolution[1],
			SWP_SHOWWINDOW | SWP_NOSIZE);
	}

	static void Windows_InitializeWindow(TWindow* SelectedWindow,
		UINT a_Style = CS_OWNDC | CS_HREDRAW | CS_DROPSHADOW,
		int a_ClearScreenExtra = 0,
		int WindowExtra = 0,
		HINSTANCE Instance = GetModuleHandle(0),
		HICON Icon = LoadIcon(0, IDI_APPLICATION),
		HCURSOR Cursor = LoadCursor(0, IDC_ARROW),
		HBRUSH Brush = (HBRUSH)BLACK_BRUSH)
	{
		SelectedWindow->InstanceHandle = Instance;
		SelectedWindow->WindowClass.style = a_Style;
		SelectedWindow->WindowClass.lpfnWndProc = WindowManager::StaticWindowProcedure;
		SelectedWindow->WindowClass.cbClsExtra = 0;
		SelectedWindow->WindowClass.cbWndExtra = 0;
		SelectedWindow->WindowClass.hInstance = SelectedWindow->InstanceHandle;
		SelectedWindow->WindowClass.hIcon = Icon;
		SelectedWindow->WindowClass.hCursor = Cursor;
		SelectedWindow->WindowClass.hbrBackground = Brush;
		SelectedWindow->WindowClass.lpszMenuName = SelectedWindow->Name;
		SelectedWindow->WindowClass.lpszClassName = SelectedWindow->Name;
		RegisterClass(&SelectedWindow->WindowClass);

		SelectedWindow->WindowHandle =
			CreateWindow(SelectedWindow->Name, SelectedWindow->Name, WS_OVERLAPPEDWINDOW, 0,
			0, SelectedWindow->Resolution[0],
			SelectedWindow->Resolution[1],
			0, 0, 0, 0);

		ShowWindow(SelectedWindow->WindowHandle, GL_TRUE);
		UpdateWindow(SelectedWindow->WindowHandle);
	}

	static void InitializePixelFormat(TWindow* SelectedWindow)
	{
		SelectedWindow->PixelFormatDescriptor = {
			sizeof(PIXELFORMATDESCRIPTOR),  /* size */
			1,                              /* version */
			PFD_SUPPORT_OPENGL |
			PFD_DRAW_TO_WINDOW |
			PFD_DOUBLEBUFFER,               /* support double-buffering */
			PFD_TYPE_RGBA,                  /* color type */
			SelectedWindow->ColourBits, 0,                             /* prefered color depth */
			0, 0,
			0, 0,
			0, 0,
			0,                /* color bits (ignored) */                              /* no alpha buffer */                              /* alpha bits (ignored) */
			0,                              /* no accumulation buffer */
			0, 0, 0, 0,                     /* accum bits (ignored) */
			SelectedWindow->DepthBits,                    /* depth buffer */
			SelectedWindow->StencilBits,                  /* no stencil buffer */
			0,                              /* no auxiliary buffers */
			PFD_MAIN_PLANE,                 /* main layer */
			0,                              /* reserved */
			0, 0, 0,                        /* no layer, visible, damage masks */
		};

		int LocalPixelFormat = ChoosePixelFormat(SelectedWindow->DeviceContextHandle,
			&SelectedWindow->PixelFormatDescriptor);

		if (LocalPixelFormat)
		{
			SetPixelFormat(SelectedWindow->DeviceContextHandle, LocalPixelFormat,
				&SelectedWindow->PixelFormatDescriptor);
			return;
		}
		return;
	}

	static void Windows_InitializeGL(TWindow* SelectedWindow)
	{
		SelectedWindow->DeviceContextHandle = GetDC(SelectedWindow->WindowHandle);
		InitializePixelFormat(SelectedWindow);
		SelectedWindow->GLRenderingContextHandle = wglCreateContext(SelectedWindow->DeviceContextHandle);
		wglMakeCurrent(SelectedWindow->DeviceContextHandle, SelectedWindow->GLRenderingContextHandle);

		InitializeGLExtensions(SelectedWindow);
	}

	static void Windows_InitGLExtensions(TWindow* SelectedWindow)
	{
		SelectedWindow->SwapIntervalEXT = nullptr;
		SelectedWindow->EXTSwapControlSupported = GL_FALSE;

		SelectedWindow->SwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)
			wglGetProcAddress("wglSwapIntervalEXT");

		if(SelectedWindow->SwapIntervalEXT)
		{
			SelectedWindow->EXTSwapControlSupported = GL_TRUE;
		}

	}

	static void Windows_ToggleVerticalSync(TWindow* SelectedWindow)
	{
		if (SelectedWindow->EXTSwapControlSupported)
		{
			SelectedWindow->SwapIntervalEXT(SelectedWindow->CurrentSyncSetting);
		}
	}

	static void Windows_ShutdownWindow(TWindow* SelectedWindow)
	{
		if (SelectedWindow->GLRenderingContextHandle)
		{
			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(SelectedWindow->GLRenderingContextHandle);
		}

		if (SelectedWindow->PaletteHandle)
		{
			DeleteObject(SelectedWindow->PaletteHandle);
		}
		ReleaseDC(SelectedWindow->WindowHandle, SelectedWindow->DeviceContextHandle);
		DestroyWindow(SelectedWindow->WindowHandle);
		UnregisterClass(SelectedWindow->Name, SelectedWindow->InstanceHandle);

		SelectedWindow->DeviceContextHandle = nullptr;
		SelectedWindow->WindowHandle = nullptr;
		SelectedWindow->GLRenderingContextHandle = nullptr;

		PostQuitMessage(0);
	}

	static void Windows_FullScreen(TWindow* SelectedWindow)
	{
		SetWindowLongPtr(SelectedWindow->WindowHandle, GWL_STYLE,
			WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);

		MoveWindow(SelectedWindow->WindowHandle, 0, 0, WindowManager::GetScreenResolution()[0],
			WindowManager::GetScreenResolution()[1], GL_TRUE);
	}

	static void Windows_Minimize(TWindow* SelectedWindow, GLboolean NewState)
	{
		if (NewState)
		{
			ShowWindow(SelectedWindow->WindowHandle, SW_MINIMIZE);
		}

		else
		{
			ShowWindow(SelectedWindow->WindowHandle, SW_RESTORE);
		}
	}

	static void Windows_Maximize(TWindow* SelectedWindow, GLboolean NewState)
	{
		if (NewState)
		{
			ShowWindow(SelectedWindow->WindowHandle, SW_MAXIMIZE);
		}

		else
		{
			ShowWindow(SelectedWindow->WindowHandle, SW_RESTORE);
		}
	}

	static void Windows_Restore(TWindow* SelectedWindow)
	{
		ShowWindow(SelectedWindow->WindowHandle, SW_RESTORE);
	}

	static void Windows_Focus(TWindow* SelectedWindow, GLboolean NewState)
	{
		SelectedWindow->InFocus = NewState;

		if (NewState)
		{
			SetFocus(SelectedWindow->WindowHandle);
		}

		else
		{
			SetFocus(nullptr);
		}
	}

	static void Windows_SetMousePosition(TWindow* SelectedWindow)
	{
		POINT l_MousePoint;
		l_MousePoint.x = SelectedWindow->MousePosition[0];
		l_MousePoint.y = SelectedWindow->MousePosition[1];
		ScreenToClient(SelectedWindow->WindowHandle, &l_MousePoint);
		SetCursorPos(l_MousePoint.x, l_MousePoint.y);
	}

	static void Windows_SetPosition(TWindow* SelectedWindow)
	{
		SetWindowPos(SelectedWindow->WindowHandle, HWND_TOP, 
			SelectedWindow->Position[0], SelectedWindow->Position[1],
			SelectedWindow->Resolution[0],	SelectedWindow->Resolution[1], 
			SWP_SHOWWINDOW | SWP_NOSIZE);
	}

	static void Windows_SetResolution(TWindow* SelectedWindow)
	{
		SetWindowPos(SelectedWindow->WindowHandle, HWND_TOP, 
			SelectedWindow->Position[0], SelectedWindow->Position[1],
			SelectedWindow->Resolution[0], SelectedWindow->Resolution[1], 
			SWP_SHOWWINDOW | SWP_NOMOVE);
	}

	static void Windows_PollForEvents()
	{
		GetMessage(&GetInstance()->m_Message, 0, 0, 0);
		TranslateMessage(&GetInstance()->m_Message);
		DispatchMessage(&GetInstance()->m_Message);
	}

	static void Windows_Initialize()
	{
		CreateTerminal();
		RECT l_Desktop;

		HWND l_DesktopHandle = GetDesktopWindow();

		GetWindowRect(l_DesktopHandle, &l_Desktop);

		GetInstance()->ScreenResolution[0] = l_Desktop.right;
		GetInstance()->ScreenResolution[1] = l_Desktop.bottom;
	}

	static void Windows_SetMousePositionInScreen()
	{
		SetCursorPos(GetInstance()->ScreenMousePosition[0],
			GetInstance()->ScreenMousePosition[1]);
	}

	static void CreateTerminal()
	{
		int hConHandle;
		long lStdHandle;
		FILE *fp;

		// allocate a console for this app
		AllocConsole();

		// redirect unbuffered STDOUT to the console
		lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen(hConHandle, "w");
		*stdout = *fp;

		setvbuf(stdout, nullptr, _IONBF, 0);
	}

	static GLuint Windows_TranslateKey(WPARAM WordParam, LPARAM LongParam)
	{
		switch (WordParam)
		{
		case VK_ESCAPE:
		{
			return KEY_ESCAPE;
		}

		case VK_F1:
		{
			return KEY_F1;
		}

		case VK_F2:
		{
			return KEY_F2;
		}

		case VK_F3:
		{
			return KEY_F3;
		}

		case VK_F4:
		{
			return KEY_F4;
		}

		case VK_F5:
		{
			return KEY_F5;
		}

		case VK_F6:
		{
			return KEY_F6;
		}

		case VK_F7:
		{
			return KEY_F7;
		}

		case VK_F8:
		{
			return KEY_F8;
		}

		case VK_F9:
		{
			return KEY_F9;
		}

		case VK_F10:
		{
			return KEY_F10;
		}

		case VK_F11:
		{
			return KEY_F11;
		}

		case VK_F12:
		{
			return KEY_F12;
		}

		case VK_BACK:
		{
			return KEY_BACKSPACE;
		}

		case VK_TAB:
		{
			return KEY_TAB;
		}

		case VK_CAPITAL:
		{
			return KEY_CAPSLOCK;
		}

		case VK_RETURN:
		{
			return KEY_ENTER;
		}

		case VK_PRINT:
		{
			return KEY_PRINTSCREEN;
		}

		case VK_SCROLL:
		{
			return KEY_SCROLLLOCK;
		}

		case VK_PAUSE:
		{
			return KEY_PAUSE;
		}

		case VK_INSERT:
		{
			return KEY_INSERT;
		}

		case VK_HOME:
		{
			return KEY_HOME;
		}

		case VK_DELETE:
		{
			return KEY_DELETE;
		}

		case VK_END:
		{
			return KEY_END;
		}

		case VK_PRIOR:
		{
			return KEY_PAGEUP;
		}

		case VK_NEXT:
		{
			return KEY_PAGEDOWN;
		}

		case VK_DOWN:
		{
			return KEY_ARROW_DOWN;
		}

		case VK_UP:
		{
			return KEY_ARROW_UP;
		}

		case VK_LEFT:
		{
			return KEY_ARROW_LEFT;
		}

		case VK_RIGHT:
		{
			return KEY_ARROW_RIGHT;
		}

		case VK_DIVIDE:
		{
			return KEY_KEYPAD_DIVIDE;
		}

		case VK_MULTIPLY:
		{
			return KEY_KEYPAD_MULTIPLY;
		}

		case VK_SUBTRACT:
		{
			return KEY_KEYPAD_DIVIDE;
		}

		case VK_ADD:
		{
			return KEY_KEYPAD_ADD;
		}

		case VK_DECIMAL:
		{
			return KEY_KEYPAD_PERIOD;
		}

		case VK_NUMPAD0:
		{
			return KEY_KEYPAD_0;
		}

		case VK_NUMPAD1:
		{
			return KEY_KEYPAD_1;
		}

		case VK_NUMPAD2:
		{
			return KEY_KEYPAD_2;
		}

		case VK_NUMPAD3:
		{
			return KEY_KEYPAD_3;
		}

		case VK_NUMPAD4:
		{
			return KEY_KEYPAD_4;
		}

		case VK_NUMPAD5:
		{
			return KEY_KEYPAD_5;
		}

		case VK_NUMPAD6:
		{
			return KEY_KEYPAD_6;
		}

		case VK_NUMPAD7:
		{
			return KEY_KEYPAD_7;
		}

		case VK_NUMPAD8:
		{
			return KEY_KEYPAD_8;
		}

		case VK_NUMPAD9:
		{
			return KEY_KEYPAD_9;
		}

		case VK_LWIN:
		{
			return KEY_WINDOW_LEFT;
		}

		case VK_RWIN:
		{
			return KEY_WINDOW_RIGHT;
		}

		default:
		{
			return WordParam;
		}
		}
	}

	MSG m_Message;
	HDC m_DeviceContextHandle;

#endif

#if defined(CURRENT_OS_LINUX)
	
	static TWindow* GetWindowByHandle(Window WindowHandle)
	{
		for(auto iter : GetInstance()->Windows)
		{
			if (iter->WindowHandle == WindowHandle)
			{
				return iter;
			}
		}
		return nullptr;	
	}

	static TWindow* GetWindowByEvent(XEvent Event)
	{
		switch(Event.type)
		{
		case Expose:
		{
			return GetWindowByHandle(Event.xexpose.window);
		}	

		case DestroyNotify:
		{
			return GetWindowByHandle(Event.xdestroywindow.window);
		}

		case CreateNotify:
		{
			return GetWindowByHandle(Event.xcreatewindow.window);
		}	

		case KeyPress:
		{
			return GetWindowByHandle(Event.xkey.window);
		}

		case KeyRelease:
		{
			return GetWindowByHandle(Event.xkey.window);
		}

		case ButtonPress:
		{
			return GetWindowByHandle(Event.xbutton.window);
		}

		case ButtonRelease:
		{
			return GetWindowByHandle(Event.xbutton.window);
		}

		case MotionNotify:
		{
			return GetWindowByHandle(Event.xmotion.window);
		}	

		case FocusIn:
		{
			return GetWindowByHandle(Event.xfocus.window);
		}

		case FocusOut:
		{
			return GetWindowByHandle(Event.xfocus.window);
		}

		case ResizeRequest:
		{
			return GetWindowByHandle(Event.xresizerequest.window);
		}

		case ConfigureNotify:
		{
			return GetWindowByHandle(Event.xconfigure.window);
		}

		case PropertyNotify:
		{
			return GetWindowByHandle(Event.xproperty.window);
		}

		case GravityNotify:
		{
			return GetWindowByHandle(Event.xgravity.window);
		}

		case ClientMessage:
		{
			return GetWindowByHandle(Event.xclient.window);
		}

		case VisibilityNotify:
		{
			return GetWindowByHandle(Event.xvisibility.window);
		}	

		default:
		{
			return nullptr;
		}
		}
	
	}

	static void Linux_Initialize()
	{
		GetInstance()->CurrentDisplay = XOpenDisplay(0);

		if(!GetInstance()->CurrentDisplay)
		{
			printf("Cannot Connect to X server\n");
			exit(0);
		}

		GetInstance()->ScreenResolution[0] = WidthOfScreen(XScreenOfDisplay(GetInstance()->CurrentDisplay, 
			DefaultScreen(GetInstance()->CurrentDisplay)));

		GetInstance()->ScreenResolution[1] = HeightOfScreen(XScreenOfDisplay(GetInstance()->CurrentDisplay,
			DefaultScreen(GetInstance()->CurrentDisplay)));
	}

	static void Linux_InitializeAtomics(TWindow* SelectedWindow)
	{
		SelectedWindow->AtomState = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_STATE", GL_FALSE);
		SelectedWindow->AtomFullScreen = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_STATE_FULLSCREEN", GL_FALSE);
		SelectedWindow->AtomMaxHorz = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_STATE_MAXIMIZED_HORZ", GL_FALSE);
		SelectedWindow->AtomMaxVert = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_STATE_MAXIMIZED_VERT", GL_FALSE);
		SelectedWindow->AtomClose = XInternAtom(WindowManager::GetDisplay(), "WM_DELETE_WINDOW", GL_FALSE);
		SelectedWindow->AtomHidden = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_STATE_HIDDEN", GL_FALSE);
		SelectedWindow->AtomActive = XInternAtom(WindowManager::GetDisplay(), "_NET_ACTIVE_WINDOW", GL_FALSE);
		SelectedWindow->AtomDemandsAttention = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_STATE_DEMANDS_ATTENTION", GL_FALSE);	
		SelectedWindow->AtomFocused = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_STATE_FOCUSED", GL_FALSE);
	}

	static void Linux_InitializeWindow(TWindow* SelectedWindow)
	{
		SelectedWindow->Attributes = new GLuint[5]{GLX_RGBA, GLX_DEPTH_SIZE, 
			SelectedWindow->DepthBits, GLX_DOUBLEBUFFER,/* GLX_STENCIL_SIZE,
			SelectedWindow->StencilBits, GLX_RED_SIZE, SelectedWindow->ColourBits, 
			GLX_GREEN_SIZE, SelectedWindow->ColourBits, GLX_RED_SIZE, SelectedWindow->ColourBits, 
			GLX_ALPHA_SIZE, SelectedWindow->ColourBits / 4,*/ None};

		if (!WindowManager::GetDisplay())
		{
			printf("Cannot Connect to X Server \n");
			exit(0);
		}

		SelectedWindow->VisualInfo = glXChooseVisual(WindowManager::GetDisplay(), 0,
			SelectedWindow->Attributes);

		if (!SelectedWindow->VisualInfo)
		{
			printf("No appropriate visual found\n");
			exit(0);
		}

		SelectedWindow->SetAttributes.colormap = XCreateColormap(WindowManager::GetDisplay(),
			DefaultRootWindow(WindowManager::GetDisplay()),
			SelectedWindow->VisualInfo->visual, AllocNone);

		SelectedWindow->SetAttributes.event_mask = ExposureMask | KeyPressMask 
			| KeyReleaseMask | MotionNotify | ButtonPressMask | ButtonReleaseMask
			| FocusIn | FocusOut | Button1MotionMask | Button2MotionMask | Button3MotionMask | 
			Button4MotionMask | Button5MotionMask | PointerMotionMask | FocusChangeMask
			| VisibilityChangeMask | PropertyChangeMask | SubstructureNotifyMask;

		SelectedWindow->WindowHandle = XCreateWindow(WindowManager::GetInstance()->CurrentDisplay,
			XDefaultRootWindow(WindowManager::GetInstance()->CurrentDisplay), 0, 0,
			SelectedWindow->Resolution[0], SelectedWindow->Resolution[1],
			0, SelectedWindow->VisualInfo->depth, InputOutput,
			SelectedWindow->VisualInfo->visual, CWColormap | CWEventMask,
			&SelectedWindow->SetAttributes);

		XMapWindow(WindowManager::GetDisplay(), SelectedWindow->WindowHandle);
		XStoreName(WindowManager::GetDisplay(), SelectedWindow->WindowHandle,
			SelectedWindow->Name);

		Linux_InitializeAtomics(SelectedWindow);

		XSetWMProtocols(WindowManager::GetDisplay(),
			SelectedWindow->WindowHandle, &SelectedWindow->AtomClose, GL_TRUE);	

		Linux_InitializeGL(SelectedWindow);
	}

	static void Linux_InitializeGL(TWindow* SelectedWindow)
	{
		SelectedWindow->Context = glXCreateContext(
			WindowManager::GetDisplay(),
			SelectedWindow->VisualInfo, 0, GL_TRUE);

		glXMakeCurrent(WindowManager::GetDisplay(),
			SelectedWindow->WindowHandle, SelectedWindow->Context);

		XWindowAttributes l_Attributes;

		XGetWindowAttributes(WindowManager::GetDisplay(),
			SelectedWindow->WindowHandle, &l_Attributes);
		SelectedWindow->Position[0] = l_Attributes.x;
		SelectedWindow->Position[1] = l_Attributes.y;
	}

	static void Linux_InitGLExtensions(TWindow* SelectedWindow)
	{
		SelectedWindow->SwapIntervalEXT = nullptr;
		SelectedWindow->SwapIntervalSGI = nullptr;
		SelectedWindow->SwapIntervalMESA = nullptr;
		SelectedWindow->EXTSwapControlSupported = GL_FALSE;
		SelectedWindow->SGISwapControlSupported = GL_FALSE;
		SelectedWindow->MESASwapControlSupported = GL_FALSE;

		SelectedWindow->SwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalEXT");
		SelectedWindow->SwapIntervalSGI = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalSGI");
		SelectedWindow->SwapIntervalMESA = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddress((const GLubyte*)"glXSwapIntervalMESA");

		if(SelectedWindow->SwapIntervalEXT)
		{
			SelectedWindow->EXTSwapControlSupported = GL_TRUE;
		}

		if(SelectedWindow->SwapIntervalSGI)
		{
			SelectedWindow->SGISwapControlSupported = GL_TRUE;
		}

		if(SelectedWindow->SwapIntervalMESA)
		{
			SelectedWindow->MESASwapControlSupported = GL_TRUE;
		}
	}

	static void Linux_ToggleVerticalSync(TWindow* SelectedWindow)
	{
		if(SelectedWindow->EXTSwapControlSupported)
		{
			SelectedWindow->SwapIntervalEXT(GetDisplay(), 
					SelectedWindow->WindowHandle, SelectedWindow->CurrentSyncSetting);
		}

		if(SelectedWindow->SGISwapControlSupported)
		{
			//SGI does not support adaptive V-sync
			if(SelectedWindow->CurrentSyncSetting > 0)
			{
				SelectedWindow->SwapIntervalSGI(SelectedWindow->CurrentSyncSetting);
			}
		}

		if(SelectedWindow->MESASwapControlSupported)
		{
			SelectedWindow->SwapIntervalMESA(SelectedWindow->CurrentSyncSetting);
		}
	}

	static void Linux_ShutdownWindow(TWindow* SelectedWindow)
	{
		if(SelectedWindow->CurrentState == WINDOWSTATE_FULLSCREEN)
		{
			RestoreWindow(SelectedWindow->Name);
		}

		glXDestroyContext(WindowManager::GetDisplay(), SelectedWindow->Context);
		XUnmapWindow(WindowManager::GetDisplay(), SelectedWindow->WindowHandle);
		XDestroyWindow(WindowManager::GetDisplay(), SelectedWindow->WindowHandle);
		SelectedWindow->WindowHandle = 0;
		SelectedWindow->Context = 0;
	}

	static void Linux_Shutdown()
	{
		XCloseDisplay(GetInstance()->CurrentDisplay);
	}

	static void Linux_Fullscreen(TWindow* SelectedWindow)
	{
		XEvent l_Event;
		memset(&l_Event, 0, sizeof(l_Event));

		l_Event.xany.type = ClientMessage;
		l_Event.xclient.message_type = SelectedWindow->AtomState;
		l_Event.xclient.format = 32;
		l_Event.xclient.window = SelectedWindow->WindowHandle;
		l_Event.xclient.data.l[0] = SelectedWindow->CurrentState == WINDOWSTATE_FULLSCREEN;
		l_Event.xclient.data.l[1] = SelectedWindow->AtomFullScreen;

		XSendEvent(WindowManager::GetDisplay(),
			XDefaultRootWindow(WindowManager::GetDisplay()),
			0, SubstructureNotifyMask, &l_Event);
	}

	static void Linux_Minimize(TWindow* SelectedWindow)
	{
		if(SelectedWindow->CurrentState == WINDOWSTATE_MINIMIZED)
		{
			XIconifyWindow(WindowManager::GetDisplay(),
				SelectedWindow->WindowHandle, 0);
		}

		else
		{
			XMapWindow(WindowManager::GetDisplay(), SelectedWindow->WindowHandle);
		}
	}

	static void Linux_Maximize(TWindow* SelectedWindow)
	{
		XEvent l_Event;
		memset(&l_Event, 0, sizeof(l_Event));

		l_Event.xany.type = ClientMessage;
		l_Event.xclient.message_type = SelectedWindow->AtomState;
		l_Event.xclient.format = 32;
		l_Event.xclient.window = SelectedWindow->WindowHandle;
		l_Event.xclient.data.l[0] = (SelectedWindow->CurrentState == WINDOWSTATE_MAXIMIZED);
		l_Event.xclient.data.l[1] = SelectedWindow->AtomMaxVert;
		l_Event.xclient.data.l[2] = SelectedWindow->AtomMaxHorz;

		XSendEvent(WindowManager::GetDisplay(),
			XDefaultRootWindow(WindowManager::GetDisplay()),
			0, SubstructureNotifyMask, &l_Event);
	}

	static void Linux_Restore(TWindow* SelectedWindow)
	{
		XMapWindow(WindowManager::GetDisplay(), SelectedWindow->WindowHandle);
	}

	static void Linux_Focus(TWindow* SelectedWindow, bool NewFocusState)
	{
		if(NewState)
		{
			XMapWindow(WindowManager::GetDisplay(), SelectedWindow->WindowHandle);
		}

		else
		{
			XUnmapWindow(WindowManager::GetDisplay(), SelectedWindow->WindowHandle);
		}
	}

	static void Linux_SetMousePositionInWindow(TWindow* SelectedWindow)
	{
		XWarpPointer(
			WindowManager::GetInstance()->CurrentDisplay,
			SelectedWindow->WindowHandle, SelectedWindow->WindowHandle,
			SelectedWindow->Position[0], SelectedWindow->Position[1],
			SelectedWindow->Resolution[0], SelectedWindow->Resolution[1],
			SelectedWindow->MousePosition[0], SelectedWindow->MousePosition[1]);
	}

	static void Linux_SetWindowPosition(TWindow* Selected)
	{
		XWindowChanges l_WindowChanges;

		l_WindowChanges.x = Selected->Position[0];
		l_WindowChanges.y = Selected->Position[1];

		XConfigureWindow(
			WindowManager::GetDisplay(),
			Selected->WindowHandle, CWX | CWY, &l_WindowChanges);
	}

	static void Linux_SetWindowResolution(TWindow* Selected)
	{
		XResizeWindow(WindowManager::GetDisplay(),
			Selected->WindowHandle, Selected->Resolution[0], Selected->Resolution[1]);	
	}

	static void Linux_PollForEvents()
	{
		XNextEvent(GetInstance()->CurrentDisplay, &GetInstance()->Event);

		XEvent l_Event = GetInstance()->Event;
		TWindow* l_Window = GetWindowByEvent(l_Event);

		switch (l_Event.type)
		{
		case Expose:
		{
			break;
		}

		case DestroyNotify:
		{
			printf("blarg");

			if(IsValid(l_Window->DestroyedEvent))
			{
				l_Window->DestroyedEvent();
			}

			printf("Window was destroyed\n");		
			ShutdownWindow(l_Window);

			break;
		}

		/*case CreateNotify:
		{	
		printf("Window was created\n");
		l_Window->InitializeGL();

		if(IsValid(l_Window->m_OnCreated))
		{
		l_Window->m_OnCreated();
		}

		break;
		}*/

		case KeyPress:
		{			
			GLuint l_FunctionKeysym = XKeycodeToKeysym(
				GetInstance()->CurrentDisplay, l_Event.xkey.keycode, 1);

			if(l_FunctionKeysym <= 255)
			{
				l_Window->Keys[l_FunctionKeysym] = KEYSTATE_DOWN;	
				if(IsValid(l_Window->KeyEvent))
				{
					l_Window->KeyEvent(l_FunctionKeysym, KEYSTATE_DOWN);
				}
			}

			else
			{
				l_Window->Keys[Linux_TranslateKey(l_FunctionKeysym)] = KEYSTATE_DOWN;

				if(IsValid(l_Window->KeyEvent))
				{
					l_Window->KeyEvent(Linux_TranslateKey(l_FunctionKeysym),  KEYSTATE_DOWN);
				}
			}

			break;
		}

		case KeyRelease:
		{
			GLboolean l_IsRetriggered = GL_FALSE;
			if(XEventsQueued(GetInstance()->CurrentDisplay, QueuedAfterReading))
			{
				XEvent l_NextEvent;
				XPeekEvent(GetInstance()->CurrentDisplay, &l_NextEvent);

				if(l_NextEvent.type == KeyPress && 
					l_NextEvent.xkey.time == l_Event.xkey.time && 
					l_NextEvent.xkey.keycode == l_Event.xkey.keycode)
				{
					XNextEvent(GetInstance()->CurrentDisplay, &l_Event);
					l_IsRetriggered = GL_TRUE;
				}
			}

			if(!l_IsRetriggered)
			{
				GLuint l_FunctionKeysym = XKeycodeToKeysym(GetInstance()->CurrentDisplay,
					l_Event.xkey.keycode, 1);

				if(l_FunctionKeysym <= 255)
				{
					l_Window->Keys[l_FunctionKeysym] = KEYSTATE_UP;

					if(IsValid(l_Window->KeyEvent))
					{
						l_Window->KeyEvent(l_FunctionKeysym, KEYSTATE_UP);
					}
				}

				else
				{
					l_Window->Keys[Linux_TranslateKey(l_FunctionKeysym)] = KEYSTATE_UP;

					if(IsValid(l_Window->KeyEvent))
					{
						l_Window->KeyEvent(Linux_TranslateKey(l_FunctionKeysym), KEYSTATE_UP);
					}
				}

				if(IsValid(l_Window->KeyEvent))
				{
					l_Window->KeyEvent(Linux_TranslateKey(l_FunctionKeysym), KEYSTATE_UP);
				}
			}

			break;	
		}

		case ButtonPress:
		{			
			switch(l_Event.xbutton.button)
			{
			case 1:
			{
				l_Window->MouseButton[MOUSE_LEFTBUTTON] = MOUSE_BUTTONDOWN;	

				if(IsValid(l_Window->MouseButtonEvent))
				{
					l_Window->MouseButtonEvent(MOUSE_LEFTBUTTON, MOUSE_BUTTONDOWN);
				}
				break;
			}

			case 2:
			{
				l_Window->MouseButton[MOUSE_MIDDLEBUTTON] = MOUSE_BUTTONDOWN;

				if(IsValid(l_Window->MouseButtonEvent))
				{
					l_Window->MouseButtonEvent(MOUSE_MIDDLEBUTTON, MOUSE_BUTTONDOWN);
				}
				break;
			}

			case 3:
			{
				l_Window->MouseButton[MOUSE_RIGHTBUTTON] = MOUSE_BUTTONDOWN;

				if(IsValid(l_Window->MouseButtonEvent))
				{
					l_Window->MouseButtonEvent(MOUSE_RIGHTBUTTON, MOUSE_BUTTONDOWN);
				}
				break;
			}

			case 4:
			{
				l_Window->MouseButton[MOUSE_SCROLL_UP] = MOUSE_BUTTONDOWN;

				if(IsValid(l_Window->MouseWheelEvent))
				{
					l_Window->MouseWheelEvent(MOUSE_SCROLL_DOWN);
				}
				break;
			}

			case 5:
			{
				l_Window->MouseButton[MOUSE_SCROLL_DOWN] = MOUSE_BUTTONDOWN;

				if(IsValid(l_Window->MouseWheelEvent))
				{
					l_Window->MouseWheelEvent(MOUSE_SCROLL_DOWN);
				}
				break;
			}

			default:
			{
				//need to add more mmouse buttons 
				break;
			}
			}

			break;
		}

		case ButtonRelease:
		{
			switch(l_Event.xbutton.button)
			{
			case 1:
			{
				//the left mouse button was released
				l_Window->MouseButton[MOUSE_LEFTBUTTON] = MOUSE_BUTTONUP;

				if(IsValid(l_Window->MouseButtonEvent))
				{
					l_Window->MouseButtonEvent(MOUSE_LEFTBUTTON, MOUSE_BUTTONUP);
				}
				break;
			}

			case 2:
			{
				//the middle mouse button was released
				l_Window->MouseButton[MOUSE_MIDDLEBUTTON] = MOUSE_BUTTONUP;

				if(IsValid(l_Window->MouseButtonEvent))
				{
					l_Window->MouseButtonEvent(MOUSE_MIDDLEBUTTON, MOUSE_BUTTONUP);
				}
				break;
			}

			case 3:
			{
				//the right mouse button was released
				l_Window->MouseButton[MOUSE_RIGHTBUTTON] = MOUSE_BUTTONUP;

				if(IsValid(l_Window->MouseButtonEvent))
				{
					l_Window->MouseButtonEvent(MOUSE_RIGHTBUTTON, MOUSE_BUTTONUP);
				}
				break;
			}

			case 4:
			{
				//the mouse wheel was scrolled up
				l_Window->MouseButton[MOUSE_SCROLL_UP] = MOUSE_BUTTONDOWN;
				break;
			}

			case 5:
			{
				//the mouse wheel wasscrolled down
				l_Window->MouseButton[MOUSE_SCROLL_DOWN] = MOUSE_BUTTONDOWN;
				break;
			}

			default:
			{
				//need to add more mouse buttons
				break;
			}
			}
			break;
		}

		//when the mouse/pointer device is moved
		case MotionNotify:
		{ 
			//set the windows mouse position to match the event
			l_Window->MousePosition[0] = 
				l_Event.xmotion.x;

			l_Window->MousePosition[1] = 
				l_Event.xmotion.y;

			///set the screen mouse position to match the event
			GetInstance()->ScreenMousePosition[0] = l_Event.xmotion.x_root;
			GetInstance()->ScreenMousePosition[1] = l_Event.xmotion.y_root;

			if(IsValid(l_Window->MouseMoveEvent))
			{
				l_Window->MouseMoveEvent(l_Event.xmotion.x, 
					l_Event.xmotion.y, l_Event.xmotion.x_root, 
					l_Event.xmotion.y_root);
			}	
			break;
		}

		//when the window goes out of focus
		case FocusOut:
		{
			l_Window->InFocus = GL_FALSE;
			if(IsValid(l_Window->FocusEvent))
			{
				l_Window->FocusEvent(
					l_Window->InFocus);
			}
			break;
		}

		//when the window is back in focus (use to call restore callback?)
		case FocusIn:
		{
			l_Window->InFocus = GL_TRUE;

			if(IsValid(l_Window->FocusEvent))
			{
				l_Window->FocusEvent(l_Window->InFocus);
			}
			break;
		}

		//when a request to resize the window is made either by 
		//dragging out the window or programmatically
		case ResizeRequest:
		{			
			l_Window->Resolution[0] = l_Event.xresizerequest.width;
			l_Window->Resolution[1] = l_Event.xresizerequest.height;

			glViewport(0, 0,
				l_Window->Resolution[0],
				l_Window->Resolution[1]);

			if(IsValid(l_Window->ResizeEvent))
			{
				l_Window->ResizeEvent(l_Event.xresizerequest.width, 
						l_Event.xresizerequest.height);
			}

			break;
		}

		//when a request to configure the window is made
		case ConfigureNotify:
		{
			glViewport(0, 0, l_Event.xconfigure.width,
				l_Event.xconfigure.height);

			//check if window was resized
			if((GLuint)l_Event.xconfigure.width != l_Window->Resolution[0] 
				|| (GLuint)l_Event.xconfigure.height != l_Window->Resolution[1])
			{
				if(IsValid(l_Window->ResizeEvent))
				{
					l_Window->ResizeEvent(l_Event.xconfigure.width, l_Event.xconfigure.height);
				}

				l_Window->Resolution[0] = l_Event.xconfigure.width;
				l_Window->Resolution[1] = l_Event.xconfigure.height;
			}

			//check if window was moved
			if((GLuint)l_Event.xconfigure.x != l_Window->Position[0]
				|| (GLuint)l_Event.xconfigure.y != l_Window->Position[1])
			{
				if(IsValid(l_Window->MovedEvent))
				{
					l_Window->MovedEvent(l_Event.xconfigure.x, l_Event.xconfigure.y);
				}

				l_Window->Position[0] = l_Event.xconfigure.x;
				l_Window->Position[1] = l_Event.xconfigure.y;
			}
			break;
		}

		case PropertyNotify:
		{
			//this is needed in order to read from the windows WM_STATE Atomic
			//to determine if the property notify event was caused by a client
			//iconify event(minimizing the window), a maximise event, a focus 
			//event and an attention demand event. NOTE these should only be 
			//for eventts that are not triggered programatically 

			Atom l_Type;
			GLint l_Format;
			ulong l_NumItems, l_BytesAfter;
			unsigned char* l_Properties = nullptr;

			XGetWindowProperty(WindowManager::GetDisplay(), l_Event.xproperty.window, 
				l_Window->AtomState, 
				0, LONG_MAX, GL_FALSE, AnyPropertyType, 
				&l_Type, &l_Format, &l_NumItems, &l_BytesAfter, 
				&l_Properties);

			if(l_Properties && (l_Format == 32))
			{
				//go through each property and match it to an existing Atomic state
				for(GLuint l_CurrentItem = 0; l_CurrentItem < l_NumItems; l_CurrentItem++)
				{
					long l_Property = ((long*)(l_Properties))[l_CurrentItem];	

					if(l_Property == l_Window->AtomHidden)
					{
						//window was minimized
						if(IsValid(l_Window->MinimizedEvent))
						{
							//if the minimized callback for the window was set							
							l_Window->MinimizedEvent();
						}
					}

					if(l_Property == l_Window->AtomMaxVert ||
						l_Property == l_Window->AtomMaxVert)
					{
						//window was maximized
						if(IsValid(l_Window->MaximizedEvent))
						{
							//if the maximized callback for the window was set
							l_Window->MaximizedEvent();
						}
					}

					if(l_Property == l_Window->AtomFocused)
					{
						//window is now in focus. we can ignore this is as FocusIn/FocusOut does this anyway
					}

					if(l_Property == l_Window->AtomDemandsAttention)
					{
						//the window demands attention like a celebrity
						printf("window demands attention \n");
					}
				}
			}

			break;
		}

		case GravityNotify:
		{
			//this is only supposed to pop up when the parent of this window(if any) has something happen
			//to it so that this window can react to said event as well.
			break;
		}

		//check for events that were created by the TinyWindow manager
		case ClientMessage:
		{
			const char* l_AtomName = XGetAtomName(WindowManager::GetDisplay(), l_Event.xclient.message_type);
			if(IsValid(l_AtomName))
			{
				printf("%s\n", l_AtomName);
			}

			if ((Atom)l_Event.xclient.data.l[0] == l_Window->AtomClose)
			{
				printf("window closed\n");
				l_Window->ShouldClose = GL_TRUE;
				l_Window->DestroyedEvent();
				ShutdownWindow(l_Window);
				
				break;
			}

			if ((Atom)l_Event.xclient.data.l[1] == l_Window->AtomFullScreen)
			{
				break;
			}
			break;
		}

		default:
		{
			break;
		}
	}
	}
	//the linux methos of setting the mouse position on the screen
	static void Linux_SetMousePositionInScreen(GLuint X, GLuint Y)
	{
		XWarpPointer(GetInstance()->CurrentDisplay, None,
			XDefaultRootWindow(GetInstance()->CurrentDisplay), 0, 0, 
			GetScreenResolution()[0], 
			GetScreenResolution()[1], 
			X, Y);
	}

	//get pointer to X11 display
	static Display* GetDisplay()
	{
		return GetInstance()->CurrentDisplay;
	}
	//debugging. used to determine what type of event was generated
	static const char* Linux_GetEventType(XEvent Event)
	{
		switch (Event.type)
		{
		case MotionNotify:
		{
			return "Motion Notify Event\n";
		}

		case ButtonPress:
		{
			return "Button Press Event\n";
		}

		case ButtonRelease:
		{
			return "Button Release Event\n";
		}

		case ColormapNotify:
		{
			return "Color Map Notify event \n";
		}

		case EnterNotify:
		{
			return "Enter Notify Event\n";
		}

		case LeaveNotify:
		{
			return "Leave Notify Event\n";
		}

		case Expose:
		{
			return "Expose Event\n";
		}

		case GraphicsExpose:
		{
			return "Graphics expose event\n";
		}

		case NoExpose:
		{
			return "No Expose Event\n";
		}

		case FocusIn:
		{
			return "Focus In Event\n";
		}

		case FocusOut:
		{
			return "Focus Out Event\n";
		}

		case KeymapNotify:
		{
			return "Key Map Notify Event\n";
		}

		case KeyPress:
		{
			return "Key Press Event\n";
		}

		case KeyRelease:
		{
			return "Key Release Event\n";
		}

		case PropertyNotify:
		{
			return "Property Notify Event\n";
		}

		case ResizeRequest:
		{
			return "Resize Property Event\n";
		}

		case CirculateNotify:
		{
			return "Circulate Notify Event\n";
		}

		case ConfigureNotify:
		{
			return "configure Notify Event\n";
		}

		case DestroyNotify:
		{
			return "Destroy Notify Request\n";
		}

		case GravityNotify:
		{
			return "Gravity Notify Event \n";
		}

		case MapNotify:
		{
			return "Map Notify Event\n";
		}

		case ReparentNotify:
		{
			return "Reparent Notify Event\n";
		}

		case UnmapNotify:
		{
			return "Unmap notify event\n";
		}

		case MapRequest:
		{
			return "Map request event\n";
		}

		case ClientMessage:
		{
			return "Client Message Event\n";
		}

		case MappingNotify:
		{
			return "Mapping notify event\n";
		}

		case SelectionClear:
		{
			return "Selection Clear event\n";
		}

		case SelectionNotify:
		{
			return "Selection Notify Event\n";
		}

		case SelectionRequest:
		{
			return "Selection Request event\n";
		}

		case VisibilityNotify:
		{
			return "Visibility Notify Event\n";
		}

		default:
		{
			return 0;
		}
		}
	}

	//translate keys from X keys to TinyWindow Keys
	static GLuint Linux_TranslateKey(GLuint KeySym)
	{
		switch (KeySym)
		{
		case XK_Escape:
		{
			return KEY_ESCAPE;
		}

		case XK_Home:
		{
			return KEY_HOME;
		}

		case XK_Left:
		{
			return KEY_ARROW_LEFT;
		}

		case XK_Right:
		{
			return KEY_ARROW_RIGHT;
		}

		case XK_Up:
		{
			return KEY_ARROW_UP;
		}

		case XK_Down:
		{
			return KEY_ARROW_DOWN;
		}

		case XK_Page_Up:
		{
			return KEY_PAGEUP;
		}

		case XK_Page_Down:
		{
			return KEY_PAGEDOWN;
		}

		case XK_End:
		{
			return KEY_END;
		}

		case XK_Print:
		{
			return KEY_PRINTSCREEN;
		}

		case XK_Insert:
		{
			return KEY_INSERT;
		}

		case XK_Num_Lock:
		{
			return KEY_NUMLOCK;
		}

		case XK_KP_Multiply:
		{
			return KEY_KEYPAD_MULTIPLY;
		}

		case XK_KP_Add:
		{
			return KEY_KEYPAD_ADD;
		}

		case XK_KP_Subtract:
		{
			return KEY_KEYPAD_SUBTRACT;
		}

		case XK_KP_Decimal:
		{
			return KEY_KEYPAD_PERIOD;
		}

		case XK_KP_Divide:
		{
			return KEY_KEYPAD_DIVIDE;
		}

		case XK_KP_0:
		{
			return KEY_KEYPAD_0;
		}

		case XK_KP_1:
		{
			return KEY_KEYPAD_1;
		}

		case XK_KP_2:
		{
			return KEY_KEYPAD_2;
		}

		case XK_KP_3:
		{
			return KEY_KEYPAD_3;
		}

		case XK_KP_4:
		{
			return KEY_KEYPAD_4;
		}

		case XK_KP_5:
		{
			return KEY_KEYPAD_5;
		}

		case XK_KP_6:
		{
			return KEY_KEYPAD_6;
		}

		case XK_KP_7:
		{
			return KEY_KEYPAD_7;
		}

		case XK_KP_8:
		{
			return KEY_KEYPAD_8;
		}

		case XK_KP_9:
		{
			return KEY_KEYPAD_9;
		}

		case XK_F1:
		{
			return KEY_F1;
		}

		case XK_F2:
		{
			return KEY_F2;
		}

		case XK_F3:
		{
			return KEY_F3;
		}

		case XK_F4:
		{
			return KEY_F4;
		}

		case XK_F5:
		{
			return KEY_F5;
		}

		case XK_F6:
		{
			return KEY_F6;
		}

		case XK_F7:
		{
			return KEY_F7;
		}

		case XK_F8:
		{
			return KEY_F8;
		}

		case XK_F9:
		{
			return KEY_F9;
		}

		case XK_F10:
		{
			return KEY_F10;
		}

		case XK_F11:
		{
			return KEY_F11;
		}

		case XK_F12:
		{
			return KEY_F12;
		}

		case XK_Shift_L:
		{
			return KEY_LEFTSHIFT;
		}

		case XK_Shift_R:
		{
			return KEY_RIGHTSHIFT;
		}

		case XK_Control_R:
		{
			return KEY_RIGHTCONTROL;
		}

		case XK_Control_L:
		{
			return KEY_LEFTCONTROL;
		}

		case XK_Caps_Lock:
		{
			return KEY_CAPSLOCK;
		}

		case XK_Alt_L:
		{
			return KEY_LEFTALT;
		}

		case XK_Alt_R:
		{
			return KEY_RIGHTALT;
		}

		default:
		{
			return 0;
		}
		}
	}

	Display* CurrentDisplay;
	XEvent Event;
#endif
};

WindowManager* WindowManager::Instance = nullptr;

#endif

#ifndef TINYWINDOW_H
#define TINYWINDOW_H

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
#define CURRENT_OS_WINDOWS
#include <Windows.h>
#include <gl/GL.h>
#include <io.h>
#include <fcntl.h>

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
#endif

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <limits.h>
#include <string.h>

#define KEYSTATE_DOWN 1 /**< the key is currently up */
#define KEYSTATE_UP 0   /**< the key is currently down */

#define KEY_ERROR -1	/**< the key pressed is considered invalid */

#define KEY_FIRST 256 + 1   /**< the fist key that is not a char */
#define KEY_F1 KEY_FIRST	/**< the F1 key */
#define KEY_F2 KEY_FIRST + 1	/**< the F2 key */
#define KEY_F3 KEY_FIRST + 2	/**< the F3 key */
#define KEY_F4 KEY_FIRST + 3	/**< the F4 key */
#define KEY_F5 KEY_FIRST + 4	/**< the F5 key */
#define KEY_F6 KEY_FIRST + 5	/**< the F6 key */
#define KEY_F7 KEY_FIRST + 6	/**< the F7 key */
#define KEY_F8 KEY_FIRST + 7	/**< the F8 key */
#define KEY_F9 KEY_FIRST + 8	/**< the F9 key */
#define KEY_F10 KEY_FIRST + 9   /**< the F10 key */
#define KEY_F11 KEY_FIRST + 10  /**< the F11 key */
#define KEY_F12 KEY_FIRST + 11  /**< the F12 key */
#define KEY_CAPSLOCK KEY_FIRST + 12 /**< the CapsLock key */
#define KEY_LEFTSHIFT KEY_FIRST + 13	/**< the left Shift key */
#define KEY_RIGHTSHIFT KEY_FIRST + 14   /**< the right Shift key */
#define KEY_LEFTCONTROL KEY_FIRST + 15  /**< the left Control key */
#define KEY_RIGHTCONTROL KEY_FIRST + 16 /**< the right Control key */
#define KEY_LEFTWINDOW KEY_FIRST + 17   /**< the left Window key */
#define KEY_RIGHTWINDOW KEY_FIRST + 18  /**< the right Window key */
#define KEY_LEFTALT KEY_FIRST + 19  /**< the left Alternate key */
#define KEY_RIGHTALT KEY_FIRST + 20 /**< the right Alternate key*/
#define KEY_ENTER KEY_FIRST + 21	/**< the Enter/Return key */
#define KEY_PRINTSCREEN KEY_FIRST + 22  /**< the PrintScreen key */
#define KEY_SCROLLLOCK KEY_FIRST + 23   /**< the ScrollLock key */
#define KEY_NUMLOCK KEY_FIRST + 24  /**< the NumLock key */
#define KEY_PAUSE KEY_FIRST + 25	/**< the pause/break key */
#define KEY_INSERT KEY_FIRST + 26   /**< the insert key */
#define KEY_HOME KEY_FIRST + 27 /**< the Home key */
#define KEY_END KEY_FIRST + 28  /**< the End key */
#define KEY_PAGEUP KEY_FIRST + 28   /**< the PageUp key */
#define KEY_PAGEDOWN KEY_FIRST + 30 /**< the PageDown key */
#define KEY_ARROW_DOWN KEY_FIRST + 31   /**< the ArrowDown key */
#define KEY_ARROW_UP KEY_FIRST + 32 /**< the ArrowUp key */
#define KEY_ARROW_LEFT KEY_FIRST + 33   /**< the ArrowLeft key */
#define KEY_ARROW_RIGHT KEY_FIRST + 34  /**< the ArrowRight key */
#define KEY_KEYPAD_DIVIDE KEY_FIRST + 35	/**< the KeyPad Divide key */
#define KEY_KEYPAD_MULTIPLY KEY_FIRST + 36  /**< the Keypad Multiply key */
#define KEY_KEYPAD_SUBTRACT KEY_FIRST + 37  /**< the Keypad Subtract key */
#define KEY_KEYPAD_ADD KEY_FIRST + 38   /**< the Keypad  Add key*/
#define KEY_KEYPAD_ENTER KEY_FIRST + 39 /**< the Keypad Enter key */
#define KEY_KEYPAD_PERIOD KEY_FIRST + 40	/**< the Keypad Period/Decimal key */
#define KEY_KEYPAD_0 KEY_FIRST + 41 /**< the Keypad 0 key */
#define KEY_KEYPAD_1 KEY_FIRST + 42 /**< the Keypad 1 key */
#define KEY_KEYPAD_2 KEY_FIRST + 43 /**< the Keypad 2 key */
#define KEY_KEYPAD_3 KEY_FIRST + 44 /**< the Keypad 3 key */
#define KEY_KEYPAD_4 KEY_FIRST + 45 /**< the Keypad 4 key */
#define KEY_KEYPAD_5 KEY_FIRST + 46 /**< the Keypad 5 key */
#define KEY_KEYPAD_6 KEY_FIRST + 47 /**< the Keypad 6 key */
#define KEY_KEYPAD_7 KEY_FIRST + 48 /**< the Keypad 7 key */
#define KEY_KEYPAD_8 KEY_FIRST + 49 /**< the keypad 8 key */
#define KEY_KEYPAD_9 KEY_FIRST + 50 /**< the Keypad 9 key */
#define KEY_BACKSPACE KEY_FIRST + 51	/**< the Backspace key */
#define KEY_TAB KEY_FIRST + 52  /**< the Tab key */
#define KEY_DELETE KEY_FIRST + 53   /**< the Delete key */
#define KEY_ESCAPE KEY_FIRST + 54   /**< the Escape key */
#define KEY_LAST KEY_ESCAPE   /**< the last key to be supported */

#define MOUSE_BUTTONUP 0	/**< the mouse button is currently up */
#define MOUSE_BUTTONDOWN 1  /**< the mouse button is currently down */

#define MOUSE_LEFTBUTTON 0  /**<  the left mouse button*/
#define MOUSE_RIGHTBUTTON 1 /**< the right mouse button */
#define MOUSE_MIDDLEBUTTON 2	/**< the middle mouse button / ScrollWheel */
#define MOUSE_LAST MOUSE_MIDDLEBUTTON + 1   /**< the last mouse button to be supported */

#define MOUSE_SCROLL_DOWN 0 /**< the mouse wheel up */
#define MOUSE_SCROLL_UP 1   /**< the mouse wheel down */

#define WINDOWSTYLE_BARE 1  /**< the window has no decorators but the window border and title bar*/
#define WINDOWSTYLE_DEFAULT 2   /**< the default window style for the respective platform */
#define WINDOWSTYLE_POPUP 3 /**< the window has no decorators*/

#define WINDOWSTATE_NORMAL 0	/**< the window is in its default state */
#define WINDOWSTATE_MAXIMIZED 1 /**< the window is currently maximized */
#define WINDOWSTATE_MINIMIZED 2 /**< the window is currently minimized */
#define WINDOWSTATE_FULLSCREEN 3	/**< the window is currently full screen */

#define DECORATOR_TITLEBAR 0x01 /**< The titlebar decoration of the window */
#define DECORATOR_ICON 0x02 /**< the icon decoration of the window*/
#define DECORATOR_BORDER 0x04 /**< the border decoration of the window*/
#define DECORATOR_MINIMIZEBUTTON 0x08 /**<the minimize button decoration of the window */
#define DECORATOR_MAXIMIZEBUTTON 0x010 /**< the maximize button decoration pf the window */
#define DECORATOR_CLOSEBUTTON 0x20 /**< the close button decoration of the window*/
#define DECORATOR_SIZEABLEBORDER 0x40 /**< the sizeable border decoration of the window*/

#define LINUX_DECORATOR_BORDER 1L << 1
#define LINUX_DECORATOR_MOVE 1L << 2
#define LINUX_DECORATOR_MINIMIZE 1L << 3
#define LINUX_DECORATOR_MAXIMIZE 1L << 4
#define LINUX_DECORATOR_CLOSE 1L << 5

#define FOUNDATION_ERROR 0
#define FOUNDATION_OKAY 1

#define ERROR_NOCONTEXT 0 /**< if a window tries to use a graphical function without a context */
#define ERROR_INVALIDWINDOWNAME 1 /**< if an invalid window name was given*/
#define ERROR_INVALIDWINDOWINDEX 2 /**< if an invalid window index was given*/
#define ERROR_INVALIDWINDOWSTATE 3 /**< if an invalid window state was given*/
#define ERROR_INVALIDRESOLUTION 4 /**< if an invalid window resolution was given */
#define ERROR_INVALIDCONTEXT 5 /**< if the OpenGL context for the window is invalid*/
#define ERROR_EXISTINGCONTEXT 6 /**< if the window already has an OpenGL context*/
#define ERROR_NOTINITIALIZED 7 /**< if the window is being used without being initialized*/
#define ERROR_ALREADYINITIALIZED 8 /**< if the window was already initialized*/
#define ERROR_INVALIDTITLEBAR 9 /**< if the Title-bar text given was invalid*/
#define ERROR_INVALIDEVENT 10 /**< if the given event callback was invalid*/
#define ERROR_WINDOWNOTFOUND 11 /**< if the window was not found in the window manager*/
#define ERROR_INVALIDWINDOWSTYLE 12 /**< if the window style gives is invalid*/
#define ERROR_INVALIDWINDOW 13 
#define ERROR_FUNCTIONNOTIMPLEMENTED 14 /**< if the function has not yet been implemented in the current version of the API*/
#define ERROR_LINUX_CANNOTCONNECTXSERVER 15 /**< Linux: if cannot connect to X11 server*/
#define ERROR_LINUX_INVALIDVISUALINFO 16 /**< Linux: if visual information given was invalid*/
#define ERROR_LINUX_CANNOTCREATEWINDOW 17 /**< Linux: when X11 fails to create a new window*/
#define ERROR_LINUX_FUNCTIONNOTIMPLEMENTED 18 /**< Linux: when the function has not yet been implemented on the Linux in the current version of the API*/
#define ERROR_WINDOWS_CANNOTCREATEWINDOW 19 /**< Windows: when Win32 cannot create a window*/
#define ERROR_WINDOWS_CANNOTINITIALIZE 20 /**< Windows: when Win32 cannot initialize */
#define ERROR_WINDOWS_FUNCTIONNOTIMPLEMENTED 21 /**< Windows: when a function has yet to be implemented on the Windows platform in the current version of the API */

#define WARNING_NOTCURRENTCONTEXT 0 /**< if using calling member functions of a window that is not the current window being drawn to*/
#define WARNING_NOGLEXTENSIONS 1 /**< if your computer does not support any OpenGL extensions*/

#define LINUX_FUNCTION 1
#define LINUX_DECORATOR 2

typedef void(*OnKeyEvent)(GLuint Key, GLboolean KeyState);	/**<To be called when a key event has occurred*/
typedef void(*OnMouseButtonEvent)(GLuint Button, GLboolean ButtonState);	/**<To be called when a Mouse button event has occurred*/
typedef void(*OnMouseWheelEvent)(GLuint WheelDirection);  /**<To be called when a mouse wheel event has occurred.*/
typedef void(*OnDestroyedEvent)(); /**<To be called when the window is being destroyed*/
typedef void(*OnMaximizedEvent)(); /**<To be called when the window has been maximized*/
typedef void(*OnMinimizedEvent)(); /**<To be called when the window has been minimized*/
//typedef void (*OnRestoredEvent)(); //only really works on windows, Linux doesn't even have an atomic for it. might need to remove
typedef void(*OnFocusEvent)(GLboolean InFocus);	/**<To be called when the window has gained event focus*/
typedef void(*OnMovedEvent)(GLuint X, GLuint Y);   /**<To be called when the window has been moved*/
typedef void(*OnResizeEvent)(GLuint Width, GLuint Height); /**<To be called when the window has been resized*/
typedef void(*OnMouseMoveEvent)(GLuint WindowX, GLuint WindowY, GLuint ScreenX, GLuint ScreenY);   /**<To be called when the mouse has been moved within the window*/

//print the warning message associated with the given warning number
static inline void PrintWarningMessage(GLuint WarningNumber)
{
	switch (WarningNumber)
	{
	case WARNING_NOGLEXTENSIONS:
	{
		printf("Warning: no OpenGL extensions available \n");
		break;
	}

	case WARNING_NOTCURRENTCONTEXT:
	{
		printf("Warning: window not the current OpenGL context being rendered to \n");
		break;
	}

	default:
	{
		printf("Warning: unspecified warning \n");
		break;
	}
	}
}

//print out the error associated with the given error number
static void PrintErrorMessage(GLuint ErrorNumber)
{
	switch (ErrorNumber)
	{
	case ERROR_NOCONTEXT:
	{
		printf("Error: An OpenGL context must first be created(initialize the window) \n");
		break;
	}

	case ERROR_INVALIDWINDOWNAME:
	{
		printf("Error: invald window name \n");
		break;
	}

	case ERROR_INVALIDWINDOWINDEX:
	{
		printf("Error: invalid window index \n");
		break;
	}

	case ERROR_INVALIDWINDOWSTATE:
	{
		printf("Error: invalid window state \n");
		break;
	}

	case ERROR_INVALIDRESOLUTION:
	{
		printf("Error: invalid resolution \n");
		break;
	}

	case ERROR_INVALIDCONTEXT:
	{
		printf("Error: Failed to create OpenGL context \n");
		break;
	}

	case ERROR_EXISTINGCONTEXT:
	{
		printf("Error: context already created \n");
		break;
	}

	case ERROR_NOTINITIALIZED:
	{
		printf("Error: Window manager not initialized \n");
		break;
	}

	case ERROR_ALREADYINITIALIZED:
	{
		printf("Error: window has already been initialized \n");
		break;
	}

	case ERROR_INVALIDTITLEBAR:
	{
		printf("Error: invalid title bar name (cannot be null or nullptr) \n");
		break;
	}

	case ERROR_INVALIDEVENT:
	{
		printf("Error: invalid event callback given \n");
		break;
	}

	case ERROR_WINDOWNOTFOUND:
	{
		printf("Error: window was not found \n");
		break;
	}

	case ERROR_INVALIDWINDOWSTYLE:
	{
		printf("Error: invalid window style given \n");
		break;
	}

	case ERROR_INVALIDWINDOW:
	{
		printf("Error: invalid window given \n");
		break;
	}

	case ERROR_FUNCTIONNOTIMPLEMENTED:
	{
		printf("Error: I'm sorry but this function has not been implemented yet :( \n");
		break;
	}

	case ERROR_LINUX_CANNOTCONNECTXSERVER:
	{
		printf("Error: cannot connect to X server \n");
		break;
	}

	case ERROR_LINUX_INVALIDVISUALINFO:
	{
		printf("Error: Invalid visual information given \n");
		break;
	}

	case ERROR_LINUX_CANNOTCREATEWINDOW:
	{
		printf("Error: failed to create window \n");
		break;
	}

	case ERROR_LINUX_FUNCTIONNOTIMPLEMENTED:
	{
		printf("Error: function not implemented on linux platform yet. sorry :( \n");
		break;
	}

	case ERROR_WINDOWS_CANNOTCREATEWINDOW:
	{
		printf("Error: failed to create window \n");
		break;
	}

	case ERROR_WINDOWS_FUNCTIONNOTIMPLEMENTED:
	{
		printf("Error: function not implemented on Windows platform yet. sorry ;( \n");
		break;
	}

	default:
	{
		printf("Error: unspecified Error \n");
		break;
	}
	}
}

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
#if defined(CURRENT_OS_WINDOWS)
			for each(auto CurrentWindow in GetInstance()->Windows)
			{
				delete CurrentWindow;
			}
#endif

#if defined(CURRENT_OS_LINUX)
			for (auto CurrentWindow : GetInstance()->Windows)
			{
				delete CurrentWindow;
			}
#endif
			GetInstance()->Windows.clear();
		}
	}

	/**
	 * use this to shutdown the window manager when your program is finished
	*/
	 static inline void ShutDown()
	{
#if defined(CURRENT_OS_WINDOWS)
		for each (auto Iter in GetInstance()->Windows)
		{
			delete Iter;
		}
#endif

#if defined(CURRENT_OS_LINUX)

		for (auto CurrentWindow : GetInstance()->Windows)
		{
			delete CurrentWindow;
		}

		XCloseDisplay(GetInstance()->CurrentDisplay);
#endif

		GetInstance()->Windows.clear();
		delete Instance;
	}

	/**
	 *use this to add a window to the manager. returns a pointer to the manager which allows for the easy creation of multiple windows
	 */
	static WindowManager* AddWindow(const char*  WindowName, GLuint Width = 1280, GLuint Height = 720, GLuint ColourBits = 8,
		GLuint DepthBits = 24, GLuint StencilBits = 8)
	{
		if (GetInstance()->IsInitialized())
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
			return nullptr;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return nullptr;
	}

	/**
	 * return the total amount of windows the manager has
	 */
	static GLuint GetNumWindows()
	{
		if (GetInstance()->IsInitialized())
		{
			return GetInstance()->Windows.size();
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * return the mouse position in screen co-ordinates
	 */
	static inline GLboolean GetMousePositionInScreen(GLuint& X, GLuint& Y)
	{
		if (GetInstance()->IsInitialized())
		{
			X = GetInstance()->ScreenMousePosition[0];
			Y = GetInstance()->ScreenMousePosition[1];
			return FOUNDATION_OKAY;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * return the mouse position in screen co-ordinates
	 */
	static GLuint* GetMousePositionInScreen()
	{
		if (GetInstance()->IsInitialized())
		{
			return GetInstance()->ScreenMousePosition;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return nullptr;
	}
	/**
	 * set the position of the mouse cursor relative to screen co-ordinates
	 */
	static inline GLboolean SetMousePositionInScreen(GLuint X, GLuint Y)
	{
		if (GetInstance()->IsInitialized())
		{
			GetInstance()->ScreenMousePosition[0] = X;
			GetInstance()->ScreenMousePosition[1] = Y;

#if defined(CURRENT_OS_WINDOWS)
			Windows_SetMousePositionInScreen();
#endif

#if defined(CURRENT_OS_LINUX)
			Linux_SetMousePositionInScreen(X, Y);
#endif
			return FOUNDATION_OKAY;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * return the Resolution of the current screen
	 */
	static GLuint* GetScreenResolution()
	{
		if (GetInstance()->IsInitialized())
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

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return nullptr;
	}
	/**
	 * return the Resolution of the current screen
	 */
	static inline GLboolean GetScreenResolution(GLuint& Width, GLuint& Height)
	{
		if (GetInstance()->IsInitialized())
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
			return FOUNDATION_OKAY;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * return the Resolution of the given window by setting width and height
	 */
	static inline GLboolean GetWindowResolution(const char* WindowName, GLuint& Width, GLuint& Height)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				Width = GetWindowByName(WindowName)->Resolution[0];
				Height = GetWindowByName(WindowName)->Resolution[1];
				return FOUNDATION_ERROR;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * return the Resolution of the given window by setting width and height
	 */
	static inline GLboolean GetWindowResolution(GLuint WindowIndex, GLuint& Width, GLuint& Height)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				Width = GetWindowByIndex(WindowIndex)->Resolution[0];
				Height = GetWindowByIndex(WindowIndex)->Resolution[1];

				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * return the Resolution of the given Window as an array of unsigned ints
	 */
	static GLuint* GetWindowResolution(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				return GetWindowByName(WindowName)->Resolution;
			}
			return nullptr;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return nullptr;
	}
	/**
	 * return the Resolution of the Given Window as an array of unsigned ints
	 */
	static GLuint* GetWindowResolution(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				return GetWindowByIndex(WindowIndex)->Resolution;
			}
			return nullptr;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return nullptr;
	}
	/**
	 * set the Size/Resolution of the given window
	 */
	static inline GLboolean SetWindowResolution(const char* WindowName, GLuint Width, GLuint Height)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->Resolution[0] = Width;
				GetWindowByName(WindowName)->Resolution[1] = Height;
#if defined(CURRENT_OS_WINDOWS)
				Windows_SetWindowResolution(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_SetWindowResolution(GetWindowByName(WindowName));
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}

		PrintErrorMessage(ERROR_INVALIDCONTEXT);
		return FOUNDATION_ERROR;
	}
	/**
	 * set the Size/Resolution of the given window
	 */
	static inline GLboolean SetWindowResolution(GLuint WindowIndex, GLuint Width, GLuint Height)
	{
		if (GetInstance()->IsInitialized())
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
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * return the Position of the given window relative to screen co-ordinates by setting X and Y
	 */ 
	static inline GLboolean GetWindowPosition(const char* WindowName, GLuint& X, GLuint& Y)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				X = GetWindowByName(WindowName)->Position[0];
				Y = GetWindowByName(WindowName)->Position[1];
				return FOUNDATION_OKAY;
			}

			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * return the Position of the given window relative to screen co-ordinates by setting X and Y
	 */
	static inline GLboolean GetWindowPosition(GLuint WindowIndex, GLuint& X, GLuint& Y)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				X = GetWindowByIndex(WindowIndex)->Position[0];
				Y = GetWindowByIndex(WindowIndex)->Position[1];
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * return the Position of the given window relative to screen co-ordinates as an array
	 */
	static GLuint* GetWindowPosition(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				return GetWindowByName(WindowName)->Position;
			}

			return nullptr;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return nullptr;
	}
	/**
	 * return the Position of the given window relative to screen co-ordinates as an array
	 */
	static GLuint* GetWindowPosition(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				return GetWindowByIndex(WindowIndex)->Position;
			}
			return nullptr;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return nullptr;
	}
	/**
	 * set the Position of the given window relative to screen co-ordinates
	 */
	static inline GLboolean SetWindowPosition(const char* WindowName, GLuint X, GLuint Y)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->Position[0] = X;
				GetWindowByName(WindowName)->Position[1] = Y;
#if defined(CURRENT_OS_WINDOWS)
				Windows_SetWindowPosition(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_SetWindowPosition(GetWindowByName(WindowName));
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * set the position of the given window relative to screen co-ordinates
	 */
	static inline GLboolean SetWindowPosition(GLuint WindowIndex, GLuint X, GLuint Y)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				GetWindowByIndex(WindowIndex)->Position[0] = X;
				GetWindowByIndex(WindowIndex)->Position[1] = Y;
#if defined(CURRENT_OS_WINDOWS)
				Windows_SetWindowPosition(GetWindowByIndex(WindowIndex));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_SetWindowPosition(GetWindowByIndex(WindowIndex));
#endif
				return FOUNDATION_OKAY;
			}
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * return the mouse Position relative to the given window's co-ordinates by setting X and Y
	 */
	static inline GLboolean GetMousePositionInWindow(const char* WindowName, GLuint& X, GLuint& Y)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				X = GetWindowByName(WindowName)->MousePosition[0];
				Y = GetWindowByName(WindowName)->MousePosition[1];
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * return the mouse position relative to the given window's co-ordinates by setting X and Y
	 */
	static inline GLboolean GetMousePositionInWindow(GLuint WindowIndex, GLuint& X, GLuint& Y)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				X = GetWindowByIndex(WindowIndex)->MousePosition[0];
				Y = GetWindowByIndex(WindowIndex)->MousePosition[1];
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * return the mouse Position relative to the given window's co-ordinates as an array
	 */
	static GLuint* GetMousePositionInWindow(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				return GetWindowByName(WindowName)->MousePosition;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return nullptr;
	}
	/**
	 * return the mouse Position relative to the given window's co-ordinates as an array
	 */
	static GLuint* GetMousePositionInWindow(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				return GetWindowByIndex(WindowIndex)->MousePosition;
			}
			return nullptr;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return nullptr;
	}
	/**
	 * set the mouse Position of the given window's co-ordinates
	 */
	static inline GLboolean SetMousePositionInWindow(const char* WindowName, GLuint X, GLuint Y)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->MousePosition[0] = X;
				GetWindowByName(WindowName)->MousePosition[1] = Y;
#if defined(CURRENT_OS_WINDOWS)
				Windows_SetMousePosition(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_SetMousePosition(GetWindowByName(WindowName));
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * set the mouse Position of the given window's co-ordinates
	 */
	static inline GLboolean SetMousePositionInWindow(GLuint WindowIndex, GLuint X, GLuint Y)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				GetWindowByIndex(WindowIndex)->MousePosition[0] = X;
				GetWindowByIndex(WindowIndex)->MousePosition[1] = Y;
#if defined(CURRENT_OS_WINDOWS)
				Windows_SetMousePosition(GetWindowByIndex(WindowIndex));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_SetMousePosition(GetWindowByIndex(WindowIndex));
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * returns the current state of the given key relative to the given window
	 */
	static GLboolean WindowGetKey(const char* WindowName, GLuint Key)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				return GetWindowByName(WindowName)->Keys[Key];
			}

			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * returns the current state of the given key relative to the given window
	 */
	static GLboolean WindowGetKey(GLuint WindowIndex, GLuint Key)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				return GetWindowByIndex(WindowIndex)->Keys[Key];
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * return whether the given window should be closing
	 */
	static GLboolean GetWindowShouldClose(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				return GetWindowByName(WindowName)->ShouldClose;
			}
			return FOUNDATION_ERROR;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * return whether the given window should be closing
	 */
	static GLboolean GetWindowShouldClose(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				return GetWindowByIndex(WindowIndex)->ShouldClose;
			}
			return FOUNDATION_ERROR;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * swap the draw buffers of the given window
	 */
	static inline GLboolean WindowSwapBuffers(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
#if defined(CURRENT_OS_WINDOWS)
				SwapBuffers(GetWindowByName(WindowName)->DeviceContextHandle);
#endif

#if defined(CURRENT_OS_LINUX)
				printf("%i\n", GetWindowByName(WindowName)->WindowHandle);
				glXSwapBuffers(GetDisplay(), GetWindowByName(WindowName)->WindowHandle);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * swap the draw buffers of the given window
	 */
	static inline GLboolean WindowSwapBuffers(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
#if defined(CURRENT_OS_WINDOWS)
				SwapBuffers(GetWindowByIndex(WindowIndex)->DeviceContextHandle);
#endif 

#if defined(CURRENT_OS_LINUX)
				glXSwapBuffers(GetDisplay(), GetWindowByIndex(WindowIndex)->WindowHandle);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * make the given window be the current OpenGL Context to be drawn to
	 */
	static inline GLboolean MakeWindowCurrentContext(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{

#if defined(CURRENT_OS_WINDOWS)
				wglMakeCurrent(GetWindowByName(WindowName)->DeviceContextHandle,
					GetWindowByName(WindowName)->GLRenderingContextHandle);
#endif

#if defined(CURRENT_OS_LINUX)
				glXMakeCurrent(GetDisplay(), GetWindowByName(WindowName)->WindowHandle,
					GetWindowByName(WindowName)->Context);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * make the given window be the current OpenGL Context to be drawn to
	 */
	static inline GLboolean MakeWindowCurrentContext(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
#if defined(CURRENT_OS_WINDOWS)
				wglMakeCurrent(GetWindowByIndex(WindowIndex)->DeviceContextHandle,
					GetWindowByIndex(WindowIndex)->GLRenderingContextHandle);
#endif

#if defined(CURRENT_OS_LINUX)
				glXMakeCurrent(GetDisplay(), GetWindowByIndex(WindowIndex)->WindowHandle,
					GetWindowByIndex(WindowIndex)->Context);
#endif
				return FOUNDATION_OKAY;
			}

			return FOUNDATION_ERROR;
		}

		PrintErrorMessage(ERROR_NOCONTEXT);
		return FOUNDATION_ERROR;
	}

	/**
	 * return whether the given window is in fullscreen mode
	 */
	static GLboolean GetWindowIsFullScreen(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				return (GetWindowByName(WindowName)->CurrentState == WINDOWSTATE_FULLSCREEN);
			}

			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOCONTEXT);
		return FOUNDATION_ERROR;
	}

	/**
	 * return whether the given window is in fullscreen mode
	 */
	static GLboolean GetWindowIsFullScreen(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				return (GetWindowByIndex(WindowIndex)->CurrentState == WINDOWSTATE_FULLSCREEN);
			}

			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOCONTEXT);
		return FOUNDATION_ERROR;
	}	

	/**
	 * toggle the given window's full screen mode
	 */
	static inline GLboolean SetFullScreen(const char* WindowName, GLboolean NewState)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				if (NewState)
				{
					GetWindowByName(WindowName)->CurrentState = WINDOWSTATE_FULLSCREEN;
#if defined(CURRENT_OS_WINDOWS)
					Windows_FullScreen(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
					Linux_Fullscreen(GetWindowByName(WindowName));
#endif

					return FOUNDATION_OKAY;
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
					return FOUNDATION_OKAY;
				}
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/*
	 * toggle the given window's full screen mode
	 */
	static inline GLboolean SetFullScreen(GLuint WindowIndex, GLboolean NewState)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				if (NewState)
				{
					GetWindowByIndex(WindowIndex)->CurrentState = WINDOWSTATE_FULLSCREEN;
#if defined(CURRENT_OS_WINDOWS)
					Windows_FullScreen(GetWindowByIndex(WindowIndex));
#endif
#if defined(CURRENT_OS_LINUX)
					Linux_Fullscreen(GetWindowByIndex(WindowIndex));
#endif
					return FOUNDATION_OKAY;
				}

				else
				{
					GetWindowByIndex(WindowIndex)->CurrentState = WINDOWSTATE_NORMAL;
#if defined(CURRENT_OS_WINDOWS)
					Windows_FullScreen(GetWindowByIndex(WindowIndex));
#endif
#if defined(CURRENT_OS_LINUX)
					Linux_Fullscreen(GetWindowByIndex(WindowIndex));
#endif
					return FOUNDATION_OKAY;
				}
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * returns whether the given window is minimized
	 */
	static GLboolean GetWindowIsMinimized(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				return (GetWindowByName(WindowName)->CurrentState == WINDOWSTATE_MINIMIZED);
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * returns whether the given window is minimized
	 */
	static GLboolean GetWindowIsMinimized(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				return (GetWindowByIndex(WindowIndex)->CurrentState == WINDOWSTATE_MINIMIZED);
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * toggle the minimization state of the given window
	 */
	static inline GLboolean MinimizeWindow(const char* WindowName, GLboolean NewState)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				if (NewState)
				{
					GetWindowByName(WindowName)->CurrentState = WINDOWSTATE_MINIMIZED;

#if defined(CURRENT_OS_WINDOWS)
					Windows_Minimize(GetWindowByName(WindowName), NewState);
#endif

#if defined(CURRENT_OS_LINUX)
					Linux_Minimize(GetWindowByName(WindowName));
#endif
					return FOUNDATION_OKAY;
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
					return FOUNDATION_OKAY;
				}
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOCONTEXT);
		return FOUNDATION_ERROR;
	}

	/**
	 * toggle the minimization state of the window
	 */
	static inline GLboolean MinimizeWindow(GLuint WindowIndex, GLboolean NewState)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				if (NewState)
				{
					GetWindowByIndex(WindowIndex)->CurrentState = WINDOWSTATE_MINIMIZED;
#if defined(CURRENT_OS_WINDOWS)
					Windows_Minimize(GetWindowByIndex(WindowIndex), NewState);
#endif

#if defined(CURRENT_OS_LINUX)
					Linux_Minimize(GetWindowByIndex(WindowIndex));
#endif
					return FOUNDATION_OKAY;
				}

				else
				{
					GetWindowByIndex(WindowIndex)->CurrentState = WINDOWSTATE_NORMAL;
#if defined(CURRENT_OS_WINDOWS)
					Windows_Minimize(GetWindowByIndex(WindowIndex), NewState);
#endif

#if defined(CURRENT_OS_LINUX)
					Linux_Minimize(GetWindowByIndex(WindowIndex));
#endif
					return FOUNDATION_OKAY;
				}
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	/**
	 * return whether the current window is currently maximized
	 */
	static GLboolean GetWindowIsMaximized(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				return (GetWindowByName(WindowName)->CurrentState == WINDOWSTATE_MAXIMIZED);
			}

			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * return whether the given window is currently maximized
	 */
	static GLboolean GetWindowIsMaximized(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				return (GetWindowByIndex(WindowIndex)->CurrentState == WINDOWSTATE_MAXIMIZED);
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * toggle the maximization state of the current window
	 */
	static inline GLboolean MaximizeWindow(const char* WindowName, GLboolean NewState)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				if (NewState)
				{
					GetWindowByName(WindowName)->CurrentState = WINDOWSTATE_MAXIMIZED;
#if defined(CURRENT_OS_WINDOWS)
					Windows_Maximize(GetWindowByName(WindowName), NewState);
#endif

#if defined(CURRENT_OS_LINUX)
					Linux_Maximize(GetWindowByName(WindowName));
#endif
					return FOUNDATION_OKAY;
				}

				else
				{
					GetWindowByName(WindowName)->CurrentState = WINDOWSTATE_NORMAL;
#if defined(CURRENT_OS_WINDOWS)
					Windows_Maximize(GetWindowByName(WindowName), NewState);
#endif

#if defined(CURRENT_OS_LINUX)
					Linux_Maximize(GetWindowByName(WindowName));
#endif
					return FOUNDATION_OKAY;
				}
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	/**
	 * toggle the maximization state of the current window
	 */
	static inline GLboolean MaximizeWindow(GLuint WindowIndex, GLboolean NewState)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_Maximize(GetWindowByIndex(WindowIndex), NewState);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Maximize(GetWindowByIndex(WindowIndex));
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	//gets and sets for window name and index
	static const char* GetWindowName(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				return GetWindowByIndex(WindowIndex)->Name;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static GLuint GetWindowIndex(const char*  WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				return GetWindowByName(WindowName)->ID;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	//set the window title bar
	static inline GLboolean SetWindowTitleBar(const char* WindowName, const char* NewTitle)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName) && IsValid(NewTitle))
			{
#if defined(CURRENT_OS_WINDOWS)
				SetWindowText(GetWindowByName(WindowName)->WindowHandle, NewTitle);
#endif

#if defined(CURRENT_OS_LINUX)
				XStoreName(GetDisplay(), GetWindowByName(WindowName)->WindowHandle, NewTitle);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}			
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean SetWindowTitleBar(GLuint WindowIndex, const char* NewName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex) && IsValid(NewName))
			{
#if defined(CURRENT_OS_WINDOWS)
				SetWindowText(GetWindowByIndex(WindowIndex)->WindowHandle, NewName);
#endif

#if defined(CURRENT_OS_LINUX)
				XStoreName(GetDisplay(), GetWindowByIndex(WindowIndex)->WindowHandle, NewName);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static GLboolean SetWindowIcon(const char* WindowName, const char* Icon, GLuint Width, GLuint Height)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName) && IsValid(Icon))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_SetWindowIcon(GetWindowByName(WindowName), Icon, Width, Height);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_SetWindowIcon(GetWindowByName(WindowName), Icon, Width, Height);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static GLboolean SetWindowIcon(GLuint WindowIndex, const char* Icon, GLuint Width, GLuint Height)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex) && IsValid(Icon))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_SetWindowIcon(GetWindowByIndex(WindowIndex), Icon, Width, Height);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_SetWindowIcon(GetWindowByIndex(WindowIndex), Icon, Width, Height);
#endif
				return FOUNDATION_OKAY;
			}

			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	//gets and sets window is in focus
	static GLboolean GetWindowIsInFocus(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				return GetWindowByName(WindowName)->InFocus;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static GLboolean GetWindowIsInFocus(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				return GetWindowByIndex(WindowIndex)->InFocus;
			}
			return FOUNDATION_ERROR;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean FocusWindow(const char* WindowName, GLboolean NewState)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_Focus(GetWindowByName(WindowName), NewState);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Focus(GetWindowByName(WindowName), NewState);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean FocusWindow(GLuint WindowIndex, GLboolean NewState)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_Focus(GetWindowByIndex(WindowIndex), NewState);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Focus(GetWindowByIndex(WindowIndex), NewState);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOCONTEXT);
		return FOUNDATION_ERROR;
	}

	//gets and sets for restoring the window
	static inline GLboolean RestoreWindow(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_Restore(GetWindowByName(WindowName));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Restore(GetWindowByName(WindowName));
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean RestoreWindow(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (WindowExists(WindowIndex))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_Restore(GetWindowByIndex(WindowIndex));
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_Restore(GetWindowByIndex(WindowIndex));
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOCONTEXT);
		return FOUNDATION_ERROR;
	}

	//initialize the window manager
	static inline GLboolean Initialize()
	{
		GetInstance()->Initialized = GL_FALSE;
#if defined(CURRENT_OS_LINUX)
		return Linux_Initialize();
#endif	

#if defined(CURRENT_OS_WINDOWS)
		return Windows_Initialize();
#endif
	}

	static inline  GLboolean IsInitialized()
	{
		return GetInstance()->Initialized;
	}

	//ask the window to poll for window events
	static inline GLboolean PollForEvents()
	{
		if (GetInstance()->IsInitialized())
		{
#if defined(CURRENT_OS_WINDOWS)
			return GetInstance()->Windows_PollForEvents();
#endif

#if defined (CURRENT_OS_LINUX)
			return GetInstance()->Linux_PollForEvents();
#endif
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	//remove a window from the manager
	static inline GLboolean RemoveWindow(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				ShutdownWindow(GetWindowByName(WindowName));
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean RemoveWindow(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				ShutdownWindow(GetWindowByIndex(WindowIndex));
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean SetWindowStyle(const char* WindowName, GLuint WindowStyle)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_SetWindowStyle(GetWindowByName(WindowName), WindowStyle);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_SetWindowStyle(GetWindowByName(WindowName), WindowStyle);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean SetWindowStyle(GLuint WindowIndex, GLuint WindowStyle)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_SetWindowStyle(GetWindowByIndex(WindowIndex), WindowStyle);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_SetWindowStyle(GetWindowByIndex(WindowIndex), WindowStyle);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean EnableWindowDecorators(const char* WindowName, GLbitfield Decorators)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_EnableDecorators(GetWindowByName(WindowName), Decorators);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_EnableDecorators(GetWindowByName(WindowName), Decorators);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean EnableWindowDecorators(GLuint WindowIndex, GLbitfield Decorators)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_EnableDecorators(GetWindowByIndex(WindowIndex), Decorators);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_EnableDecorators(GetWindowByIndex(WindowIndex), Decorators);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean DisableWindowDecorator(const char* WindowName, GLbitfield Decorators)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_DisableDecorators(GetWindowByName(WindowName), Decorators);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_DisableDecorators(GetWindowByName(WindowName), Decorators);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean DisableWindowDecorator(GLuint WindowIndex, GLbitfield Decorators)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
#if defined(CURRENT_OS_WINDOWS)
				Windows_DisableDecorators(GetWindowByIndex(WindowIndex), Decorators);
#endif

#if defined(CURRENT_OS_LINUX)
				Linux_DisableDecorators(GetWindowByIndex(WindowIndex), Decorators);
#endif
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	//set callbacks for the selected window
	static inline GLboolean SetWindowOnKeyEvent(const char* WindowName, OnKeyEvent OnKey)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->KeyEvent = OnKey;
				return FOUNDATION_OKAY;
			}

			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean SetWindowOnKeyEvent(GLuint WindowIndex, OnKeyEvent OnKey)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				GetWindowByIndex(WindowIndex)->KeyEvent = OnKey;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean SetWindowOnMouseButtonEvent(const char* WindowName, OnMouseButtonEvent OnMouseButton)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->MouseButtonEvent = OnMouseButton;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean SetWindowOnMouseButtonEvent(GLuint WindowIndex, OnMouseButtonEvent OnMouseButton)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				GetWindowByIndex(WindowIndex)->MouseButtonEvent = OnMouseButton;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean SetWindowOnMouseWheelEvent(const char* WindowName, OnMouseWheelEvent OnMouseWheel)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->MouseWheelEvent = OnMouseWheel;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean SetWindowOnMouseWheelEvent(GLuint WindowIndex, OnMouseWheelEvent OnMouseWheel)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				GetWindowByIndex(WindowIndex)->MouseWheelEvent = OnMouseWheel;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean SetWindowOnDestroyed(const char* WindowName, OnDestroyedEvent OnDestroyed)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->DestroyedEvent = OnDestroyed;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean SetWindowOnDestroyed(GLuint WindowIndex, OnDestroyedEvent OnDestroyed)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				GetWindowByIndex(WindowIndex)->DestroyedEvent = OnDestroyed;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean SetWindowOnMaximized(const char* WindowName, OnMaximizedEvent OnMaximized)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->MaximizedEvent = OnMaximized;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean SetWindowOnMaximized(GLuint WindowIndex, OnMaximizedEvent OnMaximized)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				GetWindowByIndex(WindowIndex)->MaximizedEvent = OnMaximized; \
					return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean SetWindowOnMinimized(const char* WindowName, OnMinimizedEvent OnMiniimzed)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->MinimizedEvent = OnMiniimzed;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean SetWindowOnMinimized(GLuint WindowIndex, OnMinimizedEvent OnMiniimzed)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				GetWindowByIndex(WindowIndex)->MinimizedEvent = OnMiniimzed;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean SetWindowOnFocus(const char* WindowName, OnFocusEvent OnFocus)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->FocusEvent = OnFocus;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean SetWindowOnFocus(GLuint WindowIndex, OnFocusEvent OnFocus)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				GetWindowByIndex(WindowIndex)->FocusEvent = OnFocus;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean SetWindowOnMoved(const char* WindowName, OnMovedEvent OnMoved)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->MovedEvent = OnMoved;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean SetWindowOnMoved(GLuint WindowIndex, OnMovedEvent OnMoved)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				GetWindowByIndex(WindowIndex)->MovedEvent = OnMoved;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean SetWindowOnResize(const char* WindowName, OnResizeEvent OnResize)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->ResizeEvent = OnResize;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean SetWindowOnResize(GLuint WindowIndex, OnResizeEvent OnResize)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				GetWindowByIndex(WindowIndex)->ResizeEvent = OnResize;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean SetWindowOnMouseMove(const char* WindowName, OnMouseMoveEvent OnMouseMove)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowName))
			{
				GetWindowByName(WindowName)->MouseMoveEvent = OnMouseMove;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}
	static inline GLboolean SetWindowOnMouseMove(GLuint WindowIndex, OnMouseMoveEvent OnMouseMove)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExist(WindowIndex))
			{
				GetWindowByIndex(WindowIndex)->MouseMoveEvent = OnMouseMove;
				return FOUNDATION_OKAY;
			}
			return FOUNDATION_ERROR;
		}
		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	private:

	struct TWindow
		{
			TWindow()
			{
				Name = nullptr;
				ID = NULL;
				ColourBits = NULL;
				DepthBits = NULL;
				StencilBits = NULL;
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

				Initialized = GL_FALSE;
				ContextCreated = GL_FALSE;
				CurrentWindowStyle = WINDOWSTYLE_DEFAULT;

			}
			//Name of the window
			const char*  Name;
			//ID of the Window. (where it belongs in the window manager)
			GLuint ID;
			//color format of the window. (defaults to 32 bit color)
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

			GLboolean Initialized; /**< whether the window has been successfully initialized*/
			GLboolean ContextCreated; /**< whether the OpenGL context has been successfully created*/
			GLboolean IsCurrentContext; /**< whether the window is the current window being drawn to*/

			GLuint CurrentState; /**< The current state of the window. these states include Normal, Minimized, Maximized and Full screen*/
			GLuint CurrentWindowStyle; /**< the current style of the window*/

			OnKeyEvent KeyEvent; /**< this is the callback to be used when a key has been pressed*/
			OnMouseButtonEvent MouseButtonEvent; /**< this is the callback to be used when a mouse button has been pressed*/
			OnMouseWheelEvent MouseWheelEvent; /**< this is the callback to be used when the mouse wheel has been scrolled.*/
			OnDestroyedEvent DestroyedEvent; /**< this is the callback to be used when the window has been closed in a non-programmatic fashion*/
			OnMaximizedEvent MaximizedEvent; /**< this is the callback to be used when the window has been maximized in a non-programmatic fashion*/
			OnMinimizedEvent MinimizedEvent; /**< this is the callback to be used when the window has been minimized in a non-programmatic fashion*/
			OnFocusEvent FocusEvent; /**< this is the callback to be used when the window has been given focus in a non-programmatic fashion*/
			OnMovedEvent MovedEvent; /**< this is the callback to be used the window has been moved in a non-programmatic fashion*/
			OnResizeEvent ResizeEvent; /**< this is a callback to be used when the window has been resized in a non-programmatic fashion*/
			OnMouseMoveEvent MouseMoveEvent; /**< this is a callback to be used when the mouse has been moved*/

#if defined(CURRENT_OS_WINDOWS)
			
			HDC DeviceContextHandle;
			HGLRC GLRenderingContextHandle;
			HPALETTE PaletteHandle;
			PIXELFORMATDESCRIPTOR PixelFormatDescriptor;

			WNDCLASS WindowClass;
			HWND WindowHandle;
			HINSTANCE InstanceHandle;	

#endif

#if defined(CURRENT_OS_LINUX)
			Window WindowHandle; /**< the X11 handle to the window. I wish they didn't name the type 'Window' */
			GLXContext Context; /**< the handle to the GLX rendering context */
			XVisualInfo* VisualInfo; /**< the handle to the Visual Information. similar purpose to PixelformatDesriptor*/
			GLint* Attributes;/**< attributes of the window. RGB, depth, stencil, etc */
			XSetWindowAttributes SetAttributes; /**< the attributes to be set for the window */
			GLbitfield Decorators; /**< enabled window decorators */

			/*these atomics are needed to change window states via the extended window manager
			I might move them to window manager considering these are essentially constants
			*/
			Atom AtomState;  /**< atom for the state of the window */	//_NET_WM_STATE
			Atom AtomHidden; /**< atom for the current hidden state of the window */	// _NET_WM_STATE_HIDDEN
			Atom AtomFullScreen; /**< atom for the fullscreen state of the window*/ //NET_WM_STATE_FULLSCREEN
			Atom AtomMaxHorz; /**< atom for the maximized horizontally state of the window*/ // _NET_WM_STATE_MAXIMIZED_HORZ
			Atom AtomMaxVert; /**< atom for the maximized vertically state of the window*/ // _NET_WM_STATE_MAXIMIZED_VERT
			Atom AtomClose;  /**< atom for closing the window */	// _NET_WM_CLOSE_WINDOW
			Atom AtomActive;  /**<atom for the active window */	//_NET_ACTIVE_WINDOW
			Atom AtomDemandsAttention; /**<atom for when the window demands attention*/	//_NET_WM_STATE_DEMANDS_ATTENTION
			Atom AtomFocused; /**<atom for the focused state of the window */ //_NET_WM_STATE_FOCUSED
			Atom AtomCardinal; /**< atom for cardinal coordinates */ //_NET_WM_CARDINAL
			Atom AtomIcon; /**< atom for the icon of the window */ //_NET_WM_ICON
			Atom AtomHints; /**< atom for the window decorations */ //_NET_WM_HINTS

			Atom AtomWindowType; /**< atom for the type of window*/
			Atom AtomWindowTypeDesktop; /**< atom for the desktop window type */ //_NET_WM_WINDOW_TYPE_SPLASH
			Atom AtomWindowTypeSplash; /**< atom for the splash screen window type */
			Atom AtomWindowTypeNormal; /**<atom for the normal splash screen window type*/

			Atom AtomAllowedActions; /**< atom for allowed window actions */
			Atom AtomActionResize; /**< atom for allowing the window to be resized*/
			Atom AtomActionMinimize; /**< atom for allowing the window to be minimized */
			Atom AtomActionShade; /**< atom for allowing the window to be shaded */
			Atom AtomActionMaximizeHorz; /**< atom for allowing the window to be maximized horizontally */
			Atom AtomActionMaximizeVert; /**< atom for allowing the window to be maximized vertically */
			Atom AtomActionClose; /**< atom for allowing the window to be closed*/

			Atom AtomDesktopGeometry; /**< atom for Dedktop Geometry */

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

	static void ShutdownWindow(TWindow* SelectedWindow)
	{
#if defined(CURRENT_OS_WINDOWS)
		Windows_ShutdownWindow(SelectedWindow);
#endif

#if defined(CURRENT_OS_LINUX)
		Linux_ShutdownWindow(SelectedWindow);
#endif
	}

	static inline GLboolean DoesExist(const char* WindowName)
	{
		if (GetInstance()->IsInitialized())
		{
			if (IsValid(WindowName))
			{
#if defined(CURRENT_OS_WINDOWS)
				for each(auto Iter in GetInstance()->Windows)
				{
					if (Iter->Name == WindowName)
					{
						return GL_TRUE;
					}
				}
#endif

#if defined(CURRENT_OS_LINUX)
				for (auto iter : GetInstance()->Windows)
				{
					if(iter->Name == WindowName)
					{
						return GL_TRUE;
					}
				}
#endif
			}
			PrintErrorMessage(ERROR_INVALIDWINDOWNAME);
			return GL_FALSE;
		}

		return GL_FALSE;
	}

	static inline GLboolean DoesExist(GLuint WindowIndex)
	{
		if (GetInstance()->IsInitialized())
		{
			if (WindowIndex <= (GetInstance()->Windows.size() - 1))
			{
				return FOUNDATION_OKAY;
			}

			PrintErrorMessage(ERROR_INVALIDWINDOWINDEX);
			return FOUNDATION_ERROR;
		}

		return FOUNDATION_ERROR;
	}

	static TWindow* GetWindowByName(const char* WindowName)
	{
#if defined(CURRENT_OS_WINDOWS)
			for each(auto CurrentWindow in GetInstance()->Windows)
			{
				if (CurrentWindow->Name == WindowName)
				{
					return CurrentWindow;
				}
			}
#endif

#if defined(CURRENT_OS_LINUX)

			for (auto CurrentWindow : GetInstance()->Windows)
			{
				if (CurrentWindow->Name == WindowName)
				{
					return CurrentWindow;
				}
			}
#endif
			PrintErrorMessage(ERROR_WINDOWNOTFOUND);
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

	GLboolean Initialized;
	
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

	static inline void InitializePixelFormat(TWindow* SelectedWindow)
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

	static inline GLboolean Windows_InitializeGL(TWindow* SelectedWindow)
	{
		SelectedWindow->DeviceContextHandle = GetDC(SelectedWindow->WindowHandle);
		InitializePixelFormat(SelectedWindow);
		SelectedWindow->GLRenderingContextHandle = wglCreateContext(SelectedWindow->DeviceContextHandle);
		wglMakeCurrent(SelectedWindow->DeviceContextHandle, SelectedWindow->GLRenderingContextHandle);

		SelectedWindow->ContextCreated = (SelectedWindow->GLRenderingContextHandle != nullptr);

		if (SelectedWindow->ContextCreated)
		{
			return FOUNDATION_OKAY;
		}

		PrintErrorMessage(ERROR_INVALIDCONTEXT);
		return FOUNDATION_ERROR;
	}

	static inline void Windows_ShutdownWindow(TWindow* SelectedWindow)
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
		UnregisterClass(SelectedWindow->Name, SelectedWindow->InstanceHandle);

		FreeModule(SelectedWindow->InstanceHandle);

		SelectedWindow->DeviceContextHandle = nullptr;
		SelectedWindow->WindowHandle = nullptr;
		SelectedWindow->GLRenderingContextHandle = nullptr;
	}

	static inline void Windows_FullScreen(TWindow* SelectedWindow)
	{
		SetWindowLongPtr(SelectedWindow->WindowHandle, GWL_STYLE,
			WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);

		MoveWindow(SelectedWindow->WindowHandle, 0, 0, WindowManager::GetScreenResolution()[0],
			WindowManager::GetScreenResolution()[1], GL_TRUE);
	}

	static inline void Windows_Minimize(TWindow* SelectedWindow, GLboolean NewState)
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

	static inline void Windows_Maximize(TWindow* SelectedWindow, GLboolean NewState)
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

	static inline void Windows_Restore(TWindow* SelectedWindow)
	{
		ShowWindow(SelectedWindow->WindowHandle, SW_RESTORE);
	}

	static inline void Windows_Focus(TWindow* SelectedWindow, GLboolean NewState)
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

	static inline void Windows_SetMousePosition(TWindow* SelectedWindow)
	{
		POINT l_MousePoint;
		l_MousePoint.x = SelectedWindow->MousePosition[0];
		l_MousePoint.y = SelectedWindow->MousePosition[1];
		ScreenToClient(SelectedWindow->WindowHandle, &l_MousePoint);
		SetCursorPos(l_MousePoint.x, l_MousePoint.y);
	}

	static inline void Windows_SetPosition(TWindow* SelectedWindow)
	{
		SetWindowPos(SelectedWindow->WindowHandle, HWND_TOP,
			SelectedWindow->Position[0], SelectedWindow->Position[1],
			SelectedWindow->Resolution[0], SelectedWindow->Resolution[1],
			SWP_SHOWWINDOW | SWP_NOSIZE);
	}

	static inline void Windows_SetResolution(TWindow* SelectedWindow)
	{
		SetWindowPos(SelectedWindow->WindowHandle, HWND_TOP, 
			SelectedWindow->Position[0], SelectedWindow->Position[1],
			SelectedWindow->Resolution[0], SelectedWindow->Resolution[1], 
			SWP_SHOWWINDOW | SWP_NOMOVE);
	}

	static inline GLboolean Windows_PollForEvents()
	{
		if (GetInstance()->IsInitialized())
		{
			if (PeekMessage(&GetInstance()->m_Message, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&GetInstance()->m_Message);
				DispatchMessage(&GetInstance()->m_Message);

				return FOUNDATION_OKAY;
			}
			return FOUNDATION_OKAY;
		}

		PrintErrorMessage(ERROR_NOTINITIALIZED);
		return FOUNDATION_ERROR;
	}

	static inline GLboolean Windows_Initialize()
	{
		CreateTerminal();
		RECT l_Desktop;

		HWND l_DesktopHandle = GetDesktopWindow();

		if (l_DesktopHandle)
		{

			GetWindowRect(l_DesktopHandle, &l_Desktop);

			GetInstance()->ScreenResolution[0] = l_Desktop.right;
			GetInstance()->ScreenResolution[1] = l_Desktop.bottom;
			GetInstance()->Initialized = GL_TRUE;
			return FOUNDATION_OKAY;
		}

		PrintErrorMessage(ERROR_WINDOWS_CANNOTINITIALIZE);
		return FOUNDATION_ERROR;
	}
	static inline void Windows_Shutown()
	{

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
			return KEY_LEFTWINDOW;
		}

		case VK_RWIN:
		{
			return KEY_RIGHTWINDOW;
		}

		default:
		{
			return WordParam;
		}
		}
	}

	static void Windows_SetWindowIcon(TWindow* GivenWindow, const char* Icon, GLuint Width, GLuint Height)
	{
		HANDLE icon = LoadImage(GivenWindow->InstanceHandle, Icon,
			IMAGE_ICON, Width, Height, LR_LOADFROMFILE);
		SendMessage(GivenWindow->WindowHandle, (UINT)WM_SETICON, ICON_BIG, (LPARAM)icon);
	}

	static void Windows_SetWindowStyle(TWindow* GivenWindow, GLuint WindowType)
	{
		switch (WindowType)
		{
		case WINDOWSTYLE_DEFAULT:
		{
			EnableWindowDecorators(GivenWindow->Name, DECORATOR_TITLEBAR | DECORATOR_BORDER |
				DECORATOR_CLOSEBUTTON | DECORATOR_MINIMIZEBUTTON | DECORATOR_MAXIMIZEBUTTON);
			break;
		}

		case WINDOWSTYLE_POPUP:
		{
			EnableWindowDecorators(GivenWindow->Name, 0);
			break;
		}

		case WINDOWSTYLE_BARE:
		{
			EnableWindowDecorators(GivenWindow->Name, DECORATOR_TITLEBAR | DECORATOR_BORDER);
			break;
		}

		default:
		{
			PrintErrorMessage(ERROR_INVALIDWINDOWSTYLE);
			break;
		}
		}
	}

	static void Windows_EnableDecorators(TWindow* GivenWindow, GLbitfield Decorators)
	{
		GivenWindow->CurrentWindowStyle = WS_VISIBLE | WS_CLIPSIBLINGS;

		if (Decorators & DECORATOR_BORDER)
		{
			GivenWindow->CurrentWindowStyle |= WS_BORDER;
		}

		if (Decorators & DECORATOR_TITLEBAR)
		{
			GivenWindow->CurrentWindowStyle |= WS_CAPTION;
		}

		if (Decorators & DECORATOR_ICON)
		{
			GivenWindow->CurrentWindowStyle |= WS_ICONIC;
		}

		if (Decorators & DECORATOR_CLOSEBUTTON)
		{
			GivenWindow->CurrentWindowStyle |= WS_SYSMENU;
		}

		if (Decorators & DECORATOR_MINIMIZEBUTTON)
		{
			GivenWindow->CurrentWindowStyle |= WS_MINIMIZEBOX | WS_SYSMENU;
		}

		if (Decorators & DECORATOR_MAXIMIZEBUTTON)
		{
			GivenWindow->CurrentWindowStyle |= WS_MAXIMIZEBOX | WS_SYSMENU;
		}

		if (Decorators & DECORATOR_SIZEABLEBORDER)
		{
			GivenWindow->CurrentWindowStyle |= WS_SIZEBOX;
		}

		SetWindowLongPtr(GivenWindow->WindowHandle, GWL_STYLE,
			GivenWindow->CurrentWindowStyle);
	}

	static void Windows_DisableDecorators(TWindow* GivenWindow, GLbitfield Decorators)
	{
		if (Decorators & DECORATOR_BORDER)
		{
			GivenWindow->CurrentWindowStyle &= ~WS_BORDER;
		}

		if (Decorators & DECORATOR_TITLEBAR)
		{
			GivenWindow->CurrentWindowStyle &= ~WS_MAXIMIZEBOX;
		}

		if (Decorators & DECORATOR_ICON)
		{
			GivenWindow->CurrentWindowStyle &= ~WS_ICONIC;
		}

		if (Decorators & DECORATOR_CLOSEBUTTON)
		{
			GivenWindow->CurrentWindowStyle &= ~WS_SYSMENU;
		}

		if (Decorators & DECORATOR_MINIMIZEBUTTON)
		{
			GivenWindow->CurrentWindowStyle &= ~WS_MINIMIZEBOX;
		}

		if (Decorators & DECORATOR_MAXIMIZEBUTTON)
		{
			GivenWindow->CurrentWindowStyle &= ~WS_MAXIMIZEBOX;
		}

		if (Decorators & DECORATOR_SIZEABLEBORDER)
		{
			GivenWindow->CurrentWindowStyle &= ~WS_SIZEBOX;
		}

		SetWindowLongPtr(GivenWindow->WindowHandle, GWL_STYLE,
			GivenWindow->CurrentWindowStyle | WS_VISIBLE);
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

	static GLboolean Linux_Initialize()
	{
		GetInstance()->CurrentDisplay = XOpenDisplay(0);

		if(!GetInstance()->CurrentDisplay)
		{
			PrintErrorMessage(ERROR_LINUX_CANNOTCONNECTXSERVER);
			return FOUNDATION_ERROR;
		}

		GetInstance()->ScreenResolution[0] = WidthOfScreen(XScreenOfDisplay(GetInstance()->CurrentDisplay, 
			DefaultScreen(GetInstance()->CurrentDisplay)));

		GetInstance()->ScreenResolution[1] = HeightOfScreen(XScreenOfDisplay(GetInstance()->CurrentDisplay,
			DefaultScreen(GetInstance()->CurrentDisplay)));
		GetInstance()->Initialized = GL_TRUE;
		return FOUNDATION_OKAY;
	}

	static void InitializeAtomics(TWindow* SelectedWindow)
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
		SelectedWindow->AtomCardinal = XInternAtom(WindowManager::GetDisplay(), "CARDINAL", GL_FALSE);
		SelectedWindow->AtomIcon = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_ICON", GL_FALSE);
		SelectedWindow->AtomHints = XInternAtom(WindowManager::GetDisplay(), "_MOTIF_WM_HINTS", GL_TRUE);

		SelectedWindow->AtomWindowType = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_WINDOW_TYPE", GL_FALSE);
		SelectedWindow->AtomWindowTypeDesktop = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_WINDOW_TYPE_UTILITY", GL_FALSE);
		SelectedWindow->AtomWindowTypeSplash = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_WINDOW_TYPE_SPLASH", GL_FALSE);
		SelectedWindow->AtomWindowTypeNormal = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_WINDOW_TYPE_NORMAL", GL_FALSE);

		SelectedWindow->AtomAllowedActions = XInternAtom(WindowManager::GetDisplay(), "_NET_WM_ALLOWED_ACTIONS", GL_FALSE);
		SelectedWindow->AtomActionResize = XInternAtom(WindowManager::GetDisplay(), "WM_ACTION_RESIZE", GL_FALSE);
		SelectedWindow->AtomActionMinimize = XInternAtom(WindowManager::GetDisplay(), "_WM_ACTION_MINIMIZE", GL_FALSE);
		SelectedWindow->AtomActionShade = XInternAtom(WindowManager::GetDisplay(), "WM_ACTION_SHADE", GL_FALSE);
		SelectedWindow->AtomActionMaximizeHorz = XInternAtom(WindowManager::GetDisplay(), "_WM_ACTION_MAXIMIZE_HORZ", GL_FALSE);
		SelectedWindow->AtomActionMaximizeVert = XInternAtom(WindowManager::GetDisplay(), "_WM_ACTION_MAXIMIZE_VERT", GL_FALSE);
		SelectedWindow->AtomActionClose = XInternAtom(WindowManager::GetDisplay(), "_WM_ACTION_CLOSE", GL_FALSE);

		SelectedWindow->AtomDesktopGeometry = XInternAtom(WindowManager::GetDisplay(), "_NET_DESKTOP_GEOMETRY", GL_FALSE);
	}

	static void Linux_InitializeWindow(TWindow* SelectedWindow)
	{
		SelectedWindow->Attributes = new GLint[12]{
			GLX_DOUBLEBUFFER, 
			GLX_DEPTH_SIZE, 
			SelectedWindow->DepthBits, 
			GLX_STENCIL_SIZE, 
			SelectedWindow->StencilBits,
			GLX_RED_SIZE, 
			SelectedWindow->ColourBits, 
			GLX_GREEN_SIZE, 
			SelectedWindow->ColourBits, 
			GLX_BLUE_SIZE, 
			SelectedWindow->ColourBits, 
			None};

		SelectedWindow->Decorators = 1;
		SelectedWindow->CurrentWindowStyle |= LINUX_DECORATOR_CLOSE | LINUX_DECORATOR_MAXIMIZE | LINUX_DECORATOR_MINIMIZE | LINUX_DECORATOR_MOVE;

		if (!WindowManager::GetDisplay())
		{
			PrintErrorMessage(ERROR_LINUX_CANNOTCONNECTXSERVER);
			exit(0);
		}

		SelectedWindow->VisualInfo = glXGetVisualFromFBConfig(GetDisplay(), GetBestFrameBufferConfig(SelectedWindow)); 

		//VisualInfo = glXChooseVisual(WindowManager::GetDisplay(), 0, Attributes);

		if (!SelectedWindow->VisualInfo)
		{
			PrintErrorMessage(ERROR_LINUX_INVALIDVISUALINFO);
			exit(0);
		}

		SelectedWindow->SetAttributes.colormap = XCreateColormap(GetDisplay(),
			DefaultRootWindow(GetDisplay()),
			SelectedWindow->VisualInfo->visual, AllocNone);

		SelectedWindow->SetAttributes.event_mask = ExposureMask | KeyPressMask 
			| KeyReleaseMask | MotionNotify | ButtonPressMask | ButtonReleaseMask
			| FocusIn | FocusOut | Button1MotionMask | Button2MotionMask | Button3MotionMask | 
			Button4MotionMask | Button5MotionMask | PointerMotionMask | FocusChangeMask
			| VisibilityChangeMask | PropertyChangeMask | SubstructureNotifyMask;
		
		SelectedWindow->WindowHandle = XCreateWindow(GetDisplay(),
			XDefaultRootWindow(GetDisplay()), 0, 0,
			SelectedWindow->Resolution[0], SelectedWindow->Resolution[1],
			0, SelectedWindow->VisualInfo->depth, InputOutput,
			SelectedWindow->VisualInfo->visual, CWColormap | CWEventMask,
			&SelectedWindow->SetAttributes);

		if(!SelectedWindow->WindowHandle)
		{
			PrintErrorMessage(ERROR_LINUX_CANNOTCREATEWINDOW);
			exit(0);
		}

		XMapWindow(GetDisplay(), SelectedWindow->WindowHandle);
		XStoreName(GetDisplay(), SelectedWindow->WindowHandle,
			SelectedWindow->Name);

		InitializeAtomics(SelectedWindow);

		XSetWMProtocols(GetDisplay(), SelectedWindow->WindowHandle, &SelectedWindow->AtomClose, GL_TRUE);	

		return Linux_InitializeGL(SelectedWindow);
	}

	static GLboolean Linux_InitializeGL(TWindow* SelectedWindow)
	{
		if(!SelectedWindow->Context)
		{
			SelectedWindow->Context = glXCreateContext(GetDisplay(),
				SelectedWindow->VisualInfo, 0, GL_TRUE);

			if(SelectedWindow->Context)
			{
				glXMakeCurrent(GetDisplay(),
					SelectedWindow->WindowHandle, 
					SelectedWindow->Context);

				XWindowAttributes l_Attributes;

				XGetWindowAttributes(GetDisplay(),
					SelectedWindow->WindowHandle, &l_Attributes);
				SelectedWindow->Position[0] = l_Attributes.x;
				SelectedWindow->Position[1] = l_Attributes.y;

				SelectedWindow->ContextCreated = GL_TRUE;
				return FOUNDATION_OKAY;
			}
		}

		else
		{
			PrintErrorMessage(ERROR_EXISTINGCONTEXT);
			return FOUNDATION_ERROR;	
		}

		return FOUNDATION_ERROR;
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
		if(NewFocusState)
		{
			XMapWindow(WindowManager::GetDisplay(), SelectedWindow->WindowHandle);
		}

		else
		{
			XUnmapWindow(WindowManager::GetDisplay(), SelectedWindow->WindowHandle);
		}
	}

	static void Linux_SetMousePosition(TWindow* SelectedWindow)
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

	static GLboolean Linux_PollForEvents()
	{
		if(XEventsQueued(GetInstance()->GetDisplay(), QueuedAfterReading))
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
		//	printf("blarg");

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
			return FOUNDATION_OKAY;;
		}
		return FOUNDATION_OKAY;
	}
		return FOUNDATION_OKAY;
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

	static inline void Linux_EnableDecorators(TWindow* GivenWindow, GLbitfield Decorators)
	{
		if (Decorators & DECORATOR_CLOSEBUTTON)
		{
			GivenWindow->CurrentWindowStyle |= LINUX_DECORATOR_CLOSE;
			GivenWindow->Decorators = 1;
		}

		if (Decorators & DECORATOR_MINIMIZEBUTTON)
		{
			GivenWindow->CurrentWindowStyle |= LINUX_DECORATOR_MINIMIZE;
			GivenWindow->Decorators = 1;
		}

		if (Decorators & DECORATOR_MAXIMIZEBUTTON)
		{
			GivenWindow->CurrentWindowStyle |= LINUX_DECORATOR_MAXIMIZE;
			GivenWindow->Decorators = 1;
		}

		if (Decorators & DECORATOR_ICON)
		{
			//Linux (at least cinammon) doesnt have icons in the window. only in the taskbar icon
		}

		//just need to set it to 1 to enable all decorators that include title bar 
		if (Decorators & DECORATOR_TITLEBAR)
		{
			GivenWindow->Decorators = 1;
		}

		if (Decorators & DECORATOR_BORDER)
		{
			GivenWindow->Decorators = 1;
		}

		if (Decorators & DECORATOR_SIZEABLEBORDER)
		{
			GivenWindow->Decorators = 1;
		}

		long hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, GivenWindow->CurrentWindowStyle, GivenWindow->Decorators, 0, 0 };

		XChangeProperty(GetDisplay(), GivenWindow->WindowHandle, GivenWindow->AtomHints, XA_ATOM, 32,
			PropModeReplace, (unsigned char*)hints, 5);

		XMapWindow(GetDisplay(), GivenWindow->WindowHandle);
	}

	static inline void Linux_DisableDecorators(TWindow* GivenWindow, GLbitfield Decorators)
	{
		if (Decorators & DECORATOR_CLOSEBUTTON)
		{
			//I hate doing this but it is neccessary to keep functionality going.
			GLboolean MinimizeEnabled, MaximizeEnabled;

			if (Decorators & DECORATOR_MAXIMIZEBUTTON)
			{
				MaximizeEnabled = GL_TRUE;
			}

			if (Decorators & DECORATOR_MINIMIZEBUTTON)
			{
				MinimizeEnabled = GL_TRUE;
			}

			GivenWindow->CurrentWindowStyle &= ~LINUX_DECORATOR_CLOSE;

			if (MaximizeEnabled)
			{
				GivenWindow->CurrentWindowStyle |= LINUX_DECORATOR_MAXIMIZE;
			}

			if (MinimizeEnabled)
			{
				GivenWindow->CurrentWindowStyle |= LINUX_DECORATOR_MINIMIZE;
			}

			GivenWindow->Decorators = 1;
		}

		if (Decorators & DECORATOR_MINIMIZEBUTTON)
		{
			GivenWindow->CurrentWindowStyle &= ~LINUX_DECORATOR_MINIMIZE;
			GivenWindow->Decorators = 1;
		}

		if (Decorators & DECORATOR_MAXIMIZEBUTTON)
		{
			GLboolean MinimizeEnabled;

			if (Decorators & DECORATOR_MINIMIZEBUTTON)
			{
				MinimizeEnabled = GL_TRUE;
			}

			GivenWindow->CurrentWindowStyle &= ~LINUX_DECORATOR_MAXIMIZE;

			if (MinimizeEnabled)
			{
				GivenWindow->CurrentWindowStyle |= LINUX_DECORATOR_MINIMIZE;
			}

			GivenWindow->Decorators = 1;
		}

		if (Decorators & DECORATOR_ICON)
		{
			//Linux (at least cinammon) doesnt have icons in the window. only in the taskbar icon
		}

		//just need to set it to 1 to enable all decorators that include title bar 
		if (Decorators & DECORATOR_TITLEBAR)
		{
			GivenWindow->Decorators = LINUX_DECORATOR_BORDER;
		}

		if (Decorators & DECORATOR_BORDER)
		{
			GivenWindow->Decorators = 0;
		}

		if (Decorators & DECORATOR_SIZEABLEBORDER)
		{
			GivenWindow->Decorators = 0;
		}

		long hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, GivenWindow->CurrentWindowStyle, GivenWindow->Decorators, 0, 0 };

		XChangeProperty(GetDisplay(), GivenWindow->WindowHandle, GivenWindow->AtomHints, XA_ATOM, 32,
			PropModeReplace, (unsigned char*)hints, 5);

		XMapWindow(GetDisplay(), GivenWindow->WindowHandle);
	}

	static inline void Linux_SetWindowStyle(TWindow* GivenWindow, GLuint WindowStyle)
	{
		switch (WindowStyle)
		{
		case WINDOWSTYLE_DEFAULT:
		{
			GivenWindow->Decorators = (1L << 2);
			GivenWindow->CurrentWindowStyle = LINUX_DECORATOR_MOVE | LINUX_DECORATOR_CLOSE |
				LINUX_DECORATOR_MAXIMIZE | LINUX_DECORATOR_MINIMIZE;
			long Hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, GivenWindow->CurrentWindowStyle, GivenWindow->Decorators, 0, 0 };

			XChangeProperty(GetDisplay(), GivenWindow->WindowHandle, GivenWindow->AtomHints, XA_ATOM, 32, PropModeReplace,
				(unsigned char*)Hints, 5);

			XMapWindow(GetDisplay(), GivenWindow->WindowHandle);
			break;
		}

		case WINDOWSTYLE_BARE:
		{
			GivenWindow->Decorators = (1L << 2);
			GivenWindow->CurrentWindowStyle = (1L << 2);
			long Hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, GivenWindow->CurrentWindowStyle, GivenWindow->Decorators, 0, 0 };

			XChangeProperty(GetDisplay(), GivenWindow->WindowHandle, GivenWindow->AtomHints, XA_ATOM, 32, PropModeReplace,
				(unsigned char*)Hints, 5);

			XMapWindow(GetDisplay(), GivenWindow->WindowHandle);
			break;
		}

		case WINDOWSTYLE_POPUP:
		{
			GivenWindow->Decorators = 0;
			GivenWindow->CurrentWindowStyle = (1L << 2);
			long Hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, GivenWindow->CurrentWindowStyle, GivenWindow->Decorators, 0, 0 };

			XChangeProperty(GetDisplay(), GivenWindow->WindowHandle, GivenWindow->AtomHints, XA_ATOM, 32, PropModeReplace,
				(unsigned char*)Hints, 5);

			XMapWindow(GetDisplay(), GivenWindow->WindowHandle);
			break;
		}

		default:
		{
			PrintErrorMessage(ERROR_INVALIDWINDOWSTYLE);
			break;
		}
		}
	}

	static inline void Linux_SetWindowIcon(TWindow* GivenWindow, const char* Icon, GLuint Width, GLuint Height)
	{
		//sorry :(
		PrintErrorMessage(ERROR_LINUX_FUNCTIONNOTIMPLEMENTED);
	}

	static inline GLXFBConfig GetBestFrameBufferConfig(TWindow* GivenWindow)
	{
		const GLint VisualAttributes[] =
		{
			GLX_X_RENDERABLE, GL_TRUE,
			GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
			GLX_RED_SIZE, GivenWindow->ColourBits,
			GLX_GREEN_SIZE, GivenWindow->ColourBits,
			GLX_BLUE_SIZE, GivenWindow->ColourBits,
			GLX_ALPHA_SIZE, GivenWindow->ColourBits,
			GLX_DEPTH_SIZE, GivenWindow->DepthBits,
			GLX_STENCIL_SIZE, GivenWindow->StencilBits,
			GLX_DOUBLEBUFFER, GL_TRUE,
			None
		};

		GLint FrameBufferCount;
		GLuint BestBufferConfig, BestNumSamples = 0;
		GLXFBConfig* Configs = glXChooseFBConfig(GetDisplay(), 0, VisualAttributes, &FrameBufferCount);

		for (GLuint CurrentConfig = 0; CurrentConfig < FrameBufferCount; CurrentConfig++)
		{
			XVisualInfo* VisInfo = glXGetVisualFromFBConfig(GetDisplay(), Configs[CurrentConfig]);

			if (VisInfo)
			{
				//printf("%i %i %i\n", VisInfo->depth, VisInfo->bits_per_rgb, VisInfo->colormap_size);
				GLint Samples, SampleBuffer;
				glXGetFBConfigAttrib(GetDisplay(), Configs[CurrentConfig], GLX_SAMPLE_BUFFERS, &SampleBuffer);
				glXGetFBConfigAttrib(GetDisplay(), Configs[CurrentConfig], GLX_SAMPLES, &Samples);

				if (SampleBuffer && Samples > -1)
				{
					BestBufferConfig = CurrentConfig;
					BestNumSamples = Samples;
				}
			}

			XFree(VisInfo);
		}

		GLXFBConfig BestConfig = Configs[BestBufferConfig];

		XFree(Configs);

		return BestConfig;
	}

	Display* CurrentDisplay;
	XEvent Event;
#endif
};

WindowManager* WindowManager::Instance = nullptr;

#endif

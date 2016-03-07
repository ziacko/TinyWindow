//created my Ziyad Barakat 2014 - 2015

#ifndef TINYWINDOW_H
#define TINYWINDOW_H

#if defined(_WIN32) || defined(_WIN64)
#define TW_WINDOWS
#include <Windows.h>
#include <gl/GL.h>
#include <io.h>
#include <fcntl.h>
#if defined(_MSC_VER)
//this automatically loads the OpenGL library if you are using Visual studio 
#pragma comment ( lib, "opengl32.lib" )
//this makes sure that the entry point of your program is main(). not Winmain()
#pragma comment( linker, "/subsystem:windows /ENTRY:mainCRTStartup" )
#endif //_MSC_VER
#endif	//_WIN32 || _WIN64

#if defined( __linux__ )
#define TW_LINUX
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/XKBlib.h>
#endif //__linux__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <limits.h>
#include <string.h>
#include <functional>
#include <memory>
#include <system_error>

namespace TinyWindow
{

const int defaultWindowWidth = 1280;
const int defaultWindowHeight = 720;

enum class keyState_t
{
	bad = -1,						/**< If get key state fails (could not name it ERROR) */
	up,								/**< The key is currently up */
	down,							/**< The key is currently down */
};

enum key_t
{
	bad = -1,						/**< The key pressed is considered invalid */
	first = 256 + 1,				/**< The first key that is not a char */
	F1, 							/**< The F1 key */
	F2,								/**< The F2 key */
	F3,								/**< The F3 key */
	F4,								/**< The F4 key */
	F5,								/**< The F5 key */
	F6,								/**< The F6 key */
	F7,								/**< The F7 key */
	F8,								/**< The F8 key */
	F9,								/**< The F9 key */
	F10,							/**< The F10 key */
	F11,							/**< The F11 key */
	F12,							/**< The F12 key */
	capsLock,						/**< The CapsLock key */
	leftShift,						/**< The left Shift key */
	rightShift,						/**< The right Shift key */
	leftControl,					/**< The left Control key */
	rightControl,					/**< The right Control key */
	leftWindow,						/**< The left Window key */
	rightWindow,					/**< The right Window key */
	leftAlt,						/**< The left Alternate key */
	rightAlt,						/**< The right Alternate key */
	enter,							/**< The Enter/Return key */
	printScreen,					/**< The PrintScreen key */
	scrollLock,						/**< The ScrollLock key */
	numLock,						/**< The NumLock key */
	pause,							/**< The pause/break key */
	insert,							/**< The insert key */
	home,							/**< The Home key */
	end,							/**< The End key */
	pageUp,							/**< The PageUp key */
	pageDown,						/**< The PageDown key */
	arrowDown,						/**< The ArrowDown key */
	arrowUp,						/**< The ArrowUp key */
	arrowLeft,						/**< The ArrowLeft key */
	arrowRight,						/**< The ArrowRight key */
	keypadDivide,					/**< The KeyPad Divide key */
	keypadMultiply,					/**< The Keypad Multiply key */
	keypadSubtract,					/**< The Keypad Subtract key */
	keypadAdd,						/**< The Keypad Add key */
	keypadEnter,					/**< The Keypad Enter key */
	keypadPeriod,					/**< The Keypad Period/Decimal key */
	keypad0,						/**< The Keypad 0 key */
	keypad1,						/**< The Keypad 1 key */
	keypad2,						/**< The Keypad 2 key */
	keypad3,						/**< The Keypad 3 key */
	keypad4,						/**< The Keypad 4 key */
	keypad5,						/**< The Keypad 5 key */
	keypad6,						/**< The Keypad 6 key */
	keypad7,						/**< The Keypad 7 key */
	keypad8,						/**< The keypad 8 key */
	keypad9,						/**< The Keypad 9 key */
	backspace,						/**< The Backspace key */
	tab,							/**< The Tab key */
	del,							/**< The Delete key */
	escape,							/**< The Escape key */
	last = escape,					/**< The last key to be supported */
};

enum class buttonState_t
{
	up,								/**< The mouse button is currently up */
	down							/**< The mouse button is currently down */
};

enum class mouseButton_t
{
	left,							/**< The left mouse button */
	right,							/**< The right mouse button */
	middle,							/**< The middle mouse button / ScrollWheel */
	last,							/**< The last mouse button to be supported */
};

enum class mouseScroll_t
{
	down,							/**< The mouse wheel up */
	up								/**< The mouse wheel down */
};

enum class style_t
{
	bare,							/**< The window has no decorators but the window border and title bar */
	normal,							/**< The default window style for the respective platform */
	popup,							/**< The window has no decorators */
};

enum class state_t
{
	normal,							/**< The window is in its default state */
	maximized,						/**< The window is currently maximized */
	minimized,						/**< The window is currently minimized */
	fullscreen,						/**< The window is currently full screen */
};

enum decorator_t
{
	titleBar = 0x01,				/**< The title bar decoration of the window */
	icon = 0x02,					/**< The icon decoration of the window */
	border = 0x04,					/**< The border decoration of the window */
	minimizeButton = 0x08,			/**< The minimize button decoration of the window */
	maximizeButton = 0x010,			/**< The maximize button decoration pf the window */
	closeButton = 0x20,				/**< The close button decoration of the window */
	sizeableBorder = 0x40,			/**< The sizable border decoration of the window */
};

typedef unsigned int resolution_t[2];
typedef unsigned int position_t[2];
typedef unsigned int mousePosition_t[2];
typedef unsigned int screenResolution_t[2];
typedef unsigned int screenMousePosition_t[2];

const int LINUX_FUNCTION = 1;
const int LINUX_DECORATOR = 2;

const int TW_error = -1;

class windowManager
{
	struct window_t;
	enum error_t : int;

public:

	windowManager(){}

	/**
	 * Shutdown and delete all windows in the manager
	 */
	~windowManager( void )
	{
		if ( !GetInstance()->windowList.empty() )
		{
			GetInstance()->windowList.clear();
		}
	}

	/**
	 * Use this to shutdown the window manager when your program is finished
	 */
	 static inline void ShutDown( void ) 
	{
		if (GetInstance()->IsInitialized())
		{
#if defined(__linux__)
			Linux_Shutdown();
#endif
			instance->windowList.clear();
			instance->isInitialized = false;
			
			delete instance;
			instance = nullptr;
		}
		else
		{
			PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		}
	}

	/**
	 * Use this to add a window to the manager. returns a pointer to the manager which allows for the easy creation of multiple windows
	 */
	static inline windowManager* AddWindow( const char* windowName, unsigned int width = defaultWindowWidth, unsigned int height = defaultWindowHeight, int colourBits = 8, int depthBits = 8, int stencilBits = 8 )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( IsValid( windowName ) )
			{
				std::unique_ptr<window_t> newWindow(new window_t);
				newWindow->name = windowName;
				newWindow->resolution[ 0 ] = width;
				newWindow->resolution[ 1 ] = height;
				newWindow->colorBits = colourBits;
				newWindow->depthBits = depthBits;
				newWindow->stencilBits = stencilBits;

				instance->windowList.push_back( std::move(newWindow));
				instance->windowList[instance->windowList.size() - 1]->iD = GetNumWindows() - 1;
				//newWindow->iD = GetNumWindows() - 1;

				Platform_InitializeWindow(instance->windowList[instance->windowList.size() - 1]);

				return instance;
			}
			PrintErrorMessage(std::error_code(invalidWindowName, errorCategory));
			return nullptr;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return nullptr;
	}

	/**
	 * Return the total amount of windows the manager has
	 */
	static inline int GetNumWindows( void )
	{
		if ( GetInstance()->IsInitialized() )
		{
			return instance->windowList.size();
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return TW_error;
	}

	/**
	 * Return the mouse position in screen co-ordinates
	 */
	static inline bool GetMousePositionInScreen( unsigned int& x, unsigned int& y )
	{
		if ( GetInstance()->IsInitialized() )
		{
			x = instance->screenMousePosition[0];
			y = instance->screenMousePosition[1];
			return true;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Return the mouse position in screen co-ordinates
	 */
	static inline unsigned int* GetMousePositionInScreen( void )
	{
		if ( GetInstance()->IsInitialized() )
		{
			return instance->screenMousePosition;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return nullptr;
	}

	/**
	 * Set the position of the mouse cursor relative to screen co-ordinates
	 */
	static inline bool SetMousePositionInScreen( mousePosition_t mousePosition )
	{
		if ( GetInstance()->IsInitialized() )
		{
			instance->screenMousePosition[0] = mousePosition[0];
			instance->screenMousePosition[1] = mousePosition[1];

#if defined(TW_WINDOWS)
			SetCursorPos(mousePosition[0], mousePosition[1]);
#elif defined(TW_LINUX)
			XWarpPointer(instance->currentDisplay, None,
				XDefaultRootWindow(instance->currentDisplay), 0, 0,
				GetScreenResolution()[0],
				GetScreenResolution()[1],
				mousePosition[0], mousePosition[1]);
#endif
			return true;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the position of the mouse cursor relative to screen co-ordinates
	*/
	static inline bool SetMousePositionInScreen(unsigned int x, unsigned int y)
	{
		if (GetInstance()->IsInitialized())
		{
			instance->screenMousePosition[0] = x;
			instance->screenMousePosition[1] = y;

#if defined(TW_WINDOWS)
			SetCursorPos(x, y);
#elif defined(TW_LINUX)
			XWarpPointer(instance->currentDisplay, None,
				XDefaultRootWindow(instance->currentDisplay), 0, 0,
				GetScreenResolution()[0],
				GetScreenResolution()[1],
				x, y);
#endif
			return true;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Return the Resolution of the current screen
	 */
	static inline unsigned int* GetScreenResolution( void )
	{
		if ( GetInstance()->IsInitialized() )
		{
#if defined(TW_WINDOWS)
			RECT screen;
			HWND desktop = GetDesktopWindow();
			GetWindowRect( desktop, &screen );

			instance->screenResolution[0] = screen.right;
			instance->screenResolution[1] = screen.bottom;
			return instance->screenResolution;

#elif defined(TW_LINUX)
			instance->screenResolution[0] = WidthOfScreen(XDefaultScreenOfDisplay(instance->currentDisplay));
			instance->screenResolution[1] = HeightOfScreen(XDefaultScreenOfDisplay(instance->currentDisplay));

			return instance->screenResolution;
#endif
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return nullptr;
	}
	/**
	 * Return the Resolution of the current screen
	 */
	static inline bool GetScreenResolution( unsigned int& width, unsigned int& Height )
	{
		if ( GetInstance()->IsInitialized() )
		{
#if defined(TW_WINDOWS)
			RECT screen;
			HWND desktop = GetDesktopWindow();
			GetWindowRect( desktop, &screen );
			width = screen.right;
			Height = screen.bottom;
#elif defined(TW_LINUX)
			width = WidthOfScreen(XDefaultScreenOfDisplay(instance->currentDisplay));
			Height = HeightOfScreen(XDefaultScreenOfDisplay(instance->currentDisplay));

			instance->screenResolution[0] = width;
			instance->screenResolution[1] = Height;
#endif
			return true;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Return the Resolution of the given window by setting width and height
	 */
	static inline bool GetWindowResolutionByName( const char* windowName, unsigned int& width, unsigned int& height )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				width = GetWindowByName( windowName )->resolution[ 0 ];
				height = GetWindowByName( windowName )->resolution[ 1 ];
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Return the Resolution of the given window by setting width and height
	 */
	static inline bool GetWindowResolutionByIndex( unsigned int windowIndex, unsigned int& width, unsigned int& height )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				width = GetWindowByIndex( windowIndex )->resolution[ 0 ];
				height = GetWindowByIndex( windowIndex )->resolution[ 1 ];

				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Return the Resolution of the given Window as an array of doubles
	 */
	static inline unsigned int* GetWindowResolutionByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->resolution;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return nullptr;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return nullptr;
	}
	/**
	 * Return the Resolution of the Given Window as an array of doubles
	 */
	static inline unsigned int* GetWindowResolutionByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->resolution;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return nullptr;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return nullptr;
	}

	/**
	 * Set the Size/Resolution of the given window
	 */
	static inline bool SetWindowResolutionByName( const char* windowName, resolution_t resolution )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				GetWindowByName( windowName )->resolution[ 0 ] = resolution[0];
				GetWindowByName( windowName )->resolution[ 1 ] = resolution[1];
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);

				Platform_SetWindowResolution(window);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(invalidContext, errorCategory));
		return false;
	}
	/**
	 * Set the Size/Resolution of the given window
	 */
	static inline bool SetWindowResolutionByIndex( unsigned int windowIndex, resolution_t resolution )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( WindowExists( windowIndex ) )
			{
				GetWindowByIndex(windowIndex)->resolution[0] = resolution[0];
				GetWindowByIndex( windowIndex )->resolution[ 1 ] = resolution[1];
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);

				Platform_SetWindowResolution(window);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/** 
	 * Set the Size/Resolution of the given window
	 */
	static inline bool SetWindowResolutionByName(const char* windowName, unsigned int width, unsigned int height)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByName(windowName))
			{
				GetWindowByName(windowName)->resolution[0] = width;
				GetWindowByName(windowName)->resolution[1] = height;
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);

				Platform_SetWindowResolution(window);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(invalidContext, errorCategory));
		return false;
	}
	/**
	* Set the Size/Resolution of the given window
	*/
	static inline bool SetWindowResolutionByIndex(unsigned int windowIndex, unsigned int width, unsigned int height)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByIndex(windowIndex))
			{
				GetWindowByIndex(windowIndex)->resolution[0] = width;
				GetWindowByIndex(windowIndex)->resolution[1] = height;
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);

				Platform_SetWindowResolution(window);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(invalidContext, errorCategory));
		return false;
	}

	/**
	 * Return the Position of the given window relative to screen co-ordinates by setting X and Y
	 */ 
	static inline bool GetWindowPositionByName( const char* windowName, unsigned int& x, unsigned int& y )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				x = GetWindowByName( windowName )->position[ 0 ];
				y = GetWindowByName( windowName )->position[ 1 ];
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Return the Position of the given window relative to screen co-ordinates by setting X and Y
	 */
	static inline bool GetWindowPositionByIndex( unsigned int windowIndex, unsigned int& x, unsigned int& y )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				x = GetWindowByIndex( windowIndex )->position[ 0 ];
				y = GetWindowByIndex( windowIndex )->position[ 1 ];
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Return the Position of the given window relative to screen co-ordinates as an array
	 */
	static inline unsigned int* GetWindowPositionByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->position;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return nullptr;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return nullptr;
	}
	/**
	 * Return the Position of the given window relative to screen co-ordinates as an array
	 */
	static inline unsigned int* GetWindowPositionByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->position;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return nullptr;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return nullptr;
	}

	/**
	 * Set the Position of the given window relative to screen co-ordinates
	 */
	static inline bool SetWindowPositionByName( const char* windowName, position_t windowPosition )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				GetWindowByName( windowName )->position[ 0 ] = windowPosition[0];
				GetWindowByName( windowName )->position[ 1 ] = windowPosition[1];
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);

				Platform_SetWindowPosition(window, windowPosition[0], windowPosition[1]);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Set the position of the given window relative to screen co-ordinates
	 */
	static inline bool SetWindowPositionByIndex( unsigned int windowIndex, position_t windowPosition )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				GetWindowByIndex( windowIndex )->position[ 0 ] = windowPosition[0];
				GetWindowByIndex( windowIndex )->position[ 1 ] = windowPosition[1];
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
				Platform_SetWindowPosition(window, windowPosition[0], windowPosition[1]);
				return true;
			}

			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the Position of the given window relative to screen co-ordinates
	*/
	static inline bool SetWindowPositionByName(const char* windowName, unsigned int x, unsigned int y)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByName(windowName))
			{
				GetWindowByName(windowName)->position[0] = x;
				GetWindowByName(windowName)->position[1] = y;
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);

				Platform_SetWindowPosition(window, x, y);
				PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the position of the given window relative to screen co-ordinates
	*/
	static inline bool SetWindowPositionByIndex(unsigned int windowIndex, unsigned int x, unsigned int y)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByIndex(windowIndex))
			{
				GetWindowByIndex(windowIndex)->position[0] = x;
				GetWindowByIndex(windowIndex)->position[1] = y;
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
				Platform_SetWindowPosition(window, x, y);
				return true;
			}

			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Return the mouse Position relative to the given window's co-ordinates by setting X and Y
	 */
	static inline bool GetMousePositionInWindowByName( const char* windowName, unsigned int& x, unsigned int& y )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				x = GetWindowByName( windowName )->mousePosition[ 0 ];
				y = GetWindowByName( windowName )->mousePosition[ 1 ];
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Return the mouse position relative to the given window's co-ordinates by setting X and Y
	 */
	static inline bool GetMousePositionInWindowByIndex( unsigned int windowIndex, unsigned int& x, unsigned int& y )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				x = GetWindowByIndex( windowIndex )->mousePosition[ 0 ];
				y = GetWindowByIndex( windowIndex )->mousePosition[ 1 ];
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return (bool)TW_error;
	}

	/**
	 * Return the mouse Position relative to the given window's co-ordinates as an array
	 */
	static inline unsigned int* GetMousePositionInWindowByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->mousePosition;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return nullptr;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return nullptr;
	}
	/**
	 * Return the mouse Position relative to the given window's co-ordinates as an array
	 */
	static inline unsigned int* GetMousePositionInWindowByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->mousePosition;
			}
			return nullptr;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return nullptr;
	}

	/**
	 * Set the mouse Position of the given window's co-ordinates
	 */
	static inline bool SetMousePositionInWindowByName( const char* windowName, mousePosition_t mousePosition )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				GetWindowByName( windowName )->mousePosition[ 0 ] = mousePosition[0];
				GetWindowByName( windowName )->mousePosition[ 1 ] = mousePosition[1];
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);
				Platform_SetMousePositionInWindow(window, mousePosition[0], mousePosition[1]);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Set the mouse Position of the given window's co-ordinates
	 */
	static inline bool SetMousePositionInWindowByIndex( unsigned int windowIndex, mousePosition_t mousePosition )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				GetWindowByIndex( windowIndex )->mousePosition[ 0 ] = mousePosition[0];
				GetWindowByIndex( windowIndex )->mousePosition[ 1 ] = mousePosition[1];
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);

				Platform_SetMousePositionInWindow(window, mousePosition[0], mousePosition[1]);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the mouse Position of the given window's co-ordinates
	*/
	static inline bool SetMousePositionInWindowByIndex(unsigned int windowIndex, unsigned int x, unsigned int y)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByIndex(windowIndex))
			{
				GetWindowByIndex(windowIndex)->mousePosition[0] = x;
				GetWindowByIndex(windowIndex)->mousePosition[1] = y;
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);

				Platform_SetMousePositionInWindow(window, x, y);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the mouse Position of the given window's co-ordinates
	*/
	static inline bool SetMousePositionInWindowByName(const char* windowName, unsigned int x, unsigned int y)
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByName(windowName))
			{
				GetWindowByName(windowName)->mousePosition[0] = x;
				GetWindowByName(windowName)->mousePosition[1] = y;
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);
				Platform_SetMousePositionInWindow(window, x, y);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Returns the current state of the given key relative to the given window
	 */
	static inline keyState_t WindowGetKeyByName( const char* windowName, unsigned int key )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->keys[ key ];
			}

			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return keyState_t::bad;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return keyState_t::bad;
	}
	/**
	 * Returns the current state of the given key relative to the given window
	 */
	static inline keyState_t WindowGetKeyByIndex(unsigned int windowIndex, unsigned int key)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->keys[ key ];
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return keyState_t::bad;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return keyState_t::bad;
	}

	/**
	 * Return whether the given window should be closing
	 */
	static inline bool GetWindowShouldCloseByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->shouldClose;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Return whether the given window should be closing
	 */
	static inline bool GetWindowShouldCloseByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->shouldClose;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Swap the draw buffers of the given window
	 */
	static inline bool WindowSwapBuffersByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);
				Platform_SwapBuffers(window);

				return true;
			}
			PrintErrorMessage(std::error_code(notInitialized, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Swap the draw buffers of the given window
	 */
	static inline bool WindowSwapBuffersByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
				Platform_SwapBuffers(window);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Make the given window be the current OpenGL Context to be drawn to
	 */
	static inline bool MakeWindowCurrentContextByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);
				Platform_MakeCurrentContext(window);

				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Make the given window be the current OpenGL Context to be drawn to
	 */
	static inline bool MakeWindowCurrentContextByIndex( unsigned int windowIndex )
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByIndex(windowIndex))
			{
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
				Platform_MakeCurrentContext(window);

				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Return whether the given window is in full screen mode
	 */
	static inline bool GetWindowIsFullScreenByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return (GetWindowByName(windowName)->currentState == state_t::fullscreen);
			}

			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Return whether the given window is in full screen mode
	 */
	static inline bool GetWindowIsFullScreenByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return (GetWindowByIndex(windowIndex)->currentState == state_t::fullscreen);
			}

			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}	

	/**
	 * Toggle the given window's full screen mode
	 */
	static inline bool SetFullScreenByName( const char* windowName, bool newState )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);

				window->currentState = (newState == true) ? state_t::fullscreen : state_t::normal;

				Platform_SetFullScreen(window);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/*
	 * Toggle the given window's full screen mode
	 */
	static inline bool SetFullScreenByIndex( unsigned int windowIndex, bool newState )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
				window->currentState = (newState == true) ? state_t::fullscreen : state_t::normal;

				Platform_SetFullScreen(window);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage( std::error_code(notInitialized, errorCategory ));
		return false;
	}

	/**
	 * Returns whether the given window is minimized
	 */
	static inline bool GetWindowIsMinimizedByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return (GetWindowByName(windowName)->currentState == state_t::minimized);
			}
			return (bool)TW_error;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return (bool)TW_error;
	}
	/**
	 * Returns whether the given window is minimized
	 */
	static inline bool GetWindowIsMinimizedByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return (GetWindowByIndex(windowIndex)->currentState == state_t::minimized);
			}
			return (bool)TW_error;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return (bool)TW_error;
	}

	/**
	 * Toggle the minimization state of the given window
	 */
	static inline bool MinimizeWindowByName( const char* windowName, bool newState )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);
				Platform_MinimizeWindow(window, newState);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Toggle the minimization state of the window
	 */
	static inline bool MinimizeWindowByIndex( unsigned int windowIndex, bool newState )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
				Platform_MinimizeWindow(window, newState);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Return whether the current window is currently maximized
	 */
	static inline bool GetWindowIsMaximizedByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return (GetWindowByName(windowName)->currentState == state_t::maximized);
			}

			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Return whether the given window is currently maximized
	 */
	static inline bool GetWindowIsMaximizedByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return (GetWindowByIndex(windowIndex)->currentState == state_t::maximized);
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	
	/**
	 * Toggle the maximization state of the current window
	 */
	static inline bool MaximizeWindowByName( const char* windowName, bool newState )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);
				Platform_MaximizeWindow(window, newState);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	 * Toggle the maximization state of the current window
	 */
	static inline bool MaximizeWindowByIndex( unsigned int windowIndex, bool newState )
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByIndex(windowIndex))
			{
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
				Platform_MaximizeWindow(window, newState);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Get window name by index
	 */
	static inline const char* GetWindowNameByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->name;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return nullptr;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return nullptr;
	}	
	/**
	* Get window index by name
	*/
	static inline unsigned int GetWindowIndexByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->iD;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Set the window title bar	by name
	 */
	static inline bool SetWindowTitleBarByName( const char* windowName, const char* newTitle )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if (IsValid(newTitle))
			{
				if (DoesExistByName(windowName))
				{
					std::unique_ptr<window_t>& window = GetWindowByName(windowName);
					Platform_SetWindowTitleBar(window, newTitle);
					return true;
				}
				PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(invalidWindowName, errorCategory));
			return false;
		}			
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window title bar by index
	*/
	static inline bool SetWindowTitleBarByIndex( unsigned int windowIndex, const char* newName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if (IsValid(newName))
			{
				if (DoesExistByIndex(windowIndex))
				{
					std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
					Platform_SetWindowTitleBar(window, newName);
					return true;
				}
				PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(invalidWindowName, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window icon by name (currently not functional)
	*/
	static inline bool SetWindowIconByName( void )//const char* windowName, const char* icon, unsigned int width, unsigned int height )
	{
		PrintErrorMessage(std::error_code(functionNotImplemented, errorCategory));
		return false;
	/*	if ( GetInstance()->IsInitialized() )
		{
			if (IsValid(icon))
			{
				if (DoesExistByName(windowName))
				{
#if defined(TW_WINDOWS)
					//Windows_SetWindowIcon(GetWindowByName(windowName), icon, width, height);
#elif defined(TW_LINUX)
					//Linux_SetWindowIcon();//GetWindowByName(windowName), icon, width, height);
#endif
					return true;
				}
				TinyWindow_PrintErrorMessage(std::error_code(tinyWindowError_t::TW_error_WINDOW_NOT_FOUND);
				return false;
			}

			TinyWindow_PrintErrorMessage(std::error_code(tinyWindowError_t::TW_error_INVALID_ICON_PATH);
			return false;
		}

		TinyWindow_PrintErrorMessage( std::error_code(tinyWindowError_t::TW_error_NOT_INITIALIZED );
		return false;*/
	}
	/**
	* Set the window icon by index (currently not functional)
	*/
	static inline bool SetWindowIconByIndex( void )//unsigned int windowIndex, const char* icon, unsigned int width, unsigned int height )
	{
		PrintErrorMessage(std::error_code(functionNotImplemented, errorCategory));
		return false;
		/*if ( GetInstance()->IsInitialized() )
		{
			if (IsValid(icon))
			{
				if (DoesExistByIndex(windowIndex))
				{
#if defined(TW_WINDOWS)
					Windows_SetWindowIcon(GetWindowByIndex(windowIndex), icon, width, height);
#elif defined(TW_LINUX)
					Linux_SetWindowIcon(GetWindowByIndex(windowIndex), icon, width, height);
#endif
					return true;
				}
				TinyWindow_PrintErrorMessage(std::error_code(tinyWindowError_t::TW_error_WINDOW_NOT_FOUND);
				return false;
			}
			TinyWindow_PrintErrorMessage(std::error_code(tinyWindowError_t::TW_error_INVALID_ICON_PATH);
			return false;
		}
		TinyWindow_PrintErrorMessage( std::error_code(tinyWindowError_t::TW_error_NOT_INITIALIZED );
		return false;*/
	}

	/**
	* Get whether the window is in focus by name
	*/
	static inline bool GetWindowIsInFocusByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->inFocus;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Get whether the window is in focus by index
	*/
	static inline bool GetWindowIsInFocusByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->inFocus;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window to be in focus by name
	*/
	static inline bool FocusWindowByName( const char* windowName, bool newState )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);
				Platform_FocusWindow(window, newState);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window to be in focus by index
	*/
	static inline bool FocusWindowByIndex( unsigned int windowIndex, bool newState )
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByIndex(windowIndex))
			{
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
				Platform_FocusWindow(window, newState);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	 * Restore the window by name
	 */
	static inline bool RestoreWindowByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);
				Platform_RestoreWindow(window);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Restore the window by index
	*/
	static inline bool RestoreWindowByIndex( unsigned int windowIndex )
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByIndex(windowIndex))
			{
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
				Platform_RestoreWindow(window);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Initialize the window manager
	*/
	static inline bool Initialize( void )
	{
		GetInstance()->isInitialized = false;
#if defined(TW_WINDOWS)
		CreateTerminal();
		RECT desktop;

		HWND desktopHandle = GetDesktopWindow();

		if (desktopHandle)
		{
			GetWindowRect(desktopHandle, &desktop);

			instance->screenResolution[0] = desktop.right;
			instance->screenResolution[1] = desktop.bottom;
			instance->isInitialized = true;
			return true;
		}

		PrintErrorMessage(std::error_code(windowsCannotInitialize, errorCategory));
		return false;
#elif defined(TW_LINUX)
		instance->currentDisplay = XOpenDisplay(0);

		if (!instance->currentDisplay)
		{
			PrintErrorMessage(std::error_code(linuxCannotConnectXServer, errorCategory));
			return false;
		}

		instance->screenResolution[0] = WidthOfScreen(
			XScreenOfDisplay(instance->currentDisplay,
			DefaultScreen(instance->currentDisplay)));

		instance->screenResolution[1] = HeightOfScreen(
			XScreenOfDisplay(instance->currentDisplay,
			DefaultScreen(instance->currentDisplay)));

		instance->isInitialized = true;
		return true;
#endif
	}

	/**
	* Return whether the window manager has been initialized
	*/
	static inline bool IsInitialized( void )
	{
		return GetInstance()->isInitialized;
	}

	/**
	* Ask the window manager to poll for events
	*/
	static inline void PollForEvents( void )
	{
		if ( GetInstance()->IsInitialized() )
		{
#if defined(TW_WINDOWS)
			//only process events if there are any to process
			if (PeekMessage(&instance->message, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&instance->message);
				DispatchMessage(&instance->message);
			}
#elif defined(TW_LINUX)
			//if there are any events to process
			if (XEventsQueued(instance->currentDisplay, QueuedAfterReading))
			{
				XNextEvent(instance->currentDisplay, &instance->currentEvent);

				XEvent currentEvent = instance->currentEvent;

				Linux_ProcessEvents(currentEvent);
			}
#endif
		}

		else
		{
			PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		}
	}

	/**
	* Ask the window manager to wait for events
	*/
	static inline void WaitForEvents( void )
	{
		if ( GetInstance()->IsInitialized() )
		{
#if defined(TW_WINDOWS)
			//process even if there aren't any to process
			GetMessage(&instance->message, 0, 0, 0);
			TranslateMessage(&instance->message);
			DispatchMessage(&instance->message);
#elif defined(TW_LINUX)
			//even if there aren't any events to process
			XNextEvent(instance->currentDisplay, &instance->currentEvent);

			XEvent currentEvent = instance->currentEvent;

			Linux_ProcessEvents(currentEvent);
#endif
		}

		else
		{
			PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		}
	}

	/**
	* Remove window from the manager by name
	*/
	static inline bool RemoveWindowByName( const char* windowName ) 
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				ShutdownWindow( GetWindowByName( windowName ) );
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Remove window from the manager by index
	*/
	static inline bool RemoveWindowByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				ShutdownWindow( GetWindowByIndex( windowIndex ) );
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window style preset by name
	*/
	static inline bool SetWindowStyleByName( const char* windowName, style_t windowStyle )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);
				Platform_SetWindowStyle(window, windowStyle);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window style preset by index
	*/
	static inline bool SetWindowStyleByIndex( unsigned int windowIndex, style_t windowStyle )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
				Platform_SetWindowStyle(window, windowStyle);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Enable window decorators by name
	*/
	static inline bool EnableWindowDecoratorsByName( const char* windowName, unsigned int decorators )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);
				Platform_EnableWindowDecorators(window, decorators);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Enable windows decorators by index
	*/
	static inline bool EnableWindowDecoratorsByIndex( unsigned int windowIndex, unsigned int decorators )
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByIndex(windowIndex))
			{
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
				Platform_EnableWindowDecorators(window, decorators);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Disable windows decorators by name
	*/
	static inline bool DisableWindowDecoratorByName( const char* windowName, unsigned int decorators )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByName(windowName);
				Platform_DisableWindowDecorators(window, decorators);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Disable windows decorators by index
	*/
	static inline bool DisableWindowDecoratorByIndex( unsigned int windowIndex, unsigned int decorators )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				std::unique_ptr<window_t>& window = GetWindowByIndex(windowIndex);
				Platform_DisableWindowDecorators(window, decorators);
				return true;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window on key event callback by name
	*/
	static inline bool SetWindowOnKeyEventByName(const char* windowName, std::function<void(unsigned int, keyState_t)> onKey)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				if (onKey != nullptr)
				{
					GetWindowByName(windowName)->keyEvent = onKey;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}

			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window on key event callback by index
	*/
	static inline bool SetWindowOnKeyEventByIndex(unsigned int windowIndex, std::function<void(unsigned int, keyState_t)> onKey)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				if (onKey != nullptr)
				{
					GetWindowByIndex(windowIndex)->keyEvent = onKey;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window on mouse button event callback by name
	*/
	static inline bool SetWindowOnMouseButtonEventByName(const char* windowName, std::function<void(mouseButton_t, buttonState_t)> onMouseButton)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				if (onMouseButton != nullptr)
				{
					GetWindowByName(windowName)->mouseButtonEvent = onMouseButton;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window on mouse button event callback by index
	*/
	static inline bool SetWindowOnMouseButtonEventByIndex(unsigned int windowIndex, std::function<void(mouseButton_t, buttonState_t)> onMouseButton)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				if (onMouseButton != nullptr)
				{
					GetWindowByIndex(windowIndex)->mouseButtonEvent = onMouseButton;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window on mouse wheel event callback by name
	*/
	static inline bool SetWindowOnMouseWheelEventByName(const char* windowName, std::function<void(mouseScroll_t)> onMouseWheel)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				if (onMouseWheel != nullptr)
				{
					GetWindowByName(windowName)->mouseWheelEvent = onMouseWheel;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window on mouse wheel event callback by index
	*/
	static inline bool SetWindowOnMouseWheelEventByIndex(unsigned int windowIndex, std::function<void(mouseScroll_t)> onMouseWheel)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				if (onMouseWheel != nullptr)
				{
					GetWindowByIndex(windowIndex)->mouseWheelEvent = onMouseWheel;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window on destroyed event callback by name
	*/
	static inline bool SetWindowOnDestroyedByName(const char* windowName, std::function<void(void)> onDestroyed)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				if (onDestroyed != nullptr)
				{
					GetWindowByName(windowName)->destroyedEvent = onDestroyed;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window on destroyed event callback by index
	*/
	static inline bool SetWindowOnDestroyedByIndex(unsigned int windowIndex, std::function<void(void)> onDestroyed)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				if (onDestroyed != nullptr)
				{
					GetWindowByIndex(windowIndex)->destroyedEvent = onDestroyed;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window on maximized event callback by name
	*/
	static inline bool SetWindowOnMaximizedByName(const char* windowName, std::function<void(void)> onMaximized)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				if (onMaximized != nullptr)
				{
					GetWindowByName(windowName)->maximizedEvent = onMaximized;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window on maximized event callback by index
	*/
	static inline bool SetWindowOnMaximizedByIndex(unsigned int windowIndex, std::function<void(void)> onMaximized)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				if (onMaximized != nullptr)
				{
					GetWindowByIndex(windowIndex)->maximizedEvent = onMaximized;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window on minimized event callback by name
	*/
	static inline bool SetWindowOnMinimizedByName(const char* windowName, std::function<void(void)> onMinimized)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				if (onMinimized != nullptr)
				{
					GetWindowByName(windowName)->minimizedEvent = onMinimized;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window on minimized event callback by index
	*/
	static inline bool SetWindowOnMinimizedByIndex(unsigned int windowIndex, std::function<void(void)> onMinimized)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				if (onMinimized != nullptr)
				{
					GetWindowByIndex(windowIndex)->minimizedEvent = onMinimized;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window on focus event callback by name
	*/
	static inline bool SetWindowOnFocusByName(const char* windowName, std::function<void(bool)> onFocus)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				if (onFocus != nullptr)
				{
					GetWindowByName(windowName)->focusEvent = onFocus;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window on focus event callback by index
	*/
	static inline bool SetWindowOnFocusByIndex(unsigned int windowIndex, std::function<void(bool)> onFocus)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				if (onFocus != nullptr)
				{
					GetWindowByIndex(windowIndex)->focusEvent = onFocus;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window on moved event callback by name
	*/
	static inline bool SetWindowOnMovedByName(const char* windowName, std::function<void(unsigned int, unsigned int)> onMoved)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				if (onMoved != nullptr)
				{
					GetWindowByName(windowName)->movedEvent = onMoved;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}

			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window on moved event callback by index
	*/
	static inline bool SetWindowOnMovedByIndex(unsigned int windowIndex, std::function<void(unsigned int, unsigned int)> onMoved)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				if (onMoved != nullptr)
				{
					GetWindowByIndex(windowIndex)->movedEvent = onMoved;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window on resized event callback by name
	*/
	static inline bool SetWindowOnResizeByName(const char* windowName, std::function<void(unsigned int, unsigned int)> onResize)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				if (onResize != nullptr)
				{
					GetWindowByName(windowName)->resizeEvent = onResize;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window on resized event callback by index
	*/
	static inline bool SetWindowOnResizeByIndex(unsigned int windowIndex, std::function<void(unsigned int, unsigned int)> onResize)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				if (onResize != nullptr)
				{
					GetWindowByIndex(windowIndex)->resizeEvent = onResize;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	/**
	* Set the window on mouse move event callback by name
	*/
	static inline bool SetWindowOnMouseMoveByName(const char* windowName, std::function<void(unsigned int, unsigned int, unsigned int, unsigned int)> onMouseMove)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				if (onMouseMove != nullptr)
				{
					GetWindowByName(windowName)->mouseMoveEvent = onMouseMove;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}
	/**
	* Set the window on mouse move event callback by index
	*/
	static inline bool SetWindowOnMouseMoveByIndex(unsigned int windowIndex, std::function<void(unsigned int, unsigned int, unsigned int, unsigned int)> onMouseMove)
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				if (onMouseMove != nullptr)
				{
					GetWindowByIndex(windowIndex)->mouseMoveEvent = onMouseMove;
					return true;
				}
				PrintErrorMessage(std::error_code(invalidCallback, errorCategory));
				return false;
			}
			PrintErrorMessage(std::error_code(windowNotFound, errorCategory));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

private:

	enum error_t : int
	{
		invalidWindowName,					/**< If an invalid window name was given */
		invalidIconPath,					/**< If an invalid icon path was given */
		invalidWindowIndex,					/**< If an invalid window index was given */
		invalidWindowState,					/**< If an invalid window state was given */
		invalidResolution,					/**< If an invalid window resolution was given */
		invalidContext,						/**< If the OpenGL context for the window is invalid */
		existingContext,					/**< If the window already has an OpenGL context */
		notInitialized,						/**< If the window is being used without being initialized */
		alreadyInitialized,					/**< If the window was already initialized */
		invalidTitlebar,					/**< If the Title-bar text given was invalid */
		invalidCallback,					/**< If the given event callback was invalid */
		windowNotFound,						/**< If the window was not found in the window manager */
		invalidWindowStyle,					/**< If the window style gives is invalid */
		functionNotImplemented,				/**< If the function has not yet been implemented in the current version of the API */
		linuxCannotConnectXServer,			/**< Linux: if cannot connect to an X11 server */
		linuxInvalidVisualinfo,				/**< Linux: if visual information given was invalid */
		linuxCannotCreateWindow,			/**< Linux: when X11 fails to create a new window */
		linuxFunctionNotImplemented,		/**< Linux: when the function has not yet been implemented on the Linux in the current version of the API */
		windowsCannotCreateWindows,			/**< Windows: when Win32 cannot create a window */
		windowsCannotInitialize,			/**< Windows: when Win32 cannot initialize */
		windowsFunctionNotImplemented,		/**< Windows: when a function has yet to be implemented on the Windows platform in the current version of the API */
	};

	struct window_t
	{
		const char*						name;													/**< Name of the window */
		unsigned int					iD;														/**< ID of the Window. ( where it belongs in the window manager ) */
		int								colorBits;												/**< Color format of the window. ( defaults to 32 bit color ) */
		int								depthBits;												/**< Size of the Depth buffer. ( defaults to 8 bit depth ) */
		int								stencilBits;											/**< Size of the stencil buffer, ( defaults to 8 bit ) */
		keyState_t						keys[last];												/**< Record of keys that are either pressed or released in the respective window */
		buttonState_t					mouseButton[(unsigned int)mouseButton_t::last];			/**< Record of mouse buttons that are either presses or released */
		resolution_t					resolution;												/**< Resolution/Size of the window stored in an array */
		position_t						position;												/**< Position of the Window relative to the screen co-ordinates */
		mousePosition_t					mousePosition;											/**< Position of the Mouse cursor relative to the window co-ordinates */
		bool							shouldClose;											/**< Whether the Window should be closing */
		bool							inFocus;												/**< Whether the Window is currently in focus( if it is the current window be used ) */

		bool							initialized;											/**< Whether the window has been successfully initialized */
		bool							contextCreated;											/**< Whether the OpenGL context has been successfully created */
		bool							isCurrentContext;										/**< Whether the window is the current window being drawn to */

		state_t							currentState;											/**< The current state of the window. these states include Normal, Minimized, Maximized and Full screen */
		unsigned int					currentWindowStyle;										/**< The current style of the window */

		std::function<void(unsigned int, keyState_t)>										keyEvent;					/**< This is the callback to be used when a key has been pressed */
		std::function<void(mouseButton_t, buttonState_t)>									mouseButtonEvent;			/**< This is the callback to be used when a mouse button has been pressed */
		std::function<void(mouseScroll_t)>													mouseWheelEvent;			/**< This is the callback to be used when the mouse wheel has been scrolled. */
		std::function<void(void)>															destroyedEvent;				/**< This is the callback to be used when the window has been closed in a non-programmatic fashion */
		std::function<void(void)>															maximizedEvent;				/**< This is the callback to be used when the window has been maximized in a non-programmatic fashion */
		std::function<void(void)>															minimizedEvent;				/**< This is the callback to be used when the window has been minimized in a non-programmatic fashion */
		std::function<void(bool)>															focusEvent;					/**< This is the callback to be used when the window has been given focus in a non-programmatic fashion */
		std::function<void(unsigned int, unsigned int)>										movedEvent;					/**< This is the callback to be used the window has been moved in a non-programmatic fashion */
		std::function<void(unsigned int, unsigned int)>										resizeEvent;				/**< This is a callback to be used when the window has been resized in a non-programmatic fashion */
		std::function<void(unsigned int, unsigned int, unsigned int, unsigned int)>			mouseMoveEvent;				/**< This is a callback to be used when the mouse has been moved */

#if defined(TW_WINDOWS)
			
		HDC							deviceContextHandle;			/**< A handle to a device context */
		HGLRC						glRenderingContextHandle;		/**< A handle to an OpenGL rendering context*/
		HPALETTE					paletteHandle;					/**< A handle to a Win32 palette*/
		PIXELFORMATDESCRIPTOR		pixelFormatDescriptor;			/**< Describes the pixel format of a drawing surface*/
		WNDCLASS					windowClass;					/**< Contains the window class attributes */
		HWND						windowHandle;					/**< A handle to A window */
		HINSTANCE					instanceHandle;

#else
		Window						windowHandle;					/**< The X11 handle to the window. I wish they didn't name the type 'Window' */
		GLXContext					context;						/**< The handle to the GLX rendering context */
		XVisualInfo*				visualInfo;						/**< The handle to the Visual Information. similar purpose to PixelformatDesriptor */
		int*						attributes;						/**< Attributes of the window. RGB, depth, stencil, etc */
		XSetWindowAttributes		setAttributes;					/**< The attributes to be set for the window */
		unsigned int				decorators;						/**< Enabled window decorators */

		/* these atoms are needed to change window states via the extended window manager
		I might move them to window manager considering these are essentially constants	*/
		Atom						AtomState;						/**< Atom for the state of the window */							// _NET_WM_STATE
		Atom						AtomHidden;						/**< Atom for the current hidden state of the window */				// _NET_WM_STATE_HIDDEN
		Atom						AtomFullScreen;					/**< Atom for the full screen state of the window */				// _NET_WM_STATE_FULLSCREEN
		Atom						AtomMaxHorz;					/**< Atom for the maximized horizontally state of the window */		// _NET_WM_STATE_MAXIMIZED_HORZ
		Atom						AtomMaxVert;					/**< Atom for the maximized vertically state of the window */		// _NET_WM_STATE_MAXIMIZED_VERT
		Atom						AtomClose;						/**< Atom for closing the window */									// _NET_WM_CLOSE_WINDOW
		Atom						AtomActive;						/**< Atom for the active window */									// _NET_ACTIVE_WINDOW
		Atom						AtomDemandsAttention;			/**< Atom for when the window demands attention */					// _NET_WM_STATE_DEMANDS_ATTENTION
		Atom						AtomFocused;					/**< Atom for the focused state of the window */					// _NET_WM_STATE_FOCUSED
		Atom						AtomCardinal;					/**< Atom for cardinal coordinates */								// _NET_WM_CARDINAL
		Atom						AtomIcon;						/**< Atom for the icon of the window */								// _NET_WM_ICON
		Atom						AtomHints;						/**< Atom for the window decorations */								// _NET_WM_HINTS

		Atom						AtomWindowType;					/**< Atom for the type of window */
		Atom						AtomWindowTypeDesktop;			/**< Atom for the desktop window type */							//_NET_WM_WINDOW_TYPE_SPLASH
		Atom						AtomWindowTypeSplash;			/**< Atom for the splash screen window type */
		Atom						AtomWindowTypeNormal;			/**< Atom for the normal splash screen window type */

		Atom						AtomAllowedActions;				/**< Atom for allowed window actions */
		Atom						AtomActionResize;				/**< Atom for allowing the window to be resized */
		Atom						AtomActionMinimize;				/**< Atom for allowing the window to be minimized */
		Atom						AtomActionShade;				/**< Atom for allowing the window to be shaded */
		Atom						AtomActionMaximizeHorz;			/**< Atom for allowing the window to be maximized horizontally */
		Atom						AtomActionMaximizeVert;			/**< Atom for allowing the window to be maximized vertically */
		Atom						AtomActionClose;				/**< Atom for allowing the window to be closed */

		Atom						AtomDesktopGeometry;			/**< Atom for Desktop Geometry */
#endif

		window_t(const char* name = nullptr, unsigned int iD = 0,
			unsigned int colorBits = 0, unsigned int depthBits = 0, unsigned int stencilBits = 0,
			bool shouldClose = false, state_t currentState = state_t::normal,
			std::function<void(unsigned int, keyState_t)> keyEvent = nullptr,
			std::function<void(mouseButton_t, buttonState_t)> mouseButtonEvent = nullptr, std::function<void(mouseScroll_t)> mouseWheelEvent = nullptr,
			std::function<void(void)> destroyedEvent = nullptr, std::function<void(void)> maximizedEvent = nullptr, std::function<void(void)> minimizedEvent = nullptr,
			std::function<void(bool)> focusEvent = nullptr,
			std::function<void(unsigned int, unsigned int)> movedEvent = nullptr, std::function<void(unsigned int, unsigned int)> resizeEvent = nullptr,
			std::function<void(unsigned int, unsigned int, unsigned int, unsigned int)> mouseMoveEvent = nullptr)
		{
			this->name = name;
			this->iD = iD;
			this->colorBits = colorBits;
			this->depthBits = depthBits;
			this->stencilBits = stencilBits;
			this->shouldClose = shouldClose;
			this->currentState = currentState;

			this->keyEvent = keyEvent;
			this->mouseButtonEvent = mouseButtonEvent;
			this->mouseWheelEvent = mouseWheelEvent;
			this->destroyedEvent = destroyedEvent;
			this->maximizedEvent = maximizedEvent;
			this->minimizedEvent = minimizedEvent;
			this->focusEvent = focusEvent;
			this->movedEvent = movedEvent;
			this->resizeEvent = resizeEvent;
			this->mouseMoveEvent = mouseMoveEvent;

			initialized = false;
			contextCreated = false;
			currentWindowStyle = (unsigned int)style_t::normal;

#if defined( __linux__ )
			context = 0;
#endif 
		}
	};

	class errorCategory_t : public std::error_category
	{
		public:
		virtual ~errorCategory_t() throw(){}

		const char* name() const throw() override
		{
			return "tinyWindow";
		} 

		virtual std::error_condition default_error_condition(int ev) const throw() override
		{
			if (ev < 15)
			{
				return std::error_condition();
			}

			else
			{
				return std::error_condition();
			}
		}

		virtual bool equivalent(const std::error_code& code, int condition) const throw() override
		{
			return *this == code.category() &&
				static_cast<int>(default_error_condition(code.value()).value()) == condition;
		}

		/**
		* return the error message associated with the given error number
		*/
		virtual std::string message(int errorValue) const override
		{
			switch (errorValue)
			{
			case invalidWindowName:
			{
				return "Error: invalid window name \n";
			}

			case invalidIconPath:
			{
				return "Error: invalid icon path \n";
			}

			case invalidWindowIndex:
			{
				return "Error: invalid window index \n";
			}

			case invalidWindowState:
			{
				return "Error: invalid window state \n";
			}

			case invalidResolution:
			{
				return "Error: invalid resolution \n";
			}

			case invalidContext:
			{
				return "Error: Failed to create OpenGL context \n";
			}

			case existingContext:
			{
				return "Error: context already created \n";
			}

			case notInitialized:
			{
				return "Error: Window manager not initialized \n";
			}

			case alreadyInitialized:
			{
				return "Error: window has already been initialized \n";
			}

			case invalidTitlebar:
			{
				return "Error: invalid title bar name ( cannot be null or nullptr ) \n";
			}

			case invalidCallback:
			{
				return "Error: invalid event callback given \n";
			}

			case windowNotFound:
			{
				return "Error: window was not found \n";
			}

			case invalidWindowStyle:
			{
				return "Error: invalid window style given \n";
			}

			case functionNotImplemented:
			{
				return "Error: I'm sorry but this function has not been implemented yet :( \n";
			}

			case linuxCannotConnectXServer:
			{
				return "Error: cannot connect to X server \n";
			}

			case linuxInvalidVisualinfo:
			{
				return "Error: Invalid visual information given \n";
			}

			case linuxCannotCreateWindow:
			{
				return "Error: failed to create window \n";
			}

			case linuxFunctionNotImplemented:
			{
				return "Error: function not implemented on Linux platform yet. sorry :( \n";
			}

			case windowsCannotCreateWindows:
			{
				return "Error: failed to create window \n";
			}

			case windowsFunctionNotImplemented:
			{
				return "Error: function not implemented on Windows platform yet. sorry ;( \n";
			}

			default:
			{
				return "Error: unspecified Error \n";
			}
			}
		}

		errorCategory_t(const errorCategory_t& copy);
		errorCategory_t(){};
	};

	static void PrintErrorMessage(std::error_code e)
	{
		printf("%s", e.message().c_str());
	}

	std::vector< std::unique_ptr<window_t> >				windowList;
	static std::unique_ptr<window_t>						nullWindow;
	static windowManager*									instance;
	static errorCategory_t									errorCategory;

	screenResolution_t							screenResolution;
	screenMousePosition_t							screenMousePosition;

	bool													isInitialized;

	static inline bool IsValid( const char* stringParameter )
	{
		return ( stringParameter != nullptr );
	}

	static inline bool WindowExists( unsigned int windowIndex )
	{
		return ( windowIndex <= instance->windowList.size() - 1 );
	}

	//get a static reference to the window manager
	static inline windowManager* GetInstance( void )
	{
		if ( windowManager::instance == nullptr )
		{
			windowManager::instance = new windowManager();
			return windowManager::instance;
		}

		else
		{
			return windowManager::instance;
		}
	}

	static inline void Platform_InitializeWindow( std::unique_ptr<window_t>& window )
	{
#if defined(TW_WINDOWS)
		Windows_InitializeWindow(window);
#elif defined(TW_LINUX)
		Linux_InitializeWindow(window);
#endif
	}

	static inline bool Platform_InitializeGL( std::unique_ptr<window_t>& window )
	{
#if defined(TW_WINDOWS)
		window->deviceContextHandle = GetDC(window->windowHandle);
		InitializePixelFormat(window);
		window->glRenderingContextHandle = wglCreateContext(window->deviceContextHandle);
		wglMakeCurrent(window->deviceContextHandle, window->glRenderingContextHandle);

		window->contextCreated = (window->glRenderingContextHandle != nullptr);

		if (window->contextCreated)
		{
			return true;
		}

		PrintErrorMessage(std::error_code(invalidContext, errorCategory));
		return false;
#elif defined(TW_LINUX)
		if (!window->context)
		{
			window->context = glXCreateContext(
				instance->currentDisplay,
				window->visualInfo,
				0,
				true);

			if (window->context)
			{
				glXMakeCurrent(instance->currentDisplay,
					window->windowHandle,
					window->context);

				XWindowAttributes l_Attributes;

				XGetWindowAttributes(instance->currentDisplay,
					window->windowHandle, &l_Attributes);
				window->position[0] = l_Attributes.x;
				window->position[1] = l_Attributes.y;

				window->contextCreated = true;
				return true;
			}
			return false;
		}

		else
		{
			PrintErrorMessage(std::error_code(existingContext, errorCategory));
			return false;
		}
		return false;
#endif
	}

	static inline void Platform_SetWindowResolution(std::unique_ptr<window_t>& window)
	{
#if defined(TW_WINDOWS)
		SetWindowPos(window->windowHandle, HWND_TOP,
			window->position[0], window->position[1],
			window->resolution[0], window->resolution[1],
			SWP_SHOWWINDOW | SWP_NOMOVE);
#elif defined(TW_LINUX)
		XResizeWindow(instance->currentDisplay,
			window->windowHandle, window->resolution[0], window->resolution[1]);
#endif
	}

	static inline void Platform_SetWindowPosition(std::unique_ptr<window_t>& window, unsigned int x, unsigned int y)
	{
#if defined(TW_WINDOWS)
		SetWindowPos(window->windowHandle, HWND_TOP, x, y,
			window->resolution[0], window->resolution[1],
			SWP_SHOWWINDOW | SWP_NOSIZE);
#elif defined(TW_LINUX)
		XWindowChanges windowChanges;

		windowChanges.x = x;
		windowChanges.y = y;

		XConfigureWindow(
			instance->currentDisplay,
			window->windowHandle, CWX | CWY, &windowChanges);
#endif
	}

	static inline void Platform_SetMousePositionInWindow(std::unique_ptr<window_t>& window, unsigned int x, unsigned int y)
	{
#if defined(TW_WINDOWS)
		POINT mousePoint;
		mousePoint.x = x;
		mousePoint.y = y;
		ScreenToClient(window->windowHandle, &mousePoint);
		SetCursorPos(mousePoint.x, mousePoint.y);
#elif defined(TW_LINUX)
		XWarpPointer(
			windowManager::GetDisplay(),
			window->windowHandle, window->windowHandle,
			window->position[0], window->position[1],
			window->resolution[0], window->resolution[1],
			x, y);
#endif
	}

	static inline void Platform_SwapBuffers(std::unique_ptr<window_t>& window)
	{
#if defined(TW_WINDOWS)
		SwapBuffers(window->deviceContextHandle);
#elif defined(TW_LINUX)
		glXSwapBuffers(instance->currentDisplay, window->windowHandle);
#endif
	}

	static inline void Platform_MakeCurrentContext(std::unique_ptr<window_t>& window)
	{
#if defined(TW_WINDOWS)
		wglMakeCurrent(window->deviceContextHandle,
			window->glRenderingContextHandle);
#elif defined(TW_LINUX)
		glXMakeCurrent(instance->currentDisplay, window->windowHandle,
			window->context);
#endif
	}

	static inline void Platform_SetFullScreen(std::unique_ptr<window_t>& window)
	{
#if defined(TW_WINDOWS)
		SetWindowLongPtr(window->windowHandle, GWL_STYLE,
			WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);

		MoveWindow(window->windowHandle, 0, 0, windowManager::GetScreenResolution()[0],
			windowManager::GetScreenResolution()[1], true);
#elif defined(TW_LINUX)
		XEvent currentEvent;
		memset(&currentEvent, 0, sizeof(currentEvent));

		currentEvent.xany.type = ClientMessage;
		currentEvent.xclient.message_type = window->AtomState;
		currentEvent.xclient.format = 32;
		currentEvent.xclient.window = window->windowHandle;
		currentEvent.xclient.data.l[0] = window->currentState == state_t::fullscreen;
		currentEvent.xclient.data.l[1] = window->AtomFullScreen;

		XSendEvent(instance->currentDisplay,
			XDefaultRootWindow(instance->currentDisplay),
			0, SubstructureNotifyMask, &currentEvent);
#endif
	}

	static inline void Platform_MinimizeWindow(std::unique_ptr<window_t>& window, bool newState)
	{
		if (newState)
		{
			window->currentState = state_t::minimized;

#if defined(TW_WINDOWS)
			ShowWindow(window->windowHandle, SW_MINIMIZE);
#elif defined(TW_LINUX)
			XIconifyWindow(instance->currentDisplay,
				window->windowHandle, 0);
#endif
		}

		else
		{
			window->currentState = state_t::normal;
#if defined(TW_WINDOWS)
			ShowWindow(window->windowHandle, SW_RESTORE);
#elif defined(TW_LINUX)
			XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
		}
	}

	static inline void Platform_MaximizeWindow(std::unique_ptr<window_t>& window, bool newState)
	{
		if (newState)
		{
			window->currentState = state_t::maximized;
#if defined(TW_WINDOWS)
			ShowWindow(window->windowHandle, SW_MAXIMIZE);
#elif defined(TW_LINUX)
			XEvent currentEvent;
			memset(&currentEvent, 0, sizeof(currentEvent));

			currentEvent.xany.type = ClientMessage;
			currentEvent.xclient.message_type = window->AtomState;
			currentEvent.xclient.format = 32;
			currentEvent.xclient.window = window->windowHandle;
			currentEvent.xclient.data.l[0] = (window->currentState == state_t::maximized);
			currentEvent.xclient.data.l[1] = window->AtomMaxVert;
			currentEvent.xclient.data.l[2] = window->AtomMaxHorz;

			XSendEvent(instance->currentDisplay,
				XDefaultRootWindow(instance->currentDisplay),
				0, SubstructureNotifyMask, &currentEvent);
#endif
		}

		else
		{
			window->currentState = state_t::normal;
#if defined(TW_WINDOWS)
			ShowWindow(window->windowHandle, SW_RESTORE);
#elif defined(TW_LINUX)
			XEvent currentEvent;
			memset(&currentEvent, 0, sizeof(currentEvent));

			currentEvent.xany.type = ClientMessage;
			currentEvent.xclient.message_type = window->AtomState;
			currentEvent.xclient.format = 32;
			currentEvent.xclient.window = window->windowHandle;
			currentEvent.xclient.data.l[0] = (window->currentState == state_t::maximized);
			currentEvent.xclient.data.l[1] = window->AtomMaxVert;
			currentEvent.xclient.data.l[2] = window->AtomMaxHorz;

			XSendEvent(instance->currentDisplay,
				XDefaultRootWindow(instance->currentDisplay),
				0, SubstructureNotifyMask, &currentEvent);
#endif
		}
	}

	static inline void Platform_SetWindowTitleBar(std::unique_ptr<window_t>& window, const char* newTitle)
	{
#if defined(TW_WINDOWS)
		SetWindowText(window->windowHandle, newTitle);
#elif defined(TW_LINUX)
		XStoreName(instance->currentDisplay, window->windowHandle, newTitle);
#endif
	}

	static inline void Platform_FocusWindow(std::unique_ptr<window_t>& window, bool newState)
	{
		if (newState)
		{
#if defined(TW_WINDOWS)
			SetFocus(window->windowHandle);
#elif defined(TW_LINUX)
			XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
		}

		else
		{
#if defined(_WIN32) || defined(_WIN64)
			SetFocus(nullptr);
#elif defined(TW_LINUX)
			XUnmapWindow(instance->currentDisplay, window->windowHandle);
#endif
		}
	}

	static inline void Platform_RestoreWindow(std::unique_ptr<window_t>& window)
	{
#if defined(TW_WINDOWS)
		ShowWindow(window->windowHandle, SW_RESTORE);
#elif defined(TW_LINUX)
		XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
	}

	static inline void Platform_SetWindowStyle(std::unique_ptr<window_t>& window, style_t windowStyle)
	{
#if defined(TW_WINDOWS)
		switch (windowStyle)
		{
		case style_t::normal:
		{
			EnableWindowDecoratorsByName(window->name, titleBar | border |
				closeButton | minimizeButton | maximizeButton);
			break;
		}

		case style_t::popup:
		{
			EnableWindowDecoratorsByName(window->name, 0);
			break;
		}

		case style_t::bare:
		{
			EnableWindowDecoratorsByName(window->name, titleBar | border);
			break;
		}

		default:
		{
			PrintErrorMessage(std::error_code(invalidWindowStyle, errorCategory));
			break;
		}
		}

#elif defined(TW_LINUX)
		switch (windowStyle)
		{
			case style_t::normal:
		{
			window->decorators = (1L << 2);
			window->currentWindowStyle = linuxMove | linuxClose |
				linuxMaximize | linuxMinimize;
			long Hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

			XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32, PropModeReplace,
				(unsigned char*)Hints, 5);

			XMapWindow(instance->currentDisplay, window->windowHandle);
			break;
		}

			case style_t::bare:
		{
			window->decorators = (1L << 2);
			window->currentWindowStyle = (1L << 2);
			long Hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

			XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32, PropModeReplace,
				(unsigned char*)Hints, 5);

			XMapWindow(instance->currentDisplay, window->windowHandle);
			break;
		}

			case style_t::popup:
		{
			window->decorators = 0;
			window->currentWindowStyle = (1L << 2);
			long Hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

			XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32, PropModeReplace,
				(unsigned char*)Hints, 5);

			XMapWindow(instance->currentDisplay, window->windowHandle);
			break;
		}

		default:
		{
			PrintErrorMessage(std::error_code(invalidWindowStyle, errorCategory));
			break;
		}
		}
#endif
	}

	static inline void Platform_EnableWindowDecorators(std::unique_ptr<window_t>& window, unsigned int decorators)
	{
#if defined(TW_WINDOWS)
		window->currentWindowStyle = WS_VISIBLE | WS_CLIPSIBLINGS;

		if (decorators & border)
		{
			window->currentWindowStyle |= WS_BORDER;
		}

		if (decorators & titleBar)
		{
			window->currentWindowStyle |= WS_CAPTION;
		}

		if (decorators & icon)
		{
			window->currentWindowStyle |= WS_ICONIC;
		}

		if (decorators & closeButton)
		{
			window->currentWindowStyle |= WS_SYSMENU;
		}

		if (decorators & minimizeButton)
		{
			window->currentWindowStyle |= WS_MINIMIZEBOX | WS_SYSMENU;
		}

		if (decorators & maximizeButton)
		{
			window->currentWindowStyle |= WS_MAXIMIZEBOX | WS_SYSMENU;
		}

		if (decorators & sizeableBorder)
		{
			window->currentWindowStyle |= WS_SIZEBOX;
		}

		SetWindowLongPtr(window->windowHandle, GWL_STYLE,
			window->currentWindowStyle);
#elif defined(TW_LINUX)
		if (decorators & closeButton)
		{
			window->currentWindowStyle |= linuxClose;
			window->decorators = 1;
		}

		if (decorators & minimizeButton)
		{
			window->currentWindowStyle |= linuxMinimize;
			window->decorators = 1;
		}

		if (decorators & maximizeButton)
		{
			window->currentWindowStyle |= linuxMaximize;
			window->decorators = 1;
		}

		if (decorators & icon)
		{
			//Linux ( at least cinnamon ) does not have icons in the window. only in the task bar icon
		}

		//just need to set it to 1 to enable all decorators that include title bar 
		if (decorators & titleBar)
		{
			window->decorators = 1;
		}

		if (decorators & border)
		{
			window->decorators = 1;
		}

		if (decorators & sizeableBorder)
		{
			window->decorators = 1;
		}

		long hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

		XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32,
			PropModeReplace, (unsigned char*)hints, 5);

		XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
	}

	static inline void Platform_DisableWindowDecorators(std::unique_ptr<window_t>& window, unsigned int decorators)
	{
#if defined(TW_WINDOWS)
		if (decorators & border)
		{
			window->currentWindowStyle &= ~WS_BORDER;
		}

		if (decorators & titleBar)
		{
			window->currentWindowStyle &= ~WS_MAXIMIZEBOX;
		}

		if (decorators & icon)
		{
			window->currentWindowStyle &= ~WS_ICONIC;
		}

		if (decorators & closeButton)
		{
			window->currentWindowStyle &= ~WS_SYSMENU;
		}

		if (decorators & minimizeButton)
		{
			window->currentWindowStyle &= ~WS_MINIMIZEBOX;
		}

		if (decorators & maximizeButton)
		{
			window->currentWindowStyle &= ~WS_MAXIMIZEBOX;
		}

		if (decorators & sizeableBorder)
		{
			window->currentWindowStyle &= ~WS_SIZEBOX;
		}

		SetWindowLongPtr(window->windowHandle, GWL_STYLE,
			window->currentWindowStyle | WS_VISIBLE);
#elif defined(TW_LINUX)
		if (decorators & closeButton)
		{
			//I hate doing this but it is necessary to keep functionality going.
			bool minimizeEnabled = false;
			bool maximizeEnabled = false;

			if (decorators & maximizeButton)
			{
				maximizeEnabled = true;
			}

			if (decorators & minimizeButton)
			{
				minimizeEnabled = true;
			}

			window->currentWindowStyle &= ~linuxClose;

			if (maximizeEnabled)
			{
				window->currentWindowStyle |= linuxMaximize;
			}

			if (minimizeEnabled)
			{
				window->currentWindowStyle |= linuxMinimize;
			}

			window->decorators = 1;
		}

		if (decorators & minimizeButton)
		{
			window->currentWindowStyle &= ~linuxMinimize;
			window->decorators = 1;
		}

		if (decorators & maximizeButton)
		{
			bool minimizeEnabled = false;

			if (decorators & minimizeButton)
			{
				minimizeEnabled = true;
			}

			window->currentWindowStyle &= ~linuxMaximize;

			if (minimizeEnabled)
			{
				window->currentWindowStyle |= linuxMinimize;
			}

			window->decorators = 1;
		}

		if (decorators & icon)
		{
			//Linux ( at least cinnamon ) does not have icons in the window. only in the taskb ar icon
		}

		//just need to set it to 1 to enable all decorators that include title bar 
		if (decorators & titleBar)
		{
			window->decorators = linuxBorder;
		}

		if (decorators & border)
		{
			window->decorators = 0;
		}

		if (decorators & sizeableBorder)
		{
			window->decorators = 0;
		}

		long hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

		XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32,
			PropModeReplace, (unsigned char*)hints, 5);

		XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
	}

	static inline void ShutdownWindow( std::unique_ptr<window_t>& window )
	{
#if defined(TW_WINDOWS)
		if (window->glRenderingContextHandle)
		{
			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(window->glRenderingContextHandle);
		}

		if (window->paletteHandle)
		{
			DeleteObject(window->paletteHandle);
		}
		ReleaseDC(window->windowHandle, window->deviceContextHandle);
		UnregisterClass(window->name, window->instanceHandle);

		FreeModule(window->instanceHandle);

		window->deviceContextHandle = nullptr;
		window->windowHandle = nullptr;
		window->glRenderingContextHandle = nullptr;
#elif defined(TW_LINUX)
		if (window->currentState == state_t::fullscreen)
		{
			RestoreWindowByName(window->name);
		}

		glXDestroyContext(instance->currentDisplay, window->context);
		XUnmapWindow(instance->currentDisplay, window->windowHandle);
		XDestroyWindow(instance->currentDisplay, window->windowHandle);
		window->windowHandle = 0;
		window->context = 0;
#endif
	}

	static inline bool DoesExistByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( IsValid( windowName ) )
			{
				for ( unsigned int iter = 0; iter < instance->windowList.size(); iter++ )
				{
					if( !strcmp( instance->windowList[iter]->name, windowName ) )
					{
						return true;
					}
				}
			}
			PrintErrorMessage( std::error_code(invalidWindowName, errorCategory ));
			return false;
		}
		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	static inline bool DoesExistByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( windowIndex <= ( instance->windowList.size() - 1 ) )
			{
				return true;
			}

			PrintErrorMessage( std::error_code(invalidWindowIndex, errorCategory ));
			return false;
		}

		PrintErrorMessage(std::error_code(notInitialized, errorCategory));
		return false;
	}

	static inline std::unique_ptr<window_t>& GetWindowByName( const char* windowName )
	{
			for( unsigned int iter = 0; iter < instance->windowList.size(); iter++ )
			{
				if ( !strcmp( instance->windowList[iter]->name, windowName ) )
				{
					return instance->windowList[iter];
				}
			}

			return nullWindow;
	}

	//return a static pointer to a window that corresponds to the given window index
	static inline std::unique_ptr<window_t>& GetWindowByIndex( unsigned int windowIndex )
	{
		if ( windowIndex <= instance->windowList.size() - 1 )
		{
			return instance->windowList[windowIndex];
		}
		return nullWindow;
	}
	
#if defined(TW_WINDOWS)

	enum keyLong_t
	{
		leftControlDown = 29,
		rightControlDown = 285,
		leftShiftDown = 42,
		rightShiftDown = 54,
		leftAltDown = 8248,
		rightAltDown = 8504,

		leftControlUp = 49181,
		rightControlUp = 49437,
		leftShiftUp = 49194,
		rightShiftUp = 49206,
		leftAltUp = 49208,
		rightAltUp = 49464,
	};

	MSG		message;
	HDC		deviceContextHandle;

	//the window procedure for all windows. This is used mainly to handle window events
	LRESULT CALLBACK WindowProcedure( HWND windowHandle, unsigned int winMessage, WPARAM wordParam, LPARAM longParam )
	{
		std::unique_ptr<window_t>& window = GetWindowByHandle( windowHandle );
		switch ( winMessage )
		{
		case WM_CREATE:
		{
			GetWindowByIndex( windowList.size() - 1 )->windowHandle = windowHandle;
			Platform_InitializeGL(GetWindowByIndex(windowList.size() - 1));
			break;
		}

		case WM_DESTROY:
		{
			window->shouldClose = true;

			if (window->destroyedEvent != nullptr )
			{
				window->destroyedEvent();
			}

			ShutdownWindow( window);
			break;
		}
		case WM_MOVE:
		{
			window->position[ 0 ] = LOWORD( longParam );
			window->position[ 1 ] = HIWORD( longParam );

			if ( window->movedEvent != nullptr )
			{
				window->movedEvent( window->position[ 0 ], window->position[ 1 ] );
			}

			break;
		}

		case WM_MOVING:
		{
			window->position[ 0 ] = LOWORD( longParam );
			window->position[ 1 ] = HIWORD( longParam );

			if ( window->movedEvent != nullptr )
			{
				window->movedEvent( window->position[ 0 ], window->position[ 1 ] );
			}
			break;
		}

		case WM_SIZE:
		{
			window->resolution[ 0 ] = ( unsigned int )LOWORD( longParam );
			window->resolution[ 1 ] = ( unsigned int )HIWORD( longParam );

			switch ( wordParam )
			{
				case SIZE_MAXIMIZED:
				{
					if ( window->maximizedEvent != nullptr )
					{
						window->maximizedEvent();
					}

					break;
				}

				case SIZE_MINIMIZED:
				{
					if ( window->minimizedEvent != nullptr )
					{
						window->minimizedEvent();
					}
					break;
				}

				default:
				{
					if ( window->resizeEvent != nullptr )
					{
						window->resizeEvent( window->resolution[ 0 ],
							window->resolution[ 1 ] );
					}

					break;
				}
			}
			break;
		}

		case WM_SIZING:
		{
			window->resolution[ 0 ] = ( unsigned int )LOWORD( longParam );
			window->resolution[ 1 ] = ( unsigned int )HIWORD( longParam );

			if ( window->resizeEvent != nullptr )
			{
				window->resizeEvent( window->resolution[ 0 ],
					window->resolution[ 1 ] );
			}

			break;
		}

		case WM_KEYDOWN:
		{
			unsigned int translatedKey = 0;

			switch ( HIWORD( longParam ) )
			{
			case leftControlDown:
			{
				window->keys[ leftControl ] = keyState_t::down;
				translatedKey = leftControl;
				break;
			}

			case rightControlDown:
			{
				window->keys[ rightControl ] = keyState_t::down;
				translatedKey = rightControl;
				break;
			}

			case leftShiftDown:
			{
				window->keys[ leftShift ] = keyState_t::down;
				translatedKey = leftShift;
				break;
			}

			case rightShiftDown:
			{
				window->keys[ rightShift ] = keyState_t::down;
				translatedKey = rightShift;
				break;
			}

			default:
			{
				translatedKey = Windows_TranslateKey( wordParam );
				window->keys[ translatedKey ] = keyState_t::down;
				break;
			}
			}

			if ( window->keyEvent != nullptr )
			{
				window->keyEvent( translatedKey, keyState_t::down );
			}
			break;
		}

		case WM_KEYUP:
		{
			unsigned int translatedKey = 0;

			switch ( HIWORD( longParam ) )
			{
			case leftControlUp:
			{
				window->keys[ leftControl ] = keyState_t::up;
				translatedKey = leftControl;
				break;
			}

			case rightControlUp:
			{
				window->keys[ rightControl ] = keyState_t::up;
				translatedKey = rightControl;
				break;
			}

			case leftShiftUp:
			{
				window->keys[ leftShift ] = keyState_t::up;
				translatedKey = leftShift;
				break;
			}

			case rightShiftUp:
			{
				window->keys[ rightShift ] = keyState_t::up;
				translatedKey = rightShift;
				break;
			}

			default:
			{
				translatedKey = Windows_TranslateKey( wordParam );
				window->keys[ translatedKey ] = keyState_t::up;
				break;
			}
			}

			if (window->keyEvent != nullptr )
			{
				window->keyEvent( translatedKey, keyState_t::up );
			}
			break;
		}

		case WM_SYSKEYDOWN:
		{
			unsigned int translatedKey = 0;
			switch ( HIWORD( longParam ) )
			{
			case leftAltDown:
			{
				window->keys[ leftAlt ] = keyState_t::down;
				translatedKey = leftAlt;
				break;
			}


			case rightAltDown:
			{
				window->keys[ rightAlt ] = keyState_t::down;
				translatedKey = rightAlt;
			}

			default:
			{
				break;
			}
			}

			if ( window->keyEvent != nullptr )
			{
				window->keyEvent( translatedKey, keyState_t::down );
			}

			break;
		}

		case WM_SYSKEYUP:
		{
			unsigned int translatedKey = 0;
			switch ( HIWORD( longParam ) )
			{
			case leftAltUp:
			{
				window->keys[ leftAlt ] = keyState_t::up;
				translatedKey = leftAlt;
				break;
			}


			case rightAltUp:
			{
				window->keys[ rightAlt ] = keyState_t::up;
				translatedKey = rightAlt;
				break;
			}

			default:
			{
				break;
			}
			}

			if ( window->keyEvent != nullptr )
			{
				window->keyEvent( translatedKey, keyState_t::up );
			}
			break;
		}

		//WM_KEYUP/DOWN cannot tell between uppercase and lowercase.
		/*case WM_CHAR:
		{
			int keyDown = longParam & 0x31;
			if (keyDown == 1)
			{
				window->keys[wordParam] = tinyWindowKeyState_t::DOWN;
			}

			else if (keyDown == 0)
			{
				window->keys[wordParam] = tinyWindowKeyState_t::UP;
			}

			if (window->keyEvent != nullptr)
			{
				window->keyEvent(wordParam, (tinyWindowKeyState_t)keyDown);
			}
		}*/

		case WM_MOUSEMOVE:
		{
			window->mousePosition[ 0 ] = ( unsigned int )LOWORD( longParam );
			window->mousePosition[ 1 ] = ( unsigned int )HIWORD( longParam );

			POINT point;
			point.x = (LONG)window->mousePosition[ 0 ];
			point.y = (LONG)window->mousePosition[ 1 ];

			ClientToScreen( windowHandle, &point );

			if ( window->mouseMoveEvent != nullptr )
			{
				window->mouseMoveEvent( window->mousePosition[ 0 ],
					window->mousePosition[ 1 ], point.x, point.y );
			}
			break;
		}

		case WM_LBUTTONDOWN:
		{
			window->mouseButton[(unsigned int)mouseButton_t::left] = buttonState_t::down;

			if ( window->mouseButtonEvent != nullptr )
			{
				window->mouseButtonEvent( mouseButton_t::left, buttonState_t::down );
			}
			break;
		}

		case WM_LBUTTONUP:
		{
			window->mouseButton[(unsigned int)mouseButton_t::left] = buttonState_t::up;

			if ( window->mouseButtonEvent != nullptr )
			{
				window->mouseButtonEvent( mouseButton_t::left, buttonState_t::up );
			}
			break;
		}

		case WM_RBUTTONDOWN:
		{
			window->mouseButton[(unsigned int)mouseButton_t::right] = buttonState_t::down;

			if ( window->mouseButtonEvent != nullptr )
			{
				window->mouseButtonEvent( mouseButton_t::right, buttonState_t::down );
			}
			break;
		}

		case WM_RBUTTONUP:
		{
			window->mouseButton[(unsigned int)mouseButton_t::right] = buttonState_t::up;

			if ( window->mouseButtonEvent != nullptr )
			{
				window->mouseButtonEvent( mouseButton_t::right, buttonState_t::up );
			}
			break;
		}

		case WM_MBUTTONDOWN:
		{
			window->mouseButton[(unsigned int)mouseButton_t::middle] = buttonState_t::down;

			if ( window->mouseButtonEvent != nullptr )
			{
				window->mouseButtonEvent( mouseButton_t::middle, buttonState_t::down );
			}
			break;
		}

		case WM_MBUTTONUP:
		{
			window->mouseButton[ (unsigned int)mouseButton_t::middle ] = buttonState_t::up;

			if ( window->mouseButtonEvent != nullptr )
			{
				window->mouseButtonEvent( mouseButton_t::middle, buttonState_t::up );
			}
			break;
		}

		case WM_MOUSEWHEEL:
		{
			if ( ( wordParam % WHEEL_DELTA ) > 0 )
			{
				if ( window->mouseWheelEvent != nullptr )
				{
					window->mouseWheelEvent( mouseScroll_t::down );
				}
			}

			else
			{
				if ( window->mouseWheelEvent != nullptr )
				{
					window->mouseWheelEvent( mouseScroll_t::up );
				}

			}
			break;
		}



		default:
		{
			//instance->windowList[getWindow]
			return DefWindowProc( windowHandle, winMessage, wordParam, longParam );
		}
		}
		return 0;

	}

	//this returns a static reference to the win32 window procedure. Oddly a Win32 procedure cannot be a member variable
	static LRESULT CALLBACK StaticWindowProcedure( HWND windowHandle, UINT message, WPARAM wordParam, LPARAM longParam )
	{
		return instance->WindowProcedure( windowHandle, message, wordParam, longParam );
	}

	//get the window that is associated with this Win32 window handle
	static inline std::unique_ptr<window_t>& GetWindowByHandle( HWND windowHandle )
	{
		for ( unsigned int iter = 0; iter < instance->windowList.size(); iter++ )
		{
			if ( instance->windowList[iter]->windowHandle == windowHandle )
			{
				return instance->windowList[iter];
			}
		}

		return nullWindow;
	}

	//initialize the given window using Win32
	static inline void Windows_InitializeWindow( std::unique_ptr<window_t>& window,
		UINT style = CS_OWNDC | CS_HREDRAW | CS_DROPSHADOW,
		int clearScreenExtra = 0,
		int windowExtra = 0,
		HINSTANCE winInstance = GetModuleHandle( 0 ),
		HICON icon = LoadIcon( 0, IDI_APPLICATION ),
		HCURSOR cursor = LoadCursor( 0, IDC_ARROW ),
		HBRUSH brush = ( HBRUSH )BLACK_BRUSH )
	{
		window->instanceHandle = winInstance;
		window->windowClass.style = style;
		window->windowClass.lpfnWndProc = windowManager::StaticWindowProcedure;
		window->windowClass.cbClsExtra = clearScreenExtra;
		window->windowClass.cbWndExtra = windowExtra;
		window->windowClass.hInstance = window->instanceHandle;
		window->windowClass.hIcon = icon;
		window->windowClass.hCursor = cursor;
		window->windowClass.hbrBackground = brush;
		window->windowClass.lpszMenuName = window->name;
		window->windowClass.lpszClassName = window->name;
		RegisterClass( &window->windowClass );

		window->windowHandle =
			CreateWindow( window->name, window->name, WS_OVERLAPPEDWINDOW, 0,
			0, window->resolution[ 0 ],
			window->resolution[ 1 ],
			0, 0, 0, 0 );

		ShowWindow( window->windowHandle, true );
		UpdateWindow( window->windowHandle );
	}

	//initialize the pixel format for the selected window
	static inline void InitializePixelFormat( std::unique_ptr<window_t>& window )
	{
		window->pixelFormatDescriptor = {
			sizeof( PIXELFORMATDESCRIPTOR ), /* size */
			1, /* version */
			PFD_SUPPORT_OPENGL |
			PFD_DRAW_TO_WINDOW |
			PFD_DOUBLEBUFFER, /* support double-buffering */
			PFD_TYPE_RGBA, /* color type */
			( BYTE )window->colorBits, 0, /* prefered color depth */
			0, 0,
			0, 0,
			0, 0,
			0, /* color bits ( ignored ) */ /* no alpha buffer */ /* alpha bits ( ignored ) */
			0, /* no accumulation buffer */
			0, 0, 0, 0, /* accum bits ( ignored ) */
			( BYTE )window->depthBits, /* depth buffer */
			( BYTE )window->stencilBits, /* no stencil buffer */
			0, /* no auxiliary buffers */
			PFD_MAIN_PLANE, /* main layer */
			0, /* reserved */
			0, 0, 0, /* no layer, visible, damage masks */
		};

		int LocalPixelFormat = ChoosePixelFormat( window->deviceContextHandle,
			&window->pixelFormatDescriptor );

		if ( LocalPixelFormat )
		{
			SetPixelFormat( window->deviceContextHandle, LocalPixelFormat,
				&window->pixelFormatDescriptor );
			return;
		}
		return;
	}
	
	static inline void Windows_Shutown( void )
	{

	}

	static inline void CreateTerminal( void )
	{
		int conHandle;
		long stdHandle;
		FILE* fp;

		// allocate a console for this app
		AllocConsole();

		// redirect unbuffered STDOUT to the console
		stdHandle = ( long )GetStdHandle( STD_OUTPUT_HANDLE );
		conHandle = _open_osfhandle( stdHandle, _O_TEXT );
		fp = _fdopen( conHandle, "w" );
		*stdout = *fp;

		setvbuf( stdout, nullptr, _IONBF, 0 );
	}

	static inline unsigned int Windows_TranslateKey( WPARAM wordParam)
	{
		switch ( wordParam )
		{
			case VK_ESCAPE:
			{
				return escape;
			}

			case VK_F1:
			{
				return F1;
			}

			case VK_F2:
			{
				return F2;
			}

			case VK_F3:
			{
				return F3;
			}

			case VK_F4:
			{
				return F4;
			}

			case VK_F5:
			{
				return F5;
			}

			case VK_F6:
			{
				return F6;
			}

			case VK_F7:
			{
				return F7;
			}

			case VK_F8:
			{
				return F8;
			}

			case VK_F9:
			{
				return F9;
			}

			case VK_F10:
			{
				return F10;
			}

			case VK_F11:
			{
				return F11;
			}

			case VK_F12:
			{
				return F12;
			}

			case VK_BACK:
			{
				return backspace;
			}

			case VK_TAB:
			{
				return tab;
			}

			case VK_CAPITAL:
			{
				return capsLock;
			}

			case VK_RETURN:
			{
				return enter;
			}

			case VK_PRINT:
			{
				return printScreen;
			}

			case VK_SCROLL:
			{
				return scrollLock;
			}

			case VK_PAUSE:
			{
				return pause;
			}

			case VK_INSERT:
			{
				return insert;
			}

			case VK_HOME:
			{
				return home;
			}

			case VK_DELETE:
			{
				return del;
			}

			case VK_END:
			{
				return end;
			}

			case VK_PRIOR:
			{
				return pageUp;
			}

			case VK_NEXT:
			{
				return pageDown;
			}

			case VK_DOWN:
			{
				return arrowDown;
			}

			case VK_UP:
			{
				return arrowUp;
			}

			case VK_LEFT:
			{
				return arrowLeft;
			}

			case VK_RIGHT:
			{
				return arrowRight;
			}

			case VK_DIVIDE:
			{
				return keypadDivide;
			}

			case VK_MULTIPLY:
			{
				return keypadMultiply;
			}

			case VK_SUBTRACT:
			{
				return keypadDivide;
			}

			case VK_ADD:
			{
				return keypadAdd;
			}

			case VK_DECIMAL:
			{
				return keypadPeriod;
			}

			case VK_NUMPAD0:
			{
				return keypad0;
			}

			case VK_NUMPAD1:
			{
				return keypad1;
			}

			case VK_NUMPAD2:
			{
				return keypad2;
			}

			case VK_NUMPAD3:
			{
				return keypad3;
			}

			case VK_NUMPAD4:
			{
				return keypad4;
			}

			case VK_NUMPAD5:
			{
				return keypad5;
			}

			case VK_NUMPAD6:
			{
				return keypad6;
			}

			case VK_NUMPAD7:
			{
				return keypad7;
			}

			case VK_NUMPAD8:
			{
				return keypad8;
			}

			case VK_NUMPAD9:
			{
				return keypad9;
			}

			case VK_LWIN:
			{
				return leftWindow;
			}

			case VK_RWIN:
			{
				return rightWindow;
			}

			default:
			{
				return wordParam;
			}
		}
	}

	static inline void Windows_SetWindowIcon( std::unique_ptr<window_t>& window, const char* icon, unsigned int width, unsigned int height )
	{
		SendMessage(window->windowHandle, (UINT)WM_SETICON, ICON_BIG, 
			(LPARAM)LoadImage(window->instanceHandle, icon, IMAGE_ICON, (int)width, (int)height, LR_LOADFROMFILE));
	}

#elif defined(TW_LINUX)

	enum linuxDecorator_t
	{
		linuxBorder = 1L << 1,
		linuxMove = 1L << 2,
		linuxMinimize = 1L << 3,
		linuxMaximize = 1L << 4,
		linuxClose = 1L << 5,
	};

	Display*			currentDisplay;
	XEvent				currentEvent;
	
	static std::unique_ptr<window_t>& GetWindowByHandle( Window windowHandle )
	{
		for(unsigned int iter = 0; iter < GetInstance()->windowList.size(); iter++ )
		{
			if ( instance->windowList[iter]->windowHandle == windowHandle )
			{
				return instance->windowList[iter];
			}
		}
		return nullWindow;
	}

	static std::unique_ptr<window_t>& GetWindowByEvent( XEvent currentEvent )
	{
		switch( currentEvent.type )
		{
			case Expose:
			{
				return GetWindowByHandle( currentEvent.xexpose.window );
			}	

			case DestroyNotify:
			{
				return GetWindowByHandle( currentEvent.xdestroywindow.window );
			}

			case CreateNotify:
			{
				return GetWindowByHandle( currentEvent.xcreatewindow.window );
			}	

			case KeyPress:
			{
				return GetWindowByHandle( currentEvent.xkey.window );
			}

			case KeyRelease:
			{
				return GetWindowByHandle( currentEvent.xkey.window );
			}

			case ButtonPress:
			{
				return GetWindowByHandle( currentEvent.xbutton.window );
			}

			case ButtonRelease:
			{
				return GetWindowByHandle( currentEvent.xbutton.window );
			}

			case MotionNotify:
			{
				return GetWindowByHandle( currentEvent.xmotion.window );
			}	

			case FocusIn:
			{
				return GetWindowByHandle( currentEvent.xfocus.window );
			}

			case FocusOut:
			{
				return GetWindowByHandle( currentEvent.xfocus.window );
			}

			case ResizeRequest:
			{
				return GetWindowByHandle( currentEvent.xresizerequest.window );
			}

			case ConfigureNotify:
			{
				return GetWindowByHandle( currentEvent.xconfigure.window );
			}

			case PropertyNotify:
			{
				return GetWindowByHandle( currentEvent.xproperty.window );
			}

			case GravityNotify:
			{
				return GetWindowByHandle( currentEvent.xgravity.window );
			}

			case ClientMessage:
			{
				return GetWindowByHandle( currentEvent.xclient.window );
			}

			case VisibilityNotify:
			{
				return GetWindowByHandle( currentEvent.xvisibility.window );
			}	

			default:
			{
				return nullWindow;
			}
		}
	}

	static void InitializeAtoms( std::unique_ptr<window_t>& window )
	{
		window->AtomState = XInternAtom(instance->currentDisplay, "_NET_WM_STATE", false);
		window->AtomFullScreen = XInternAtom(instance->currentDisplay, "_NET_WM_STATE_FULLSCREEN", false);
		window->AtomMaxHorz = XInternAtom(instance->currentDisplay, "_NET_WM_STATE_MAXIMIZED_HORZ", false);
		window->AtomMaxVert = XInternAtom(instance->currentDisplay, "_NET_WM_STATE_MAXIMIZED_VERT", false);
		window->AtomClose = XInternAtom(instance->currentDisplay, "WM_DELETE_WINDOW", false);
		window->AtomHidden = XInternAtom(instance->currentDisplay, "_NET_WM_STATE_HIDDEN", false);
		window->AtomActive = XInternAtom(instance->currentDisplay, "_NET_ACTIVE_WINDOW", false);
		window->AtomDemandsAttention = XInternAtom(instance->currentDisplay, "_NET_WM_STATE_DEMANDS_ATTENTION", false);
		window->AtomFocused = XInternAtom(instance->currentDisplay, "_NET_WM_STATE_FOCUSED", false);
		window->AtomCardinal = XInternAtom(instance->currentDisplay, "CARDINAL", false);
		window->AtomIcon = XInternAtom(instance->currentDisplay, "_NET_WM_ICON", false);
		window->AtomHints = XInternAtom(instance->currentDisplay, "_MOTIF_WM_HINTS", true);

		window->AtomWindowType = XInternAtom(instance->currentDisplay, "_NET_WM_WINDOW_TYPE", false);
		window->AtomWindowTypeDesktop = XInternAtom(instance->currentDisplay, "_NET_WM_WINDOW_TYPE_UTILITY", false);
		window->AtomWindowTypeSplash = XInternAtom(instance->currentDisplay, "_NET_WM_WINDOW_TYPE_SPLASH", false);
		window->AtomWindowTypeNormal = XInternAtom(instance->currentDisplay, "_NET_WM_WINDOW_TYPE_NORMAL", false);

		window->AtomAllowedActions = XInternAtom(instance->currentDisplay, "_NET_WM_ALLOWED_ACTIONS", false);
		window->AtomActionResize = XInternAtom(instance->currentDisplay, "WM_ACTION_RESIZE", false);
		window->AtomActionMinimize = XInternAtom(instance->currentDisplay, "_WM_ACTION_MINIMIZE", false);
		window->AtomActionShade = XInternAtom(instance->currentDisplay, "WM_ACTION_SHADE", false);
		window->AtomActionMaximizeHorz = XInternAtom(instance->currentDisplay, "_WM_ACTION_MAXIMIZE_HORZ", false);
		window->AtomActionMaximizeVert = XInternAtom(instance->currentDisplay, "_WM_ACTION_MAXIMIZE_VERT", false);
		window->AtomActionClose = XInternAtom(instance->currentDisplay, "_WM_ACTION_CLOSE", false);

		window->AtomDesktopGeometry = XInternAtom(instance->currentDisplay, "_NET_DESKTOP_GEOMETRY", false);
	}

	static void Linux_InitializeWindow( std::unique_ptr<window_t>& window )
	{
		window->attributes = new int[ 5 ]{
			GLX_RGBA,
			GLX_DOUBLEBUFFER, 
			GLX_DEPTH_SIZE, 
			window->depthBits, 
			None};

		window->decorators = 1;
		window->currentWindowStyle |= linuxClose | linuxMaximize | linuxMinimize | linuxMove;

		if ( !instance->currentDisplay )
		{
			PrintErrorMessage( std::error_code(linuxCannotConnectXServer, errorCategory ));
			exit( 0 );
		}

		//window->VisualInfo = glXGetVisualFromFBConfig( GetDisplay(), GetBestFrameBufferConfig( window ) ); 

		window->visualInfo = glXChooseVisual( instance->currentDisplay, 0, window->attributes );

		if ( !window->visualInfo )
		{
			PrintErrorMessage( std::error_code(linuxInvalidVisualinfo, errorCategory));
			exit( 0 );
		}

		window->setAttributes.colormap = XCreateColormap( instance->currentDisplay,
			DefaultRootWindow( instance->currentDisplay ),
			window->visualInfo->visual, AllocNone );

		window->setAttributes.event_mask = ExposureMask | KeyPressMask 
			| KeyReleaseMask | MotionNotify | ButtonPressMask | ButtonReleaseMask
			| FocusIn | FocusOut | Button1MotionMask | Button2MotionMask | Button3MotionMask | 
			Button4MotionMask | Button5MotionMask | PointerMotionMask | FocusChangeMask
			| VisibilityChangeMask | PropertyChangeMask | SubstructureNotifyMask;
		
		window->windowHandle = XCreateWindow( instance->currentDisplay,
			XDefaultRootWindow( instance->currentDisplay ), 0, 0,
			window->resolution[ 0 ], window->resolution[ 1 ],
			0, window->visualInfo->depth, InputOutput,
			window->visualInfo->visual, CWColormap | CWEventMask,
			&window->setAttributes );

		if( !window->windowHandle )
		{
			PrintErrorMessage( std::error_code(linuxCannotCreateWindow, errorCategory));
			exit( 0 );
		}

		XMapWindow( instance->currentDisplay, window->windowHandle );
		XStoreName( instance->currentDisplay, window->windowHandle,
			window->name );

		InitializeAtoms(window);

		XSetWMProtocols( instance->currentDisplay, window->windowHandle, &window->AtomClose, true );	

		Platform_InitializeGL(window);
	}

	static void Linux_ShutdownWindow( std::unique_ptr<window_t>& window )
	{
		XDestroyWindow(instance->currentDisplay, window->windowHandle);	
	}

	static void Linux_Shutdown( void )
	{
		for(unsigned int iter = 0; iter < instance->windowList.size(); iter++)
		{
			Linux_ShutdownWindow(instance->windowList[iter]);
		}

		XCloseDisplay( instance->currentDisplay );
	}

	static void Linux_ProcessEvents( XEvent currentEvent )
	{
		std::unique_ptr<window_t>& window = GetWindowByEvent( currentEvent );

		switch ( currentEvent.type )	
		{
			case Expose:
			{
				break;
			}

			case DestroyNotify:
			{
				printf("shutting down \n");
				if ( window->destroyedEvent != nullptr )
				{
					window->destroyedEvent();
				}
				ShutdownWindow(window);

				break;
			}

			/*case CreateNotify:
			{
			printf( "Window was created\n" );
			l_Window->InitializeGL();

			if( IsValid( l_Window->m_OnCreated ) )
			{
			l_Window->m_OnCreated();
			}

			break;
			} */

			case KeyPress:
			{
				unsigned int functionKeysym = XkbKeycodeToKeysym( 
					instance->currentDisplay, currentEvent.xkey.keycode, 0, currentEvent.xkey.state & ShiftMask ? 1 : 0 );

				if ( functionKeysym <= 255 )
				{
					window->keys[ functionKeysym ] = keyState_t::down;
					if ( window->keyEvent != nullptr )
					{
						window->keyEvent( functionKeysym, keyState_t::down );
					}
				}

				else
				{
					window->keys[ Linux_TranslateKey( functionKeysym ) ] = keyState_t::down;

					if ( window->keyEvent != nullptr )
					{
						window->keyEvent( Linux_TranslateKey( functionKeysym ), keyState_t::down );
					}
				}

				break;
			}

			case KeyRelease:
			{
				bool isRetriggered = false;
				if ( XEventsQueued( instance->currentDisplay, QueuedAfterReading ) )
				{
					XEvent nextEvent;
					XPeekEvent( instance->currentDisplay, &nextEvent );

					if ( nextEvent.type == KeyPress &&
						nextEvent.xkey.time == currentEvent.xkey.time &&
						nextEvent.xkey.keycode == currentEvent.xkey.keycode )
					{
						unsigned int functionKeysym = XkbKeycodeToKeysym( 
							instance->currentDisplay, currentEvent.xkey.keycode, 0, 
							currentEvent.xkey.state & ShiftMask ? 1 : 0 );

						XNextEvent( instance->currentDisplay, &currentEvent );
						window->keyEvent( Linux_TranslateKey( functionKeysym ), keyState_t::down );
						isRetriggered = true;
					}
				}

				if ( !isRetriggered )
				{
					unsigned int functionKeysym = XkbKeycodeToKeysym( 
					instance->currentDisplay, currentEvent.xkey.keycode, 0, currentEvent.xkey.state & ShiftMask ? 1 : 0 );

					if ( functionKeysym <= 255 )
					{
						window->keys[ functionKeysym ] = keyState_t::up;

						if ( window->keyEvent != nullptr )
						{
							window->keyEvent( functionKeysym, keyState_t::up );
						}
					}

					else
					{
						window->keys[ Linux_TranslateKey( functionKeysym ) ] = keyState_t::up;

						if ( window->keyEvent != nullptr )
						{
							window->keyEvent( Linux_TranslateKey( functionKeysym ), keyState_t::up );
						}
					}

					if ( window->keyEvent != nullptr )
					{
						window->keyEvent( Linux_TranslateKey( functionKeysym ), keyState_t::up );
					}
				}

				break;
			}

			case ButtonPress:
			{
				switch ( currentEvent.xbutton.button )
				{
				case 1:
				{
					window->mouseButton[ (unsigned int)mouseButton_t::left ] = buttonState_t::down;

					if ( window->mouseButtonEvent != nullptr )
					{
						window->mouseButtonEvent( mouseButton_t::left, buttonState_t::down );
					}
					break;
				}

				case 2:
				{
					window->mouseButton[ (unsigned int)mouseButton_t::middle ] = buttonState_t::down;

					if ( window->mouseButtonEvent != nullptr )
					{
						window->mouseButtonEvent( mouseButton_t::middle, buttonState_t::down );
					}
					break;
				}

				case 3:
				{
					window->mouseButton[ (unsigned int)mouseButton_t::right ] = buttonState_t::down;

					if ( window->mouseButtonEvent != nullptr )
					{
						window->mouseButtonEvent( mouseButton_t::right, buttonState_t::down );
					}
					break;
				}

				case 4:
				{
					window->mouseButton[ (unsigned int)mouseScroll_t::up ] = buttonState_t::down;

					if ( window->mouseWheelEvent != nullptr )
					{
						window->mouseWheelEvent( mouseScroll_t::down );
					}
					break;
				}

				case 5:
				{
					window->mouseButton[ (unsigned int)mouseScroll_t::down ] = buttonState_t::down;

					if ( window->mouseWheelEvent != nullptr )
					{
						window->mouseWheelEvent( mouseScroll_t::down );
					}
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

			case ButtonRelease:
			{
				switch ( currentEvent.xbutton.button )
				{
				case 1:
				{
					//the left mouse button was released
					window->mouseButton[ (unsigned int)mouseButton_t::left ] = buttonState_t::up;

					if ( window->mouseButtonEvent != nullptr )
					{
						window->mouseButtonEvent( mouseButton_t::left, buttonState_t::up );
					}
					break;
				}

				case 2:
				{
					//the middle mouse button was released
					window->mouseButton[ (unsigned int)mouseButton_t::middle ] = buttonState_t::up;

					if ( window->mouseButtonEvent != nullptr )
					{
						window->mouseButtonEvent( mouseButton_t::middle, buttonState_t::up );
					}
					break;
				}

				case 3:
				{
					//the right mouse button was released
					window->mouseButton[ (unsigned int)mouseButton_t::right ] = buttonState_t::up;

					if ( window->mouseButtonEvent != nullptr )
					{
						window->mouseButtonEvent( mouseButton_t::right, buttonState_t::up );
					}
					break;
				}

				case 4:
				{
					//the mouse wheel was scrolled up
					window->mouseButton[ (unsigned int)mouseScroll_t::up ] = buttonState_t::down;
					break;
				}

				case 5:
				{
					//the mouse wheel was scrolled down
					window->mouseButton[ (unsigned int)mouseScroll_t::down ] = buttonState_t::down;
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
				window->mousePosition[ 0 ] =
					currentEvent.xmotion.x;

				window->mousePosition[ 1 ] =
					currentEvent.xmotion.y;

				///set the screen mouse position to match the event
				instance->screenMousePosition[ 0 ] = currentEvent.xmotion.x_root;
				instance->screenMousePosition[ 1 ] = currentEvent.xmotion.y_root;

				if ( window->mouseMoveEvent != nullptr )
				{
					window->mouseMoveEvent( currentEvent.xmotion.x,
						currentEvent.xmotion.y, currentEvent.xmotion.x_root,
						currentEvent.xmotion.y_root );
				}
				break;
			}

			//when the window goes out of focus
			case FocusOut:
			{
				window->inFocus = false;
				if ( window->focusEvent != nullptr )
				{
					window->focusEvent( 
						window->inFocus );
				}
				break;
			}

			//when the window is back in focus ( use to call restore callback? )
			case FocusIn:
			{
				window->inFocus = true;

				if ( window->focusEvent != nullptr )
				{
					window->focusEvent( window->inFocus );
				}
				break;
			}

			//when a request to resize the window is made either by 
			//dragging out the window or programmatically
			case ResizeRequest:
			{
				window->resolution[ 0 ] = currentEvent.xresizerequest.width;
				window->resolution[ 1 ] = currentEvent.xresizerequest.height;

				glViewport( 0, 0,
					window->resolution[ 0 ],
					window->resolution[ 1 ] );

				if ( window->resizeEvent != nullptr )
				{
					window->resizeEvent( currentEvent.xresizerequest.width,
						currentEvent.xresizerequest.height );
				}

				break;
			}

			//when a request to configure the window is made
			case ConfigureNotify:
			{
				glViewport( 0, 0, currentEvent.xconfigure.width,
					currentEvent.xconfigure.height );

				//check if window was resized
				if ( ( unsigned int )currentEvent.xconfigure.width != window->resolution[ 0 ]
					|| ( unsigned int )currentEvent.xconfigure.height != window->resolution[ 1 ] )
				{
					if ( window->resizeEvent != nullptr )
					{
						window->resizeEvent( currentEvent.xconfigure.width, currentEvent.xconfigure.height );
					}

					window->resolution[ 0 ] = currentEvent.xconfigure.width;
					window->resolution[ 1 ] = currentEvent.xconfigure.height;
				}

				//check if window was moved
				if ( ( unsigned int )currentEvent.xconfigure.x != window->position[ 0 ]
					|| ( unsigned int )currentEvent.xconfigure.y != window->position[ 1 ] )
				{
					if ( window->movedEvent != nullptr )
					{
						window->movedEvent( currentEvent.xconfigure.x, currentEvent.xconfigure.y );
					}

					window->position[ 0 ] = currentEvent.xconfigure.x;
					window->position[ 1 ] = currentEvent.xconfigure.y;
				}
				break;
			}

			case PropertyNotify:
			{
				//this is needed in order to read from the windows WM_STATE Atomic
				//to determine if the property notify event was caused by a client
				//iconify event( minimizing the window ), a maximise event, a focus 
				//event and an attention demand event. NOTE these should only be 
				//for eventts that are not triggered programatically 

				Atom type;
				int format;
				ulong numItems, bytesAfter;
				unsigned char*  properties = nullptr;

				XGetWindowProperty( instance->currentDisplay, currentEvent.xproperty.window,
					window->AtomState,
					0, LONG_MAX, false, AnyPropertyType,
					&type, &format, &numItems, &bytesAfter,
					& properties );

				if (  properties && ( format == 32 ) )
				{
					//go through each property and match it to an existing Atomic state
					for ( unsigned int currentItem = 0; currentItem < numItems; currentItem++ )
					{
						Atom currentProperty = ( ( long* )(  properties ) )[ currentItem ];

						if ( currentProperty == window->AtomHidden )
						{
							//window was minimized
							if ( window->minimizedEvent != nullptr )
							{
								//if the minimized callback for the window was set							
								window->minimizedEvent();
							}
						}

						if ( currentProperty == window->AtomMaxVert ||
							currentProperty == window->AtomMaxVert )
						{
							//window was maximized
							if ( window->maximizedEvent != nullptr )
							{
								//if the maximized callback for the window was set
								window->maximizedEvent();
							}
						}

						if ( currentProperty == window->AtomFocused )
						{
							//window is now in focus. we can ignore this is as FocusIn/FocusOut does this anyway
						}

						if ( currentProperty == window->AtomDemandsAttention )
						{
							//the window demands attention like a celebrity
							printf( "window demands attention \n" );
						}
					}
				}

				break;
			}

			case GravityNotify:
			{
				//this is only supposed to pop up when the parent of this window( if any ) has something happen
				//to it so that this window can react to said event as well.
				break;
			}

			//check for events that were created by the TinyWindow manager
			case ClientMessage:
			{
				const char* atomName = XGetAtomName( instance->currentDisplay, currentEvent.xclient.message_type );
				if ( IsValid( atomName ) )
				{
					//printf( "%s\n", l_AtomName );
				}

				if ( ( Atom )currentEvent.xclient.data.l[ 0 ] == window->AtomClose )
				{
					window->shouldClose = true;
					if( window->destroyedEvent != nullptr )
					{
						window->destroyedEvent();
					}
					break;	
				}

				//check if full screen
				if ( ( Atom )currentEvent.xclient.data.l[ 1 ] == window->AtomFullScreen )
				{
					break;
				}
				break;
	
			}

			default:
			{
				return;
			}
		}
	}

	//get pointer to X11 display
	static Display* GetDisplay( void )
	{
		return GetInstance()->currentDisplay;
	}

	//debugging. used to determine what type of event was generated
	static const char* Linux_GetEventType( XEvent currentEvent )
	{
		switch ( currentEvent.type )
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
	static unsigned int Linux_TranslateKey( unsigned int keySymbol )
	{
		switch ( keySymbol )
		{
		case XK_Escape:
		{
			return escape;
		}

		case XK_Home:
		{
			return home;
		}

		case XK_Left:
		{
			return arrowLeft;
		}

		case XK_Right:
		{
			return arrowRight;
		}

		case XK_Up:
		{
			return arrowUp;
		}

		case XK_Down:
		{
			return arrowDown;
		}

		case XK_Page_Up:
		{
			return pageUp;
		}

		case XK_Page_Down:
		{
			return pageDown;
		}

		case XK_End:
		{
			return end;
		}

		case XK_Print:
		{
			return printScreen;
		}

		case XK_Insert:
		{
			return insert;
		}

		case XK_Num_Lock:
		{
			return numLock;
		}

		case XK_KP_Multiply:
		{
			return keypadMultiply;
		}

		case XK_KP_Add:
		{
			return keypadAdd;
		}

		case XK_KP_Subtract:
		{
			return keypadSubtract;
		}

		case XK_KP_Decimal:
		{
			return keypadPeriod;
		}

		case XK_KP_Divide:
		{
			return keypadDivide;
		}

		case XK_KP_0:
		{
			return keypad0;
		}

		case XK_KP_1:
		{
			return keypad1;
		}

		case XK_KP_2:
		{
			return keypad2;
		}

		case XK_KP_3:
		{
			return keypad3;
		}

		case XK_KP_4:
		{
			return keypad4;
		}

		case XK_KP_5:
		{
			return keypad5;
		}

		case XK_KP_6:
		{
			return keypad6;
		}

		case XK_KP_7:
		{
			return keypad7;
		}

		case XK_KP_8:
		{
			return keypad8;
		}

		case XK_KP_9:
		{
			return keypad9;
		}

		case XK_F1:
		{
			return F1;
		}

		case XK_F2:
		{
			return F2;
		}

		case XK_F3:
		{
			return F3;
		}

		case XK_F4:
		{
			return F4;
		}

		case XK_F5:
		{
			return F5;
		}

		case XK_F6:
		{
			return F6;
		}

		case XK_F7:
		{
			return F7;
		}

		case XK_F8:
		{
			return F8;
		}

		case XK_F9:
		{
			return F9;
		}

		case XK_F10:
		{
			return F10;
		}

		case XK_F11:
		{
			return F11;
		}

		case XK_F12:
		{
			return F12;
		}

		case XK_Shift_L:
		{
			return leftShift;
		}

		case XK_Shift_R:
		{
			return rightShift;
		}

		case XK_Control_R:
		{
			return rightControl;
		}

		case XK_Control_L:
		{
			return leftControl;
		}

		case XK_Caps_Lock:
		{
			return capsLock;
		}

		case XK_Alt_L:
		{
			return leftAlt;
		}

		case XK_Alt_R:
		{
			return rightAlt;
		}

		default:
		{
			return 0;
		}
		}
	}

	static void Linux_SetWindowIcon( void ) /*std::unique_ptr<window_t> window, const char* icon, unsigned int width, unsigned int height */
	{
		//sorry :( 
		PrintErrorMessage( std::error_code(linuxFunctionNotImplemented, errorCategory));
	}

	static GLXFBConfig GetBestFrameBufferConfig(std::unique_ptr<window_t>& givenWindow)
	{
		const int visualAttributes[  ] =
		{
			GLX_X_RENDERABLE, true,
			GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
			GLX_RED_SIZE, givenWindow->colorBits,
			GLX_GREEN_SIZE, givenWindow->colorBits,
			GLX_BLUE_SIZE, givenWindow->colorBits,
			GLX_ALPHA_SIZE, givenWindow->colorBits,
			GLX_DEPTH_SIZE, givenWindow->depthBits,
			GLX_STENCIL_SIZE, givenWindow->stencilBits,
			GLX_DOUBLEBUFFER, true,
			None
		};

		int frameBufferCount;
		unsigned int bestBufferConfig;//, bestNumSamples = 0;
		GLXFBConfig* configs = glXChooseFBConfig(instance->currentDisplay, 0, visualAttributes, &frameBufferCount);

		for ( int currentConfig = 0; currentConfig < frameBufferCount; currentConfig++ )
		{
			XVisualInfo* visualInfo = glXGetVisualFromFBConfig(instance->currentDisplay, configs[currentConfig]);

			if ( visualInfo )
			{
				//printf( "%i %i %i\n", VisInfo->depth, VisInfo->bits_per_rgb, VisInfo->colormap_size );
				int samples, sampleBuffer;
				glXGetFBConfigAttrib( instance->currentDisplay, configs[ currentConfig ], GLX_SAMPLE_BUFFERS, &sampleBuffer );
				glXGetFBConfigAttrib(instance->currentDisplay, configs[currentConfig], GLX_SAMPLES, &samples);

				if ( sampleBuffer && samples > -1 )
				{
					bestBufferConfig = currentConfig;
					//bestNumSamples = samples;
				}
			}

			XFree( visualInfo );
		}

		GLXFBConfig BestConfig = configs[ bestBufferConfig ];

		XFree( configs );

		return BestConfig;
	}

#endif
};

windowManager* windowManager::instance = nullptr;
std::unique_ptr<windowManager::window_t> windowManager::nullWindow = nullptr;
windowManager::errorCategory_t windowManager::errorCategory = windowManager::errorCategory_t();
}



#endif

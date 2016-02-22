//created my Ziyad Barakat 2014 - 2015

#ifndef TINYWINDOW_H
#define TINYWINDOW_H

#if defined( _WIN32 ) || defined( _WIN64 )
#include <Windows.h>
#include <gl/GL.h>
#include <io.h>
#include <fcntl.h>
//this automatically loads the OpenGL library if you are using Visual studio 
#pragma comment ( lib, "opengl32.lib" )
//this makes sure that the entry point of your program is main(). not Winmain()
#pragma comment( linker, "/subsystem:windows /ENTRY:mainCRTStartup" )
#endif

#if defined( __linux__ )
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/XKBlib.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <limits.h>
#include <string.h>
#include <functional>

const int DEFAULT_WINDOW_WIDTH = 1280;
const int DEFAULT_WINDOW_HEIGHT = 720;

enum tinyWindowKeyState_t
{
	KEYSTATE_UP = 0,				/**< the key is currently up */
	KEYSTATE_DOWN,					/**< the key is currently down */
};

enum tinyWindowKey_t
{
	KEY_ERROR = -1,					/**< the key pressed is considered invalid */
	KEY_FIRST = 256 + 1,			/**< the fist key that is not a char */
	KEY_F1, 						/**< the F1 key */
	KEY_F2,							/**< the F2 key */
	KEY_F3,							/**< the F3 key */
	KEY_F4,							/**< the F4 key */
	KEY_F5,							/**< the F5 key */
	KEY_F6,							/**< the F6 key */
	KEY_F7,							/**< the F7 key */
	KEY_F8,							/**< the F8 key */
	KEY_F9,							/**< the F9 key */
	KEY_F10,						/**< the F10 key */
	KEY_F11,						/**< the F11 key */
	KEY_F12,						/**< the F12 key */
	KEY_CAPSLOCK,					/**< the CapsLock key */
	KEY_LEFTSHIFT,					/**< the left Shift key */
	KEY_RIGHTSHIFT,					/**< the right Shift key */
	KEY_LEFTCONTROL,				/**< the left Control key */
	KEY_RIGHTCONTROL,				/**< the right Control key */
	KEY_LEFTWINDOW,					/**< the left Window key */
	KEY_RIGHTWINDOW,				/**< the right Window key */
	KEY_LEFTALT,					/**< the left Alternate key */
	KEY_RIGHTALT,					/**< the right Alternate key */
	KEY_ENTER,						/**< the Enter/Return key */
	KEY_PRINTSCREEN,				/**< the PrintScreen key */
	KEY_SCROLLLOCK,					/**< the ScrollLock key */
	KEY_NUMLOCK,					/**< the NumLock key */
	KEY_PAUSE,						/**< the pause/break key */
	KEY_INSERT,						/**< the insert key */
	KEY_HOME,						/**< the Home key */
	KEY_END,						/**< the End key */
	KEY_PAGEUP,						/**< the PageUp key */
	KEY_PAGEDOWN,					/**< the PageDown key */
	KEY_ARROW_DOWN,					/**< the ArrowDown key */
	KEY_ARROW_UP,					/**< the ArrowUp key */
	KEY_ARROW_LEFT,					/**< the ArrowLeft key */
	KEY_ARROW_RIGHT,				/**< the ArrowRight key */
	KEY_KEYPAD_DIVIDE,				/**< the KeyPad Divide key */
	KEY_KEYPAD_MULTIPLY,			/**< the Keypad Multiply key */
	KEY_KEYPAD_SUBTRACT,			/**< the Keypad Subtract key */
	KEY_KEYPAD_ADD,					/**< the Keypad Add key */
	KEY_KEYPAD_ENTER,				/**< the Keypad Enter key */
	KEY_KEYPAD_PERIOD,				/**< the Keypad Period/Decimal key */
	KEY_KEYPAD_0,					/**< the Keypad 0 key */
	KEY_KEYPAD_1,					/**< the Keypad 1 key */
	KEY_KEYPAD_2,					/**< the Keypad 2 key */
	KEY_KEYPAD_3,					/**< the Keypad 3 key */
	KEY_KEYPAD_4,					/**< the Keypad 4 key */
	KEY_KEYPAD_5,					/**< the Keypad 5 key */
	KEY_KEYPAD_6,					/**< the Keypad 6 key */
	KEY_KEYPAD_7,					/**< the Keypad 7 key */
	KEY_KEYPAD_8,					/**< the keypad 8 key */
	KEY_KEYPAD_9,					/**< the Keypad 9 key */
	KEY_BACKSPACE,					/**< the Backspace key */
	KEY_TAB,						/**< the Tab key */
	KEY_DELETE,						/**< the Delete key */
	KEY_ESCAPE,						/**< the Escape key */
	KEY_LAST = KEY_ESCAPE,			/**< the last key to be supported */
};

enum tinyWindowButtonState_t
{
	MOUSE_BUTTONUP = 0,				/**< the mouse button is currently up */
	MOUSE_BUTTONDOWN				/**< the mouse button is currently down */
};

enum tinyWindowMouseButton_t
{
	MOUSE_LEFTBUTTON = 0,			/**< the left mouse button */
	MOUSE_RIGHTBUTTON,				/**< the right mouse button */
	MOUSE_MIDDLEBUTTON,				/**< the middle mouse button / ScrollWheel */
	MOUSE_LAST,						/**< the last mouse button to be supported */
};

enum tinyWindowMouseScroll_t
{
	MOUSE_SCROLL_DOWN = 0,			/**< the mouse wheel up */
	MOUSE_SCROLL_UP					/**< the mouse wheel down */
};

enum tinyWindowStyle_t
{
	WINDOWSTYLE_BARE = 1,			/**< the window has no decorators but the window border and title bar */
	WINDOWSTYLE_DEFAULT,			/**< the default window style for the respective platform */
	WINDOWSTYLE_POPUP,				/**< the window has no decorators */
};

enum tinyWindowState_t
{
	WINDOWSTATE_NORMAL = 0,			/**< the window is in its default state */
	WINDOWSTATE_MAXIMIZED,			/**< the window is currently maximized */
	WINDOWSTATE_MINIMIZED,			/**< the window is currently minimized */
	WINDOWSTATE_FULLSCREEN,			/**< the window is currently full screen */
};

enum tinyWindowDecorator_t
{
	DECORATOR_TITLEBAR = 0x01,				/**< The title bar decoration of the window */
	DECORATOR_ICON = 0x02,					/**< the icon decoration of the window */
	DECORATOR_BORDER = 0x04,				/**< the border decoration of the window */
	DECORATOR_MINIMIZEBUTTON = 0x08,		/**< the minimize button decoration of the window */
	DECORATOR_MAXIMIZEBUTTON = 0x010,		/**< the maximize button decoration pf the window */
	DECORATOR_CLOSEBUTTON = 0x20,			/**< the close button decoration of the window */
	DECORATOR_SIZEABLEBORDER = 0x40,		/**< the sizable border decoration of the window */
};

enum tinyWindowError_t
{
	TINYWINDOW_ERROR = -1,
	TINYWINDOW_ERROR_NO_CONTEXT = 0,							/**< if a window tries to use a graphical function without a context */
	TINYWINDOW_ERROR_INVALID_WINDOW_NAME,						/**< if an invalid window name was given */
	TINYWINDOW_ERROR_INVALID_ICON_PATH,							/**< if an invalid icon path was given */
	TINYWINDOW_ERROR_INVALID_WINDOW_INDEX,						/**< if an invalid window index was given */
	TINYWINDOW_ERROR_INVALID_WINDOW_STATE,						/**< if an invalid window state was given */
	TINYWINDOW_ERROR_INVALID_RESOLUTION,						/**< if an invalid window resolution was given */
	TINYWINDOW_ERROR_INVALID_CONTEXT,							/**< if the OpenGL context for the window is invalid */
	TINYWINDOW_ERROR_EXISTING_CONTEXT,							/**< if the window already has an OpenGL context */
	TINYWINDOW_ERROR_NOT_INITIALIZED,							/**< if the window is being used without being initialized */
	TINYWINDOW_ERROR_ALREADY_INITIALIZED,						/**< if the window was already initialized */
	TINYWINDOW_ERROR_INVALID_TITLEBAR,							/**< if the Title-bar text given was invalid */
	TINYWINDOW_ERROR_INVALID_CALLBACK,							/**< if the given event callback was invalid */
	TINYWINDOW_ERROR_WINDOW_NOT_FOUND,							/**< if the window was not found in the window manager */
	TINYWINDOW_ERROR_INVALID_WINDOWSTYLE,						/**< if the window style gives is invalid */
	TINYWINDOW_ERROR_FUNCTION_NOT_IMPLEMENTED,					/**< if the function has not yet been implemented in the current version of the API */
	TINYWINDOW_ERROR_LINUX_CANNOT_CONNECT_X_SERVER,				/**< Linux: if cannot connect to an X11 server */
	TINYWINDOW_ERROR_LINUX_INVALID_VISUALINFO,					/**< Linux: if visual information given was invalid */
	TINYWINDOW_ERROR_LINUX_CANNOT_CREATE_WINDOW,				/**< Linux: when X11 fails to create a new window */
	TINYWINDOW_ERROR_LINUX_FUNCTION_NOT_IMPLEMENTED,			/**< Linux: when the function has not yet been implemented on the Linux in the current version of the API */
	TINYWINDOW_ERROR_WINDOWS_CANNOT_CREATE_WINDOW,				/**< Windows: when Win32 cannot create a window */
	TINYWINDOW_ERROR_WINDOWS_CANNOT_INITIALIZE,					/**< Windows: when Win32 cannot initialize */
	TINYWINDOW_ERROR_WINDOWS_FUNCTION_NOT_IMPLEMENTED,			/**< Windows: when a function has yet to be implemented on the Windows platform in the current version of the API */
};

const int LINUX_FUNCTION = 1;
const int LINUX_DECORATOR = 2;

//print the warning message associated with the given warning number
/*
static void TinyWindow_PrintWarningMessage( GLuint warningNumber )
{
	switch ( warningNumber )
	{
		case TINYWINDOW_WARNING_NO_GL_EXTENSIONS:
		{
			printf( "Warning: no OpenGL extensions available \n" );
			break;
		}

		case TINYWINDOW_WARNING_NOT_CURRENT_CONTEXT:
		{
			printf( "Warning: window not the current OpenGL context being rendered to \n" );
			break;
		}

		default:
		{
			printf( "Warning: unspecified warning \n" );
			break;
		}
	}
}*/

/**
* print out the error associated with the given error number	
*/
static void TinyWindow_PrintErrorMessage( const unsigned int errorNumber )
{
	switch ( errorNumber )
	{
		case TINYWINDOW_ERROR_NO_CONTEXT:
		{
			printf( "Error: An OpenGL context must first be created( initialize the window ) \n" );
			break;
		}

		case TINYWINDOW_ERROR_INVALID_WINDOW_NAME:
		{
			printf( "Error: invalid window name \n" );
			break;
		}

		case TINYWINDOW_ERROR_INVALID_ICON_PATH:
		{
			printf( "Error: invalid icon path \n" );
			break;
		}

		case TINYWINDOW_ERROR_INVALID_WINDOW_INDEX:
		{
			printf( "Error: invalid window index \n" );
			break;
		}

		case TINYWINDOW_ERROR_INVALID_WINDOW_STATE:
		{
			printf( "Error: invalid window state \n" );
			break;
		}

		case TINYWINDOW_ERROR_INVALID_RESOLUTION:
		{
			printf( "Error: invalid resolution \n" );
			break;
		}

		case TINYWINDOW_ERROR_INVALID_CONTEXT:
		{
			printf( "Error: Failed to create OpenGL context \n" );
			break;
		}

		case TINYWINDOW_ERROR_EXISTING_CONTEXT:
		{
			printf( "Error: context already created \n" );
			break;
		}

		case TINYWINDOW_ERROR_NOT_INITIALIZED:
		{
			printf( "Error: Window manager not initialized \n" );
			break;
		}

		case TINYWINDOW_ERROR_ALREADY_INITIALIZED:
		{
			printf( "Error: window has already been initialized \n" );
			break;
		}

		case TINYWINDOW_ERROR_INVALID_TITLEBAR:
		{
			printf( "Error: invalid title bar name ( cannot be null or nullptr ) \n" );
			break;
		}

		case TINYWINDOW_ERROR_INVALID_CALLBACK:
		{
			printf( "Error: invalid event callback given \n" );
			break;
		}

		case TINYWINDOW_ERROR_WINDOW_NOT_FOUND:
		{
			printf( "Error: window was not found \n" );
			break;
		}

		case TINYWINDOW_ERROR_INVALID_WINDOWSTYLE:
		{
			printf( "Error: invalid window style given \n" );
			break;
		}

		case TINYWINDOW_ERROR_FUNCTION_NOT_IMPLEMENTED:
		{
			printf( "Error: I'm sorry but this function has not been implemented yet :( \n" );
			break;
		}

		case TINYWINDOW_ERROR_LINUX_CANNOT_CONNECT_X_SERVER:
		{
			printf( "Error: cannot connect to X server \n" );
			break;
		}

		case TINYWINDOW_ERROR_LINUX_INVALID_VISUALINFO:
		{
			printf( "Error: Invalid visual information given \n" );
			break;
		}

		case TINYWINDOW_ERROR_LINUX_CANNOT_CREATE_WINDOW:
		{
			printf( "Error: failed to create window \n" );
			break;
		}

		case TINYWINDOW_ERROR_LINUX_FUNCTION_NOT_IMPLEMENTED:
		{
			printf( "Error: function not implemented on linux platform yet. sorry :( \n" );
			break;
		}

		case TINYWINDOW_ERROR_WINDOWS_CANNOT_CREATE_WINDOW:
		{
			printf( "Error: failed to create window \n" );
			break;
		}

		case TINYWINDOW_ERROR_WINDOWS_FUNCTION_NOT_IMPLEMENTED:
		{
			printf( "Error: function not implemented on Windows platform yet. sorry ;( \n" );
			break;
		}

		default:
		{
			printf( "Error: unspecified Error \n" );
			break;
		}
	}
}

class windowManager
{
	struct window_t;

public:

	windowManager(){}

	/**
	 * shutdown and delete all windows in the manager
	 */
	~windowManager( void )
	{
		if ( !GetInstance()->windowList.empty() )
		{
			for ( auto CurrentWindow : GetInstance()->windowList )
			{
				delete CurrentWindow;
			}
			GetInstance()->windowList.clear();
		}
	}

	/**
	 * use this to shutdown the window manager when your program is finished
	 */
	 static inline void ShutDown( void ) 
	{
		if (GetInstance()->IsInitialized())
		{
			for (auto CurrentWindow : instance->windowList)
			{
				delete CurrentWindow;
			}

#if defined( CURRENT_OS_LINUX )
			XCloseDisplay(instance->currentDisplay);
#endif

			instance->windowList.clear();
			instance->isInitialized = false;
			delete instance;

		}
		TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_NOT_INITIALIZED);
	}

	/**
	 *use this to add a window to the manager. returns a pointer to the manager which allows for the easy creation of multiple windows
	 */
	static inline windowManager* AddWindow( const char* windowName, unsigned int width = DEFAULT_WINDOW_WIDTH, unsigned int height = DEFAULT_WINDOW_HEIGHT, unsigned int colourBits = 8, unsigned int depthBits = 8, unsigned int stencilBits = 8 )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( IsValid( windowName ) )
			{
				window_t* newWindow = new window_t;
				newWindow->name = windowName;
				newWindow->resolution[ 0 ] = width;
				newWindow->resolution[ 1 ] = height;
				newWindow->colorBits = colourBits;
				newWindow->depthBits = depthBits;
				newWindow->stencilBits = stencilBits;

				instance->windowList.push_back( newWindow );
				newWindow->iD = GetNumWindows() - 1;

				Platform_InitializeWindow( newWindow );

				return instance;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_WINDOW_NAME);
			return nullptr;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return nullptr;
	}

	/**
	 * return the total amount of windows the manager has
	 */
	static inline int GetNumWindows( void )
	{
		if ( GetInstance()->IsInitialized() )
		{
			return instance->windowList.size();
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return TINYWINDOW_ERROR;
	}

	/**
	 * return the mouse position in screen co-ordinates
	 */
	static inline bool GetMousePositionInScreen( unsigned int& x, unsigned int& y )
	{
		if ( GetInstance()->IsInitialized() )
		{
			x = instance->screenMousePosition[0];
			y = instance->screenMousePosition[1];
			return true;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	 * return the mouse position in screen co-ordinates
	 */
	static inline unsigned int* GetMousePositionInScreen( void )
	{
		if ( GetInstance()->IsInitialized() )
		{
			return instance->screenMousePosition;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return nullptr;
	}

	/**
	 * set the position of the mouse cursor relative to screen co-ordinates
	 */
	static inline bool SetMousePositionInScreen( unsigned int x, unsigned int y )
	{
		if ( GetInstance()->IsInitialized() )
		{
			instance->screenMousePosition[0] = x;
			instance->screenMousePosition[1] = y;

#if defined( _WIN32 ) || defined( _WIN64 )
			SetCursorPos(x, y);
#elif defined(__linux__)
			XWarpPointer(instance->currentDisplay, None,
				XDefaultRootWindow(instance->currentDisplay), 0, 0,
				GetScreenResolution()[0],
				GetScreenResolution()[1],
				x, y);
#endif
			return true;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * return the Resolution of the current screen
	 */
	static inline unsigned int* GetScreenResolution( void )
	{
		if ( GetInstance()->IsInitialized() )
		{
#if defined( _WIN32 ) || defined( _WIN64 )
			RECT screen;
			HWND desktop = GetDesktopWindow();
			GetWindowRect( desktop, &screen );

			instance->screenResolution[0] = screen.right;
			instance->screenResolution[1] = screen.bottom;
			return instance->screenResolution;

#elif defined(__linux__)
			instance->screenResolution[0] = WidthOfScreen(XDefaultScreenOfDisplay(instance->currentDisplay));
			instance->screenResolution[1] = HeightOfScreen(XDefaultScreenOfDisplay(instance->currentDisplay));

			return instance->screenResolution;
#endif
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return nullptr;
	}
	/**
	 * return the Resolution of the current screen
	 */
	static inline bool GetScreenResolution( unsigned int& width, unsigned int& Height )
	{
		if ( GetInstance()->IsInitialized() )
		{
#if defined( _WIN32 ) || defined( _WIN64 )
			RECT screen;
			HWND desktop = GetDesktopWindow();
			GetWindowRect( desktop, &screen );
			width = screen.right;
			Height = screen.bottom;
#elif defined(__linux__)
			width = WidthOfScreen(XDefaultScreenOfDisplay(instance->currentDisplay));
			Height = HeightOfScreen(XDefaultScreenOfDisplay(instance->currentDisplay));

			instance->screenResolution[0] = width;
			instance->screenResolution[1] = Height;
#endif
			return true;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * return the Resolution of the given window by setting width and height
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
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	 * return the Resolution of the given window by setting width and height
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
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * return the Resolution of the given Window as an array of doubles
	 */
	static inline unsigned int* GetWindowResolutionByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->resolution;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return nullptr;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return nullptr;
	}
	/**
	 * return the Resolution of the Given Window as an array of doubles
	 */
	static inline unsigned int* GetWindowResolutionByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->resolution;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return nullptr;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return nullptr;
	}

	/**
	 * set the Size/Resolution of the given window
	 */
	static inline bool SetWindowResolutionByName( const char* windowName, unsigned int width, unsigned int height )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				GetWindowByName( windowName )->resolution[ 0 ] = width;
				GetWindowByName( windowName )->resolution[ 1 ] = height;
				window_t* window = GetWindowByName(windowName);
#if defined( _WIN32 ) || defined( _WIN64 )
				SetWindowPos(window->windowHandle, HWND_TOP,
					window->position[0], window->position[1],
					window->resolution[0], window->resolution[1],
					SWP_SHOWWINDOW | SWP_NOMOVE);
#elif defined(__linux__)
				XResizeWindow(instance->currentDisplay,
					window->windowHandle, window->resolution[0], window->resolution[1]);
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_INVALID_CONTEXT );
		return false;
	}
	/**
	 * set the Size/Resolution of the given window
	 */
	static inline bool SetWindowResolutionByIndex( unsigned int windowIndex, unsigned int width, unsigned int height )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( WindowExists( windowIndex ) )
			{
				GetWindowByIndex( windowIndex )->resolution[ 0 ] = width;
				GetWindowByIndex( windowIndex )->resolution[ 1 ] = height;
				window_t* window = GetWindowByIndex(windowIndex);

#if defined( _WIN32 ) || defined( _WIN64 )
				
				SetWindowPos(window->windowHandle, HWND_TOP,
					window->position[0], window->position[1],
					window->resolution[0], window->resolution[1],
					SWP_SHOWWINDOW | SWP_NOMOVE);
#elif defined(__linux__)
				XResizeWindow(instance->currentDisplay,
					window->windowHandle, window->resolution[0], window->resolution[1]);
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * return the Position of the given window relative to screen co-ordinates by setting X and Y
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
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	 * return the Position of the given window relative to screen co-ordinates by setting X and Y
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
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * return the Position of the given window relative to screen co-ordinates as an array
	 */
	static inline unsigned int* GetWindowPositionByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->position;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return nullptr;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return nullptr;
	}
	/**
	 * return the Position of the given window relative to screen co-ordinates as an array
	 */
	static inline unsigned int* GetWindowPositionByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->position;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return nullptr;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return nullptr;
	}

	/**
	 * set the Position of the given window relative to screen co-ordinates
	 */
	static inline bool SetWindowPositionByName( const char* windowName, unsigned int x, unsigned int y )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				GetWindowByName( windowName )->position[ 0 ] = x;
				GetWindowByName( windowName )->position[ 1 ] = y;
				window_t* window = GetWindowByName(windowName);
#if defined( _WIN32 ) || defined( _WIN64 )
				SetWindowPos(window->windowHandle, HWND_TOP, x, y,
					window->resolution[0], window->resolution[1],
					SWP_SHOWWINDOW | SWP_NOSIZE);
#elif defined(__linux__)
				XWindowChanges windowChanges;

				windowChanges.x = x;
				windowChanges.y = y;

				XConfigureWindow(
					instance->currentDisplay,
					window->windowHandle, CWX | CWY, &windowChanges);
#endif
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
				return true;
			}
			TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_WINDOW_NOT_FOUND );
			return false;
		}
		
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	 * set the position of the given window relative to screen co-ordinates
	 */
	static inline bool SetWindowPositionByIndex( unsigned int windowIndex, unsigned int x, unsigned int y )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				GetWindowByIndex( windowIndex )->position[ 0 ] = x;
				GetWindowByIndex( windowIndex )->position[ 1 ] = y;
				window_t* window = GetWindowByIndex(windowIndex);
#if defined( _WIN32 ) || defined( _WIN64 )
				SetWindowPos(window->windowHandle, HWND_TOP, x, y,
					window->resolution[0], window->resolution[1],
					SWP_SHOWWINDOW | SWP_NOSIZE);
#elif defined(__linux__)
				XWindowChanges windowChanges;

				windowChanges.x = x;
				windowChanges.y = y;

				XConfigureWindow(
					instance->currentDisplay,
					window->windowHandle, CWX | CWY, &windowChanges);
#endif
				return true;
			}

			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * return the mouse Position relative to the given window's co-ordinates by setting X and Y
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
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	 * return the mouse position relative to the given window's co-ordinates by setting X and Y
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
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return (bool)TINYWINDOW_ERROR;
	}

	/**
	 * return the mouse Position relative to the given window's co-ordinates as an array
	 */
	static inline unsigned int* GetMousePositionInWindowByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->mousePosition;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return nullptr;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return nullptr;
	}
	/**
	 * return the mouse Position relative to the given window's co-ordinates as an array
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
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return nullptr;
	}

	/**
	 * set the mouse Position of the given window's co-ordinates
	 */
	static inline bool SetMousePositionInWindowByName( const char* windowName, unsigned int x, unsigned int y )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				GetWindowByName( windowName )->mousePosition[ 0 ] = x;
				GetWindowByName( windowName )->mousePosition[ 1 ] = y;
				window_t* window = GetWindowByName(windowName);
#if defined( _WIN32 ) || defined( _WIN64 )
				POINT mousePoint;
				mousePoint.x = x;
				mousePoint.y = y;
				ScreenToClient(window->windowHandle, &mousePoint);
				SetCursorPos(mousePoint.x, mousePoint.y);
#elif defined(__linux__)
				XWarpPointer(
					windowManager::GetDisplay(),
					window->windowHandle, window->windowHandle,
					window->position[0], window->position[1],
					window->resolution[0], window->resolution[1],
					window->mousePosition[0], window->mousePosition[1]);
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	 * set the mouse Position of the given window's co-ordinates
	 */
	static inline bool SetMousePositionInWindowByIndex( unsigned int windowIndex, unsigned int x, unsigned int y )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				GetWindowByIndex( windowIndex )->mousePosition[ 0 ] = x;
				GetWindowByIndex( windowIndex )->mousePosition[ 1 ] = y;
				window_t* window = GetWindowByIndex(windowIndex);
#if defined( _WIN32 ) || defined( _WIN64 )
				POINT mousePoint;
				mousePoint.x = x;
				mousePoint.y = y;
				ScreenToClient(window->windowHandle, &mousePoint);
				SetCursorPos(mousePoint.x, mousePoint.y);
#else
				XWarpPointer(
					instance->currentDisplay,
					window->windowHandle, window->windowHandle,
					window->position[0], window->position[1],
					window->resolution[0], window->resolution[1],
					window->mousePosition[0], window->mousePosition[1]);
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * returns the current state of the given key relative to the given window
	 */
	static inline bool WindowGetKeyByName( const char* windowName, unsigned int key )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->keys[ key ];
			}

			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	 * returns the current state of the given key relative to the given window
	 */
	static inline bool WindowGetKeyByIndex( unsigned int windowIndex, unsigned int key )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->keys[ key ];
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * return whether the given window should be closing
	 */
	static inline bool GetWindowShouldCloseByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->shouldClose;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	 * return whether the given window should be closing
	 */
	static inline bool GetWindowShouldCloseByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->shouldClose;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * swap the draw buffers of the given window
	 */
	static inline bool WindowSwapBuffersByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
#if defined( _WIN32 ) || defined( _WIN64 )
				SwapBuffers( GetWindowByName( windowName )->deviceContextHandle );
#elif defined(__linux__)
				glXSwapBuffers( instance->currentDisplay, GetWindowByName( windowName )->windowHandle );
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_NOT_INITIALIZED);
			return false;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	 * swap the draw buffers of the given window
	 */
	static inline bool WindowSwapBuffersByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
#if defined( _WIN32 ) || defined( _WIN64 )
				SwapBuffers( GetWindowByIndex( windowIndex )->deviceContextHandle );
#elif defined(__linux__)
				glXSwapBuffers(instance->currentDisplay, GetWindowByIndex( windowIndex )->windowHandle );
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * make the given window be the current OpenGL Context to be drawn to
	 */
	static inline bool MakeWindowCurrentContextByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{

#if defined( _WIN32 ) || defined( _WIN64 )
				wglMakeCurrent( GetWindowByName( windowName )->deviceContextHandle,
					GetWindowByName( windowName )->glRenderingContextHandle );
#elif defined(__linux__)
				glXMakeCurrent( instance->currentDisplay, GetWindowByName( windowName )->windowHandle,
					GetWindowByName( windowName )->context );
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	 * make the given window be the current OpenGL Context to be drawn to
	 */
	static inline bool MakeWindowCurrentContextByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
#if defined( _WIN32 ) || defined( _WIN64 )
				wglMakeCurrent( GetWindowByIndex( windowIndex )->deviceContextHandle,
					GetWindowByIndex( windowIndex )->glRenderingContextHandle );
#elif defined(__linux__)
				glXMakeCurrent( instance->currentDisplay, GetWindowByIndex( windowIndex )->windowHandle,
					GetWindowByIndex( windowIndex )->context );
#endif
				return true;
			}

			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NO_CONTEXT );
		return false;
	}

	/**
	 * return whether the given window is in fullscreen mode
	 */
	static inline bool GetWindowIsFullScreenByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return ( GetWindowByName( windowName )->currentState == WINDOWSTATE_FULLSCREEN );
			}

			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NO_CONTEXT );
		return false;
	}
	/**
	 * return whether the given window is in fullscreen mode
	 */
	static inline bool GetWindowIsFullScreenByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return ( GetWindowByIndex( windowIndex )->currentState == WINDOWSTATE_FULLSCREEN );
			}

			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NO_CONTEXT );
		return false;
	}	

	/**
	 * toggle the given window's full screen mode
	 */
	static inline bool SetFullScreenByName( const char* windowName, bool newState )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				window_t* window = GetWindowByName(windowName);
				if ( newState )
				{					
					window->currentState = WINDOWSTATE_FULLSCREEN;
#if defined( _WIN32 ) || defined( _WIN64 )
					SetWindowLongPtr(window->windowHandle, GWL_STYLE,
						WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);

					MoveWindow(window->windowHandle, 0, 0, windowManager::GetScreenResolution()[0],
						windowManager::GetScreenResolution()[1], true);
#elif defined(__linux__)
					XEvent currentEvent;
					memset(&currentEvent, 0, sizeof(currentEvent));

					currentEvent.xany.type = ClientMessage;
					currentEvent.xclient.message_type = window->AtomState;
					currentEvent.xclient.format = 32;
					currentEvent.xclient.window = window->windowHandle;
					currentEvent.xclient.data.l[0] = window->currentState == WINDOWSTATE_FULLSCREEN;
					currentEvent.xclient.data.l[1] = window->AtomFullScreen;

					XSendEvent(instance->currentDisplay,
						XDefaultRootWindow(instance->currentDisplay),
						0, SubstructureNotifyMask, &currentEvent);
#endif
					return true;
				}

				else
				{
					GetWindowByName( windowName )->currentState = WINDOWSTATE_NORMAL;
#if defined( _WIN32 ) || defined( _WIN64 )
					SetWindowLongPtr(window->windowHandle, GWL_STYLE,
						WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);

					MoveWindow(window->windowHandle, 0, 0, windowManager::GetScreenResolution()[0],
						windowManager::GetScreenResolution()[1], true);
#elif defined(__linux__)
					XEvent currentEvent;
					memset(&currentEvent, 0, sizeof(currentEvent));

					currentEvent.xany.type = ClientMessage;
					currentEvent.xclient.message_type = window->AtomState;
					currentEvent.xclient.format = 32;
					currentEvent.xclient.window = window->windowHandle;
					currentEvent.xclient.data.l[0] = window->currentState == WINDOWSTATE_FULLSCREEN;
					currentEvent.xclient.data.l[1] = window->AtomFullScreen;

					XSendEvent(instance->currentDisplay,
						XDefaultRootWindow(instance->currentDisplay),
						0, SubstructureNotifyMask, &currentEvent);
#endif
					return true;
				}
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/*
	 * toggle the given window's full screen mode
	 */
	static inline bool SetFullScreenByIndex( unsigned int windowIndex, bool newState )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				window_t* window = GetWindowByIndex(windowIndex);
				if ( newState )
				{
					GetWindowByIndex( windowIndex )->currentState = WINDOWSTATE_FULLSCREEN;
#if defined( _WIN32 ) || defined( _WIN64 )
					SetWindowLongPtr(window->windowHandle, GWL_STYLE,
						WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);

					MoveWindow(window->windowHandle, 0, 0, windowManager::GetScreenResolution()[0],
						windowManager::GetScreenResolution()[1], true);
#elif defined(__linux__)
					XEvent currentEvent;
					memset(&currentEvent, 0, sizeof(currentEvent));

					currentEvent.xany.type = ClientMessage;
					currentEvent.xclient.message_type = window->AtomState;
					currentEvent.xclient.format = 32;
					currentEvent.xclient.window = window->windowHandle;
					currentEvent.xclient.data.l[0] = window->currentState == WINDOWSTATE_FULLSCREEN;
					currentEvent.xclient.data.l[1] = window->AtomFullScreen;

					XSendEvent(instance->currentDisplay,
						XDefaultRootWindow(instance->currentDisplay),
						0, SubstructureNotifyMask, &currentEvent);
#endif
					return true;
				}

				else
				{
					GetWindowByIndex( windowIndex )->currentState = WINDOWSTATE_NORMAL;
#if defined( _WIN32 ) || defined( _WIN64 )
					SetWindowLongPtr(window->windowHandle, GWL_STYLE,
						WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);

					MoveWindow(window->windowHandle, 0, 0, windowManager::GetScreenResolution()[0],
						windowManager::GetScreenResolution()[1], true);
#elif defined(__linux__)
					XEvent currentEvent;
					memset(&currentEvent, 0, sizeof(currentEvent));

					currentEvent.xany.type = ClientMessage;
					currentEvent.xclient.message_type = window->AtomState;
					currentEvent.xclient.format = 32;
					currentEvent.xclient.window = window->windowHandle;
					currentEvent.xclient.data.l[0] = window->currentState == WINDOWSTATE_FULLSCREEN;
					currentEvent.xclient.data.l[1] = window->AtomFullScreen;

					XSendEvent(instance->currentDisplay,
						XDefaultRootWindow(instance->currentDisplay),
						0, SubstructureNotifyMask, &currentEvent);
#endif
					return true;
				}
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * returns whether the given window is minimized
	 */
	static inline bool GetWindowIsMinimizedByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return ( GetWindowByName( windowName )->currentState == WINDOWSTATE_MINIMIZED );
			}
			return (bool)TINYWINDOW_ERROR;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return (bool)TINYWINDOW_ERROR;
	}
	/**
	 * returns whether the given window is minimized
	 */
	static inline bool GetWindowIsMinimizedByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return ( GetWindowByIndex( windowIndex )->currentState == WINDOWSTATE_MINIMIZED );
			}
			return (bool)TINYWINDOW_ERROR;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return (bool)TINYWINDOW_ERROR;
	}

	/**
	 * toggle the minimization state of the given window
	 */
	static inline bool MinimizeWindowByName( const char* windowName, bool newState )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				window_t* window = GetWindowByName(windowName);
				if ( newState )
				{
					window->currentState = WINDOWSTATE_MINIMIZED;

#if defined( _WIN32 ) || defined( _WIN64 )
					ShowWindow(window->windowHandle, SW_MINIMIZE);
#elif defined(__linux__)
					XIconifyWindow(instance->currentDisplay,
						window->windowHandle, 0);
#endif
					return true;
				}

				else
				{
					GetWindowByName( windowName )->currentState = WINDOWSTATE_NORMAL;
#if defined( _WIN32 ) || defined( _WIN64 )
					ShowWindow(window->windowHandle, SW_RESTORE);
#elif defined(__linux__)
					XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
					return true;
				}
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NO_CONTEXT );
		return false;
	}
	/**
	 * toggle the minimization state of the window
	 */
	static inline bool MinimizeWindowByIndex( unsigned int windowIndex, bool newState )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				window_t* window = GetWindowByIndex(windowIndex);
				if (newState)
				{
					window->currentState = WINDOWSTATE_MINIMIZED;

#if defined( _WIN32 ) || defined( _WIN64 )
					ShowWindow(window->windowHandle, SW_MINIMIZE);
#elif defined(__linux__)
					XIconifyWindow(instance->currentDisplay,
						window->windowHandle, 0);
#endif
					return true;
				}

				else
				{
					GetWindowByIndex(windowIndex)->currentState = WINDOWSTATE_NORMAL;
#if defined( _WIN32 ) || defined( _WIN64 )
					ShowWindow(window->windowHandle, SW_RESTORE);
#elif defined(__linux__)
					XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
					return true;
				}
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * return whether the current window is currently maximized
	 */
	static inline bool GetWindowIsMaximizedByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return ( GetWindowByName( windowName )->currentState == WINDOWSTATE_MAXIMIZED );
			}

			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	 * return whether the given window is currently maximized
	 */
	static inline bool GetWindowIsMaximizedByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return ( GetWindowByIndex( windowIndex )->currentState == WINDOWSTATE_MAXIMIZED );
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	
	/**
	 * toggle the maximization state of the current window
	 */
	static inline bool MaximizeWindowByName( const char* windowName, bool newState )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				window_t* window = GetWindowByName(windowName);
				if ( newState )
				{
					GetWindowByName( windowName )->currentState = WINDOWSTATE_MAXIMIZED;
#if defined( _WIN32 ) || defined( _WIN64 )
					ShowWindow(window->windowHandle, SW_MAXIMIZE);
#elif defined(__linux__)
					XEvent currentEvent;
					memset(&currentEvent, 0, sizeof(currentEvent));

					currentEvent.xany.type = ClientMessage;
					currentEvent.xclient.message_type = window->AtomState;
					currentEvent.xclient.format = 32;
					currentEvent.xclient.window = window->windowHandle;
					currentEvent.xclient.data.l[0] = (window->currentState == WINDOWSTATE_MAXIMIZED);
					currentEvent.xclient.data.l[1] = window->AtomMaxVert;
					currentEvent.xclient.data.l[2] = window->AtomMaxHorz;

					XSendEvent(instance->currentDisplay,
						XDefaultRootWindow(instance->currentDisplay),
						0, SubstructureNotifyMask, &currentEvent);
#endif
					return true;
				}

				else
				{
					GetWindowByName( windowName )->currentState = WINDOWSTATE_NORMAL;
#if defined( _WIN32 ) || defined( _WIN64 )
					ShowWindow(window->windowHandle, SW_RESTORE);
#elif defined(__linux__)
					XEvent currentEvent;
					memset(&currentEvent, 0, sizeof(currentEvent));

					currentEvent.xany.type = ClientMessage;
					currentEvent.xclient.message_type = window->AtomState;
					currentEvent.xclient.format = 32;
					currentEvent.xclient.window = window->windowHandle;
					currentEvent.xclient.data.l[0] = (window->currentState == WINDOWSTATE_MAXIMIZED);
					currentEvent.xclient.data.l[1] = window->AtomMaxVert;
					currentEvent.xclient.data.l[2] = window->AtomMaxHorz;

					XSendEvent(instance->currentDisplay,
						XDefaultRootWindow(instance->currentDisplay),
						0, SubstructureNotifyMask, &currentEvent);
#endif
					return true;
				}
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	 * toggle the maximization state of the current window
	 */
	static inline bool MaximizeWindowByIndex( unsigned int windowIndex, bool newState )
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByIndex(windowIndex))
			{
				window_t* window = GetWindowByIndex(windowIndex);
				if (newState)
				{
					window->currentState = WINDOWSTATE_MAXIMIZED;
#if defined( _WIN32 ) || defined( _WIN64 )
					ShowWindow(window->windowHandle, SW_MAXIMIZE);
#elif defined(__linux__)
					XEvent currentEvent;
					memset(&currentEvent, 0, sizeof(currentEvent));

					currentEvent.xany.type = ClientMessage;
					currentEvent.xclient.message_type = window->AtomState;
					currentEvent.xclient.format = 32;
					currentEvent.xclient.window = window->windowHandle;
					currentEvent.xclient.data.l[0] = (window->currentState == WINDOWSTATE_MAXIMIZED);
					currentEvent.xclient.data.l[1] = window->AtomMaxVert;
					currentEvent.xclient.data.l[2] = window->AtomMaxHorz;

					XSendEvent(instance->currentDisplay,
						XDefaultRootWindow(instance->currentDisplay),
						0, SubstructureNotifyMask, &currentEvent);
#endif
					return true;
				}

				else
				{
					window->currentState = WINDOWSTATE_NORMAL;
#if defined( _WIN32 ) || defined( _WIN64 )
					ShowWindow(window->windowHandle, SW_RESTORE);
#elif defined(__linux__)
					XEvent currentEvent;
					memset(&currentEvent, 0, sizeof(currentEvent));

					currentEvent.xany.type = ClientMessage;
					currentEvent.xclient.message_type = window->AtomState;
					currentEvent.xclient.format = 32;
					currentEvent.xclient.window = window->windowHandle;
					currentEvent.xclient.data.l[0] = (window->currentState == WINDOWSTATE_MAXIMIZED);
					currentEvent.xclient.data.l[1] = window->AtomMaxVert;
					currentEvent.xclient.data.l[2] = window->AtomMaxHorz;

					XSendEvent(instance->currentDisplay,
						XDefaultRootWindow(instance->currentDisplay),
						0, SubstructureNotifyMask, &currentEvent);
#endif
					return true;
				}
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_NOT_INITIALIZED);
		return false;
	}

	/**
	 * get window name by index
	 */
	static inline const char* GetWindowNameByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->name;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return nullptr;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return nullptr;
	}	
	/**
	* get window index by name
	*/
	static inline unsigned int GetWindowIndexByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->iD;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	 * set the window title bar	by name
	 */
	static inline bool SetWindowTitleBarByName( const char* windowName, const char* newTitle )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if (IsValid(newTitle))
			{
				if (DoesExistByName(windowName) && IsValid(newTitle))
				{
#if defined( _WIN32 ) || defined( _WIN64 )
					SetWindowText(GetWindowByName(windowName)->windowHandle, newTitle);
#elif defined(__linux__)
					XStoreName(instance->currentDisplay, GetWindowByName(windowName)->windowHandle, newTitle);
#endif
					return true;
				}
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_WINDOW_NAME);
			return false;
		}			
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window title bar by index
	*/
	static inline bool SetWindowTitleBarByIndex( unsigned int windowIndex, const char* newName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if (IsValid(newName))
			{
				if (DoesExistByIndex(windowIndex))
				{
#if defined( _WIN32 ) || defined( _WIN64 )
					SetWindowText(GetWindowByIndex(windowIndex)->windowHandle, newName);
#elif defined(__linux__)
					XStoreName(instance->currentDisplay, GetWindowByIndex(windowIndex)->windowHandle, newName);
#endif
					return true;
				}
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_WINDOW_NAME);
			return false;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window icon by name (currently not functional)
	*/
	static inline bool SetWindowIconByName( void )//const char* windowName, const char* icon, unsigned int width, unsigned int height )
	{
		TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_FUNCTION_NOT_IMPLEMENTED);
		return false;
	/*	if ( GetInstance()->IsInitialized() )
		{
			if (IsValid(icon))
			{
				if (DoesExistByName(windowName))
				{
#if defined( _WIN32 ) || defined( _WIN64 )
					//Windows_SetWindowIcon(GetWindowByName(windowName), icon, width, height);
#elif defined(__linux__)
					//Linux_SetWindowIcon();//GetWindowByName(windowName), icon, width, height);
#endif
					return true;
				}
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
				return false;
			}

			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_ICON_PATH);
			return false;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;*/
	}
	/**
	* set the window icon by index (currently not functional)
	*/
	static inline bool SetWindowIconByIndex( void )//unsigned int windowIndex, const char* icon, unsigned int width, unsigned int height )
	{
		TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_FUNCTION_NOT_IMPLEMENTED);
		return false;
		/*if ( GetInstance()->IsInitialized() )
		{
			if (IsValid(icon))
			{
				if (DoesExistByIndex(windowIndex))
				{
#if defined( _WIN32 ) || defined( _WIN64 )
					Windows_SetWindowIcon(GetWindowByIndex(windowIndex), icon, width, height);
#elif defined(__linux__)
					Linux_SetWindowIcon(GetWindowByIndex(windowIndex), icon, width, height);
#endif
					return true;
				}
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_ICON_PATH);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;*/
	}

	/**
	* get whether the window is in focus by name
	*/
	static inline bool GetWindowIsInFocusByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				return GetWindowByName( windowName )->inFocus;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* get whether the window is in focus by index
	*/
	static inline bool GetWindowIsInFocusByIndex( unsigned int windowIndex )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				return GetWindowByIndex( windowIndex )->inFocus;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}

		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window to be in focus by name
	*/
	static inline bool FocusWindowByName( const char* windowName, bool newState )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				window_t* window = GetWindowByName(windowName);
				if (newState)
				{
#if defined( _WIN32 ) || defined( _WIN64 )
					SetFocus(window->windowHandle);
#elif defined(__linux__)
					XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
					return true;
				}

				else
				{
#if defined(_WIN32) || defined(_WIN64)
					SetFocus(nullptr);
#elif defined(__linux__)
					XUnmapWindow(instance->currentDisplay, window->windowHandle);
#endif
					return true;
				}
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window to be in focus by index
	*/
	static inline bool FocusWindowByIndex( unsigned int windowIndex, bool newState )
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByIndex(windowIndex))
			{
				window_t* window = GetWindowByIndex(windowIndex);
				if (newState)
				{
#if defined( _WIN32 ) || defined( _WIN64 )
					SetFocus(window->windowHandle);
#elif defined(__linux__)
					XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
					return true;
				}

				else
				{
#if defined(_WIN32) || defined(_WIN64)
					SetFocus(nullptr);
#elif defined(__linux__)
					XUnmapWindow(instance->currentDisplay, window->windowHandle);
#endif
					return true;
				}
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_NOT_INITIALIZED);
		return false;
	}

	/**
	 * restore the window by name
	 */
	static inline bool RestoreWindowByName( const char* windowName )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				window_t* window = GetWindowByName(windowName);
#if defined( _WIN32 ) || defined( _WIN64 )
				ShowWindow(window->windowHandle, SW_RESTORE);
#elif defined(__linux__)
				XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* restore the window by index
	*/
	static inline bool RestoreWindowByIndex( unsigned int windowIndex )
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByIndex(windowIndex))
			{
				window_t* window = GetWindowByIndex(windowIndex);
#if defined( _WIN32 ) || defined( _WIN64 )
				ShowWindow(window->windowHandle, SW_RESTORE);
#elif defined(__linux__)
				XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_NOT_INITIALIZED);
		return false;
	}

	/**
	* initialize the window manager
	*/
	static inline bool Initialize( void )
	{
		GetInstance()->isInitialized = false;
#if defined( _WIN32 ) || defined( _WIN64 )
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

		TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOWS_CANNOT_INITIALIZE);
		return false;
#elif defined(__linux__)
		instance->currentDisplay = XOpenDisplay(0);

		if (!instance->currentDisplay)
		{
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_LINUX_CANNOT_CONNECT_X_SERVER);
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
	* return whether the window manager has been initialized
	*/
	static inline bool IsInitialized( void )
	{
		return GetInstance()->isInitialized;
	}

	/**
	* ask the window manager to poll for events
	*/
	static inline void PollForEvents( void )
	{
		if ( GetInstance()->IsInitialized() )
		{
#if defined( _WIN32 ) || defined( _WIN64 )
			//only process events if there are any to process
			if (PeekMessage(&instance->message, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&instance->message);
				DispatchMessage(&instance->message);
			}
#elif defined(__linux__)
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
			TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		}
	}

	/**
	* ask the window manager to wait for events
	*/
	static inline void WaitForEvents( void )
	{
		if ( GetInstance()->IsInitialized() )
		{
#if defined( _WIN32 ) || defined( _WIN64 )
			//process even if there aren't any to process
			GetMessage(&instance->message, 0, 0, 0);
			TranslateMessage(&instance->message);
			DispatchMessage(&instance->message);
#elif defined(__linux__)
			//even if there aren't any events to process
			XNextEvent(instance->currentDisplay, &instance->currentEvent);

			XEvent currentEvent = instance->currentEvent;

			Linux_ProcessEvents(currentEvent);
#endif
		}

		else
		{
			TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		}
	}

	/**
	* remove window from the manager by name
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
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* remove window from the manager by index
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
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window style preset by name
	*/
	static inline bool SetWindowStyleByName( const char* windowName, unsigned int windowStyle )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				window_t* window = GetWindowByName(windowName);
#if defined( _WIN32 ) || defined( _WIN64 )
				switch (windowStyle)
				{
					case WINDOWSTYLE_DEFAULT:
					{
						EnableWindowDecoratorsByName(window->name, DECORATOR_TITLEBAR | DECORATOR_BORDER |
							DECORATOR_CLOSEBUTTON | DECORATOR_MINIMIZEBUTTON | DECORATOR_MAXIMIZEBUTTON);
						break;
					}

					case WINDOWSTYLE_POPUP:
					{
						EnableWindowDecoratorsByName(window->name, 0);
						break;
					}

					case WINDOWSTYLE_BARE:
					{
						EnableWindowDecoratorsByName(window->name, DECORATOR_TITLEBAR | DECORATOR_BORDER);
						break;
					}

					default:
					{
						TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_WINDOWSTYLE);
						break;
					}
				}

#elif defined(__linux__)
				switch (windowStyle)
				{
					case WINDOWSTYLE_DEFAULT:
					{
						window->decorators = (1L << 2);
						window->currentWindowStyle = LINUX_DECORATOR_MOVE | LINUX_DECORATOR_CLOSE |
							LINUX_DECORATOR_MAXIMIZE | LINUX_DECORATOR_MINIMIZE;
						long Hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

						XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32, PropModeReplace,
							(unsigned char*)Hints, 5);

						XMapWindow(instance->currentDisplay, window->windowHandle);
						break;
					}

					case WINDOWSTYLE_BARE:
					{
						window->decorators = (1L << 2);
						window->currentWindowStyle = (1L << 2);
						long Hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

						XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32, PropModeReplace,
							(unsigned char*)Hints, 5);

						XMapWindow(instance->currentDisplay, window->windowHandle);
						break;
					}

					case WINDOWSTYLE_POPUP:
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
						TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_WINDOWSTYLE);
						break;
					}
				}
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window style preset by index
	*/
	static inline bool SetWindowStyleByIndex( unsigned int windowIndex, unsigned int windowStyle )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				window_t* window = GetWindowByIndex(windowIndex);
#if defined( _WIN32 ) || defined( _WIN64 )
				switch (windowStyle)
				{
					case WINDOWSTYLE_DEFAULT:
					{
						EnableWindowDecoratorsByName(window->name, DECORATOR_TITLEBAR | DECORATOR_BORDER |
							DECORATOR_CLOSEBUTTON | DECORATOR_MINIMIZEBUTTON | DECORATOR_MAXIMIZEBUTTON);
						break;
					}

					case WINDOWSTYLE_POPUP:
					{
						EnableWindowDecoratorsByName(window->name, 0);
						break;
					}

					case WINDOWSTYLE_BARE:
					{
						EnableWindowDecoratorsByName(window->name, DECORATOR_TITLEBAR | DECORATOR_BORDER);
						break;
					}

					default:
					{
						TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_WINDOWSTYLE);
						break;
					}
				}
#elif defined(__linux__)
				switch (windowStyle)
				{
					case WINDOWSTYLE_DEFAULT:
					{
						window->decorators = (1L << 2);
						window->currentWindowStyle = LINUX_DECORATOR_MOVE | LINUX_DECORATOR_CLOSE |
							LINUX_DECORATOR_MAXIMIZE | LINUX_DECORATOR_MINIMIZE;
						long Hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

						XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32, PropModeReplace,
							(unsigned char*)Hints, 5);

						XMapWindow(instance->currentDisplay, window->windowHandle);
						break;
					}

					case WINDOWSTYLE_BARE:
					{
						window->decorators = (1L << 2);
						window->currentWindowStyle = (1L << 2);
						long Hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

						XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32, PropModeReplace,
							(unsigned char*)Hints, 5);

						XMapWindow(instance->currentDisplay, window->windowHandle);
						break;
					}

					case WINDOWSTYLE_POPUP:
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
						TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_WINDOWSTYLE);
						break;
					}
				}
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* enable window decorators by name
	*/
	static inline bool EnableWindowDecoratorsByName( const char* windowName, unsigned int decorators )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				window_t* window = GetWindowByName(windowName);
#if defined( _WIN32 ) || defined( _WIN64 )
				window->currentWindowStyle = WS_VISIBLE | WS_CLIPSIBLINGS;

				if (decorators & DECORATOR_BORDER)
				{
					window->currentWindowStyle |= WS_BORDER;
				}

				if (decorators & DECORATOR_TITLEBAR)
				{
					window->currentWindowStyle |= WS_CAPTION;
				}

				if (decorators & DECORATOR_ICON)
				{
					window->currentWindowStyle |= WS_ICONIC;
				}

				if (decorators & DECORATOR_CLOSEBUTTON)
				{
					window->currentWindowStyle |= WS_SYSMENU;
				}

				if (decorators & DECORATOR_MINIMIZEBUTTON)
				{
					window->currentWindowStyle |= WS_MINIMIZEBOX | WS_SYSMENU;
				}

				if (decorators & DECORATOR_MAXIMIZEBUTTON)
				{
					window->currentWindowStyle |= WS_MAXIMIZEBOX | WS_SYSMENU;
				}

				if (decorators & DECORATOR_SIZEABLEBORDER)
				{
					window->currentWindowStyle |= WS_SIZEBOX;
				}

				SetWindowLongPtr(window->windowHandle, GWL_STYLE,
					window->currentWindowStyle);
#elif defined(__linux__)
				if (decorators & DECORATOR_CLOSEBUTTON)
				{
					window->currentWindowStyle |= LINUX_DECORATOR_CLOSE;
					window->decorators = 1;
				}

				if (decorators & DECORATOR_MINIMIZEBUTTON)
				{
					window->currentWindowStyle |= LINUX_DECORATOR_MINIMIZE;
					window->decorators = 1;
				}

				if (decorators & DECORATOR_MAXIMIZEBUTTON)
				{
					window->currentWindowStyle |= LINUX_DECORATOR_MAXIMIZE;
					window->decorators = 1;
				}

				if (decorators & DECORATOR_ICON)
				{
					//Linux ( at least cinnamon ) does not have icons in the window. only in the task bar icon
				}

				//just need to set it to 1 to enable all decorators that include title bar 
				if (decorators & DECORATOR_TITLEBAR)
				{
					window->decorators = 1;
				}

				if (decorators & DECORATOR_BORDER)
				{
					window->decorators = 1;
				}

				if (decorators & DECORATOR_SIZEABLEBORDER)
				{
					window->decorators = 1;
				}

				long hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

				XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32,
					PropModeReplace, (unsigned char*)hints, 5);

				XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* enable windows decorators by index
	*/
	static inline bool EnableWindowDecoratorsByIndex( unsigned int windowIndex, unsigned int decorators )
	{
		if (GetInstance()->IsInitialized())
		{
			if (DoesExistByIndex(windowIndex))
			{
				window_t* window = GetWindowByIndex(windowIndex);
#if defined( _WIN32 ) || defined( _WIN64 )
				window->currentWindowStyle = WS_VISIBLE | WS_CLIPSIBLINGS;

				if (decorators & DECORATOR_BORDER)
				{
					window->currentWindowStyle |= WS_BORDER;
				}

				if (decorators & DECORATOR_TITLEBAR)
				{
					window->currentWindowStyle |= WS_CAPTION;
				}

				if (decorators & DECORATOR_ICON)
				{
					window->currentWindowStyle |= WS_ICONIC;
				}

				if (decorators & DECORATOR_CLOSEBUTTON)
				{
					window->currentWindowStyle |= WS_SYSMENU;
				}

				if (decorators & DECORATOR_MINIMIZEBUTTON)
				{
					window->currentWindowStyle |= WS_MINIMIZEBOX | WS_SYSMENU;
				}

				if (decorators & DECORATOR_MAXIMIZEBUTTON)
				{
					window->currentWindowStyle |= WS_MAXIMIZEBOX | WS_SYSMENU;
				}

				if (decorators & DECORATOR_SIZEABLEBORDER)
				{
					window->currentWindowStyle |= WS_SIZEBOX;
				}

				SetWindowLongPtr(window->windowHandle, GWL_STYLE,
					window->currentWindowStyle);
#elif defined(__linux__)
				if (decorators & DECORATOR_CLOSEBUTTON)
				{
					window->currentWindowStyle |= LINUX_DECORATOR_CLOSE;
					window->decorators = 1;
				}

				if (decorators & DECORATOR_MINIMIZEBUTTON)
				{
					window->currentWindowStyle |= LINUX_DECORATOR_MINIMIZE;
					window->decorators = 1;
				}

				if (decorators & DECORATOR_MAXIMIZEBUTTON)
				{
					window->currentWindowStyle |= LINUX_DECORATOR_MAXIMIZE;
					window->decorators = 1;
				}

				if (decorators & DECORATOR_ICON)
				{
					//Linux ( at least cinnamon ) does not have icons in the window. only in the task bar icon
				}

				//just need to set it to 1 to enable all decorators that include title bar 
				if (decorators & DECORATOR_TITLEBAR)
				{
					window->decorators = 1;
				}

				if (decorators & DECORATOR_BORDER)
				{
					window->decorators = 1;
				}

				if (decorators & DECORATOR_SIZEABLEBORDER)
				{
					window->decorators = 1;
				}

				long hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

				XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32,
					PropModeReplace, (unsigned char*)hints, 5);

				XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_NOT_INITIALIZED);
		return false;
	}

	/**
	* disable windows decorators by name
	*/
	static inline bool DisableWindowDecoratorByName( const char* windowName, unsigned int decorators )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByName( windowName ) )
			{
				window_t* window = GetWindowByName(windowName);
#if defined( _WIN32 ) || defined( _WIN64 )
				if (decorators & DECORATOR_BORDER)
				{
					window->currentWindowStyle &= ~WS_BORDER;
				}

				if (decorators & DECORATOR_TITLEBAR)
				{
					window->currentWindowStyle &= ~WS_MAXIMIZEBOX;
				}

				if (decorators & DECORATOR_ICON)
				{
					window->currentWindowStyle &= ~WS_ICONIC;
				}

				if (decorators & DECORATOR_CLOSEBUTTON)
				{
					window->currentWindowStyle &= ~WS_SYSMENU;
				}

				if (decorators & DECORATOR_MINIMIZEBUTTON)
				{
					window->currentWindowStyle &= ~WS_MINIMIZEBOX;
				}

				if (decorators & DECORATOR_MAXIMIZEBUTTON)
				{
					window->currentWindowStyle &= ~WS_MAXIMIZEBOX;
				}

				if (decorators & DECORATOR_SIZEABLEBORDER)
				{
					window->currentWindowStyle &= ~WS_SIZEBOX;
				}

				SetWindowLongPtr(window->windowHandle, GWL_STYLE,
					window->currentWindowStyle | WS_VISIBLE);
#elif defined(__linux__)
				if (decorators & DECORATOR_CLOSEBUTTON)
				{
					//I hate doing this but it is necessary to keep functionality going.
					bool minimizeEnabled = false;
				    bool maximizeEnabled = false;

					if (decorators & DECORATOR_MAXIMIZEBUTTON)
					{
						maximizeEnabled = true;
					}

					if (decorators & DECORATOR_MINIMIZEBUTTON)
					{
						minimizeEnabled = true;
					}

					window->currentWindowStyle &= ~LINUX_DECORATOR_CLOSE;

					if (maximizeEnabled)
					{
						window->currentWindowStyle |= LINUX_DECORATOR_MAXIMIZE;
					}

					if (minimizeEnabled)
					{
						window->currentWindowStyle |= LINUX_DECORATOR_MINIMIZE;
					}

					window->decorators = 1;
				}

				if (decorators & DECORATOR_MINIMIZEBUTTON)
				{
					window->currentWindowStyle &= ~LINUX_DECORATOR_MINIMIZE;
					window->decorators = 1;
				}

				if (decorators & DECORATOR_MAXIMIZEBUTTON)
				{
					bool minimizeEnabled = false;

					if (decorators & DECORATOR_MINIMIZEBUTTON)
					{
						minimizeEnabled = true;
					}

					window->currentWindowStyle &= ~LINUX_DECORATOR_MAXIMIZE;

					if (minimizeEnabled)
					{
						window->currentWindowStyle |= LINUX_DECORATOR_MINIMIZE;
					}

					window->decorators = 1;
				}

				if (decorators & DECORATOR_ICON)
				{
					//Linux ( at least cinnamon ) does not have icons in the window. only in the taskb ar icon
				}

				//just need to set it to 1 to enable all decorators that include title bar 
				if (decorators & DECORATOR_TITLEBAR)
				{
					window->decorators = LINUX_DECORATOR_BORDER;
				}

				if (decorators & DECORATOR_BORDER)
				{
					window->decorators = 0;
				}

				if (decorators & DECORATOR_SIZEABLEBORDER)
				{
					window->decorators = 0;
				}

				long hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

				XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32,
					PropModeReplace, (unsigned char*)hints, 5);

				XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* disable windows decorators by index
	*/
	static inline bool DisableWindowDecoratorByIndex( unsigned int windowIndex, unsigned int decorators )
	{
		if ( GetInstance()->IsInitialized() )
		{
			if ( DoesExistByIndex( windowIndex ) )
			{
				window_t* window = GetWindowByIndex(windowIndex);
#if defined( _WIN32 ) || defined( _WIN64 )
				if (decorators & DECORATOR_BORDER)
				{
					window->currentWindowStyle &= ~WS_BORDER;
				}

				if (decorators & DECORATOR_TITLEBAR)
				{
					window->currentWindowStyle &= ~WS_MAXIMIZEBOX;
				}

				if (decorators & DECORATOR_ICON)
				{
					window->currentWindowStyle &= ~WS_ICONIC;
				}

				if (decorators & DECORATOR_CLOSEBUTTON)
				{
					window->currentWindowStyle &= ~WS_SYSMENU;
				}

				if (decorators & DECORATOR_MINIMIZEBUTTON)
				{
					window->currentWindowStyle &= ~WS_MINIMIZEBOX;
				}

				if (decorators & DECORATOR_MAXIMIZEBUTTON)
				{
					window->currentWindowStyle &= ~WS_MAXIMIZEBOX;
				}

				if (decorators & DECORATOR_SIZEABLEBORDER)
				{
					window->currentWindowStyle &= ~WS_SIZEBOX;
				}

				SetWindowLongPtr(window->windowHandle, GWL_STYLE,
					window->currentWindowStyle | WS_VISIBLE);
#elif defined(__linux__)
				if (decorators & DECORATOR_CLOSEBUTTON)
				{
					//I hate doing this but it is neccessary to keep functionality going.
					bool minimizeEnabled = 0;
				    bool maximizeEnabled = 0;

					if (decorators & DECORATOR_MAXIMIZEBUTTON)
					{
						maximizeEnabled = true;
					}

					if (decorators & DECORATOR_MINIMIZEBUTTON)
					{
						minimizeEnabled = true;
					}

					window->currentWindowStyle &= ~LINUX_DECORATOR_CLOSE;

					if (maximizeEnabled)
					{
						window->currentWindowStyle |= LINUX_DECORATOR_MAXIMIZE;
					}

					if (minimizeEnabled)
					{
						window->currentWindowStyle |= LINUX_DECORATOR_MINIMIZE;
					}

					window->decorators = 1;
				}

				if (decorators & DECORATOR_MINIMIZEBUTTON)
				{
					window->currentWindowStyle &= ~LINUX_DECORATOR_MINIMIZE;
					window->decorators = 1;
				}

				if (decorators & DECORATOR_MAXIMIZEBUTTON)
				{
					bool minimizeEnabled = false;

					if (decorators & DECORATOR_MINIMIZEBUTTON)
					{
						minimizeEnabled = true;
					}

					window->currentWindowStyle &= ~LINUX_DECORATOR_MAXIMIZE;

					if (minimizeEnabled)
					{
						window->currentWindowStyle |= LINUX_DECORATOR_MINIMIZE;
					}

					window->decorators = 1;
				}

				if (decorators & DECORATOR_ICON)
				{
					//Linux ( at least cinnamon ) does not have icons in the window. only in the taskb ar icon
				}

				//just need to set it to 1 to enable all decorators that include title bar 
				if (decorators & DECORATOR_TITLEBAR)
				{
					window->decorators = LINUX_DECORATOR_BORDER;
				}

				if (decorators & DECORATOR_BORDER)
				{
					window->decorators = 0;
				}

				if (decorators & DECORATOR_SIZEABLEBORDER)
				{
					window->decorators = 0;
				}

				long hints[5] = { LINUX_FUNCTION | LINUX_DECORATOR, window->currentWindowStyle, window->decorators, 0, 0 };

				XChangeProperty(instance->currentDisplay, window->windowHandle, window->AtomHints, XA_ATOM, 32,
					PropModeReplace, (unsigned char*)hints, 5);

				XMapWindow(instance->currentDisplay, window->windowHandle);
#endif
				return true;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window on key event callback by name
	*/
	static inline bool SetWindowOnKeyEventByName(const char* windowName, std::function<void(unsigned int, bool)> onKey)
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}

			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window on key event callback by index
	*/
	static inline bool SetWindowOnKeyEventByIndex(unsigned int windowIndex, std::function<void(unsigned int, bool)> onKey)
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window on mouse button event callback by name
	*/
	static inline bool SetWindowOnMouseButtonEventByName(const char* windowName, std::function<void(unsigned int, bool)> onMouseButton)
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window on mouse button event callback by index
	*/
	static inline bool SetWindowOnMouseButtonEventByIndex(unsigned int windowIndex, std::function<void(unsigned int, bool)> onMouseButton)
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window on mouse wheel event callback by name
	*/
	static inline bool SetWindowOnMouseWheelEventByName(const char* windowName, std::function<void(unsigned int)> onMouseWheel)
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window on mouse wheel event callback by index
	*/
	static inline bool SetWindowOnMouseWheelEventByIndex(unsigned int windowIndex, std::function<void(unsigned int)> onMouseWheel)
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window on destroyed event callback by name
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window on destroyed event callback by index
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window on maximized event callback by name
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window on maximized event callback by index
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window on minimized event callback by name
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window on minimized event callback by index
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window on focus event callback by name
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window on focus event callback by index
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window on moved event callback by name
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}

			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window on moved event callback by index
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window on resized event callback by name
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window on resized event callback by index
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

	/**
	* set the window on mouse move event callback by name
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}
	/**
	* set the window on mouse move event callback by index
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
				TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CALLBACK);
				return false;
			}
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_WINDOW_NOT_FOUND);
			return false;
		}
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_NOT_INITIALIZED );
		return false;
	}

private:

	struct window_t
	{
		const char*																			name;							/**< Name of the window */
		unsigned int				iD;								/**< ID of the Window. ( where it belongs in the window manager ) */
		int							colorBits;						/**< color format of the window. ( defaults to 32 bit color ) */
		int							depthBits;						/**< Size of the Depth buffer. ( defaults to 8 bit depth ) */
		int							stencilBits;					/**< Size of the stencil buffer, ( defaults to 8 bit ) */
		bool						keys[ KEY_LAST ];				/**< Record of keys that are either pressed or released in the respective window */
		bool						mouseButton[ MOUSE_LAST ];		/**< Record of mouse buttons that are either presses or released */
		unsigned int				resolution[ 2 ];				/**< Resolution/Size of the window stored in an array */
		unsigned int				position[ 2 ];					/**< Position of the Window relative to the screen co-ordinates */
		unsigned int				mousePosition[ 2 ];				/**< Position of the Mouse cursor relative to the window co-ordinates */
		bool						shouldClose;					/**< Whether the Window should be closing */
		bool						inFocus;						/**< Whether the Window is currently in focus( if it is the current window be used ) */

		bool						initialized;					/**< whether the window has been successfully initialized */
		bool						contextCreated;					/**< whether the OpenGL context has been successfully created */
		bool						isCurrentContext;				/**< whether the window is the current window being drawn to */

		unsigned int				currentState;					/**< The current state of the window. these states include Normal, Minimized, Maximized and Full screen */
		unsigned int				currentWindowStyle;				/**< the current style of the window */

		std::function<void(unsigned int, bool)>												keyEvent;					/**< this is the callback to be used when a key has been pressed */
		std::function<void(unsigned int, bool)>												mouseButtonEvent;			/**< this is the callback to be used when a mouse button has been pressed */
		std::function<void(unsigned int)>													mouseWheelEvent;			/**< this is the callback to be used when the mouse wheel has been scrolled. */
		std::function<void(void)>															destroyedEvent;				/**< this is the callback to be used when the window has been closed in a non-programmatic fashion */
		std::function<void(void)>															maximizedEvent;				/**< this is the callback to be used when the window has been maximized in a non-programmatic fashion */
		std::function<void(void)>															minimizedEvent;				/**< this is the callback to be used when the window has been minimized in a non-programmatic fashion */
		std::function<void(bool)>															focusEvent;					/**< this is the callback to be used when the window has been given focus in a non-programmatic fashion */
		std::function<void(unsigned int, unsigned int)>										movedEvent;					/**< this is the callback to be used the window has been moved in a non-programmatic fashion */
		std::function<void(unsigned int, unsigned int)>										resizeEvent;				/**< this is a callback to be used when the window has been resized in a non-programmatic fashion */
		std::function<void(unsigned int, unsigned int, unsigned int, unsigned int)>			mouseMoveEvent;				/**< this is a callback to be used when the mouse has been moved */

#if defined( _WIN32 ) || defined( _WIN64 )
			
		HDC							deviceContextHandle;
		HGLRC						glRenderingContextHandle;
		HPALETTE					paletteHandle;
		PIXELFORMATDESCRIPTOR		pixelFormatDescriptor;
		WNDCLASS					windowClass;
		HWND						windowHandle;
		HINSTANCE					instanceHandle;

#else
		Window						windowHandle;					/**< the X11 handle to the window. I wish they didn't name the type 'Window' */
		GLXContext					context;						/**< the handle to the GLX rendering context */
		XVisualInfo*				visualInfo;						/**< the handle to the Visual Information. similar purpose to PixelformatDesriptor */
		int*						attributes;						/**< attributes of the window. RGB, depth, stencil, etc */
		XSetWindowAttributes		setAttributes;					/**< the attributes to be set for the window */
		unsigned int				decorators;						/**< enabled window decorators */

		/*these atoms are needed to change window states via the extended window manager
		I might move them to window manager considering these are essentially constants	*/
		Atom						AtomState;						/**< atom for the state of the window */							// _NET_WM_STATE
		Atom						AtomHidden;						/**< atom for the current hidden state of the window */				// _NET_WM_STATE_HIDDEN
		Atom						AtomFullScreen;					/**< atom for the full screen state of the window */				// _NET_WM_STATE_FULLSCREEN
		Atom						AtomMaxHorz;					/**< atom for the maximized horizontally state of the window */		// _NET_WM_STATE_MAXIMIZED_HORZ
		Atom						AtomMaxVert;					/**< atom for the maximized vertically state of the window */		// _NET_WM_STATE_MAXIMIZED_VERT
		Atom						AtomClose;						/**< atom for closing the window */									// _NET_WM_CLOSE_WINDOW
		Atom						AtomActive;						/**< atom for the active window */									// _NET_ACTIVE_WINDOW
		Atom						AtomDemandsAttention;			/**< atom for when the window demands attention */					// _NET_WM_STATE_DEMANDS_ATTENTION
		Atom						AtomFocused;					/**< atom for the focused state of the window */					// _NET_WM_STATE_FOCUSED
		Atom						AtomCardinal;					/**< atom for cardinal coordinates */								// _NET_WM_CARDINAL
		Atom						AtomIcon;						/**< atom for the icon of the window */								// _NET_WM_ICON
		Atom						AtomHints;						/**< atom for the window decorations */								// _NET_WM_HINTS

		Atom						AtomWindowType;					/**< atom for the type of window */
		Atom						AtomWindowTypeDesktop;			/**< atom for the desktop window type */							//_NET_WM_WINDOW_TYPE_SPLASH
		Atom						AtomWindowTypeSplash;			/**< atom for the splash screen window type */
		Atom						AtomWindowTypeNormal;			/**< atom for the normal splash screen window type */

		Atom						AtomAllowedActions;				/**< atom for allowed window actions */
		Atom						AtomActionResize;				/**< atom for allowing the window to be resized */
		Atom						AtomActionMinimize;				/**< atom for allowing the window to be minimized */
		Atom						AtomActionShade;				/**< atom for allowing the window to be shaded */
		Atom						AtomActionMaximizeHorz;			/**< atom for allowing the window to be maximized horizontally */
		Atom						AtomActionMaximizeVert;			/**< atom for allowing the window to be maximized vertically */
		Atom						AtomActionClose;				/**< atom for allowing the window to be closed */

		Atom						AtomDesktopGeometry;			/**< atom for Desktop Geometry */
#endif

		window_t(const char* name = nullptr, unsigned int iD = 0,
			unsigned int colorBits = 0, unsigned int depthBits = 0, unsigned int stencilBits = 0,
			bool shouldClose = false, unsigned int currentState = WINDOWSTATE_NORMAL,
			std::function<void(unsigned int, bool)> keyEvent = nullptr,
			std::function<void(unsigned int, bool)> mouseButtonEvent = nullptr, std::function<void(unsigned int)> mouseWheelEvent = nullptr,
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
			currentWindowStyle = WINDOWSTYLE_DEFAULT;

#if defined( __linux )
			context = 0;
#endif 
		}
	};

	std::vector< window_t* >	windowList;
	static windowManager*		instance;

	unsigned int				screenResolution[ 2 ];
	unsigned int				screenMousePosition[ 2 ];

	bool						isInitialized;

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

	static inline void Platform_InitializeWindow( window_t* window )
	{
#if defined( _WIN32 ) || defined( _WIN64 )
		Windows_InitializeWindow( window );
#elif defined(__linux__)
		Linux_InitializeWindow( window );
#endif
	}

	static inline bool Platform_InitializeGL( window_t* window )
	{
#if defined( _WIN32 ) || defined( _WIN64 )
		window->deviceContextHandle = GetDC(window->windowHandle);
		InitializePixelFormat(window);
		window->glRenderingContextHandle = wglCreateContext(window->deviceContextHandle);
		wglMakeCurrent(window->deviceContextHandle, window->glRenderingContextHandle);

		window->contextCreated = (window->glRenderingContextHandle != nullptr);

		if (window->contextCreated)
		{
			return true;
		}

		TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_INVALID_CONTEXT);
		return false;
#elif defined(__linux__)
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
			TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_EXISTING_CONTEXT);
			return false;
		}
		return false;
#endif
	}

	static inline void ShutdownWindow( window_t* window )
	{
#if defined( _WIN32 ) || defined( _WIN64 )
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
#elif defined(__linux__)
		if (window->currentState == WINDOWSTATE_FULLSCREEN)
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
				for ( auto window : instance->windowList )
				{
					if( !strcmp( window->name, windowName ) )
					{
						return true;
					}
				}
			}
			TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_INVALID_WINDOW_NAME );
			return false;
		}
		TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_NOT_INITIALIZED);
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

			TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_INVALID_WINDOW_INDEX );
			return false;
		}

		TinyWindow_PrintErrorMessage(TINYWINDOW_ERROR_NOT_INITIALIZED);
		return false;
	}

	static inline window_t* GetWindowByName( const char* windowName )
	{
			for( auto window : instance->windowList )
			{
				if ( !strcmp( window->name, windowName ) )
				{
					return window;
				}
			}

			return nullptr;
	}

	//return a static pointer to a window that corresponds to the given window index
	static inline window_t* GetWindowByIndex( unsigned int windowIndex )
	{
		if ( windowIndex <= instance->windowList.size() - 1 )
		{
			return instance->windowList[windowIndex];
		}
		return nullptr;
	}
	
#if defined( _WIN32 ) || defined( _WIN64 )

	enum tinyWindowKeyLong_t
	{
		LEFT_CONTROL_DOWN_LONG = 29,
		RIGHT_CONTROL_DOWN_LONG = 285,
		LEFT_SHIFT_DOWN_LONG = 42,
		RIGHT_SHIFT_DOWN_LONG = 54,
		LEFT_ALT_DOWN_LONG = 8248,
		RIGHT_ALT_DOWN_LONG = 8504,

		LEFT_CONTROL_UP_LONG = 49181,
		RIGHT_CONTROL_UP_LONG = 49437,
		LEFT_SHIFT_UP_LONG = 49194,
		RIGHT_SHIFT_UP_LONG = 49206,
		LEFT_ALT_UP_LONG = 49208,
		RIGHT_ALT_UP_LONG = 49464,
	};

	MSG		message;
	HDC		deviceContextHandle;

	//the windwow procedure for all windows. This is used mainly to handle window events
	LRESULT CALLBACK WindowProcedure( HWND windowHandle, unsigned int message, WPARAM wordParam, LPARAM longParam )
	{
		window_t* window = GetWindowByHandle( windowHandle );
		switch ( message )
		{
		case WM_CREATE:
		{
			GetWindowByIndex( windowList.size() - 1 )->windowHandle = windowHandle;
			window = GetWindowByHandle( windowHandle );

			Platform_InitializeGL( window );
			break;
		}

		case WM_DESTROY:
		{
			window->shouldClose = true;

			if (window->destroyedEvent != nullptr )
			{
				window->destroyedEvent();
			}

			ShutdownWindow( window );
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
			case LEFT_CONTROL_DOWN_LONG:
			{
				window->keys[ KEY_LEFTCONTROL ] = KEYSTATE_DOWN;
				translatedKey = KEY_LEFTCONTROL;
				break;
			}

			case RIGHT_CONTROL_DOWN_LONG:
			{
				window->keys[ KEY_RIGHTCONTROL ] = KEYSTATE_DOWN;
				translatedKey = KEY_RIGHTCONTROL;
				break;
			}

			case LEFT_SHIFT_DOWN_LONG:
			{
				window->keys[ KEY_LEFTSHIFT ] = KEYSTATE_DOWN;
				translatedKey = KEY_LEFTSHIFT;
				break;
			}

			case RIGHT_SHIFT_DOWN_LONG:
			{
				window->keys[ KEY_RIGHTSHIFT ] = KEYSTATE_DOWN;
				translatedKey = KEY_RIGHTSHIFT;
				break;
			}

			default:
			{
				translatedKey = Windows_TranslateKey( wordParam );
				window->keys[ translatedKey ] = KEYSTATE_DOWN;
				break;
			}
			}

			if ( window->keyEvent != nullptr )
			{
				window->keyEvent( translatedKey, KEYSTATE_DOWN );
			}
			break;
		}

		case WM_KEYUP:
		{
			unsigned int translatedKey = 0;

			switch ( HIWORD( longParam ) )
			{
			case LEFT_CONTROL_UP_LONG:
			{
				window->keys[ KEY_LEFTCONTROL ] = KEYSTATE_UP;
				translatedKey = KEY_LEFTCONTROL;
				break;
			}

			case RIGHT_CONTROL_UP_LONG:
			{
				window->keys[ KEY_RIGHTCONTROL ] = KEYSTATE_UP;
				translatedKey = KEY_RIGHTCONTROL;
				break;
			}

			case LEFT_SHIFT_UP_LONG:
			{
				window->keys[ KEY_LEFTSHIFT ] = KEYSTATE_UP;
				translatedKey = KEY_LEFTSHIFT;
				break;
			}

			case RIGHT_SHIFT_UP_LONG:
			{
				window->keys[ KEY_RIGHTSHIFT ] = KEYSTATE_UP;
				translatedKey = KEY_RIGHTSHIFT;
				break;
			}

			default:
			{
				translatedKey = Windows_TranslateKey( wordParam );
				window->keys[ translatedKey ] = KEYSTATE_UP;
				break;
			}
			}

			if (window->keyEvent != nullptr )
			{
				window->keyEvent( translatedKey, KEYSTATE_UP );
			}
			break;
		}

		case WM_SYSKEYDOWN:
		{
			unsigned int translatedKey = 0;
			switch ( HIWORD( longParam ) )
			{
			case LEFT_ALT_DOWN_LONG:
			{
				window->keys[ KEY_LEFTALT ] = KEYSTATE_DOWN;
				translatedKey = KEY_LEFTALT;
				break;
			}


			case RIGHT_ALT_DOWN_LONG:
			{
				window->keys[ KEY_RIGHTALT ] = KEYSTATE_DOWN;
				translatedKey = KEY_RIGHTALT;
			}

			default:
			{
				break;
			}
			}

			if ( window->keyEvent != nullptr )
			{
				window->keyEvent( translatedKey, KEYSTATE_DOWN );
			}

			break;
		}

		case WM_SYSKEYUP:
		{
			unsigned int translatedKey = 0;
			switch ( HIWORD( longParam ) )
			{
			case LEFT_ALT_UP_LONG:
			{
				window->keys[ KEY_LEFTALT ] = KEYSTATE_UP;
				translatedKey = KEY_LEFTALT;
				break;
			}


			case RIGHT_ALT_UP_LONG:
			{
				window->keys[ KEY_RIGHTALT ] = KEYSTATE_UP;
				translatedKey = KEY_RIGHTALT;
				break;
			}

			default:
			{
				break;
			}
			}

			if ( window->keyEvent != nullptr )
			{
				window->keyEvent( translatedKey, KEYSTATE_UP );
			}
			break;
		}

		case WM_MOUSEMOVE:
		{
			window->mousePosition[ 0 ] = ( unsigned int )LOWORD( longParam );
			window->mousePosition[ 1 ] = ( unsigned int )HIWORD( longParam );

			POINT point;
			point.x = window->mousePosition[ 0 ];
			point.y = window->mousePosition[ 1 ];

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
			window->mouseButton[ MOUSE_LEFTBUTTON ] = MOUSE_BUTTONDOWN;

			if ( window->mouseButtonEvent != nullptr )
			{
				window->mouseButtonEvent( MOUSE_LEFTBUTTON, MOUSE_BUTTONDOWN );
			}
			break;
		}

		case WM_LBUTTONUP:
		{
			window->mouseButton[ MOUSE_LEFTBUTTON ] = MOUSE_BUTTONUP;

			if ( window->mouseButtonEvent != nullptr )
			{
				window->mouseButtonEvent( MOUSE_LEFTBUTTON, MOUSE_BUTTONUP );
			}
			break;
		}

		case WM_RBUTTONDOWN:
		{
			window->mouseButton[ MOUSE_RIGHTBUTTON ] = MOUSE_BUTTONDOWN;

			if ( window->mouseButtonEvent != nullptr )
			{
				window->mouseButtonEvent( MOUSE_RIGHTBUTTON, MOUSE_BUTTONDOWN );
			}
			break;
		}

		case WM_RBUTTONUP:
		{
			window->mouseButton[ MOUSE_RIGHTBUTTON ] = MOUSE_BUTTONUP;

			if ( window->mouseButtonEvent != nullptr )
			{
				window->mouseButtonEvent( MOUSE_RIGHTBUTTON, MOUSE_BUTTONUP );
			}
			break;
		}

		case WM_MBUTTONDOWN:
		{
			window->mouseButton[ MOUSE_MIDDLEBUTTON ] = MOUSE_BUTTONDOWN;

			if ( window->mouseButtonEvent != nullptr )
			{
				window->mouseButtonEvent( MOUSE_MIDDLEBUTTON, MOUSE_BUTTONDOWN );
			}
			break;
		}

		case WM_MBUTTONUP:
		{
			window->mouseButton[ MOUSE_MIDDLEBUTTON ] = MOUSE_BUTTONUP;

			if ( window->mouseButtonEvent != nullptr )
			{
				window->mouseButtonEvent( MOUSE_MIDDLEBUTTON, MOUSE_BUTTONUP );
			}
			break;
		}

		case WM_MOUSEWHEEL:
		{
			if ( ( wordParam % WHEEL_DELTA ) > 0 )
			{
				if ( window->mouseWheelEvent != nullptr )
				{
					window->mouseWheelEvent( MOUSE_SCROLL_DOWN );
				}
			}

			else
			{
				if ( window->mouseWheelEvent != nullptr )
				{
					window->mouseWheelEvent( MOUSE_SCROLL_UP );
				}

			}
			break;
		}

		default:
		{
			return DefWindowProc( windowHandle, message, wordParam, longParam );
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
	static inline window_t* GetWindowByHandle( HWND windowHandle )
	{
		for ( unsigned int iter = 0; iter < instance->windowList.size(); iter++ )
		{
			if ( instance->windowList[iter]->windowHandle == windowHandle )
			{
				return instance->windowList[iter];
			}
		}

		return nullptr;
	}

	//initialize the given window using Win32
	static inline void Windows_InitializeWindow( window_t* window,
		UINT style = CS_OWNDC | CS_HREDRAW | CS_DROPSHADOW,
		int clearScreenExtra = 0,
		int windowExtra = 0,
		HINSTANCE instance = GetModuleHandle( 0 ),
		HICON icon = LoadIcon( 0, IDI_APPLICATION ),
		HCURSOR cursor = LoadCursor( 0, IDC_ARROW ),
		HBRUSH brush = ( HBRUSH )BLACK_BRUSH )
	{
		window->instanceHandle = instance;
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
	static inline void InitializePixelFormat( window_t* window )
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
				return wordParam;
			}
		}
	}

	static inline void Windows_SetWindowIcon( window_t* window, const char* icon, unsigned int width, unsigned int height )
	{
		SendMessage(window->windowHandle, (UINT)WM_SETICON, ICON_BIG, 
			(LPARAM)LoadImage(window->instanceHandle, icon, IMAGE_ICON, width, height, LR_LOADFROMFILE));
	}

#elif defined(__linux__)

	enum tinyWindowLinuxDecorator_t
	{
		LINUX_DECORATOR_BORDER = 1L << 1,
		LINUX_DECORATOR_MOVE = 1L << 2,
		LINUX_DECORATOR_MINIMIZE = 1L << 3,
		LINUX_DECORATOR_MAXIMIZE = 1L << 4,
		LINUX_DECORATOR_CLOSE = 1L << 5,
	};

	Display*			currentDisplay;
	XEvent				currentEvent;
	
	static window_t* GetWindowByHandle( Window windowHandle )
	{
		for( auto iter : GetInstance()->windowList )
		{
			if ( iter->windowHandle == windowHandle )
			{
				return iter;
			}
		}
		return nullptr;	
	}

	static window_t* GetWindowByEvent( XEvent currentEvent )
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
				return nullptr;
			}
		}
	}

	static void InitializeAtoms( window_t* window )
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

	static void Linux_InitializeWindow( window_t* window )
	{
		window->attributes = new int[ 5 ]{
			GLX_RGBA,
			GLX_DOUBLEBUFFER, 
			GLX_DEPTH_SIZE, 
			window->depthBits, 
			None};

		window->decorators = 1;
		window->currentWindowStyle |= LINUX_DECORATOR_CLOSE | LINUX_DECORATOR_MAXIMIZE | LINUX_DECORATOR_MINIMIZE | LINUX_DECORATOR_MOVE;

		if ( !instance->currentDisplay )
		{
			TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_LINUX_CANNOT_CONNECT_X_SERVER );
			exit( 0 );
		}

		//window->VisualInfo = glXGetVisualFromFBConfig( GetDisplay(), GetBestFrameBufferConfig( window ) ); 

		window->visualInfo = glXChooseVisual( instance->currentDisplay, 0, window->attributes );

		if ( !window->visualInfo )
		{
			TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_LINUX_INVALID_VISUALINFO );
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
			TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_LINUX_CANNOT_CREATE_WINDOW );
			exit( 0 );
		}

		XMapWindow( instance->currentDisplay, window->windowHandle );
		XStoreName( instance->currentDisplay, window->windowHandle,
			window->name );

		InitializeAtoms( window );

		XSetWMProtocols( instance->currentDisplay, window->windowHandle, &window->AtomClose, true );	

		Platform_InitializeGL( window );
	}

	static void Linux_ShutdownWindow( window_t* window )
	{
		XDestroyWindow(instance->currentDisplay, window->windowHandle);	
	}

	static void Linux_Shutdown( void )
	{
		XCloseDisplay( instance->currentDisplay );
	}

	static void Linux_ProcessEvents( XEvent currentEvent )
	{
		window_t* window = GetWindowByEvent( currentEvent );

		switch ( currentEvent.type )	
		{
			case Expose:
			{
				break;
			}

			case DestroyNotify:
			{
				//	printf( "blarg" );

				if ( window->destroyedEvent != nullptr )
				{
					window->destroyedEvent();

				}
#if defined(DEBUG)
				printf( "Window was destroyed\n" );
#endif
				ShutdownWindow( window );

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
					window->keys[ functionKeysym ] = KEYSTATE_DOWN;
					if ( window->keyEvent != nullptr )
					{
						window->keyEvent( functionKeysym, KEYSTATE_DOWN );
					}
				}

				else
				{
					window->keys[ Linux_TranslateKey( functionKeysym ) ] = KEYSTATE_DOWN;

					if ( window->keyEvent != nullptr )
					{
						window->keyEvent( Linux_TranslateKey( functionKeysym ), KEYSTATE_DOWN );
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
						window->keyEvent( Linux_TranslateKey( functionKeysym ), KEYSTATE_DOWN );
						isRetriggered = true;
					}
				}

				if ( !isRetriggered )
				{
					unsigned int functionKeysym = XkbKeycodeToKeysym( 
					instance->currentDisplay, currentEvent.xkey.keycode, 0, currentEvent.xkey.state & ShiftMask ? 1 : 0 );

					if ( functionKeysym <= 255 )
					{
						window->keys[ functionKeysym ] = KEYSTATE_UP;

						if ( window->keyEvent != nullptr )
						{
							window->keyEvent( functionKeysym, KEYSTATE_UP );
						}
					}

					else
					{
						window->keys[ Linux_TranslateKey( functionKeysym ) ] = KEYSTATE_UP;

						if ( window->keyEvent != nullptr )
						{
							window->keyEvent( Linux_TranslateKey( functionKeysym ), KEYSTATE_UP );
						}
					}

					if ( window->keyEvent != nullptr )
					{
						window->keyEvent( Linux_TranslateKey( functionKeysym ), KEYSTATE_UP );
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
					window->mouseButton[ MOUSE_LEFTBUTTON ] = MOUSE_BUTTONDOWN;

					if ( window->mouseButtonEvent != nullptr )
					{
						window->mouseButtonEvent( MOUSE_LEFTBUTTON, MOUSE_BUTTONDOWN );
					}
					break;
				}

				case 2:
				{
					window->mouseButton[ MOUSE_MIDDLEBUTTON ] = MOUSE_BUTTONDOWN;

					if ( window->mouseButtonEvent != nullptr )
					{
						window->mouseButtonEvent( MOUSE_MIDDLEBUTTON, MOUSE_BUTTONDOWN );
					}
					break;
				}

				case 3:
				{
					window->mouseButton[ MOUSE_RIGHTBUTTON ] = MOUSE_BUTTONDOWN;

					if ( window->mouseButtonEvent != nullptr )
					{
						window->mouseButtonEvent( MOUSE_RIGHTBUTTON, MOUSE_BUTTONDOWN );
					}
					break;
				}

				case 4:
				{
					window->mouseButton[ MOUSE_SCROLL_UP ] = MOUSE_BUTTONDOWN;

					if ( window->mouseWheelEvent != nullptr )
					{
						window->mouseWheelEvent( MOUSE_SCROLL_DOWN );
					}
					break;
				}

				case 5:
				{
					window->mouseButton[ MOUSE_SCROLL_DOWN ] = MOUSE_BUTTONDOWN;

					if ( window->mouseWheelEvent != nullptr )
					{
						window->mouseWheelEvent( MOUSE_SCROLL_DOWN );
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
					window->mouseButton[ MOUSE_LEFTBUTTON ] = MOUSE_BUTTONUP;

					if ( window->mouseButtonEvent != nullptr )
					{
						window->mouseButtonEvent( MOUSE_LEFTBUTTON, MOUSE_BUTTONUP );
					}
					break;
				}

				case 2:
				{
					//the middle mouse button was released
					window->mouseButton[ MOUSE_MIDDLEBUTTON ] = MOUSE_BUTTONUP;

					if ( window->mouseButtonEvent != nullptr )
					{
						window->mouseButtonEvent( MOUSE_MIDDLEBUTTON, MOUSE_BUTTONUP );
					}
					break;
				}

				case 3:
				{
					//the right mouse button was released
					window->mouseButton[ MOUSE_RIGHTBUTTON ] = MOUSE_BUTTONUP;

					if ( window->mouseButtonEvent != nullptr )
					{
						window->mouseButtonEvent( MOUSE_RIGHTBUTTON, MOUSE_BUTTONUP );
					}
					break;
				}

				case 4:
				{
					//the mouse wheel was scrolled up
					window->mouseButton[ MOUSE_SCROLL_UP ] = MOUSE_BUTTONDOWN;
					break;
				}

				case 5:
				{
					//the mouse wheel was scrolled down
					window->mouseButton[ MOUSE_SCROLL_DOWN ] = MOUSE_BUTTONDOWN;
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
					ShutdownWindow( window );

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

	static void Linux_SetWindowIcon( void ) /*window_t* window, const char* icon, unsigned int width, unsigned int height */
	{
		//sorry :( 
		TinyWindow_PrintErrorMessage( TINYWINDOW_ERROR_LINUX_FUNCTION_NOT_IMPLEMENTED );
	}

	static GLXFBConfig GetBestFrameBufferConfig( window_t* givenWindow )
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

#endif

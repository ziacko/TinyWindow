//created by Ziyad Barakat 2014 - 2016

#ifndef TINYWINDOW_H
#define TINYWINDOW_H

#if defined(_WIN32) || defined(_WIN64)
#define TW_WINDOWS
#if defined(_MSC_VER)
//this automatically loads the OpenGL library if you are using Visual studio. feel free to comment out
#pragma comment (lib, "opengl32.lib")
//for gamepad support
#pragma comment (lib, "winmm.lib")
//this makes sure that the entry point of your program is main() not Winmain(). feel free to comment out
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif //_MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif //WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX 1
#endif //NOMINMAX

#include <Windows.h>
#if !defined(TW_USE_VULKAN)
#include <gl/GL.h>
#else
#include <vulkan.h>
#endif
#include <io.h>
#include <fcntl.h>
#include <mmsystem.h>
#endif	//_WIN32 || _WIN64

#if defined(__linux__)
#define TW_LINUX
#if !defined(TW_USE_VULKAN)
#include <GL/glx.h>
#else
#include <vulkan.h>
#endif
#include <X11/X.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/XKBlib.h>
#endif //__linux__

#include <assert.h>
#include <stdint.h>
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

	template<typename type>
	struct vec2_t
	{
		vec2_t()
		{
			this->x = 0;
			this->y = 0;
		}

		vec2_t(type x, type y)
		{
			this->x = x;
			this->y = y;
		}

		union
		{
			type x;
			type width;
		};

		union
		{
			type y;
			type height;
		};

		static vec2_t Zero()
		{
			return vec2_t<type>(0, 0);
		}
	};

	enum class keyState_t
	{
		bad,									/**< If get key state fails (could not name it ERROR) */
		up,										/**< The key is currently up */
		down,									/**< The key is currently down */
	};

	enum class key_t
	{
		bad = -1,								/**< The key pressed is considered invalid */
		first = 256 + 1,						/**< The first key that is not a char */
		F1, 									/**< The F1 key */
		F2,										/**< The F2 key */
		F3,										/**< The F3 key */
		F4,										/**< The F4 key */
		F5,										/**< The F5 key */
		F6,										/**< The F6 key */
		F7,										/**< The F7 key */
		F8,										/**< The F8 key */
		F9,										/**< The F9 key */
		F10,									/**< The F10 key */
		F11,									/**< The F11 key */
		F12,									/**< The F12 key */
		capsLock,								/**< The CapsLock key */
		leftShift,								/**< The left Shift key */
		rightShift,								/**< The right Shift key */
		leftControl,							/**< The left Control key */
		rightControl,							/**< The right Control key */
		leftWindow,								/**< The left Window key */
		rightWindow,							/**< The right Window key */
		leftAlt,								/**< The left Alternate key */
		rightAlt,								/**< The right Alternate key */
		enter,									/**< The Enter/Return key */
		printScreen,							/**< The PrintScreen key */
		scrollLock,								/**< The ScrollLock key */
		numLock,								/**< The NumLock key */
		pause,									/**< The pause/break key */
		insert,									/**< The insert key */
		home,									/**< The Home key */
		end,									/**< The End key */
		pageUp,									/**< The PageUp key */
		pageDown,								/**< The PageDown key */
		arrowDown,								/**< The ArrowDown key */
		arrowUp,								/**< The ArrowUp key */
		arrowLeft,								/**< The ArrowLeft key */
		arrowRight,								/**< The ArrowRight key */
		keypadDivide,							/**< The KeyPad Divide key */
		keypadMultiply,							/**< The Keypad Multiply key */
		keypadSubtract,							/**< The Keypad Subtract key */
		keypadAdd,								/**< The Keypad Add key */
		keypadEnter,							/**< The Keypad Enter key */
		keypadPeriod,							/**< The Keypad Period/Decimal key */
		keypad0,								/**< The Keypad 0 key */
		keypad1,								/**< The Keypad 1 key */
		keypad2,								/**< The Keypad 2 key */
		keypad3,								/**< The Keypad 3 key */
		keypad4,								/**< The Keypad 4 key */
		keypad5,								/**< The Keypad 5 key */
		keypad6,								/**< The Keypad 6 key */
		keypad7,								/**< The Keypad 7 key */
		keypad8,								/**< The keypad 8 key */
		keypad9,								/**< The Keypad 9 key */
		backspace,								/**< The Backspace key */
		tab,									/**< The Tab key */
		del,									/**< The Delete key */
		spacebar,								/**< The Spacebar key */
		escape,									/**< The Escape key */
		last = escape,							/**< The last key to be supported */
	};

	enum class buttonState_t
	{
		up,										/**< The mouse button is currently up */
		down									/**< The mouse button is currently down */
	};

	enum class mouseButton_t
	{
		left,									/**< The left mouse button */
		right,									/**< The right mouse button */
		middle,									/**< The middle mouse button / ScrollWheel */
		last,									/**< The last mouse button to be supported */
	};

	enum class mouseScroll_t
	{
		down,									/**< The mouse wheel up */
		up										/**< The mouse wheel down */
	};

	enum class state_t
	{
		normal,									/**< The window is in its default state */
		maximized,								/**< The window is currently maximized */
		minimized,								/**< The window is currently minimized */
		fullscreen,								/**< The window is currently full screen */
	};

	enum decorator_t
	{
		titleBar =			1L << 1,			/**< The title bar decoration of the window */
		icon =				1L << 2,			/**< The icon decoration of the window */
		border =			1L << 3,			/**< The border decoration of the window */
		minimizeButton =	1L << 4,			/**< The minimize button decoration of the window */
		maximizeButton =	1L << 5,			/**< The maximize button decoration pf the window */
		closeButton =		1L << 6,			/**< The close button decoration of the window */
		sizeableBorder =	1L << 7,			/**< The sizable border decoration of the window */
	};

	enum class style_t
	{
		bare,									/**< The window has no decorators but the window border and title bar */
		normal,									/**< The default window style for the respective platform */
		popup,									/**< The window has no decorators */
	};

	enum class error_t
	{
		success,								/**< If a function call was successful*/
		invalidWindowName,						/**< If an invalid window name was given */
		invalidIconPath,						/**< If an invalid icon path was given */
		invalidWindowIndex,						/**< If an invalid window index was given */
		invalidWindowState,						/**< If an invalid window state was given */
		invalidResolution,						/**< If an invalid window resolution was given */
		invalidContext,							/**< If the OpenGL context for the window is invalid */
		existingContext,						/**< If the window already has an OpenGL context */
		notInitialized,							/**< If the window is being used without being initialized */
		alreadyInitialized,						/**< If the window was already initialized */
		invalidTitlebar,						/**< If the Title-bar text given was invalid */
		invalidCallback,						/**< If the given event callback was invalid */
		windowInvalid,							/**< If the window given was invalid */
		invalidWindowStyle,						/**< If the window style gives is invalid */
		functionNotImplemented,					/**< If the function has not yet been implemented in the current version of the API */
		linuxCannotConnectXServer,				/**< Linux: if cannot connect to an X11 server */
		linuxInvalidVisualinfo,					/**< Linux: if visual information given was invalid */
		linuxCannotCreateWindow,				/**< Linux: when X11 fails to create a new window */
		linuxFunctionNotImplemented,			/**< Linux: when the function has not yet been implemented on the Linux in the current version of the API */
		windowsCannotCreateWindows,				/**< Windows: when Win32 cannot create a window */
		windowsCannotInitialize,				/**< Windows: when Win32 cannot initialize */
		windowsFunctionNotImplemented,			/**< Windows: when a function has yet to be implemented on the Windows platform in the current version of the API */
	};

	typedef std::function<void(key_t key, keyState_t keyState)>											keyEvent_t;
	typedef std::function<void(mouseButton_t mouseButton, buttonState_t buttonState)>					mouseButtonEvent_t;
	typedef std::function<void(mouseScroll_t mouseScrollDirection)>										mouseWheelEvent_t;
	typedef std::function<void()>																		destroyedEvent_t;
	typedef std::function<void()>																		maximizedEvent_t;
	typedef std::function<void()>																		minimizedEvent_t;
	typedef std::function<void(bool isFocused)>															focusEvent_t;
	typedef std::function<void(vec2_t<int> windowPosition)>												movedEvent_t;
	typedef std::function<void(vec2_t<unsigned int> windowResolution)>									resizeEvent_t;
	typedef std::function<void(vec2_t<int> windowMousePosition, vec2_t<int> screenMousePosition)>		mouseMoveEvent_t;

	class errorCategory_t : public std::error_category
	{
	public:

		const char* name() const throw() override
		{
			return "tinyWindow";
		}

		/**
		* return the error message associated with the given error number
		*/
		virtual std::string message(int errorValue) const override
		{
			error_t err = (error_t)errorValue;
			switch (err)
			{
				case error_t::invalidWindowName:
				{
					return "Error: invalid window name \n";
				}

				case error_t::invalidIconPath:
				{
					return "Error: invalid icon path \n";
				}

				case error_t::invalidWindowIndex:
				{
					return "Error: invalid window index \n";
				}

				case error_t::invalidWindowState:
				{
					return "Error: invalid window state \n";
				}

				case error_t::invalidResolution:
				{
					return "Error: invalid resolution \n";
				}

				case error_t::invalidContext:
				{
					return "Error: Failed to create OpenGL context \n";
				}

				case error_t::existingContext:
				{
					return "Error: context already created \n";
				}

				case error_t::notInitialized:
				{
					return "Error: Window manager not initialized \n";
				}

				case error_t::alreadyInitialized:
				{
					return "Error: window has already been initialized \n";
				}

				case error_t::invalidTitlebar:
				{
					return "Error: invalid title bar name (cannot be null or nullptr) \n";
				}

				case error_t::invalidCallback:
				{
					return "Error: invalid event callback given \n";
				}

				case error_t::windowInvalid:
				{
					return "Error: window was not found \n";
				}

				case error_t::invalidWindowStyle:
				{
					return "Error: invalid window style given \n";
				}

				case error_t::functionNotImplemented:
				{
					return "Error: I'm sorry but this function has not been implemented yet :(\n";
				}

				case error_t::linuxCannotConnectXServer:
				{
					return "Error: cannot connect to X server \n";
				}

				case error_t::linuxInvalidVisualinfo:
				{
					return "Error: Invalid visual information given \n";
				}

				case error_t::linuxCannotCreateWindow:
				{
					return "Error: failed to create window \n";
				}

				case error_t::linuxFunctionNotImplemented:
				{
					return "Error: function not implemented on Linux platform yet. sorry :(\n";
				}

				case error_t::windowsCannotCreateWindows:
				{
					return "Error: failed to create window \n";
				}

				case error_t::windowsFunctionNotImplemented:
				{
					return "Error: function not implemented on Windows platform yet. sorry ;(\n";
				}

				case error_t::success:
				{
					return "function call was successful \n";
				}

				default:
				{
					return "Error: unspecified Error \n";
				}
			}
		}

		errorCategory_t() {};

		const static errorCategory_t& get()
		{
			const static errorCategory_t category;
			return category;
		}
	};

	inline std::error_code make_error_code(error_t errorCode)
	{
		return std::error_code(static_cast<int>(errorCode), errorCategory_t::get());
	}
};

//ugh I hate this hack
namespace std
{
	template<> struct is_error_code_enum<TinyWindow::error_t> : std::true_type {};
};

namespace TinyWindow
{
	class tWindow
	{
		friend class windowManager;

	public:

		windowManager&							manager;
		const char*								name;													/**< Name of the window */
		int										colorBits;												/**< Color format of the window. (defaults to 32 bit color) */
		int										depthBits;												/**< Size of the Depth buffer. (defaults to 8 bit depth) */
		int										stencilBits;											/**< Size of the stencil buffer, (defaults to 8 bit) */
		keyState_t								keys[(unsigned int)key_t::last];						/**< Record of keys that are either pressed or released in the respective window */
		buttonState_t							mouseButton[(unsigned int)mouseButton_t::last];			/**< Record of mouse buttons that are either presses or released */
		TinyWindow::vec2_t<unsigned int>		resolution;												/**< Resolution/Size of the window stored in an array */
		TinyWindow::vec2_t<int>					position;												/**< Position of the Window relative to the screen co-ordinates */
		TinyWindow::vec2_t<int>					mousePosition;											/**< Position of the Mouse cursor relative to the window co-ordinates */
		bool									shouldClose;											/**< Whether the Window should be closing */
		bool									inFocus;												/**< Whether the Window is currently in focus(if it is the current window be used) */
		bool									initialized;											/**< Whether the window has been successfully initialized */
		bool									contextCreated;											/**< Whether the OpenGL context has been successfully created */
		bool									isCurrentContext;										/**< Whether the window is the current window being drawn to */
		state_t									currentState;											/**< The current state of the window. these states include Normal, Minimized, Maximized and Full screen */
		unsigned int							currentStyle;											/**< The current style of the window */

		keyEvent_t								keyEvent;												/**< This is the callback to be used when a key has been pressed */
		mouseButtonEvent_t						mouseButtonEvent;										/**< This is the callback to be used when a mouse button has been pressed */
		mouseWheelEvent_t						mouseWheelEvent;										/**< This is the callback to be used when the mouse wheel has been scrolled. */
		destroyedEvent_t						destroyedEvent;											/**< This is the callback to be used when the window has been closed in a non-programmatic fashion */
		maximizedEvent_t						maximizedEvent;											/**< This is the callback to be used when the window has been maximized in a non-programmatic fashion */
		minimizedEvent_t						minimizedEvent;											/**< This is the callback to be used when the window has been minimized in a non-programmatic fashion */
		focusEvent_t							focusEvent;												/**< This is the callback to be used when the window has been given focus in a non-programmatic fashion */
		movedEvent_t							movedEvent;												/**< This is the callback to be used the window has been moved in a non-programmatic fashion */
		resizeEvent_t							resizeEvent;											/**< This is a callback to be used when the window has been resized in a non-programmatic fashion */
		mouseMoveEvent_t						mouseMoveEvent;											/**< This is a callback to be used when the mouse has been moved */

	private:

#if defined(TW_USE_VULKAN)
		VkInstance								vulkanInstanceHandle;
		VkSurfaceKHR							vulkanSurfaceHandle;
#endif

#if defined(TW_WINDOWS)

		HDC								deviceContextHandle;									/**< A handle to a device context */
		HGLRC							glRenderingContextHandle;								/**< A handle to an OpenGL rendering context*/
		HPALETTE						paletteHandle;											/**< A handle to a Win32 palette*/
		PIXELFORMATDESCRIPTOR			pixelFormatDescriptor;									/**< Describes the pixel format of a drawing surface*/
		WNDCLASS						windowClass;											/**< Contains the window class attributes */
		HWND							windowHandle;											/**< A handle to A window */
		HINSTANCE						instanceHandle;											/**< A handle to the window class instance */
		int								accumWheelDelta;										/**< holds the accumulated mouse wheel delta for this window */

#elif defined(TW_LINUX)

		Window							windowHandle;											/**< The X11 handle to the window. I wish they didn't name the type 'Window' */
		GLXContext						context;												/**< The handle to the GLX rendering context */
		XVisualInfo*					visualInfo;												/**< The handle to the Visual Information. similar purpose to PixelformatDesriptor */
		int*							attributes;												/**< Attributes of the window. RGB, depth, stencil, etc */
		XSetWindowAttributes			setAttributes;											/**< The attributes to be set for the window */
		unsigned int					linuxDecorators;										/**< Enabled window decorators */
		Display*						currentDisplay;											/**< Handle to the X11 window */

																		/* these atoms are needed to change window states via the extended window manager*/
		Atom							AtomState;						/**< Atom for the state of the window */							// _NET_WM_STATE
		Atom							AtomHidden;						/**< Atom for the current hidden state of the window */				// _NET_WM_STATE_HIDDEN
		Atom							AtomFullScreen;					/**< Atom for the full screen state of the window */				// _NET_WM_STATE_FULLSCREEN
		Atom							AtomMaxHorz;					/**< Atom for the maximized horizontally state of the window */		// _NET_WM_STATE_MAXIMIZED_HORZ
		Atom							AtomMaxVert;					/**< Atom for the maximized vertically state of the window */		// _NET_WM_STATE_MAXIMIZED_VERT
		Atom							AtomClose;						/**< Atom for closing the window */									// _NET_WM_CLOSE_WINDOW
		Atom							AtomActive;						/**< Atom for the active window */									// _NET_ACTIVE_WINDOW
		Atom							AtomDemandsAttention;			/**< Atom for when the window demands attention */					// _NET_WM_STATE_DEMANDS_ATTENTION
		Atom							AtomFocused;					/**< Atom for the focused state of the window */					// _NET_WM_STATE_FOCUSED
		Atom							AtomCardinal;					/**< Atom for cardinal coordinates */								// _NET_WM_CARDINAL
		Atom							AtomIcon;						/**< Atom for the icon of the window */								// _NET_WM_ICON
		Atom							AtomHints;						/**< Atom for the window decorations */								// _NET_WM_HINTS

		Atom							AtomWindowType;					/**< Atom for the type of window */
		Atom							AtomWindowTypeDesktop;			/**< Atom for the desktop window type */							//_NET_WM_WINDOW_TYPE_SPLASH
		Atom							AtomWindowTypeSplash;			/**< Atom for the splash screen window type */
		Atom							AtomWindowTypeNormal;			/**< Atom for the normal splash screen window type */

		Atom							AtomAllowedActions;				/**< Atom for allowed window actions */
		Atom							AtomActionResize;				/**< Atom for allowing the window to be resized */
		Atom							AtomActionMinimize;				/**< Atom for allowing the window to be minimized */
		Atom							AtomActionShade;				/**< Atom for allowing the window to be shaded */
		Atom							AtomActionMaximizeHorz;			/**< Atom for allowing the window to be maximized horizontally */
		Atom							AtomActionMaximizeVert;			/**< Atom for allowing the window to be maximized vertically */
		Atom							AtomActionClose;				/**< Atom for allowing the window to be closed */

		Atom							AtomDesktopGeometry;			/**< Atom for Desktop Geometry */

		enum decorator_t
		{
			linuxBorder = 1L << 1,
			linuxMove = 1L << 2,
			linuxMinimize = 1L << 3,
			linuxMaximize = 1L << 4,
			linuxClose = 1L << 5,
		};

		enum hint_t
		{
			function = 1,
			decorator,
		};

		void InitializeAtoms()
		{
			AtomState = XInternAtom(currentDisplay, "_NET_WM_STATE", false);
			AtomFullScreen = XInternAtom(currentDisplay, "_NET_WM_STATE_FULLSCREEN", false);
			AtomMaxHorz = XInternAtom(currentDisplay, "_NET_WM_STATE_MAXIMIZED_HORZ", false);
			AtomMaxVert = XInternAtom(currentDisplay, "_NET_WM_STATE_MAXIMIZED_VERT", false);
			AtomClose = XInternAtom(currentDisplay, "WM_DELETE_WINDOW", false);
			AtomHidden = XInternAtom(currentDisplay, "_NET_WM_STATE_HIDDEN", false);
			AtomActive = XInternAtom(currentDisplay, "_NET_ACTIVE_WINDOW", false);
			AtomDemandsAttention = XInternAtom(currentDisplay, "_NET_WM_STATE_DEMANDS_ATTENTION", false);
			AtomFocused = XInternAtom(currentDisplay, "_NET_WM_STATE_FOCUSED", false);
			AtomCardinal = XInternAtom(currentDisplay, "CARDINAL", false);
			AtomIcon = XInternAtom(currentDisplay, "_NET_WM_ICON", false);
			AtomHints = XInternAtom(currentDisplay, "_MOTIF_WM_HINTS", true);

			AtomWindowType = XInternAtom(currentDisplay, "_NET_WM_WINDOW_TYPE", false);
			AtomWindowTypeDesktop = XInternAtom(currentDisplay, "_NET_WM_WINDOW_TYPE_UTILITY", false);
			AtomWindowTypeSplash = XInternAtom(currentDisplay, "_NET_WM_WINDOW_TYPE_SPLASH", false);
			AtomWindowTypeNormal = XInternAtom(currentDisplay, "_NET_WM_WINDOW_TYPE_NORMAL", false);

			AtomAllowedActions = XInternAtom(currentDisplay, "_NET_WM_ALLOWED_ACTIONS", false);
			AtomActionResize = XInternAtom(currentDisplay, "WM_ACTION_RESIZE", false);
			AtomActionMinimize = XInternAtom(currentDisplay, "_WM_ACTION_MINIMIZE", false);
			AtomActionShade = XInternAtom(currentDisplay, "WM_ACTION_SHADE", false);
			AtomActionMaximizeHorz = XInternAtom(currentDisplay, "_WM_ACTION_MAXIMIZE_HORZ", false);
			AtomActionMaximizeVert = XInternAtom(currentDisplay, "_WM_ACTION_MAXIMIZE_VERT", false);
			AtomActionClose = XInternAtom(currentDisplay, "_WM_ACTION_CLOSE", false);

			AtomDesktopGeometry = XInternAtom(currentDisplay, "_NET_DESKTOP_GEOMETRY", false);
		}
#endif

	public:

		tWindow(
			windowManager& mmanager,
			const char* name,
			vec2_t<unsigned int>& resolution,
			unsigned int colorBits,
			unsigned int depthBits,
			unsigned int stencilBits);

		/**
		* Set the Size/Resolution of the given window
		*/
		std::error_code SetResolution(TinyWindow::vec2_t<unsigned int> resolution)
		{
			this->resolution = resolution;
#if defined(TW_WINDOWS)
			SetWindowPos(windowHandle, HWND_TOP,
				position.x, position.y,
				resolution.x, resolution.y,
				SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
#elif defined(TW_LINUX)
			XResizeWindow(currentDisplay,
				windowHandle, resolution.x, resolution.y);
#endif
			return TinyWindow::error_t::success;
		}

		/**
		* Set the Position of the given window relative to screen co-ordinates
		*/
		std::error_code SetPosition(TinyWindow::vec2_t<int> position)
		{
			this->position = position;

#if defined(TW_WINDOWS)
			SetWindowPos(windowHandle, HWND_TOP, position.x, position.y,
				resolution.x, resolution.y,
				SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
#elif defined(TW_LINUX)
			XWindowChanges windowChanges;

			windowChanges.x = position.x;
			windowChanges.y = position.y;

			XConfigureWindow(
				currentDisplay,
				windowHandle, CWX | CWY, &windowChanges);
#endif
			return TinyWindow::error_t::success;
		}

		/**
		* Set the mouse Position of the given window's co-ordinates
		*/
		std::error_code SetMousePosition(TinyWindow::vec2_t<unsigned int> mousePosition)
		{
			this->mousePosition.x = mousePosition.x;
			this->mousePosition.y = mousePosition.y;
#if defined(TW_WINDOWS)
			POINT mousePoint;
			mousePoint.x = mousePosition.x;
			mousePoint.y = mousePosition.y;
			ClientToScreen(windowHandle, &mousePoint);
			SetCursorPos(mousePoint.x, mousePoint.y);
#elif defined(TW_LINUX)
			XWarpPointer(
				currentDisplay,
				windowHandle, windowHandle,
				position.x, position.y,
				resolution.width, resolution.height,
				mousePosition.x, mousePosition.y);
#endif
			return TinyWindow::error_t::success;
		}

#if defined(TW_USE_VULKAN) //these are hidden if TW_USE_VULKAN is defined
		//get reference to instance
		inline VkInstance& GetVulkanInstance()
		{
			return vulkanInstanceHandle;
		}

		//get reference to surface
		inline VkSurfaceKHR& GetVulkanSurface()
		{
			return vulkanSurfaceHandle;
		}
#else
		/**
		* Swap the draw buffers of the given window.
		*/
		inline void SwapDrawBuffers()
		{
#if defined(TW_WINDOWS)
			SwapBuffers(deviceContextHandle);
#elif defined(TW_LINUX)
			glXSwapBuffers(currentDisplay, windowHandle);
#endif
			// since there's no way that this can fail. there's nothing to return
		}

		/**
		* Make the given window be the current OpenGL Context to be drawn to
		*/
		void MakeCurrentContext()
		{
#if defined(TW_WINDOWS)
			wglMakeCurrent(deviceContextHandle, glRenderingContextHandle);
#elif defined(TW_LINUX)
			glXMakeCurrent(currentDisplay, windowHandle, context);
#endif
			// since there's no way that this can fail. there's nothing to return
		}
#endif
		/**
		* Toggle the minimization state of the given window
		*/
		std::error_code Minimize(bool newState)
		{
			if (newState)
			{
				currentState = state_t::minimized;

#if defined(TW_WINDOWS)
				ShowWindow(windowHandle, SW_MINIMIZE);
#elif defined(TW_LINUX)
				XIconifyWindow(currentDisplay,
					windowHandle, 0);
#endif
			}

			else
			{
				currentState = state_t::normal;
#if defined(TW_WINDOWS)
				ShowWindow(windowHandle, SW_RESTORE);
#elif defined(TW_LINUX)
				XMapWindow(currentDisplay, windowHandle);
#endif
			}
			return TinyWindow::error_t::success;
		}

		/**
		* Toggle the maximization state of the current window
		*/
		std::error_code Maximize(bool newState)
		{
			if (newState)
			{
				currentState = state_t::maximized;
#if defined(TW_WINDOWS)
				ShowWindow(windowHandle, SW_MAXIMIZE);
#elif defined(TW_LINUX)
				XEvent currentEvent;
				memset(&currentEvent, 0, sizeof(currentEvent));

				currentEvent.xany.type = ClientMessage;
				currentEvent.xclient.message_type = AtomState;
				currentEvent.xclient.format = 32;
				currentEvent.xclient.window = windowHandle;
				currentEvent.xclient.data.l[0] = (currentState == state_t::maximized);
				currentEvent.xclient.data.l[1] = AtomMaxVert;
				currentEvent.xclient.data.l[2] = AtomMaxHorz;

				XSendEvent(currentDisplay,
					XDefaultRootWindow(currentDisplay),
					0, SubstructureNotifyMask, &currentEvent);
#endif
			}

			else
			{
				currentState = state_t::normal;
#if defined(TW_WINDOWS)
				ShowWindow(windowHandle, SW_RESTORE);
#elif defined(TW_LINUX)
				XEvent currentEvent;
				memset(&currentEvent, 0, sizeof(currentEvent));

				currentEvent.xany.type = ClientMessage;
				currentEvent.xclient.message_type = AtomState;
				currentEvent.xclient.format = 32;
				currentEvent.xclient.window = windowHandle;
				currentEvent.xclient.data.l[0] = (currentState == state_t::maximized);
				currentEvent.xclient.data.l[1] = AtomMaxVert;
				currentEvent.xclient.data.l[2] = AtomMaxHorz;

				XSendEvent(currentDisplay,
					XDefaultRootWindow(currentDisplay),
					0, SubstructureNotifyMask, &currentEvent);
#endif
			}
			return TinyWindow::error_t::success;
		}

		/**
		* Toggle the given window's full screen mode
		*/
		std::error_code SetFullScreen(bool newState)
		{
			currentState = (newState == true) ? state_t::fullscreen : state_t::normal;

#if defined(TW_WINDOWS)

			SetWindowLongPtr(windowHandle, GWL_STYLE,
				WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);

			RECT desktop;
			GetWindowRect(windowHandle, &desktop);
			MoveWindow(windowHandle, 0, 0, desktop.right, desktop.bottom, true);

#elif defined(TW_LINUX)

			XEvent currentEvent;
			memset(&currentEvent, 0, sizeof(currentEvent));

			currentEvent.xany.type = ClientMessage;
			currentEvent.xclient.message_type = AtomState;
			currentEvent.xclient.format = 32;
			currentEvent.xclient.window = windowHandle;
			currentEvent.xclient.data.l[0] = currentState == state_t::fullscreen;
			currentEvent.xclient.data.l[1] = AtomFullScreen;

			XSendEvent(currentDisplay,
				XDefaultRootWindow(currentDisplay),
				0, SubstructureNotifyMask, &currentEvent);
#endif
			return TinyWindow::error_t::success;
		}

		/**
		* Set the window title bar	by name
		*/
		std::error_code SetTitleBar(const char* newTitle)
		{
			if (newTitle != nullptr)
			{
#if defined(TW_WINDOWS)
				SetWindowText(windowHandle, newTitle);
#elif defined(TW_LINUX)
				XStoreName(currentDisplay, windowHandle, newTitle);
#endif
				return TinyWindow::error_t::success;
			}
			return TinyWindow::error_t::invalidTitlebar;
		}

		/**
		* Set the window icon by name (currently not functional)
		*/
		std::error_code SetIcon()//const char* windowName, const char* icon, unsigned int width, unsigned int height)
		{
			return TinyWindow::error_t::functionNotImplemented;
		}

		/**
		* Set the window to be in focus by name
		*/
		std::error_code Focus(bool newState)
		{
			if (newState)
			{
#if defined(TW_WINDOWS)
				SetFocus(windowHandle);
#elif defined(TW_LINUX)
				XMapWindow(currentDisplay, windowHandle);
#endif
			}

			else
			{
#if defined(_WIN32) || defined(_WIN64)
				SetFocus(nullptr);
#elif defined(TW_LINUX)
				XUnmapWindow(currentDisplay, windowHandle);
#endif
			}
			return TinyWindow::error_t::success;
		}

		/**
		* Restore the window by name
		*/
		std::error_code Restore()
		{
#if defined(TW_WINDOWS)
			ShowWindow(windowHandle, SW_RESTORE);
#elif defined(TW_LINUX)
			XMapWindow(currentDisplay, windowHandle);
#endif
			return TinyWindow::error_t::success;
		}

		/**
		* Set the window style preset by name
		*/
		std::error_code SetStyle(style_t windowStyle)
		{
#if defined(TW_WINDOWS)
			switch (windowStyle)
			{
			case style_t::normal:
			{
				EnableDecorators(titleBar | border |
					closeButton | minimizeButton | maximizeButton | sizeableBorder);
				break;
			}

			case style_t::popup:
			{
				EnableDecorators(0);
				break;
			}

			case style_t::bare:
			{
				EnableDecorators(titleBar | border);
				break;
			}

			default:
			{
				return TinyWindow::error_t::invalidWindowStyle;
			}
			}

#elif defined(TW_LINUX)
			switch (windowStyle)
			{
			case style_t::normal:
			{
				linuxDecorators = (1L << 2);
				currentStyle = linuxMove | linuxClose |
					linuxMaximize | linuxMinimize;
				long Hints[5] = { hint_t::function | hint_t::decorator, currentStyle, linuxDecorators, 0, 0 };

				XChangeProperty(currentDisplay, windowHandle, AtomHints, XA_ATOM, 32, PropModeReplace,
					(unsigned char*)Hints, 5);

				XMapWindow(currentDisplay, windowHandle);
				break;
			}

			case style_t::bare:
			{
				linuxDecorators = (1L << 2);
				currentStyle = (1L << 2);
				long Hints[5] = { function | decorator, currentStyle, linuxDecorators, 0, 0 };

				XChangeProperty(currentDisplay, windowHandle, AtomHints, XA_ATOM, 32, PropModeReplace,
					(unsigned char*)Hints, 5);

				XMapWindow(currentDisplay, windowHandle);
				break;
			}

			case style_t::popup:
			{
				linuxDecorators = 0;
				currentStyle = (1L << 2);
				long Hints[5] = { function | decorator, currentStyle, linuxDecorators, 0, 0 };

				XChangeProperty(currentDisplay, windowHandle, AtomHints, XA_ATOM, 32, PropModeReplace,
					(unsigned char*)Hints, 5);

				XMapWindow(currentDisplay, windowHandle);
				break;
			}

			default:
			{
				return TinyWindow::error_t::invalidWindowStyle;
			}
			}
#endif
			return TinyWindow::error_t::success;
		}

		/**
		* Enable window decorators by name
		*/
		std::error_code EnableDecorators(unsigned int decorators)
		{
#if defined(TW_WINDOWS)

			currentStyle = WS_VISIBLE | WS_CLIPSIBLINGS;

			if (decorators & border)
			{
				currentStyle |= WS_BORDER;
			}

			if (decorators & titleBar)
			{
				currentStyle |= WS_CAPTION;
			}

			if (decorators & icon)
			{
				currentStyle |= WS_ICONIC;
			}

			if (decorators & closeButton)
			{
				currentStyle |= WS_SYSMENU;
			}

			if (decorators & minimizeButton)
			{
				currentStyle |= WS_MINIMIZEBOX | WS_SYSMENU;
			}

			if (decorators & maximizeButton)
			{
				currentStyle |= WS_MAXIMIZEBOX | WS_SYSMENU;
			}

			if (decorators & sizeableBorder)
			{
				currentStyle |= WS_SIZEBOX;
			}

			SetWindowLongPtr(windowHandle, GWL_STYLE, currentStyle);
			SetWindowPos(windowHandle, HWND_TOP, position.x, position.y,
				resolution.width, resolution.height, SWP_FRAMECHANGED);

#elif defined(TW_LINUX)

			if (decorators & closeButton)
			{
				currentStyle |= linuxClose;
				decorators = 1;
			}

			if (decorators & minimizeButton)
			{
				currentStyle |= linuxMinimize;
				decorators = 1;
			}

			if (decorators & maximizeButton)
			{
				currentStyle |= linuxMaximize;
				decorators = 1;
			}

			if (decorators & icon)
			{
				//Linux (at least cinnamon) does not have icons in the window. only in the task bar icon
			}

			//just need to set it to 1 to enable all decorators that include title bar
			if (decorators & titleBar)
			{
				decorators = 1;
			}

			if (decorators & border)
			{
				decorators = 1;
			}

			if (decorators & sizeableBorder)
			{
				decorators = 1;
			}

			long hints[5] = { function | decorator, currentStyle, decorators, 0, 0 };

			XChangeProperty(currentDisplay, windowHandle, AtomHints, XA_ATOM, 32,
				PropModeReplace, (unsigned char*)hints, 5);

			XMapWindow(currentDisplay, windowHandle);
#endif
			return TinyWindow::error_t::success;
		}

		/**
		* Disable windows decorators by name
		*/
		std::error_code DisableDecorators(unsigned int decorators)
		{
#if defined(TW_WINDOWS)
			if (decorators & border)
			{
				currentStyle &= ~WS_BORDER;
			}

			if (decorators & titleBar)
			{
				currentStyle &= ~WS_CAPTION;
			}

			if (decorators & icon)
			{
				currentStyle &= ~WS_ICONIC;
			}

			if (decorators & closeButton)
			{
				currentStyle &= ~WS_SYSMENU;
			}

			if (decorators & minimizeButton)
			{
				currentStyle &= ~WS_MINIMIZEBOX;
			}

			if (decorators & maximizeButton)
			{
				currentStyle &= ~WS_MAXIMIZEBOX;
			}

			if (decorators & sizeableBorder)
			{
				currentStyle &= ~WS_SIZEBOX;
			}

			SetWindowLongPtr(windowHandle, GWL_STYLE,
				currentStyle | WS_VISIBLE);

			SetWindowPos(windowHandle, HWND_TOP, position.x, position.y,
				resolution.width, resolution.height, SWP_FRAMECHANGED);
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

				currentStyle &= ~linuxClose;

				if (maximizeEnabled)
				{
					currentStyle |= linuxMaximize;
				}

				if (minimizeEnabled)
				{
					currentStyle |= linuxMinimize;
				}

				decorators = 1;
			}

			if (decorators & minimizeButton)
			{
				currentStyle &= ~linuxMinimize;
				decorators = 1;
			}

			if (decorators & maximizeButton)
			{
				bool minimizeEnabled = false;

				if (decorators & minimizeButton)
				{
					minimizeEnabled = true;
				}

				currentStyle &= ~linuxMaximize;

				if (minimizeEnabled)
				{
					currentStyle |= linuxMinimize;
				}

				decorators = 1;
			}

			if (decorators & icon)
			{
				//Linux (at least cinnamon) does not have icons in the window. only in the taskb ar icon
			}

			//just need to set it to 1 to enable all decorators that include title bar
			if (decorators & titleBar)
			{
				decorators = linuxBorder;
			}

			if (decorators & border)
			{
				decorators = 0;
			}

			if (decorators & sizeableBorder)
			{
				decorators = 0;
			}

			long hints[5] = { function | decorator, currentStyle, decorators, 0, 0 };

			XChangeProperty(currentDisplay, windowHandle, AtomHints, XA_ATOM, 32,
				PropModeReplace, (unsigned char*)hints, 5);

			XMapWindow(currentDisplay, windowHandle);
#endif
			return TinyWindow::error_t::success;
		}

		//if windows is defined then allow the user to only GET the necessary info
#if defined(TW_WINDOWS)
		inline HDC GetDeviceContextDeviceHandle()
		{
			return deviceContextHandle;
		}

		inline HGLRC GetGLRenderingContextHandle()
		{
			return glRenderingContextHandle;
		}

		inline HWND GetWindowHandle()
		{
			return windowHandle;
		}

		inline HINSTANCE GetWindowClassInstance()
		{
			return instanceHandle;
		}
#endif

#if defined(TW_LINUX)
		Window GetWindowHandle()
		{
			return windowHandle;
		}

		GLXContext GetGLXContext()
		{
			return context;
		}

		Display* GetCurrentDisplay()
		{
			return currentDisplay;
		}
#endif
	};

	class windowManager
	{
		friend class tWindow;


		windowManager()
		{
	#if defined(TW_WINDOWS)
			CreateTerminal(); //feel free to comment this out
			RECT desktop;

			HWND desktopHandle = GetDesktopWindow();

			if (desktopHandle)
			{
				GetWindowRect(desktopHandle, &desktop);

				screenResolution.x = desktop.right;
				screenResolution.y = desktop.bottom;
				return;
			}
	#elif defined(TW_LINUX)
			currentDisplay = XOpenDisplay(0);

			if (!currentDisplay)
			{
				return;
			}

			screenResolution.x = WidthOfScreen(
				XScreenOfDisplay(currentDisplay,
					DefaultScreen(currentDisplay)));

			screenResolution.y = HeightOfScreen(
				XScreenOfDisplay(currentDisplay,
					DefaultScreen(currentDisplay)));
	#endif
		}
	public:
		windowManager(const windowManager&) = delete;
		windowManager& operator=(const windowManager&) = delete;

		/**
		 * Shutdown and delete all windows in the manager
		 */
		~windowManager()
		{
			windowList.clear();

			// some clever clog might start creating windows in destructors "just in case"
			assert(windowList.empty());

	#if defined(__linux__)
			Linux_Shutdown();
	#endif
		}

		/**
		 * Use this to add a window to the manager. returns a pointer to the manager which allows for the easy creation of multiple windows
		 */
		std::unique_ptr<tWindow> AddWindow(
				const char* windowName,
				vec2_t<unsigned int> resolution = vec2_t<unsigned int>(defaultWindowWidth, defaultWindowHeight),
				int colourBits = 8,
				int depthBits = 8,
				int stencilBits = 8
		) {
			if (windowName == nullptr)
				return nullptr;

			auto ptr = new tWindow(
				*this,
				windowName,
				resolution,
				colourBits,
				depthBits,
				stencilBits
			);

			// ICK ; this could be better

			if (windowList.back())
			{
				return std::unique_ptr<tWindow>(ptr);
			}

			// if back is nullptr then the window didn't setup correctly and has already deleted
			windowList.pop_back();

			return nullptr;
		}

		/**
		 * Return the total amount of windows the manager has
		 */
		int GetNumWindows()
		{
			return (int)windowList.size();
		}

		/**
		* Return the mouse position in screen co-ordinates
		*/
		TinyWindow::vec2_t<int> GetMousePositionInScreen()
		{
			return screenMousePosition;
		}

		/**
		 * Set the position of the mouse cursor relative to screen co-ordinates
		 */
		void SetMousePositionInScreen(TinyWindow::vec2_t<int> mousePosition)
		{
			screenMousePosition.x = mousePosition.x;
			screenMousePosition.y = mousePosition.y;

	#if defined(TW_WINDOWS)
			SetCursorPos(screenMousePosition.y, screenMousePosition.y);
	#elif defined(TW_LINUX)
			XWarpPointer(currentDisplay, None,
				XDefaultRootWindow(currentDisplay), 0, 0,
				screenResolution.x,
				screenResolution.y,
				screenMousePosition.x, screenMousePosition.y);
	#endif
		}

		/**
		* Return the Resolution of the current screen
		*/
		TinyWindow::vec2_t<unsigned int> GetScreenResolution()
		{
	#if defined(TW_WINDOWS)
			RECT screen;
			HWND desktop = GetDesktopWindow();
			GetWindowRect(desktop, &screen);
			screenResolution.width = screen.right;
			screenResolution.height = screen.bottom;
	#elif defined(TW_LINUX)
			screenResolution.width = WidthOfScreen(XDefaultScreenOfDisplay(currentDisplay));
			screenResolution.height = HeightOfScreen(XDefaultScreenOfDisplay(currentDisplay));
	#endif
			return screenResolution;
		}

		/**
		* Ask the window manager to poll for events
		*/
		inline void PollForEvents(const bool wait = false)
		{
	#if defined(TW_WINDOWS)
			//only process events if there are any to process
			MSG		winMessage;

			if (wait)
				GetMessage(&winMessage, 0, 0, 0);

			while (wait || PeekMessage(&winMessage, 0, 0, 0, PM_REMOVE))
			{
				//the only place I can see this being needed if someone called PostQuitMessage manually
				TranslateMessage(&winMessage);
				DispatchMessage(&winMessage);
				if (winMessage.message == WM_QUIT)
				{
					// I want to "shutdown" but there's not a lot I can do to force the issue
					// ... who else has our windows?
					// ... do you have our windows?
					// ... what can I do about that?
					// ... I'll mark all windows as closed and hope for the best
					for (auto& window : windowList)
					{
						window->shouldClose = true;
					}
				}

				if (wait)
					return;
			}

	#elif defined(TW_LINUX)
			// if there are any events to process or we're waiting for an event
			if (wait || XEventsQueued(currentDisplay, QueuedAfterReading))
			{
				XNextEvent(currentDisplay, &currentEvent);
				Linux_ProcessEvents(currentEvent);
			}
	#endif
		}

		/**
		* Ask the window manager to wait for events
		*/
		inline void WaitForEvents()
		{
			PollForEvents(true);
		}

#if 0
		/**
		* Remove window from the manager by name
		*/
		std::error_code RemoveWindow(tWindow* window)
		{
			if (window != nullptr)
			{
				ShutdownWindow(window);
				return TinyWindow::error_t::success;
			}
			return TinyWindow::error_t::windowInvalid;
		}
#endif
	private:

		std::vector<std::unique_ptr<tWindow>>		windowList;

		TinyWindow::vec2_t<unsigned int>			screenResolution;
		TinyWindow::vec2_t<int>						screenMousePosition;

		bool Platform_InitializeWindow(tWindow* window)
		{
	#if defined(TW_WINDOWS)
			return Windows_InitializeWindow(window);
	#elif defined(TW_LINUX)
			Linux_InitializeWindow(window);
	#endif
		}

		std::error_code Platform_InitializeGL(tWindow* window)
		{
	#if defined(TW_WINDOWS)
			assert(false && "This was inlaid");
	#elif defined(TW_LINUX)
				window->context = glXCreateContext(
					currentDisplay,
					window->visualInfo,
					0,
					true);

				if (window->context)
				{
					glXMakeCurrent(currentDisplay,
						window->windowHandle,
						window->context);

					XWindowAttributes l_Attributes;

					XGetWindowAttributes(currentDisplay,
						window->windowHandle, &l_Attributes);
					window->position.x = l_Attributes.x;
					window->position.y = l_Attributes.y;

					window->contextCreated = true;
					window->InitializeAtoms();
					return TinyWindow::error_t::success;
				}
				return TinyWindow::error_t::linuxCannotConnectXServer;
	#endif
		}

		void ShutdownWindow(tWindow* window)
		{
	#if defined(TW_WINDOWS)
			window->shouldClose = true;
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

			for (auto it = windowList.begin(); it != windowList.end(); ++it)
			{
				if (window == it->get())
				{
					windowList.erase(it);
					break;
				}
			}
	#elif defined(TW_LINUX)
			if (window->currentState == state_t::fullscreen)
			{
				window->Restore();
			}

			glXDestroyContext(currentDisplay, window->context);
			XUnmapWindow(currentDisplay, window->windowHandle);
			XDestroyWindow(currentDisplay, window->windowHandle);
			window->windowHandle = 0;
			window->context = 0;
	#endif
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

		HDC		deviceContextHandle;

		//the window procedure for all windows. This is used mainly to handle window events
		static LRESULT CALLBACK WindowProcedure(HWND windowHandle, unsigned int winMessage, WPARAM wordParam, LPARAM longParam)
		{
			windowManager* manager = (windowManager*)GetWindowLongPtr(windowHandle, GWLP_USERDATA);
			tWindow* window = nullptr;
			if (manager != nullptr)
			{
				window = manager->GetWindowByHandle(windowHandle);
			}

			switch (winMessage)
			{
				case WM_DESTROY:
				{
					if (manager != nullptr)
					{
						window->shouldClose = true;

						if (window->destroyedEvent != nullptr)
						{
							window->destroyedEvent();
						}
						manager->ShutdownWindow(window);
					}
					break;
				}

				case WM_MOVE:
				{
					window->position.x = LOWORD(longParam);
					window->position.y = HIWORD(longParam);

					if (window->movedEvent != nullptr)
					{
						window->movedEvent(window->position);
					}

					break;
				}

				case WM_MOVING:
				{
					window->position.x = LOWORD(longParam);
					window->position.y = HIWORD(longParam);

					if (window->movedEvent != nullptr)
					{
						window->movedEvent(window->position);
					}
					break;
				}

				case WM_SIZE:
				{
					window->resolution.width = (unsigned int)LOWORD(longParam);
					window->resolution.height = (unsigned int)HIWORD(longParam);

					switch (wordParam)
					{
						case SIZE_MAXIMIZED:
						{
							if (window->maximizedEvent != nullptr)
							{
								window->maximizedEvent();
							}

							break;
						}

						case SIZE_MINIMIZED:
						{
							if (window->minimizedEvent != nullptr)
							{
								window->minimizedEvent();
							}
							break;
						}

						default:
						{
							if (window->resizeEvent != nullptr)
							{
								window->resizeEvent(window->resolution);
							}
							break;
						}
					}
					break;
				}

				case WM_SIZING:
				{
					window->resolution.width = (unsigned int)LOWORD(longParam);
					window->resolution.height = (unsigned int)HIWORD(longParam);

					if (window->resizeEvent != nullptr)
					{
						window->resizeEvent(window->resolution);
					}
					break;
				}

				case WM_KEYDOWN:
				{
					key_t translatedKey;

					switch (HIWORD(longParam))
					{
						case leftControlDown:
						{
							window->keys[(unsigned int)key_t::leftControl] = keyState_t::down;
							translatedKey = key_t::leftControl;
							break;
						}

						case rightControlDown:
						{
							window->keys[(unsigned int)key_t::rightControl] = keyState_t::down;
							translatedKey = key_t::rightControl;
							break;
						}

						case leftShiftDown:
						{
							window->keys[(unsigned int)key_t::leftShift] = keyState_t::down;
							translatedKey = key_t::leftShift;
							break;
						}

						case rightShiftDown:
						{
							window->keys[(unsigned int)key_t::rightShift] = keyState_t::down;
							translatedKey = key_t::rightShift;
							break;
						}

						default:
						{
							translatedKey = (key_t)Windows_TranslateKey(wordParam);
							window->keys[(unsigned int)translatedKey] = keyState_t::down;
							break;
						}
					}

					if (window->keyEvent != nullptr)
					{
						window->keyEvent(translatedKey, keyState_t::down);
					}
					break;
				}

				case WM_KEYUP:
				{
					TinyWindow::key_t translatedKey ;

					switch (HIWORD(longParam))
					{
						case leftControlUp:
						{
							window->keys[(unsigned int)TinyWindow::key_t::leftControl] = keyState_t::up;
							translatedKey = TinyWindow::key_t::leftControl;
							break;
						}

						case rightControlUp:
						{
							window->keys[(unsigned int)TinyWindow::key_t::rightControl] = keyState_t::up;
							translatedKey = TinyWindow::key_t::rightControl;
							break;
						}

						case leftShiftUp:
						{
							window->keys[(unsigned int)TinyWindow::key_t::leftShift] = keyState_t::up;
							translatedKey = TinyWindow::key_t::leftShift;
							break;
						}

						case rightShiftUp:
						{
							window->keys[(unsigned int)TinyWindow::key_t::rightShift] = keyState_t::up;
							translatedKey = TinyWindow::key_t::rightShift;
							break;
						}

						default:
						{
							translatedKey = (TinyWindow::key_t)Windows_TranslateKey(wordParam);
							window->keys[(unsigned int)translatedKey] = keyState_t::up;
							break;
						}
					}

					if (window->keyEvent != nullptr)
					{
						window->keyEvent(translatedKey, keyState_t::up);
					}
					break;
				}

				case WM_SYSKEYDOWN:
				{
					TinyWindow::key_t translatedKey ;
					switch (HIWORD(longParam))
					{
						case leftAltDown:
						{
							window->keys[(unsigned int)TinyWindow::key_t::leftAlt] = keyState_t::down;
							translatedKey = TinyWindow::key_t::leftAlt;
							break;
						}

						case rightAltDown:
						{
							window->keys[(unsigned int)TinyWindow::key_t::rightAlt] = keyState_t::down;
							translatedKey = TinyWindow::key_t::rightAlt;
						}

						default:
						{
							return 0;
						}
					}

					if (window->keyEvent != nullptr)
					{
						window->keyEvent(translatedKey, keyState_t::down);
					}

					break;
				}

				case WM_SYSKEYUP:
				{
					TinyWindow::key_t translatedKey;
					switch (HIWORD(longParam))
					{
						case leftAltUp:
						{
							window->keys[(unsigned int)TinyWindow::key_t::leftAlt] = keyState_t::up;
							translatedKey = TinyWindow::key_t::leftAlt;
							break;
						}


						case rightAltUp:
						{
							window->keys[(unsigned int)TinyWindow::key_t::rightAlt] = keyState_t::up;
							translatedKey = TinyWindow::key_t::rightAlt;
							break;
						}

						default:
						{
							return 0;
						}
					}

					if (window->keyEvent != nullptr)
					{
						window->keyEvent(translatedKey, keyState_t::up);
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
					window->mousePosition.x = (int)LOWORD(longParam);
					window->mousePosition.y = (int)HIWORD(longParam);

					POINT point;
					point.x = (LONG)window->mousePosition.x;
					point.y = (LONG)window->mousePosition.y;

					ClientToScreen(windowHandle, &point);

					if (window->mouseMoveEvent != nullptr)
					{
						window->mouseMoveEvent(window->mousePosition, vec2_t<int>(point.x, point.y));
					}
					break;
				}

				case WM_LBUTTONDOWN:
				{
					window->mouseButton[(unsigned int)mouseButton_t::left] = buttonState_t::down;

					if (window->mouseButtonEvent != nullptr)
					{
						window->mouseButtonEvent(mouseButton_t::left, buttonState_t::down);
					}
					break;
				}

				case WM_LBUTTONUP:
				{
					window->mouseButton[(unsigned int)mouseButton_t::left] = buttonState_t::up;

					if (window->mouseButtonEvent != nullptr)
					{
						window->mouseButtonEvent(mouseButton_t::left, buttonState_t::up);
					}
					break;
				}

				case WM_RBUTTONDOWN:
				{
					window->mouseButton[(unsigned int)mouseButton_t::right] = buttonState_t::down;

					if (window->mouseButtonEvent != nullptr)
					{
						window->mouseButtonEvent(mouseButton_t::right, buttonState_t::down);
					}
					break;
				}

				case WM_RBUTTONUP:
				{
					window->mouseButton[(unsigned int)mouseButton_t::right] = buttonState_t::up;

					if (window->mouseButtonEvent != nullptr)
					{
						window->mouseButtonEvent(mouseButton_t::right, buttonState_t::up);
					}
					break;
				}

				case WM_MBUTTONDOWN:
				{
					window->mouseButton[(unsigned int)mouseButton_t::middle] = buttonState_t::down;

					if (window->mouseButtonEvent != nullptr)
					{
						window->mouseButtonEvent(mouseButton_t::middle, buttonState_t::down);
					}
					break;
				}

				case WM_MBUTTONUP:
				{
					window->mouseButton[(unsigned int)mouseButton_t::middle] = buttonState_t::up;

					if (window->mouseButtonEvent != nullptr)
					{
						window->mouseButtonEvent(mouseButton_t::middle, buttonState_t::up);
					}
					break;
				}

				case WM_MOUSEWHEEL:
				{
					int delta = GET_WHEEL_DELTA_WPARAM(wordParam);
					if (delta > 0)
					{
						//if was previously negative, revert to zero
						if (window->accumWheelDelta < 0)
						{
							window->accumWheelDelta = 0;
						}

						else
						{
							window->accumWheelDelta += delta;
						}

						if (window->accumWheelDelta >= WHEEL_DELTA)
						{
							if (window->mouseWheelEvent != nullptr)
							{
								window->mouseWheelEvent(mouseScroll_t::down);
							}
							//reset accum
							window->accumWheelDelta = 0;
						}
					}

					else
					{
						//if was previously positive, revert to zero
						if (window->accumWheelDelta > 0)
						{
							window->accumWheelDelta = 0;
						}

						else
						{
							window->accumWheelDelta += delta;
						}

						//if the delta is equal to or greater than delta
						if (window->accumWheelDelta <= -WHEEL_DELTA)
						{
							if (window->mouseWheelEvent != nullptr)
							{
								window->mouseWheelEvent(mouseScroll_t::up);
							}
							//reset accum
							window->accumWheelDelta = 0;
						}
					}

					break;
				}

				default:
				{
					//windowList[getWindow]
					return DefWindowProc(windowHandle, winMessage, wordParam, longParam);
				}
			}
			return 0;
		}

		//get the window that is associated with this Win32 window handle
		tWindow* GetWindowByHandle(HWND windowHandle)
		{
			for (unsigned int windowIndex = 0; windowIndex < windowList.size(); windowIndex++)
			{
				if (windowList[windowIndex]->windowHandle == windowHandle)
				{
					return windowList[windowIndex].get();
				}
			}
			return nullptr;
		}

		//initialize the given window using Win32
		bool Windows_InitializeWindow(tWindow* window,
			UINT style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DROPSHADOW,
			int clearScreenExtra = 0, int windowExtra = 0,
			HINSTANCE winInstance = GetModuleHandle(0),
			HICON icon = LoadIcon(0, IDI_APPLICATION),
			HCURSOR cursor = LoadCursor(0, IDC_ARROW),
			HBRUSH brush = (HBRUSH)GetStockObject(WHITE_BRUSH))
		{
			window->instanceHandle = winInstance;
			window->windowClass.style = style;
			window->windowClass.lpfnWndProc = windowManager::WindowProcedure;
			window->windowClass.cbClsExtra = clearScreenExtra;
			window->windowClass.cbWndExtra = windowExtra;
			window->windowClass.hInstance = window->instanceHandle;
			window->windowClass.hIcon = icon;
			window->windowClass.hCursor = cursor;
			window->windowClass.hbrBackground = brush;
			window->windowClass.lpszMenuName = window->name;
			window->windowClass.lpszClassName = window->name;
			RegisterClass(&window->windowClass);

			window->windowHandle =
				CreateWindow(window->name, window->name, WS_OVERLAPPEDWINDOW, 0,
				0, window->resolution.width,
				window->resolution.height,
				0, 0, 0, 0);

			SetWindowLongPtr(window->windowHandle, GWLP_USERDATA, (LONG_PTR)this);

			//if TW_USE_VULKAN is defined then stop TinyWindow from creating an OpenGL context since it will conflict with a vulkan context
#if !defined(TW_USE_VULKAN)
			{
				window->deviceContextHandle = GetDC(window->windowHandle);
				InitializePixelFormat(window);
				window->glRenderingContextHandle = wglCreateContext(window->deviceContextHandle);
				wglMakeCurrent(window->deviceContextHandle, window->glRenderingContextHandle);

				window->contextCreated = (window->glRenderingContextHandle != nullptr);

				if (!(window->contextCreated))
				{
					return false;
				}
			}
#endif
			ShowWindow(window->windowHandle, true);
			UpdateWindow(window->windowHandle);

			window->SetStyle(style_t::normal);

			return true;
		}

		//initialize the pixel format for the selected window
		void InitializePixelFormat(tWindow* window)
		{
			window->pixelFormatDescriptor = {
				sizeof(PIXELFORMATDESCRIPTOR), /* size */
				1, /* version */
				PFD_DRAW_TO_WINDOW |
				PFD_DOUBLEBUFFER, /* support double-buffering */
				PFD_TYPE_RGBA, /* color type */
				(BYTE)window->colorBits, 0, /* preferred color depth */
				0, 0,
				0, 0,
				0, 0,
				0, /* color bits (ignored) */ /* no alpha buffer */ /* alpha bits (ignored) */
				0, /* no accumulation buffer */
				0, 0, 0, 0, /* accum bits (ignored) */
				(BYTE)window->depthBits, /* depth buffer */
				(BYTE)window->stencilBits, /* no stencil buffer */
				0, /* no auxiliary buffers */
				PFD_MAIN_PLANE, /* main layer */
				0, /* reserved */
				0, 0, 0, /* no layer, visible, damage masks */
			};

			int LocalPixelFormat = ChoosePixelFormat(window->deviceContextHandle,
				&window->pixelFormatDescriptor);

			if (LocalPixelFormat)
			{
				SetPixelFormat(window->deviceContextHandle, LocalPixelFormat,
					&window->pixelFormatDescriptor);
				return;
			}
			return;
		}

		void Windows_Shutown()
		{

		}

		void CreateTerminal()
		{
			int conHandle;
			long stdHandle;
			FILE* fp;

			// allocate a console for this app
			AllocConsole();

			// redirect unbuffered STDOUT to the console
			stdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
			conHandle = _open_osfhandle(stdHandle, _O_TEXT);
			fp = _fdopen(conHandle, "w");
			*stdout = *fp;

			setvbuf(stdout, nullptr, _IONBF, 0);
		}

		static TinyWindow::key_t Windows_TranslateKey(WPARAM wordParam)
		{
			switch (wordParam)
			{
				case VK_ESCAPE:
				{
					return TinyWindow::key_t::escape;
				}

				case VK_SPACE:
				{
					return TinyWindow::key_t::spacebar;
				}

				case VK_F1:
				{
					return TinyWindow::key_t::F1;
				}

				case VK_F2:
				{
					return TinyWindow::key_t::F2;
				}

				case VK_F3:
				{
					return TinyWindow::key_t::F3;
				}

				case VK_F4:
				{
					return TinyWindow::key_t::F4;
				}

				case VK_F5:
				{
					return TinyWindow::key_t::F5;
				}

				case VK_F6:
				{
					return TinyWindow::key_t::F6;
				}

				case VK_F7:
				{
					return TinyWindow::key_t::F7;
				}

				case VK_F8:
				{
					return TinyWindow::key_t::F8;
				}

				case VK_F9:
				{
					return TinyWindow::key_t::F9;
				}

				case VK_F10:
				{
					return TinyWindow::key_t::F10;
				}

				case VK_F11:
				{
					return TinyWindow::key_t::F11;
				}

				case VK_F12:
				{
					return TinyWindow::key_t::F12;
				}

				case VK_BACK:
				{
					return TinyWindow::key_t::backspace;
				}

				case VK_TAB:
				{
					return TinyWindow::key_t::tab;
				}

				case VK_CAPITAL:
				{
					return TinyWindow::key_t::capsLock;
				}

				case VK_RETURN:
				{
					return TinyWindow::key_t::enter;
				}

				case VK_PRINT:
				{
					return TinyWindow::key_t::printScreen;
				}

				case VK_SCROLL:
				{
					return TinyWindow::key_t::scrollLock;
				}

				case VK_PAUSE:
				{
					return TinyWindow::key_t::pause;
				}

				case VK_INSERT:
				{
					return TinyWindow::key_t::insert;
				}

				case VK_HOME:
				{
					return TinyWindow::key_t::home;
				}

				case VK_DELETE:
				{
					return TinyWindow::key_t::del;
				}

				case VK_END:
				{
					return TinyWindow::key_t::end;
				}

				case VK_PRIOR:
				{
					return TinyWindow::key_t::pageUp;
				}

				case VK_NEXT:
				{
					return TinyWindow::key_t::pageDown;
				}

				case VK_DOWN:
				{
					return TinyWindow::key_t::arrowDown;
				}

				case VK_UP:
				{
					return TinyWindow::key_t::arrowUp;
				}

				case VK_LEFT:
				{
					return TinyWindow::key_t::arrowLeft;
				}

				case VK_RIGHT:
				{
					return TinyWindow::key_t::arrowRight;
				}

				case VK_DIVIDE:
				{
					return TinyWindow::key_t::keypadDivide;
				}

				case VK_MULTIPLY:
				{
					return TinyWindow::key_t::keypadMultiply;
				}

				case VK_SUBTRACT:
				{
					return TinyWindow::key_t::keypadDivide;
				}

				case VK_ADD:
				{
					return TinyWindow::key_t::keypadAdd;
				}

				case VK_DECIMAL:
				{
					return TinyWindow::key_t::keypadPeriod;
				}

				case VK_NUMPAD0:
				{
					return TinyWindow::key_t::keypad0;
				}

				case VK_NUMPAD1:
				{
					return TinyWindow::key_t::keypad1;
				}

				case VK_NUMPAD2:
				{
					return TinyWindow::key_t::keypad2;
				}

				case VK_NUMPAD3:
				{
					return TinyWindow::key_t::keypad3;
				}

				case VK_NUMPAD4:
				{
					return TinyWindow::key_t::keypad4;
				}

				case VK_NUMPAD5:
				{
					return TinyWindow::key_t::keypad5;
				}

				case VK_NUMPAD6:
				{
					return TinyWindow::key_t::keypad6;
				}

				case VK_NUMPAD7:
				{
					return TinyWindow::key_t::keypad7;
				}

				case VK_NUMPAD8:
				{
					return TinyWindow::key_t::keypad8;
				}

				case VK_NUMPAD9:
				{
					return TinyWindow::key_t::keypad9;
				}

				case VK_LWIN:
				{
					return TinyWindow::key_t::leftWindow;
				}

				case VK_RWIN:
				{
					return TinyWindow::key_t::rightWindow;
				}

				default:
				{
					return (TinyWindow::key_t)wordParam;
				}
			}
		}

		static void Windows_SetWindowIcon(tWindow* window, const char* icon, unsigned int width, unsigned int height)
		{
			SendMessage(window->windowHandle, (UINT)WM_SETICON, ICON_BIG,
				(LPARAM)LoadImage(window->instanceHandle, icon, IMAGE_ICON, (int)width, (int)height, LR_LOADFROMFILE));
		}

#elif defined(TW_LINUX)

		Display*			currentDisplay;
		XEvent				currentEvent;

		tWindow* GetWindowByHandle(Window windowHandle)
		{
			for(unsigned int windowIndex = 0; windowIndex < windowList.size(); windowIndex++)
			{
				if (windowList[windowIndex]->windowHandle == windowHandle)
				{
					return windowList[windowIndex].get();
				}
			}
			return nullptr;
		}

		tWindow* GetWindowByEvent(XEvent currentEvent)
		{
			switch(currentEvent.type)
			{
				case Expose:
				{
					return GetWindowByHandle(currentEvent.xexpose.window);
				}

				case DestroyNotify:
				{
					return GetWindowByHandle(currentEvent.xdestroywindow.window);
				}

				case CreateNotify:
				{
					return GetWindowByHandle(currentEvent.xcreatewindow.window);
				}

				case KeyPress:
				{
					return GetWindowByHandle(currentEvent.xkey.window);
				}

				case KeyRelease:
				{
					return GetWindowByHandle(currentEvent.xkey.window);
				}

				case ButtonPress:
				{
					return GetWindowByHandle(currentEvent.xbutton.window);
				}

				case ButtonRelease:
				{
					return GetWindowByHandle(currentEvent.xbutton.window);
				}

				case MotionNotify:
				{
					return GetWindowByHandle(currentEvent.xmotion.window);
				}

				case FocusIn:
				{
					return GetWindowByHandle(currentEvent.xfocus.window);
				}

				case FocusOut:
				{
					return GetWindowByHandle(currentEvent.xfocus.window);
				}

				case ResizeRequest:
				{
					return GetWindowByHandle(currentEvent.xresizerequest.window);
				}

				case ConfigureNotify:
				{
					return GetWindowByHandle(currentEvent.xconfigure.window);
				}

				case PropertyNotify:
				{
					return GetWindowByHandle(currentEvent.xproperty.window);
				}

				case GravityNotify:
				{
					return GetWindowByHandle(currentEvent.xgravity.window);
				}

				case ClientMessage:
				{
					return GetWindowByHandle(currentEvent.xclient.window);
				}

				case VisibilityNotify:
				{
					return GetWindowByHandle(currentEvent.xvisibility.window);
				}

				default:
				{
					return nullptr;
				}
			}
		}

		std::error_code Linux_InitializeWindow(tWindow* window)
		{
			window->attributes = new int[ 5]{
				GLX_RGBA,
				GLX_DOUBLEBUFFER,
				GLX_DEPTH_SIZE,
				window->depthBits,
				None};

			window->linuxDecorators = 1;
			window->currentStyle |= window->linuxClose | window->linuxMaximize | window->linuxMinimize | window->linuxMove;

			if (!currentDisplay)
			{
				return TinyWindow::error_t::linuxCannotConnectXServer;
			}

			//window->VisualInfo = glXGetVisualFromFBConfig(GetDisplay(), GetBestFrameBufferConfig(window));

			window->visualInfo = glXChooseVisual(currentDisplay, 0, window->attributes);

			if (!window->visualInfo)
			{
				return TinyWindow::error_t::linuxInvalidVisualinfo;
			}

			window->setAttributes.colormap = XCreateColormap(currentDisplay,
				DefaultRootWindow(currentDisplay),
				window->visualInfo->visual, AllocNone);

			window->setAttributes.event_mask = ExposureMask | KeyPressMask
				| KeyReleaseMask | MotionNotify | ButtonPressMask | ButtonReleaseMask
				| FocusIn | FocusOut | Button1MotionMask | Button2MotionMask | Button3MotionMask |
				Button4MotionMask | Button5MotionMask | PointerMotionMask | FocusChangeMask
				| VisibilityChangeMask | PropertyChangeMask | SubstructureNotifyMask;

			window->windowHandle = XCreateWindow(currentDisplay,
				XDefaultRootWindow(currentDisplay), 0, 0,
				window->resolution.width, window->resolution.height,
				0, window->visualInfo->depth, InputOutput,
				window->visualInfo->visual, CWColormap | CWEventMask,
				&window->setAttributes);

			if(!window->windowHandle)
			{
				return TinyWindow::error_t::linuxCannotCreateWindow;
				exit(0);
			}

			XMapWindow(currentDisplay, window->windowHandle);
			XStoreName(currentDisplay, window->windowHandle,
				window->name);

			XSetWMProtocols(currentDisplay, window->windowHandle, &window->AtomClose, true);

			window->currentDisplay = currentDisplay;
			Platform_InitializeGL(window);

			return TinyWindow::error_t::success;
		}

		void Linux_ShutdownWindow(tWindow* window)
		{
			XDestroyWindow(currentDisplay, window->windowHandle);
		}

		void Linux_Shutdown()
		{
			for(unsigned int windowIndex = 0; windowIndex < windowList.size(); windowIndex++)
			{
				Linux_ShutdownWindow(windowList[windowIndex].get());
			}

			XCloseDisplay(currentDisplay);
		}

		void Linux_ProcessEvents(XEvent currentEvent)
		{
			tWindow* window = GetWindowByEvent(currentEvent);

			switch (currentEvent.type)
			{
				case Expose:
				{
					break;
				}

				case DestroyNotify:
				{
					if (window->destroyedEvent != nullptr)
					{
						window->destroyedEvent();
					}

					ShutdownWindow(window);
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
				} */

				case KeyPress:
				{
					unsigned int functionKeysym = XkbKeycodeToKeysym(
						currentDisplay, currentEvent.xkey.keycode, 0, currentEvent.xkey.state & ShiftMask ? 1 : 0);

						unsigned int translatedKey = Linux_TranslateKey(functionKeysym);
						window->keys[ translatedKey] = keyState_t::down;
						if (window->keyEvent != nullptr)
						{
							window->keyEvent(translatedKey, keyState_t::down);
						}

					break;
				}

				case KeyRelease:
				{
					bool isRetriggered = false;
					if (XEventsQueued(currentDisplay, QueuedAfterReading))
					{
						XEvent nextEvent;
						XPeekEvent(currentDisplay, &nextEvent);

						if (nextEvent.type == KeyPress &&
							nextEvent.xkey.time == currentEvent.xkey.time &&
							nextEvent.xkey.keycode == currentEvent.xkey.keycode)
						{
							unsigned int functionKeysym = XkbKeycodeToKeysym(
								currentDisplay, currentEvent.xkey.keycode, 0,
								currentEvent.xkey.state & ShiftMask ? 1 : 0);

							XNextEvent(currentDisplay, &currentEvent);
							window->keyEvent(Linux_TranslateKey(functionKeysym), keyState_t::down);
							isRetriggered = true;
						}
					}

					if (!isRetriggered)
					{
						unsigned int functionKeysym = XkbKeycodeToKeysym(
						currentDisplay, currentEvent.xkey.keycode, 0, currentEvent.xkey.state & ShiftMask ? 1 : 0);

						unsigned int translatedKey = Linux_TranslateKey(functionKeysym);
						window->keys[ translatedKey] = keyState_t::up;
						if (window->keyEvent != nullptr)
						{
							window->keyEvent(translatedKey, keyState_t::up);
						}
					}

					break;
				}

				case ButtonPress:
				{
					switch (currentEvent.xbutton.button)
					{
					case 1:
					{
						window->mouseButton[ (unsigned int)mouseButton_t::left] = buttonState_t::down;

						if (window->mouseButtonEvent != nullptr)
						{
							window->mouseButtonEvent(mouseButton_t::left, buttonState_t::down);
						}
						break;
					}

					case 2:
					{
						window->mouseButton[ (unsigned int)mouseButton_t::middle] = buttonState_t::down;

						if (window->mouseButtonEvent != nullptr)
						{
							window->mouseButtonEvent(mouseButton_t::middle, buttonState_t::down);
						}
						break;
					}

					case 3:
					{
						window->mouseButton[ (unsigned int)mouseButton_t::right] = buttonState_t::down;

						if (window->mouseButtonEvent != nullptr)
						{
							window->mouseButtonEvent(mouseButton_t::right, buttonState_t::down);
						}
						break;
					}

					case 4:
					{
						window->mouseButton[ (unsigned int)mouseScroll_t::up] = buttonState_t::down;

						if (window->mouseWheelEvent != nullptr)
						{
							window->mouseWheelEvent(mouseScroll_t::down);
						}
						break;
					}

					case 5:
					{
						window->mouseButton[ (unsigned int)mouseScroll_t::down] = buttonState_t::down;

						if (window->mouseWheelEvent != nullptr)
						{
							window->mouseWheelEvent(mouseScroll_t::down);
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
					switch (currentEvent.xbutton.button)
					{
					case 1:
					{
						//the left mouse button was released
						window->mouseButton[ (unsigned int)mouseButton_t::left] = buttonState_t::up;

						if (window->mouseButtonEvent != nullptr)
						{
							window->mouseButtonEvent(mouseButton_t::left, buttonState_t::up);
						}
						break;
					}

					case 2:
					{
						//the middle mouse button was released
						window->mouseButton[ (unsigned int)mouseButton_t::middle] = buttonState_t::up;

						if (window->mouseButtonEvent != nullptr)
						{
							window->mouseButtonEvent(mouseButton_t::middle, buttonState_t::up);
						}
						break;
					}

					case 3:
					{
						//the right mouse button was released
						window->mouseButton[ (unsigned int)mouseButton_t::right] = buttonState_t::up;

						if (window->mouseButtonEvent != nullptr)
						{
							window->mouseButtonEvent(mouseButton_t::right, buttonState_t::up);
						}
						break;
					}

					case 4:
					{
						//the mouse wheel was scrolled up
						window->mouseButton[ (unsigned int)mouseScroll_t::up] = buttonState_t::down;
						break;
					}

					case 5:
					{
						//the mouse wheel was scrolled down
						window->mouseButton[ (unsigned int)mouseScroll_t::down] = buttonState_t::down;
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
					window->mousePosition.x =
						currentEvent.xmotion.x;

					window->mousePosition.y =
						currentEvent.xmotion.y;

					///set the screen mouse position to match the event
					screenMousePosition.x = currentEvent.xmotion.x_root;
					screenMousePosition.y = currentEvent.xmotion.y_root;

					if (window->mouseMoveEvent != nullptr)
					{
						window->mouseMoveEvent( vec2_t<int>(currentEvent.xmotion.x,
							currentEvent.xmotion.y), vec2_t<int>(currentEvent.xmotion.x_root,
							currentEvent.xmotion.y_root));
					}
					break;
				}

				//when the window goes out of focus
				case FocusOut:
				{
					window->inFocus = false;
					if (window->focusEvent != nullptr)
					{
						window->focusEvent(
							window->inFocus);
					}
					break;
				}

				//when the window is back in focus (use to call restore callback?)
				case FocusIn:
				{
					window->inFocus = true;

					if (window->focusEvent != nullptr)
					{
						window->focusEvent(window->inFocus);
					}
					break;
				}

				//when a request to resize the window is made either by
				//dragging out the window or programmatically
				case ResizeRequest:
				{
					window->resolution.width = currentEvent.xresizerequest.width;
					window->resolution.height = currentEvent.xresizerequest.height;

					glViewport(0, 0,
						window->resolution.width,
						window->resolution.height);

					if (window->resizeEvent != nullptr)
					{
						window->resizeEvent(vec2_t<unsigned int>(currentEvent.xresizerequest.width,
							currentEvent.xresizerequest.height));
					}

					break;
				}

				//when a request to configure the window is made
				case ConfigureNotify:
				{
					glViewport(0, 0, currentEvent.xconfigure.width,
						currentEvent.xconfigure.height);

					//check if window was resized
					if ((unsigned int)currentEvent.xconfigure.width != window->resolution.width
						|| (unsigned int)currentEvent.xconfigure.height != window->resolution.height)
					{
						if (window->resizeEvent != nullptr)
						{
							window->resizeEvent(vec2_t<unsigned int>(currentEvent.xconfigure.width, currentEvent.xconfigure.height));
						}

						window->resolution.width = currentEvent.xconfigure.width;
						window->resolution.height = currentEvent.xconfigure.height;
					}

					//check if window was moved
					if (currentEvent.xconfigure.x != window->position.x
						|| currentEvent.xconfigure.y != window->position.y)
					{
						if (window->movedEvent != nullptr)
						{
							window->movedEvent(vec2_t<int>(currentEvent.xconfigure.x, currentEvent.xconfigure.y));
						}

						window->position.x = currentEvent.xconfigure.x;
						window->position.y = currentEvent.xconfigure.y;
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

					Atom type;
					int format;
					ulong numItems, bytesAfter;
					unsigned char* properties = nullptr;

					XGetWindowProperty(currentDisplay, currentEvent.xproperty.window,
						window->AtomState,
						0, LONG_MAX, false, AnyPropertyType,
						&type, &format, &numItems, &bytesAfter,
						& properties);

					if (properties && (format == 32))
					{
						//go through each property and match it to an existing Atomic state
						for (unsigned int itemIndex = 0; itemIndex < numItems; itemIndex++)
						{
							Atom currentProperty = ((long*)(properties))[ itemIndex];

							if (currentProperty == window->AtomHidden)
							{
								//window was minimized
								if (window->minimizedEvent != nullptr)
								{
									//if the minimized callback for the window was set
									window->minimizedEvent();
								}
							}

							if (currentProperty == window->AtomMaxVert ||
								currentProperty == window->AtomMaxVert)
							{
								//window was maximized
								if (window->maximizedEvent != nullptr)
								{
									//if the maximized callback for the window was set
									window->maximizedEvent();
								}
							}

							if (currentProperty == window->AtomFocused)
							{
								//window is now in focus. we can ignore this is as FocusIn/FocusOut does this anyway
							}

							if (currentProperty == window->AtomDemandsAttention)
							{
								//the window demands user attention
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
					const char* atomName = XGetAtomName(currentDisplay, currentEvent.xclient.message_type);
					if (atomName != nullptr)
					{
						//printf("%s\n", l_AtomName);
					}

					if ((Atom)currentEvent.xclient.data.l[0] == window->AtomClose)
					{
						window->shouldClose = true;
						if(window->destroyedEvent != nullptr)
						{
							window->destroyedEvent();
						}
						break;
					}

					//check if full screen
					if ((Atom)currentEvent.xclient.data.l[1] == window->AtomFullScreen)
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

		//debugging. used to determine what type of event was generated
		static const char* Linux_GetEventType(XEvent currentEvent)
		{
			switch (currentEvent.type)
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
		static unsigned int Linux_TranslateKey(unsigned int keySymbol)
		{
			switch (keySymbol)
			{
			case XK_Escape:
			{
				return escape;
			}

			case XK_space:
			{
				return spacebar;
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
				return keySymbol;
			}
			}
		}

		std::error_code Linux_SetWindowIcon() /*std::unique_ptr<window_t> window, const char* icon, unsigned int width, unsigned int height */
		{
			//sorry :(
			return TinyWindow::error_t::linuxFunctionNotImplemented;
		}

		GLXFBConfig GetBestFrameBufferConfig(tWindow* window)
		{
			const int visualAttributes[ ] =
			{
				GLX_X_RENDERABLE, true,
				GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
				GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
				GLX_RED_SIZE, window->colorBits,
				GLX_GREEN_SIZE, window->colorBits,
				GLX_BLUE_SIZE, window->colorBits,
				GLX_ALPHA_SIZE, window->colorBits,
				GLX_DEPTH_SIZE, window->depthBits,
				GLX_STENCIL_SIZE, window->stencilBits,
				GLX_DOUBLEBUFFER, true,
				None
			};

			int frameBufferCount;
			unsigned int bestBufferConfig;//, bestNumSamples = 0;
			GLXFBConfig* configs = glXChooseFBConfig(currentDisplay, 0, visualAttributes, &frameBufferCount);

			for (int configIndex = 0; configIndex < frameBufferCount; configIndex++)
			{
				XVisualInfo* visualInfo = glXGetVisualFromFBConfig(currentDisplay, configs[configIndex]);

				if (visualInfo)
				{
					//printf("%i %i %i\n", VisInfo->depth, VisInfo->bits_per_rgb, VisInfo->colormap_size);
					int samples, sampleBuffer;
					glXGetFBConfigAttrib(currentDisplay, configs[ configIndex], GLX_SAMPLE_BUFFERS, &sampleBuffer);
					glXGetFBConfigAttrib(currentDisplay, configs[configIndex], GLX_SAMPLES, &samples);

					if (sampleBuffer && samples > -1)
					{
						bestBufferConfig = configIndex;
						//bestNumSamples = samples;
					}
				}

				XFree(visualInfo);
			}

			GLXFBConfig BestConfig = configs[ bestBufferConfig];

			XFree(configs);

			return BestConfig;
		}
#endif
	public:
		static std::unique_ptr<TinyWindow::windowManager> New(void)
		{
			return std::unique_ptr<TinyWindow::windowManager>(new TinyWindow::windowManager());
		}
	};

	inline
	void* twGetGLProc(const char* procname)
	{
#if defined(TW_WINDOWS)
		const auto wgl = wglGetProcAddress(procname);

		return wgl ? wgl : GetProcAddress(GetModuleHandle("OpenGL32.dll"), procname);
#else
#	error TODO ; Implement for the platform
#endif
	}
}

inline
TinyWindow::tWindow::tWindow
	(
		TinyWindow::windowManager& mmanager,
		const char* name,
		vec2_t<unsigned int>& resolution,
		unsigned int colorBits,
		unsigned int depthBits,
		unsigned int stencilBits
	) :
	manager(mmanager)
{
	this->name = name;
	this->resolution = resolution;
	this->colorBits = colorBits;
	this->depthBits = depthBits;
	this->stencilBits = stencilBits;

	this->shouldClose = false;
	this->currentState = state_t::normal;

	this->keyEvent = nullptr;
	this->mouseButtonEvent = nullptr;
	this->mouseWheelEvent = nullptr;
	this->destroyedEvent = nullptr;
	this->maximizedEvent = nullptr;
	this->minimizedEvent = nullptr;
	this->focusEvent = nullptr;
	this->movedEvent = nullptr;
	this->resizeEvent = nullptr;
	this->mouseMoveEvent = nullptr;

	initialized = false;
	contextCreated = false;
	currentStyle = titleBar | icon | border | minimizeButton | maximizeButton | closeButton | sizeableBorder;

#if defined(__linux__)
	context = 0;
#endif
	manager.windowList.emplace_back(this);
	if (!manager.Platform_InitializeWindow(this))
	{
		manager.windowList.back().release();
	}
}

#endif

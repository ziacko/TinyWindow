TinyWindow
==========
![alt tag](https://raw.githubusercontent.com/ziacko/tinywindow/master/TinyWindow_Logo.png)

a cross platform single header window management library


The TinyWindow library was started being developed back in 2014 as a replacement for existing window management APIs such as GLFW and SDL for my own edification.  The API focuses on being flexible, easy to use and using multiple windows simultaneously. The two primary methods of utilizing this library is through the use of the tWindow class and the WindowManager class.


I can be reached at ziyadbarakat@gmail.com

documentation:
Documentation is generated using Doxygen:

    cd Docs
		doxygen Doxyfile

You can then obtain a PDF of the documentation by running:

    cd latex
		make

A file titled `refman.pdf` should be created in that directory.

Known issues:

- exclusive fullscreen / changing monitor settings only works on native X11, not XWayland

- cannot set mouse position in screen in Wayland or XWayland

- cannot change some decorators in some Linux desktop managers like Plasma

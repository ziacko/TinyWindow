TinyWindow
==========

a cross platform single header window management library

The TinyWindow library is a cross-platform (Windows and Linux) open-source project. This project was primarily created to make games however, users are free to use the library for whatever they need. for example a user can have a window for the sole purpose of rendering a scene and have another with the purpose of showing live debugging information without the use of a third party tool.

This is a side project I created that is meant to be served as a much smaller and slimmer version of the Foundation Window API that is housed within a single header file.

The TinyWindow library was started being developed back in 2014 as a replacement for existing window management APIs such as GLFW and SDL for my own edification.  The API focuses on being flexible, easy to use and using multiple windows simultaneously. The two primary methods of utilizing this library is through the use of the Window class and the WindowManager class.

My name is Ziyad Barakat and I am a software engineer with over 3 years of programming experience. my core languages are C, C++, C#, Javascript, HTML, CSS and GLSL.

I can be reached at ziyadbarakat@gmail.com

for info on future updates you can see the project trello <a href="https://trello.com/b/haEI2FMZ/tinywindow">here</a>

documentation:
Documentation is generated using Doxygen:

    cd Docs
		doxygen Doxyfile

You can then obtain a PDF of the documentation by running:

    cd latex
		make

A file titled `refman.pdf` should be created in that directory.

#include "TinyWindow.h"

void blarg(GLuint Key, GLboolean KeyState)
{
	if (Key == ' ' && KeyState == KEYSTATE_DOWN)
	{
		printf("Penish\n");
	}
}


int main()
{
	WindowManager::Initialize();

	WindowManager::AddWindow("Example");

	WindowManager::SetWindowOnKeyEvent("Example", blarg);

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

	while (!WindowManager::GetWindowShouldClose("Example"))
	{
		WindowManager::PollForEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		WindowManager::WindowSwapBuffers("Example");
	}

	WindowManager::ShutDown();
	return 0;
}
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

	WindowManager::AddWindow("Example")->AddWindow("Example2");

	WindowManager::SetWindowOnKeyEvent("Example", blarg);

	while (!WindowManager::GetWindowShouldClose("Example"))
	{
		for(GLuint WindowIndex = 0; WindowIndex < WindowManager::GetNumWindows(); WindowIndex++)
		{
			glClearColor(1.0f, 0.25f, 0.25f, 1.0f);
			WindowManager::PollForEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			WindowManager::MakeWindowCurrentContext(WindowIndex);

			WindowManager::WindowSwapBuffers(WindowIndex);
		}
	}

	WindowManager::ShutDown();
	return 0;
}

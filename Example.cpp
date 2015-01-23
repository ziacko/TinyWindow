#include "TinyWindow.h"

void blarg(GLuint Key, GLboolean KeyState)
{
	{
		//WindowManager::ToggleVerticalSync("Example", 0);
	}
}

int main()
{
	WindowManager::Initialize();

	WindowManager::AddWindow("Example");

	WindowManager::SetWindowOnKeyEvent("Example", blarg);

	while (!WindowManager::GetWindowShouldClose("Example"))
	{ 	
			glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
			WindowManager::PollForEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			WindowManager::MakeWindowCurrentContext("Example");

			WindowManager::WindowSwapBuffers("Example");
	}

	WindowManager::ShutDown();
	return 0;
}

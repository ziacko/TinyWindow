#include "TinyWindow.h"
//#include "TutorialConfig.h"

using namespace TinyWindow;
void handleKeyPresses(unsigned int key, keyState_t keyState)
{
	if(keyState == keyState_t::down)
	{
		printf("%c \t", key);
	}
}

int main()
{
	windowManager* manager = new windowManager();

	manager->AddWindow("Example");
	manager->SetWindowOnKeyEventByName("Example", handleKeyPresses);

	while (!manager->GetWindowShouldCloseByIndex(0))
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		manager->PollForEvents();// or WaitForEvents
		
		manager->MakeWindowCurrentContextByIndex(0);
		manager->WindowSwapBuffersByIndex(0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	manager->ShutDown();
	return 0;
}

#include "Core.h"
#include "LoginState.h"

void run()
{
	RenderWindow window{ {1300, 800}, "MOODLE" };
	Gui gui{ window };
	if (run_login(gui))
		//cerr << 1 << '\n';
		gui.mainLoop();
}
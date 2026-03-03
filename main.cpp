#include "AppWindow.h"

int main()
{
	AppWindow app;
	if (app.init())
	{
		while (app.isRun())
		{
			app.broadcast();
		}
	}
	//asdasd
	return 0;
}
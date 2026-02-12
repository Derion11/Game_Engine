#pragma once
#include "Window.h"

class AppWindow: public Window
{
	public:
		AppWindow();
		~AppWindow();

		// Diwariskan melalui class Window
		void onCreate() override;
		void onUpdate() override;
		void onDestroy() override;

};


#pragma once
#include "Window.h"
#include "GraphicsEngine.h"

class AppWindow: public Window
{
	public:
		AppWindow();
		~AppWindow();

		// Method diwariskan melalui class Window
		void onCreate() override;
		void onUpdate() override;
		void onDestroy() override;

};


#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

class AppWindow: public Window
{
	public:
		AppWindow();
		~AppWindow();

		// Method diwariskan melalui class Window
		void onCreate() override;
		void onUpdate() override;
		void onDestroy() override;
private:
	SwapChain* m_swap_chain; //pointer ke objek SwapChain, digunakan untuk mengelola buffer swap dan menampilkan hasil rendering ke layar

};


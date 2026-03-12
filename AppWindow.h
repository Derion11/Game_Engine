#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

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
	VertexBuffer* m_vb; //pointer ke objek VertexBuffer, digunakan untuk menyimpan data vertex yang akan digunakan dalam rendering grafis
};


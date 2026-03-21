#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"

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
	VertexShader* m_vs; //pointer ke objek VertexShader, digunakan untuk mengatur shader vertex yang akan digunakan dalam pipeline rendering
};


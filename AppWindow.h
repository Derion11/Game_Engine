#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"


class AppWindow: public Window
{
	public:
		AppWindow();

		void updateQuadPosition();

		~AppWindow();

		// Method diwariskan melalui class Window
		void onCreate() override;
		void onUpdate() override;
		void onDestroy() override;
private:
	SwapChain* m_swap_chain; //pointer ke objek SwapChain, digunakan untuk mengelola buffer swap dan menampilkan hasil rendering ke layar
	VertexBuffer* m_vb; //pointer ke objek VertexBuffer, digunakan untuk menyimpan data vertex yang akan digunakan dalam rendering grafis
	VertexShader* m_vs; //pointer ke objek VertexShader, digunakan untuk mengatur shader vertex yang akan digunakan dalam pipeline rendering
	PixelShader* m_ps; //pointer ke objek PixelShader, digunakan untuk mengatur shader pixel yang akan digunakan dalam pipeline rendering
	ConstantBuffer* m_cb; //pointer ke objek ConstantBuffer, digunakan untuk menyimpan data konstan yang akan digunakan dalam rendering, seperti matriks transformasi atau parameter shader lainnya	
private:
	unsigned long m_old_time = 0;
	//float m_delta_time = 0;
	float m_time;

	float m_old_delta;
	float m_new_delta;
	float m_delta_time;

	float m_delta_pos;

};


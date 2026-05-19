#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"


class AppWindow : public Window, public InputListener
{
	public:
		AppWindow();

		void updateQuadPosition();

		~AppWindow();

		// Method diwariskan melalui class Window
		void onCreate() override;
		void onUpdate() override;
		void onDestroy() override;

		// Inherited via InputListener
		void onKeyDown(int key) override;
		void onKeyUp(int key) override;
private:
	SwapChain* m_swap_chain; //pointer ke objek SwapChain, digunakan untuk mengelola buffer swap dan menampilkan hasil rendering ke layar
	VertexBuffer* m_vb; //pointer ke objek VertexBuffer, digunakan untuk menyimpan data vertex yang akan digunakan dalam rendering grafis
	IndexBuffer* m_ib; //pointer ke objek IndexBuffer, digunakan untuk menyimpan data indeks yang akan digunakan dalam rendering grafis
	VertexShader* m_vs; //pointer ke objek VertexShader, digunakan untuk mengatur shader vertex yang akan digunakan dalam pipeline rendering
	PixelShader* m_ps; //pointer ke objek PixelShader, digunakan untuk mengatur shader pixel yang akan digunakan dalam pipeline rendering
	ConstantBuffer* m_cb; //pointer ke objek ConstantBuffer, digunakan untuk menyimpan data konstan yang akan digunakan dalam rendering, seperti matriks transformasi atau parameter shader lainnya	
private:
	float m_old_delta;
	float m_new_delta;
	float m_delta_time;

	float m_time;
	float m_delta_pos;
	float m_delta_scale;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

};


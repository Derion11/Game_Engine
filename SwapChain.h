#pragma once
#include <d3d11.h>
class DeviceContext;
class SwapChain
{
public:
	SwapChain();
	bool init(HWND hwnd, UINT width, UINT height);
	bool present(bool vsync);
	bool release();

	~SwapChain();
private:
	IDXGISwapChain* m_swap_chain; //pointer ke objek swap chain, digunakan untuk mengelola buffer swap dan menampilkan hasil rendering ke layar
	ID3D11RenderTargetView* m_rtv; //pointer ke tampilan target render, digunakan untuk mengarahkan perintah rendering ke buffer belakang swap chain
private:
	friend class DeviceContext;
};


#pragma once
#include <d3d11.h>

class SwapChain
{
public:
	SwapChain();
	bool init(HWND hwnd, UINT width, UINT height);
	bool release();
	//bool present();

	~SwapChain();
private:
	IDXGISwapChain* m_swap_chain; //pointer ke objek swap chain, digunakan untuk mengelola buffer swap dan menampilkan hasil rendering ke layar

};


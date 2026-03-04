#include "DeviceContext.h"
#include "SwapChain.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) :m_device_context(device_context)
{
}

bool DeviceContext::clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red, green, blue, alpha }; //membuat array yang berisi nilai warna yang akan digunakan untuk membersihkan target render
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color); //memanggil metode ClearRenderTargetView pada konteks perangkat DirectX 11 untuk membersihkan target render dengan warna yang ditentukan
	return true;
}

bool DeviceContext::release()
{
	m_device_context->Release();
	delete this;
	return true;
}


DeviceContext::~DeviceContext()
{

}
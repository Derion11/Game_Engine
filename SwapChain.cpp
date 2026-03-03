#include "SwapChain.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::get()->m_d3d_device; // mendapatkan pointer ke perangkat DirectX 11 dari instance GraphicsEngine yang sedang berjalan, memungkinkan SwapChain untuk menggunakan perangkat tersebut untuk membuat swap chain dan mengelola sumber daya grafis
	DXGI_SWAP_CHAIN_DESC desc; // mendefinisikan struktur DXGI_SWAP_CHAIN_DESC yang akan digunakan untuk mengkonfigurasi swap chain, termasuk pengaturan seperti resolusi, format, dan mode jendela
	ZeroMemory(&desc, sizeof(desc)); // menginisialisasi struktur DXGI_SWAP_CHAIN_DESC dengan nol, memastikan bahwa semua anggota struktur memiliki nilai default yang aman sebelum diatur secara eksplisit
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr=GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device,&desc,&m_swap_chain);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool SwapChain::release()
{
	m_swap_chain->Release();
	delete this;
	return true;
}

SwapChain::~SwapChain()
{
}
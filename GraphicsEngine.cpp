#include "GraphicsEngine.h"
#include "SwapChain.h"

GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, //menggunakan driver perangkat keras untuk rendering grafis
		D3D_DRIVER_TYPE_WARP,     //menggunakan driver perangkat lunak WARP (Windows Advanced Rasterization Platform) untuk rendering grafis
		D3D_DRIVER_TYPE_REFERENCE //menggunakan driver referensi untuk rendering grafis, biasanya digunakan untuk pengujian dan debugging
	};
	UINT num_driver_types = ARRAYSIZE(driver_types); // menghitung jumlah elemen dalam array

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0 //menggunakan fitur level 11.0 dari DirectX 11
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);
	
	HRESULT res = 0;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;) //melakukan iterasi melalui jenis driver yang tersedia untuk mencoba membuat perangkat DirectX 11
	{
		res=D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, //menyediakan array fitur level yang ingin digunakan, dalam hal ini hanya satu level yaitu 11.0
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(res)) //memeriksa apakah pembuatan perangkat berhasil
		{
			break;
		}
			++driver_type_index;
	}

	if (FAILED(res))
	{
		return false;
	}

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device); //menggunakan metode QueryInterface untuk mendapatkan pointer ke perangkat DXGI dari perangkat DirectX 11 yang telah dibuat, memungkinkan pengelolaan sumber daya grafis dan swap chain
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
	
	//m_dxgi_factory->CreateSwapChain(m_d3d_device, &SwapChain::get()->get_desc(), &SwapChain::get()->get_swap_chain()); //membuat swap chain menggunakan pabrik DXGI, yang akan digunakan untuk menampilkan hasil rendering ke layar


	return true;
}

bool GraphicsEngine::release()
{
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_context->Release();
	m_d3d_device->Release();
	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}

SwapChain * GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

GraphicsEngine * GraphicsEngine::get()
{
	static GraphicsEngine engine; //membuat instance tunggal dari kelas GraphicsEngine yang akan digunakan secara global
	return &engine;
}

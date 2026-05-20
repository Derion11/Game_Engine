#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include <d3dcompiler.h> // header yang menyediakan fungsi untuk mengkompilasi shader dari file sumber.

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

	m_imm_device_context = new DeviceContext(m_imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device); //menggunakan metode QueryInterface untuk mendapatkan pointer ke perangkat DXGI dari perangkat DirectX 11 yang telah dibuat, memungkinkan pengelolaan sumber daya grafis dan swap chain
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}

bool GraphicsEngine::release()
{
	if (m_vs)m_vs->Release();
	if (m_ps)m_ps->Release();

	if (m_vsblob)m_vsblob->Release();
	if (m_psblob)m_psblob->Release();

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_device_context->release();

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

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return this -> m_imm_device_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

IndexBuffer* GraphicsEngine::createIndexBuffer()
{
	return new IndexBuffer();
}

ConstantBuffer* GraphicsEngine::createConstantBuffer()
{

	return new ConstantBuffer();
}

VertexShader* GraphicsEngine::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = new VertexShader();

	if (!vs->init(shader_byte_code, byte_code_size)) //memanggil metode init pada objek VertexShader yang baru dibuat untuk menginisialisasi shader vertex dengan byte code shader yang diberikan, memungkinkan pembuatan shader vertex yang akan digunakan dalam pipeline rendering
	{
		vs->release(); //jika inisialisasi gagal, objek VertexShader akan dihapus untuk mencegah kebocoran memori
		return nullptr;
	}

	return vs;
}

PixelShader* GraphicsEngine::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader();

	if (!ps->init(shader_byte_code, byte_code_size)) // memanggil metode init pada objek PixelShader yang baru dibuat untuk menginisialisasi shader pixel dengan byte code shader yang diberikan, memungkinkan pembuatan shader pixel yang akan digunakan dalam pipeline rendering
	{
		ps->release(); //jika inisialisasi gagal, objek PixelShader akan dihapus untuk mencegah kebocoran memori
		return nullptr;
	}

	return ps;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if(!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob))) //menggunakan fungsi D3DCompileFromFile untuk mengkompilasi shader vertex dari file sumber yang diberikan, menghasilkan byte code shader yang disimpan dalam m_vsblob untuk digunakan dalam konfigurasi buffer vertex dan pipeline rendering
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer(); //mengambil pointer ke byte code shader yang dihasilkan dari proses kompilasi dan menyimpannya dalam variabel shader_byte_code, memungkinkan akses ke byte code shader yang diperlukan untuk konfigurasi buffer vertex dan pipeline rendering
	*byte_code_size = m_blob->GetBufferSize(); //mengambil ukuran byte code shader yang dihasilkan dari proses kompilasi dan menyimpannya dalam variabel byte_code_size, memungkinkan akses ke informasi ukuran byte code shader yang diperlukan untuk konfigurasi buffer vertex dan pipeline rendering
	return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob))) //menggunakan fungsi D3DCompileFromFile untuk mengkompilasi shader vertex dari file sumber yang diberikan, menghasilkan byte code shader yang disimpan dalam m_vsblob untuk digunakan dalam konfigurasi buffer vertex dan pipeline rendering
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();
	return true;
}

void GraphicsEngine::releaseCompiledShaders()
{
	if (m_blob)m_blob->Release(); //melepaskan sumber daya yang digunakan untuk shader vertex yang telah dikompilasi, memungkinkan pembersihan sumber daya yang terkait dengan shader vertex yang telah dikompilasi untuk mencegah kebocoran memori
}

GraphicsEngine * GraphicsEngine::get()
{
	static GraphicsEngine engine; //membuat instance tunggal dari kelas GraphicsEngine yang akan digunakan secara global
	return &engine;
}

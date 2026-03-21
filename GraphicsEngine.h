#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;
class VertexShader;

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool init();	//inisialisasi engine grafis dan device DirectX 11
	bool release(); //melepaskan sumber daya yang digunakan oleh engine grafis
	~GraphicsEngine();

public:
	SwapChain * createSwapChain();
	DeviceContext* getImmediateDeviceContext(); //mengembalikan pointer ke konteks perangkat langsung (immediate device context) yang digunakan untuk mengirim perintah rendering ke GPU, memungkinkan akses ke konteks perangkat untuk operasi rendering
	VertexBuffer* createVertexBuffer(); //membuat dan mengembalikan pointer ke objek VertexBuffer baru, memungkinkan pembuatan buffer vertex untuk menyimpan data vertex yang akan digunakan dalam rendering grafis
	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size); //membuat dan mengembalikan pointer ke objek VertexShader baru, memungkinkan pembuatan shader vertex untuk digunakan dalam pipeline rendering
public:
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShaders(); //melepaskan sumber daya yang digunakan untuk shader yang telah dikompilasi, memungkinkan pembersihan sumber daya yang terkait dengan shader yang telah dikompilasi untuk mencegah kebocoran memori
	//DEFAULT SHADER SEDERHANA
	bool createShaders(); //membuat shader yang akan digunakan dalam rendering grafis, memungkinkan pembuatan dan pengelolaan shader untuk digunakan dalam pipeline rendering
	bool setShaders(); //mengatur shader yang akan digunakan dalam rendering grafis, memungkinkan pengaturan shader aktif yang akan digunakan dalam pipeline rendering
public:
	static GraphicsEngine* get(); //mengembalikan referensi ke instance tunggal dari kelas GraphicsEngine, memungkinkan akses global ke engine grafis
private:
	DeviceContext* m_imm_device_context;
private:
	ID3D11Device* m_d3d_device; //pointer ke perangkat DirectX 11
	D3D_FEATURE_LEVEL m_feature_level; //menyimpan level fitur yang digunakan oleh perangkat DirectX 11
private:
	IDXGIDevice* m_dxgi_device; //pointer ke perangkat DXGI, digunakan untuk mengelola sumber daya grafis dan swap chain
	IDXGIAdapter* m_dxgi_adapter; //pointer ke adapter DXGI, digunakan untuk mengelola perangkat keras grafis yang tersedia
	IDXGIFactory* m_dxgi_factory; //pointer ke pabrik DXGI, digunakan untuk membuat swap chain dan objek terkait lainnya
	ID3D11DeviceContext* m_imm_context; //pointer ke konteks perangkat DirectX 11, digunakan untuk mengirim perintah rendering ke GPU

private:
	ID3DBlob* m_blob = nullptr; //pointer ke blob yang menyimpan byte code shader, digunakan untuk konfigurasi buffer vertex dan pipeline rendering, memungkinkan penyimpanan dan pengelolaan byte code shader yang diperlukan untuk rendering grafis

	ID3DBlob* m_vsblob = nullptr; //pointer ke blob yang menyimpan byte code shader vertex, digunakan untuk konfigurasi buffer vertex dan pipeline rendering	
	ID3DBlob* m_psblob = nullptr; //pointer ke blob yang menyimpan byte code shader pixel, digunakan untuk konfigurasi pipeline rendering
	ID3D11VertexShader* m_vs = nullptr; //pointer ke shader vertex DirectX 11, digunakan untuk mengatur shader vertex yang akan digunakan dalam pipeline rendering
	ID3D11PixelShader* m_ps = nullptr; //pointer ke shader pixel DirectX 11, digunakan untuk mengatur shader pixel yang akan digunakan dalam pipeline rendering
private:
	friend class SwapChain; //menyatakan kelas SwapChain sebagai teman dari kelas GraphicsEngine, memungkinkan SwapChain untuk mengakses anggota pribadi dari GraphicsEngine
	friend class VertexBuffer;
	friend class VertexShader;
};


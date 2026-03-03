#pragma once
#include <d3d11.h>
class SwapChain;

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool init();	//inisialisasi engine grafis dan device DirectX 11
	bool release(); //melepaskan sumber daya yang digunakan oleh engine grafis
	~GraphicsEngine();

public:
	SwapChain * createSwapChain();
public:
	static GraphicsEngine* get(); //mengembalikan referensi ke instance tunggal dari kelas GraphicsEngine, memungkinkan akses global ke engine grafis
private:
	ID3D11Device* m_d3d_device; //pointer ke perangkat DirectX 11
	D3D_FEATURE_LEVEL m_feature_level; //menyimpan level fitur yang digunakan oleh perangkat DirectX 11
	ID3D11DeviceContext* m_imm_context; //pointer ke konteks perangkat DirectX 11, digunakan untuk mengirim perintah rendering ke GPU
private:
	IDXGIDevice* m_dxgi_device; //pointer ke perangkat DXGI, digunakan untuk mengelola sumber daya grafis dan swap chain
	IDXGIAdapter* m_dxgi_adapter; //pointer ke adapter DXGI, digunakan untuk mengelola perangkat keras grafis yang tersedia
	IDXGIFactory* m_dxgi_factory; //pointer ke pabrik DXGI, digunakan untuk membuat swap chain dan objek terkait lainnya
private:
	friend class SwapChain; //menyatakan kelas SwapChain sebagai teman dari kelas GraphicsEngine, memungkinkan SwapChain untuk mengakses anggota pribadi dari GraphicsEngine

};


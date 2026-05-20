#pragma once
#include <d3d11.h>

class DeviceContext;

class ConstantBuffer

{
public:
	ConstantBuffer();
	bool load(void* buffer, UINT size_buffer);
	void update(DeviceContext* context, void* buffer);
	bool release();
	~ConstantBuffer();
private:
	ID3D11Buffer* m_buffer; //pointer ke buffer DirectX 11 yang digunakan untuk menyimpan data vertex, memungkinkan penyimpanan dan pengelolaan data vertex yang akan digunakan dalam rendering grafis
private:
	friend class DeviceContext; //menyatakan kelas DeviceContext sebagai teman dari kelas VertexBuffer, memungkinkan DeviceContext untuk mengakses anggota pribadi dari VertexBuffer
};


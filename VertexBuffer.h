#pragma once
#include <d3d11.h>

class DeviceContext;

class VertexBuffer

{
public:
	VertexBuffer();
	bool load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	//bool getSizeVertexList();
	bool release();
	~VertexBuffer();
private:
	UINT m_size_vertex;
	UINT m_size_list;
private:
	ID3D11Buffer* m_buffer; //pointer ke buffer DirectX 11 yang digunakan untuk menyimpan data vertex, memungkinkan penyimpanan dan pengelolaan data vertex yang akan digunakan dalam rendering grafis
	ID3D11InputLayout* m_layout; //pointer ke layout input DirectX 11 yang digunakan untuk mendefinisikan format data vertex, memungkinkan pengaturan bagaimana data vertex diinterpretasikan dan digunakan dalam pipeline rendering
private:
	friend class DeviceContext; //menyatakan kelas DeviceContext sebagai teman dari kelas VertexBuffer, memungkinkan DeviceContext untuk mengakses anggota pribadi dari VertexBuffer
};


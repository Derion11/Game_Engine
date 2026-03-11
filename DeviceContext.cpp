#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"


DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) :m_device_context(device_context)
{
}

void DeviceContext::clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red, green, blue, alpha }; //membuat array yang berisi nilai warna yang akan digunakan untuk membersihkan target render
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color); //memanggil metode ClearRenderTargetView pada konteks perangkat DirectX 11 untuk membersihkan target render dengan warna yang ditentukan
}

void DeviceContext::setVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex; //mengambil ukuran setiap vertex dari anggota kelas VertexBuffer untuk digunakan sebagai stride dalam pengaturan buffer vertex
	UINT offset = 0; //menetapkan offset ke 0, menunjukkan bahwa data vertex akan dimulai dari awal buffer
	m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset); //memanggil metode IASetVertexBuffers pada konteks perangkat DirectX 11 untuk mengatur buffer vertex yang akan digunakan dalam rendering, dengan menentukan slot input, jumlah buffer, pointer ke buffer, stride, dan offset
	m_device_context->IASetInputLayout(vertex_buffer->m_layout); //memanggil metode IASetInputLayout pada konteks perangkat DirectX 11 untuk mengatur layout input yang sesuai dengan format data vertex yang digunakan dalam buffer vertex
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
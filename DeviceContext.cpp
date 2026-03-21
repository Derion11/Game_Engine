#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) :m_device_context(device_context)
{
}

void DeviceContext::clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red, green, blue, alpha }; //membuat array yang berisi nilai warna yang akan digunakan untuk membersihkan target render
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color); //memanggil metode ClearRenderTargetView pada konteks perangkat DirectX 11 untuk membersihkan target render dengan warna yang ditentukan
	m_device_context->OMSetRenderTargets(1, &swap_chain->m_rtv, NULL); //memanggil metode OMSetRenderTargets pada konteks perangkat DirectX 11 untuk mengatur target render yang akan digunakan dalam rendering, dengan menentukan jumlah target, pointer ke target render, dan pointer ke depth stencil view (dalam hal ini, tidak digunakan sehingga diatur ke nullptr)
}

void DeviceContext::setVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex; //mengambil ukuran setiap vertex dari anggota kelas VertexBuffer untuk digunakan sebagai stride dalam pengaturan buffer vertex
	UINT offset = 0; //menetapkan offset ke 0, menunjukkan bahwa data vertex akan dimulai dari awal buffer
	m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset); //memanggil metode IASetVertexBuffers pada konteks perangkat DirectX 11 untuk mengatur buffer vertex yang akan digunakan dalam rendering, dengan menentukan slot input, jumlah buffer, pointer ke buffer, stride, dan offset
	m_device_context->IASetInputLayout(vertex_buffer->m_layout); //memanggil metode IASetInputLayout pada konteks perangkat DirectX 11 untuk mengatur layout input yang sesuai dengan format data vertex yang digunakan dalam buffer vertex
}

void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); //memanggil metode IASetPrimitiveTopology pada konteks perangkat DirectX 11 untuk mengatur topologi primitif menjadi triangle list, yang menunjukkan bahwa setiap tiga vertex akan membentuk sebuah segitiga
	m_device_context->Draw(vertex_count, start_vertex_index); //memanggil metode Draw pada konteks perangkat DirectX 11 untuk menggambar segitiga berdasarkan jumlah vertex yang ditentukan dan indeks awal vertex
}

void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT start_vertex_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); //memanggil metode IASetPrimitiveTopology pada konteks perangkat DirectX 11 untuk mengatur topologi primitif menjadi triangle strip, yang menunjukkan bahwa setiap vertex setelah dua vertex pertama akan membentuk segitiga dengan dua vertex sebelumnya
	m_device_context->Draw(vertex_count, start_vertex_index); //memanggil metode Draw pada konteks perangkat DirectX 11 untuk menggambar segitiga berdasarkan jumlah vertex yang ditentukan dan indeks awal vertex
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp{}; //membuat struktur D3D11_VIEWPORT untuk menyimpan informasi tentang ukuran dan posisi viewport
	vp.Width = width;  
	vp.Height = height;
	vp.MinDepth = 0.0f; //menetapkan nilai minimum depth untuk viewport ke 0.0f
	vp.MaxDepth = 1.0f; //menetapkan nilai maksimum depth untuk viewport ke 1.0f
	m_device_context->RSSetViewports(1, &vp); //memanggil metode RSSetViewports pada konteks perangkat DirectX 11 untuk mengatur viewport yang akan digunakan dalam rendering, dengan menentukan jumlah viewport dan pointer ke struktur viewport
}

void DeviceContext::setVertexShader(VertexShader* vertex_shader)
{
	m_device_context->VSSetShader(vertex_shader->m_vs, nullptr, 0); //memanggil metode VSSetShader pada konteks perangkat DirectX 11 untuk mengatur shader vertex yang akan digunakan dalam pipeline rendering, dengan menentukan pointer ke shader vertex, pointer ke array class instance (dalam hal ini, tidak digunakan sehingga diatur ke nullptr), dan jumlah class instance (dalam hal ini, tidak digunakan sehingga diatur ke 0)
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
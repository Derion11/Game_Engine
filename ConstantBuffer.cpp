#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

ConstantBuffer::ConstantBuffer()
{
}

bool ConstantBuffer::load(void* buffer, UINT size_buffer)
{
	if (m_buffer)m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_buffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // menetapkan flag pengikatan buffer ke constant buffer, menunjukkan bahwa buffer ini akan digunakan untuk menyimpan data konstan yang akan digunakan dalam rendering, seperti matriks transformasi atau parameter shader lainnya
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0; 

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;


	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		return false;
	}


	
	return true;
}

void ConstantBuffer::update(DeviceContext* context, void* buffer)
{
	context->m_device_context->UpdateSubresource(this->m_buffer, NULL, NULL, buffer, NULL, NULL); //memanggil metode UpdateSubresource pada konteks perangkat DirectX 11 untuk memperbarui data dalam buffer konstan dengan data baru yang diberikan, memungkinkan perubahan nilai konstan yang digunakan dalam rendering tanpa perlu membuat buffer baru
}

bool ConstantBuffer::release()
{
	if (m_buffer)m_buffer->Release();
	delete this;
	return true;
}

ConstantBuffer::~ConstantBuffer()
{
}

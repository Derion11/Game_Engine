#include "IndexBuffer.h"
#include "GraphicsEngine.h"

IndexBuffer::IndexBuffer() :m_buffer(0)
{
}

bool IndexBuffer::load(void* list_indices, UINT size_list)
{
	if (m_buffer)m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT; //menetapkan penggunaan buffer ke default, yang berarti buffer akan digunakan untuk operasi rendering biasa
	buff_desc.ByteWidth = 4 * size_list; //menghitung ukuran total buffer dalam byte dengan mengalikan ukuran setiap vertex dengan jumlah vertex dalam daftar
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER; //menetapkan flag pengikatan buffer ke vertex buffer, menunjukkan bahwa buffer ini akan digunakan untuk menyimpan data vertex yang akan digunakan dalam rendering
	buff_desc.CPUAccessFlags = 0; //menetapkan flag akses CPU ke 0, menunjukkan bahwa buffer tidak akan diakses langsung oleh CPU setelah dibuat
	buff_desc.MiscFlags = 0; //menetapkan flag tambahan ke 0, menunjukkan bahwa tidak ada pengaturan khusus yang diterapkan pada buffer

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_indices; //menetapkan pointer ke data vertex yang akan digunakan untuk menginisialisasi buffer, dengan menunjuk ke daftar vertex yang diberikan sebagai parameter

	m_size_list = size_list;

	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		return false;
	}

	return true;
}

UINT IndexBuffer::getSizeIndexList()
{
	return this->m_size_list;
}

bool IndexBuffer::release()
{
	m_buffer->Release();
	delete this;
	return true;
}

IndexBuffer::~IndexBuffer()
{
}
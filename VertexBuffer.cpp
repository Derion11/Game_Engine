#include "VertexBuffer.h"
#include "GraphicsEngine.h"

VertexBuffer::VertexBuffer():m_layout(0), m_buffer(0)
{
}

bool VertexBuffer::load(void* list_vertices, UINT size_vertex, UINT size_list, void*shader_byte_code, UINT size_byte_shader)
{
	if (m_buffer)m_buffer->Release();
	if (m_layout)m_layout->Release();


	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT; //menetapkan penggunaan buffer ke default, yang berarti buffer akan digunakan untuk operasi rendering biasa
	buff_desc.ByteWidth = size_vertex * size_list; //menghitung ukuran total buffer dalam byte dengan mengalikan ukuran setiap vertex dengan jumlah vertex dalam daftar
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; //menetapkan flag pengikatan buffer ke vertex buffer, menunjukkan bahwa buffer ini akan digunakan untuk menyimpan data vertex yang akan digunakan dalam rendering
	buff_desc.CPUAccessFlags = 0; //menetapkan flag akses CPU ke 0, menunjukkan bahwa buffer tidak akan diakses langsung oleh CPU setelah dibuat
	buff_desc.MiscFlags = 0; //menetapkan flag tambahan ke 0, menunjukkan bahwa tidak ada pengaturan khusus yang diterapkan pada buffer

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices; //menetapkan pointer ke data vertex yang akan digunakan untuk menginisialisasi buffer, dengan menunjuk ke daftar vertex yang diberikan sebagai parameter

	m_size_vertex = size_vertex; //menyimpan ukuran setiap vertex dalam anggota kelas untuk referensi di masa mendatang
	m_size_list = size_list;
	
	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)));
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
	{
		return false;
	}



	return true;
}

UINT VertexBuffer::getSizeVertexList()
{
	return this->m_size_list;
}

bool VertexBuffer::release()
{
	m_layout->Release();
	m_buffer->Release();
	delete this;
	return true;
}

VertexBuffer::~VertexBuffer()
{
}
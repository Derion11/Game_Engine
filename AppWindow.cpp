#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init(); //memanggil metode init() dari kelas GraphicsEngine untuk menginisialisasi engine grafis dan perangkat DirectX 11 saat jendela dibuat
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	
	RECT rc = this->getClientWindowRect(); //memanggil metode getClientWindowRect() dari kelas Window untuk mendapatkan ukuran jendela klien, yang akan digunakan untuk mengkonfigurasi swap chain agar sesuai dengan ukuran jendela
	m_swap_chain->init(this->m_hwnd,rc.right-rc.left, rc.bottom-rc.top);

	vertex list[] =
	{
		//Koordinat segitiga dalam ruang 3D -> {x, y, z}
		{-0.5f, -0.5f, 0.0f },	// Vertex 1
		{ -0.5f, 0.5f, 0.0f },	// Vertex 2
		{ 0.5f, 0.5f, 0.0f },	// Vertex 3


		{0.5f, 0.5f, 0.0f },	// V4
		{ 0.5f, -0.5f, 0.0f },	// V5
		{ -0.5f, -0.5f, 0.0f }	// V6
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer(); //memanggil metode createVertexBuffer() dari kelas GraphicsEngine untuk membuat buffer vertex baru yang akan digunakan untuk menyimpan data vertex segitiga
	UINT size_list = ARRAYSIZE(list);
	
	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr; //mendeklarasikan pointer void untuk menyimpan byte code shader, yang akan digunakan untuk mengonfigurasi buffer vertex agar sesuai dengan format data vertex yang digunakan dalam shader
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader); //memanggil metode getShaderBufferAndSize() dari kelas GraphicsEngine untuk mendapatkan pointer ke byte code shader dan ukuran byte code, yang akan digunakan untuk mengonfigurasi buffer vertex agar sesuai dengan format data vertex yang digunakan dalam shader
	
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader); //memanggil metode load() pada objek VertexBuffer untuk memuat data vertex segitiga ke dalam buffer vertex, dengan menentukan pointer ke daftar vertex, ukuran setiap vertex, jumlah vertex dalam daftar, dan parameter tambahan untuk shader byte code (dalam hal ini, tidak digunakan sehingga diatur ke nullptr dan 0)


}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get()->setShaders();

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

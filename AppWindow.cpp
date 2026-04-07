#include "AppWindow.h"
#include <Windows.h>

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

__declspec(align(16))  //menyatakan struktur constant dengan atribut align(16) untuk memastikan bahwa data dalam buffer konstan diatur pada batas memori 16 byte, yang diperlukan untuk kinerja optimal dalam rendering grafis menggunakan DirectX 11
struct constant
{
	float m_angle;
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
		//Koordinat quad dalam ruang 3D -> {x, y, z} dengan drawTriangleStrip.
		{-0.5f, -0.5f, 0.0f,	-0.32f,-0.11f,0.0f,		0,0,0,	0,1,0},	// Vertex 1
		{ -0.5f, 0.5f, 0.0f,	-0.11f,0.78f,0.0f,		1,1,0,	0,1,1},	// Vertex 2
		{ 0.5f, -0.5f, 0.0f,	0.75f,-0.73f,0.0f,		0,0,1,	0,1,0},	// Vertex 3
		{ 0.5f, 0.5f, 0.0f,		0.88f, 0.77f,0.0f,		1,1,1,	1,0,0}	// V4

		//Koordinat quad dalam ruang 3D -> {x, y, z} drawTriangleList.
		//{-0.5f, -0.5f, 0.0f },	// Vertex 1
		//{ -0.5f, 0.5f, 0.0f },	// Vertex 2
		//{ 0.5f, 0.5f, 0.0f },		// Vertex 3
		//{0.5f, 0.5f, 0.0f },		// V4
		//{ 0.5f, -0.5f, 0.0f },	// V5
		//{ -0.5f, -0.5f, 0.0f }	// V6
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer(); //memanggil metode createVertexBuffer() dari kelas GraphicsEngine untuk membuat buffer vertex baru yang akan digunakan untuk menyimpan data vertex segitiga
	UINT size_list = ARRAYSIZE(list);
	
	void* shader_byte_code = nullptr; //mendeklarasikan pointer void untuk menyimpan byte code shader, yang akan digunakan untuk mengonfigurasi buffer vertex agar sesuai dengan format data vertex yang digunakan dalam shader
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader); //memanggil metode load() pada objek VertexBuffer untuk memuat data vertex segitiga ke dalam buffer vertex, dengan menentukan pointer ke daftar vertex, ukuran setiap vertex, jumlah vertex dalam daftar, dan parameter tambahan untuk shader byte code (dalam hal ini, tidak digunakan sehingga diatur ke nullptr dan 0)

	GraphicsEngine::get()->releaseCompiledShaders(); //memanggil metode releaseCompiledShaders() dari kelas GraphicsEngine untuk melepaskan sumber daya yang digunakan untuk shader yang telah dikompilasi, memungkinkan pembersihan sumber daya yang terkait dengan shader yang telah dikompilasi untuk mencegah kebocoran memori setelah shader vertex telah dibuat dan digunakan dalam konfigurasi buffer vertex
	

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShaders(); //memanggil metode releaseCompiledShaders() dari kelas GraphicsEngine untuk melepaskan sumber daya yang digunakan untuk shader yang telah dikompilasi, memungkinkan pembersihan sumber daya yang terkait dengan shader yang telah dikompilasi untuk mencegah kebocoran memori setelah shader vertex telah dibuat dan digunakan dalam konfigurasi buffer vertex

	constant cc;
	cc.m_angle = 0;  

	m_cb = GraphicsEngine::get()->createConstantBuffer(); //memanggil metode createConstantBuffer() dari kelas GraphicsEngine untuk membuat buffer konstan baru yang akan digunakan untuk menyimpan data konstan yang akan digunakan dalam rendering, seperti matriks transformasi atau parameter shader lainnya
	m_cb->load(&cc, sizeof(constant)); //memanggil metode load() pada objek ConstantBuffer untuk memuat data konstan ke dalam buffer konstan, dengan menentukan pointer ke data konstan (dalam hal ini, tidak digunakan sehingga diatur ke nullptr) dan ukuran data konstan (dalam hal ini, ukuran matriks 4x4 yang terdiri dari 16 float)

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	// CLEAR RENDER TARGET
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	// SET VIEWPORT RENDER TARGET UNTUK KITA GAMBAR
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	// UPDATE TIME	
	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();
	m_angle += 1.57f * m_delta_time;
	constant cc;
	cc.m_angle = m_angle;


	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	// SET CONSTANT BUFFER
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	
	
	// SET DEFAULT SHADER
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs); // memanggil metode setVertexShader() pada konteks perangkat langsung untuk mengatur shader vertex yang akan digunakan dalam pipeline rendering, memungkinkan penggunaan shader vertex yang telah dibuat untuk memproses data vertex selama rendering
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	// SET VERTICES DARI SEGITIGA UNTUK GAMBAR
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// GAMBAR SEGITIGA
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}

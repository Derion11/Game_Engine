#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"


struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))  //menyatakan struktur constant dengan atribut align(16) untuk memastikan bahwa data dalam buffer konstan diatur pada batas memori 16 byte, yang diperlukan untuk kinerja optimal dalam rendering grafis menggunakan DirectX 11
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;

	float m_time;
};
 
AppWindow::AppWindow()
{
}

void AppWindow::updateQuadPosition()
{
	/*unsigned long new_time = 0;					<- Tutorial 9
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();*/

	m_time += 1.57f * m_delta_time;
	constant cc;
	cc.m_time = m_time;

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	Matrix4x4 temp;

	// cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2.0f,-2.0f,0), Vector3D(2.0f,2.0f,0), m_delta_pos));

	m_delta_scale += m_delta_time / 0.7f;

	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale)+1.0f)/2.0f));

	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));

	//cc.m_world *= temp;

	cc.m_world.setScale(Vector3D(1, 1, 1));

	temp.setIdentity();
	temp.setRotationZ(0.0f);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	cc.m_world *= temp;




	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		// Menghitung lebar dan tinggi jendela klien dengan menggunakan metode getClientWindowRect() dari kelas Window untuk mendapatkan ukuran jendela klien, yang kemudian digunakan untuk mengatur matriks proyeksi ortografis agar sesuai dengan ukuran jendela
		(this->getClientWindowRect().right - this->getClientWindowRect().left)/ 300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 300.0f,
		-4.0f,
		4.0f
	);


	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::get()->addListener(this); //mendaftarkan objek AppWindow sebagai listener untuk sistem input, memungkinkan AppWindow untuk menerima dan menangani input dari pengguna melalui metode onKeyDown() dan onKeyUp()

	GraphicsEngine::get()->init(); //memanggil metode init() dari kelas GraphicsEngine untuk menginisialisasi engine grafis dan perangkat DirectX 11 saat jendela dibuat
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	
	RECT rc = this->getClientWindowRect(); //memanggil metode getClientWindowRect() dari kelas Window untuk mendapatkan ukuran jendela klien, yang akan digunakan untuk mengkonfigurasi swap chain agar sesuai dengan ukuran jendela
	m_swap_chain->init(this->m_hwnd,rc.right-rc.left, rc.bottom-rc.top);

	vertex vertex_list[] =
	{
		//Koordinat quad dalam ruang 3D -> {x, y, z}.
		// Tampak Depan
		{Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(1,0,0),	Vector3D(0.2f,0,0)},
		{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1,1,0),	Vector3D(0.2f,0.2f,0)},
		{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(1,1,0),	Vector3D(0.2f,0.2f,0)},
		{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1,0,0),	Vector3D(0.2f,0,0)},

		// Tampak Belakang
		{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),	Vector3D(0,0.2f,0)},
		{Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),	Vector3D(0,0.2f,0.2f)},
		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(0,1,1),	Vector3D(0,0.2f,0.2f)},
		{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(0,1,0),	Vector3D(0,0.2f,0)}

	};

	m_vb = GraphicsEngine::get()->createVertexBuffer(); //memanggil metode createVertexBuffer() dari kelas GraphicsEngine untuk membuat buffer vertex baru yang akan digunakan untuk menyimpan data vertex segitiga
	UINT size_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] =
	{
		0,1,2, // Segitiga pertama
		2,3,0, // Segitiga kedua
		// Bagian belakang
		4,5,6,
		6,7,4,
		// Bagian atas
		1,6,5,
		5,2,1,
		// Bagian bawah
		7,0,3,
		3,4,7,
		// Bagian kanan
		3,2,5,
		5,4,3,
		// Bagian kiri
		7,6,1,
		1,0,7

	};


	m_ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib->load(index_list, size_index_list);



	
	void* shader_byte_code = nullptr; //mendeklarasikan pointer void untuk menyimpan byte code shader, yang akan digunakan untuk mengonfigurasi buffer vertex agar sesuai dengan format data vertex yang digunakan dalam shader
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader); //memanggil metode load() pada objek VertexBuffer untuk memuat data vertex segitiga ke dalam buffer vertex, dengan menentukan pointer ke daftar vertex, ukuran setiap vertex, jumlah vertex dalam daftar, dan parameter tambahan untuk shader byte code (dalam hal ini, tidak digunakan sehingga diatur ke nullptr dan 0)

	GraphicsEngine::get()->releaseCompiledShaders(); //memanggil metode releaseCompiledShaders() dari kelas GraphicsEngine untuk melepaskan sumber daya yang digunakan untuk shader yang telah dikompilasi, memungkinkan pembersihan sumber daya yang terkait dengan shader yang telah dikompilasi untuk mencegah kebocoran memori setelah shader vertex telah dibuat dan digunakan dalam konfigurasi buffer vertex
	

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShaders(); //memanggil metode releaseCompiledShaders() dari kelas GraphicsEngine untuk melepaskan sumber daya yang digunakan untuk shader yang telah dikompilasi, memungkinkan pembersihan sumber daya yang terkait dengan shader yang telah dikompilasi untuk mencegah kebocoran memori setelah shader vertex telah dibuat dan digunakan dalam konfigurasi buffer vertex

	constant cc;
	cc.m_time = 0;  

	m_cb = GraphicsEngine::get()->createConstantBuffer(); //memanggil metode createConstantBuffer() dari kelas GraphicsEngine untuk membuat buffer konstan baru yang akan digunakan untuk menyimpan data konstan yang akan digunakan dalam rendering, seperti matriks transformasi atau parameter shader lainnya
	m_cb->load(&cc, sizeof(constant)); //memanggil metode load() pada objek ConstantBuffer untuk memuat data konstan ke dalam buffer konstan, dengan menentukan pointer ke data konstan (dalam hal ini, tidak digunakan sehingga diatur ke nullptr) dan ukuran data konstan (dalam hal ini, ukuran matriks 4x4 yang terdiri dari 16 float)

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	// Memanggil metode update() pada sistem input untuk memproses input dari pengguna, memungkinkan aplikasi untuk merespons input seperti penekanan tombol atau pergerakan mouse selama setiap frame pembaruan
	InputSystem::get()->update();

	// CLEAR RENDER TARGET
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	// SET VIEWPORT RENDER TARGET UNTUK KITA GAMBAR
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	



	updateQuadPosition();
	
	


	// SET CONSTANT BUFFER
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	
	
	// SET DEFAULT SHADER
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs); // memanggil metode setVertexShader() pada konteks perangkat langsung untuk mengatur shader vertex yang akan digunakan dalam pipeline rendering, memungkinkan penggunaan shader vertex yang telah dibuat untuk memproses data vertex selama rendering
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	// SET INDEKS DARI SEGITIGA UNTUK GAMBAR
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	// SET INDEKS DARI SEGITIGA UNTUK GAMBAR
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	// GAMBAR SEGITIGA
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
	m_swap_chain->present(true);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();

	m_delta_time = (m_old_delta)?((m_new_delta - m_old_delta) / 1000.0f):0;

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_ib->release();
	m_cb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		m_rot_x += 1.0f * m_delta_time;
	}
	else if (key == 'S')
	{
		m_rot_x -= 1.0f * m_delta_time;
	}
	else if (key == 'A')
	{
		m_rot_y += 1.0f * m_delta_time;
	}
	else if (key == 'D')
	{
		m_rot_y -= 1.0f * m_delta_time;
	}
}

void AppWindow::onKeyUp(int key)
{
}

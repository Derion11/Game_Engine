#include "AppWindow.h"

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

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 1, 0, 1);

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

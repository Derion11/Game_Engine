#include "AppWindow.h"

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	//Window::onCreate();
	GraphicsEngine::get()->init(); //memanggil metode init() dari kelas GraphicsEngine untuk menginisialisasi engine grafis dan perangkat DirectX 11 saat jendela dibuat
}

void AppWindow::onUpdate()
{
	//Window::onUpdate();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	GraphicsEngine::get()->release();
}

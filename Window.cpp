#include "Window.h"

//Window* window = nullptr; // Pointer global ke objek Window

Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) // Prosedur jendela
{
	switch (msg)
	{
	case WM_CREATE: // Pesan pembuatan jendela
	{
		// Event fired when the window is created
		// collected here..
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		// .. and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->setHWND(hwnd);
		window->onCreate();
		break;
	}
	case WM_DESTROY: // Pesan penghancuran jendela
	{
		// Event fired when the window is destroyed
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	
	
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam); // Prosedur jendela default
	}
	return NULL;
}


bool Window::init() // Inisialisasi window
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL; // ekstra byte untuk kelas
	wc.cbSize = sizeof(WNDCLASSEX); // ukuran struktur
	wc.cbWndExtra = NULL; // ekstra byte untuk jendela
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; // warna latar belakang jendela
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // kursor default
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ikon default
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // ikon kecil default
	wc.hInstance = NULL; // instance aplikasi
	wc.lpszClassName = L"MyWindowClass"; // nama kelas jendela
	wc.lpszMenuName = L""; // nama menu
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;


	if (!::RegisterClassEx(&wc)) // Jika pendaftaran kelas gagal
		return false;

	//Sebelum modifikasi kode untuk pointer
	//if (!window) // Jika pointer global belum diinisialisasi
	//	window = this; // Set pointer global ke objek Window saat ini

	m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, // gaya jendela
					L"MyWindowClass", // nama kelas jendela
					L"DirectX Application", // judul jendela
					WS_OVERLAPPEDWINDOW, // gaya jendela
					CW_USEDEFAULT, CW_USEDEFAULT, // posisi x dan y
					800, 600, // lebar dan tinggi
					NULL, // jendela induk
					NULL, // menu
					NULL, // instance aplikasi
					this); // parameter tambahan

	if (!m_hwnd) // Jika pembuatan jendela gagal
		return false;

	::ShowWindow(m_hwnd, SW_SHOW); // Tampilkan jendela
	::UpdateWindow(m_hwnd); // Perbarui jendela

	m_is_run = true; // Tandai jendela sebagai berjalan
	
	return true;
}

bool Window::broadcast()
{
	MSG msg;

	while(::PeekMessage(&msg,NULL,0,0,PM_REMOVE) > 0)
	{
		TranslateMessage(&msg); // Terjemahkan pesan
		DispatchMessage(&msg); // Kirim pesan ke prosedur jendela
	}

	this->onUpdate(); // Panggil metode onUpdate dari objek Window

	Sleep(1); // Beri kesempatan pada sistem operasi untuk menjalankan tugas lainnya


	return true;
}

bool Window::release()
{
	if (!::DestroyWindow(m_hwnd)) // Jika penghancuran jendela gagal
		return false;

	return true;
}

bool Window::isRun()
{
	return m_is_run;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc); // Mendapatkan ukuran jendela klien
	return rc;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
	m_is_run = false;
}

Window::~Window()
{
}
#pragma once
#include <Windows.h> // Header API Win32.


class Window
{
public:
	Window();
	// Inisialisasi window
	bool init();
	bool broadcast();
	bool release();
	bool isRun(); // Cek apakah jendela masih berjalan


	virtual void onCreate()=0;
	virtual void onUpdate()=0;
	virtual void onDestroy();


	~Window();
protected: // handle jendela
	HWND m_hwnd;
	bool m_is_run;

};


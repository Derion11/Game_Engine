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

	RECT getClientWindowRect(); // Mendapatkan ukuran jendela klien
	void setHWND(HWND hwnd); // Mengatur handle jendela (HWND) untuk objek Window, memungkinkan integrasi dengan sistem jendela Windows dan pengelolaan pesan serta interaksi dengan jendela yang dibuat

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();


	~Window();
protected: // handle jendela
	HWND m_hwnd;
	bool m_is_run;

};


#pragma once
#include "InputListener.h"
#include <unordered_set> // Alternatif untuk menyimpan daftar listener, menggunakan unordered_set untuk efisiensi dalam pencarian dan penghapusan listener
//#include <map> // Untuk menyimpan daftar listener, ketika diperlukan

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	void update(); // Metode untuk memproses input, dapat dipanggil setiap frame atau sesuai kebutuhan
	void addListener(InputListener* listener); // Kelas yang ingin menerima input harus mendaftarkan dirinya sebagai listener
	void removeListener(InputListener* listener); // Kelas yang ingin berhenti menerima input harus menghapus dirinya sebagai listener

public:
	static InputSystem* get();
private:
	//std::map<InputListener*, InputListener*> m_map_listeners;
	std::unordered_set<InputListener*> m_set_listeners; // Menggunakan unordered_set untuk menyimpan listener, memungkinkan pencarian dan penghapusan yang lebih efisien dibandingkan dengan std::map, karena hanya menyimpan pointer ke listener tanpa nilai boolean tambahan
	unsigned char m_keys_state[256] = {}; // Array untuk menyimpan status tombol, dengan ukuran 256 untuk mencakup semua tombol yang mungkin digunakan
	unsigned char m_old_keys_state[256] = {};
};


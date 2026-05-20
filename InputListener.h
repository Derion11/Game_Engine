#pragma once
#include "Point.h"


class InputListener
{
	public:
		InputListener()
		{

		}
		~InputListener()
		{

		}
		// Keyboard pure virtual method, untuk menangani penekanan dan pelepasan tombol keyboard, menerima parameter key yang merupakan kode tombol yang ditekan atau dilepaskan, memungkinkan kelas turunan untuk merespons input keyboard dengan cara yang sesuai, seperti menggerakkan karakter, mengubah tampilan, atau melakukan aksi tertentu dalam aplikasi grafis
		virtual void onKeyDown(int key) = 0;
		virtual void onKeyUp(int key) = 0;

		// Mouse pure virtual method, untuk menangani pergerakan mouse, menerima parameter delta_mouse_pos yang merupakan perubahan posisi mouse sejak pembaruan terakhir, memungkinkan kelas turunan untuk merespons pergerakan mouse dengan cara yang sesuai, seperti mengubah posisi kamera atau objek dalam aplikasi grafis
		virtual void onMouseMove(const Point& delta_mouse_pos) = 0;

		virtual void onLeftMouseDown(const Point& mouse_pos) = 0;
		virtual void onLeftMouseUp(const Point& mouse_pos) = 0;

		virtual void onRightMouseDown(const Point& mouse_pos) = 0;
		virtual void onRightMouseUp(const Point& mouse_pos) = 0;
};
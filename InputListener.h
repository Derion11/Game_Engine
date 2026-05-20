#pragma once

class InputListener
{
	public:
		InputListener()
		{

		}
		~InputListener()
		{

		}
	// Metode virtual untuk menangani input, dapat di-override oleh kelas turunan
		virtual void onKeyDown(int key) = 0;
		virtual void onKeyUp(int key) = 0;
};
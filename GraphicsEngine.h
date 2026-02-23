#pragma once
#include <d3d11.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool init();	//inisialisasi engine grafis dan device DirectX 11
	bool release(); //melepaskan sumber daya yang digunakan oleh engine grafis
	~GraphicsEngine();



};


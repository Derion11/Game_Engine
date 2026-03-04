#pragma once
#include <d3d11.h>

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	bool release();
	//bool clearRenderTargetColor();
	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context; //pointer ke konteks perangkat DirectX 11, digunakan untuk mengirim perintah rendering ke GPU

};


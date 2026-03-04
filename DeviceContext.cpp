#include "DeviceContext.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) :m_device_context(device_context)
{
}

bool DeviceContext::release()
{
	//m_device_context->Release();


	return true;
}

//bool DeviceContext::clearRenderTargetColor()
//{
//	return true;
//}

DeviceContext::~DeviceContext()
{

}
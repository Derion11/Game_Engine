#include "PixelShader.h"
#include "GraphicsEngine.h"


PixelShader::PixelShader()
{
}


void PixelShader::release()
{
	m_ps->Release();
	delete this;
}

bool PixelShader::init(const void* shader_byte_code, size_t byte_code_size)
{

	if (!SUCCEEDED(GraphicsEngine::get()->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps))) // menggunakan metode CreatePixelShader dari perangkat DirectX 11 untuk membuat shader pixel baru berdasarkan byte code shader yang diberikan, memungkinkan pembuatan shader pixel yang akan digunakan dalam pipeline rendering
		return false;

	return true;
}

PixelShader::~PixelShader()
{
}
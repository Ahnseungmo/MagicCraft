#include "Framework.h"

Material::Material(wstring shaderFile)
{
    vertexShader = Shader::AddVS(shaderFile);
    pixelShader = Shader::AddPS(shaderFile);

    colorBuffer = new ColorBuffer();
}

Material::~Material()
{
	delete colorBuffer;
}

void Material::SetColor(float r, float g, float b, float a)
{
	colorBuffer->Set(r, g, b, a);
}

void Material::SetShader(wstring file)
{
	vertexShader = Shader::AddVS(file);
	pixelShader = Shader::AddPS(file);
}

void Material::SetVertexShader(wstring file)
{
	vertexShader = Shader::AddVS(file);
}

void Material::SetPixelShader(wstring file)
{
	pixelShader = Shader::AddPS(file);
}

void Material::Set()
{
	if (baseMap)
		baseMap->PSSet(0);

	colorBuffer->SetPS(0);

	vertexShader->Set();
	pixelShader->Set();
}

void Material::SetBaseMap(wstring file)
{
	baseMap = Texture::Add(file);
}

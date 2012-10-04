#ifndef _SHADER_H
#define _SHADER_H

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <d3d9.h>
#include <d3dx9.h>

class Shader
{
public:
	Shader();
	~Shader();

	IDirect3DPixelShader9 *GetPixelShader() { return psShader; }
	IDirect3DVertexShader9 *GetVertexShader() { return vsShader; }
	void CompileFromStream(IDirect3DDevice9 *d3dDevice, const char *psShaderCode, const char *vsShaderCode);
	void CompileFromStream(IDirect3DDevice9 *d3dDevice, D3DXMACRO *macro, const char *psShaderCode, const char *vsShaderCode);
private:
	IDirect3DPixelShader9  *psShader;
	IDirect3DVertexShader9 *vsShader;
};

#endif
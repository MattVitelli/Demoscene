#include "Shader.h"
#include "config.h"

Shader::Shader()
{
	psShader = NULL;
	vsShader = NULL;
}

Shader::~Shader()
{
	if(psShader != NULL)
		psShader->Release();
	if(vsShader != NULL)
		vsShader->Release();
}

void Shader::CompileFromStream(IDirect3DDevice9 *d3dDevice, const char *psShaderCode, const char *vsShaderCode)
{
	CompileFromStream(d3dDevice, NULL, psShaderCode, vsShaderCode);
}

void Shader::CompileFromStream(IDirect3DDevice9 *d3dDevice, D3DXMACRO *macro, const char *psShaderCode, const char *vsShaderCode)
{
	ID3DXBuffer *tmpPS;
	ID3DXBuffer *tmpVS;
    #ifndef DEBUG
	DWORD shaderFlag = (D3DXSHADER_OPTIMIZATION_LEVEL3|D3DXSHADER_PREFER_FLOW_CONTROL|D3DXSHADER_PACKMATRIX_ROWMAJOR);
	D3DXCompileShader( vsShaderCode, strlen(vsShaderCode), macro, 0, "vs_main", D3DXGetVertexShaderProfile(d3dDevice), shaderFlag, &tmpVS, 0, 0 );
    D3DXCompileShader( psShaderCode, strlen(psShaderCode), macro, 0, "ps_main", D3DXGetPixelShaderProfile(d3dDevice), shaderFlag, &tmpPS, 0, 0 );
    #else
    ID3DXBuffer *errors;
	DWORD shaderFlag = D3DXSHADER_DEBUG*0+1*(D3DXSHADER_OPTIMIZATION_LEVEL3|D3DXSHADER_PREFER_FLOW_CONTROL|D3DXSHADER_PACKMATRIX_ROWMAJOR);
    if( D3DXCompileShader( psShaderCode, strlen(psShaderCode), macro, 0, "ps_main", D3DXGetPixelShaderProfile(d3dDevice), shaderFlag, &tmpPS, &errors, 0 ) <0 )
    {
        OutputDebugString( (char*)errors->GetBufferPointer() );
        errors->Release();
        DebugBreak();
    }
	if( D3DXCompileShader( vsShaderCode, strlen(vsShaderCode), macro, 0, "vs_main", D3DXGetVertexShaderProfile(d3dDevice), shaderFlag, &tmpVS, &errors, 0 ) <0 )
    {
        OutputDebugString( (char*)errors->GetBufferPointer() );
        errors->Release();
        DebugBreak();
    }
    #endif
	d3dDevice->CreateVertexShader( (DWORD *)tmpVS->GetBufferPointer(), &vsShader);
    d3dDevice->CreatePixelShader( (DWORD*)tmpPS->GetBufferPointer(), &psShader );
}
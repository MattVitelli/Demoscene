//--------------------------------------------------------------------------//
// iq / rgba  .  tiny codes  .  2008                                        //
//--------------------------------------------------------------------------//

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Shader.h"
#include "fp.h"
#include "config.h"
#include "ShaderCode.h"
#include "Camera.h"
#include "InputManager.h"
#include <string.h>
#include <stdio.h>
#include <string>
#include "Maze.h"
//------------------------------------------------------------------------------------------------------------------

static const float quadVerts[4*5] =
{
  1.0f,-1.0f,0.0f,1.0f,0.0f,
 -1.0f,-1.0f,0.0f,0.0f,0.0f,
  1.0f, 1.0f,0.0f,1.0f,1.0f,
 -1.0f, 1.0f,0.0f,0.0f,1.0f
};

//------------------------------------------------------------------------------------------------------------------
static IDirect3DTexture9 *texture;
static Shader *gShader;
static Camera *camera;
static D3DXVECTOR4 *chambers;
#define CHAMBER_SIZE 4
#define MAZE_FLAG 15
//------------------------------------------------------------------------------------------------------------------

void create_random_texture(IDirect3DDevice9 *d3dDevice, IDirect3DTexture9 **surface, UINT size)
{
	d3dDevice->CreateTexture(size, size, 1, D3DUSAGE_DYNAMIC, D3DFMT_R32F, D3DPOOL_DEFAULT, surface, NULL);
	D3DLOCKED_RECT rect;
	(*surface)->LockRect(0, &rect, NULL, 0);
	int elemCount = size*size;
	float *data = (float *)rect.pBits;
	/*
	for(int i = 0; i < elemCount; i++)
	{
		data[i] = ((float)maze[i])/16.0f;//(rand()%16);//(/(float)RAND_MAX)*2.0f-1.0f;
	}
	*/
	(*surface)->UnlockRect(0);
	//D3DXSaveTextureToFile("test.dds", D3DXIFF_DDS, *surface, NULL);
}

std::string create_random_chambers(int size)
{
	int *maze = CreateMaze(size, size);
	char buffer[256];
	for(int j = 0; j < size; j++)
	{
		std::string mazeStr = "";
		for(int i = 0; i < size; i++)
		{
			
			_itoa(maze[i+j*size], buffer, 16);
			mazeStr += buffer;
			mazeStr += " ";
		}
		mazeStr += "\n";
		OutputDebugString(mazeStr.c_str());
	}
//	maze[0] = 0; maze[1] = 0;
//	maze[2] = 0; maze[3] = 0;
	//for(int i = 0; i < size*size; i++)
	//	maze[i] = MAZE_FLAG;
	
	
	std::string output = "#define EPS 0.001\n";
	output += "#define CHAMBER_SIZE ";
	_itoa(size, buffer, 10);output += buffer; output += "\n";
	output += "static const float chambers[] = { ";
	int totalSize = size*size;
	for(int i = 0; i < totalSize; i++)
	{
		_itoa(maze[i],buffer, 10);
		output += buffer;
		output += ",";
	}
	output += " };";

	return output;
}

void intro_init( IDirect3DDevice9 *d3dDevice )
{
	D3DXMACRO macro[] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ "NUMBER_OF_LIGHTS,"		 "3"  },
		{ NULL,                          NULL }
	};
	std::string maze = create_random_chambers(CHAMBER_SIZE);
	maze += densityPS;
	const char *densityShader = maze.c_str();

	gShader = new Shader();
	gShader->CompileFromStream(d3dDevice, macro, densityShader, densityVS);
	camera = new Camera();
	create_random_texture(d3dDevice, &texture, 16);
}

void intro_handle_input(InputManager *input, float time)
{
	MoveInfo info;
	memset(&info, 0, sizeof(MoveInfo));
	if(input->IsKeyDown(DIK_W))
		info.forward += 1;
	if(input->IsKeyDown(DIK_S))
		info.forward -= 1;
	if(input->IsKeyDown(DIK_D))
		info.strafe += 1;
	if(input->IsKeyDown(DIK_A))
		info.strafe -= 1;

	int xRel, yRel;
	input->GetRelativeMousePos(xRel, yRel);
	info.pitch -= 0.01f*(float)yRel;
	info.yaw -= 0.01f*(float)xRel;
	camera->UpdateMove(info, time);
	char            str[256];
	D3DXVECTOR3 pos = camera->GetPosition();
	sprintf( str, "Camera Pos: %4.2f x, %4.2f y, %4.2f z\n", pos.x, pos.y, pos.z);

    OutputDebugString(str);
}

void intro_do( IDirect3DDevice9 *d3dDevice, float time)
{	
    d3dDevice->BeginScene();
	camera->SetupRenderParameters(d3dDevice);
	D3DSURFACE_DESC surfDesc;
	texture->GetLevelDesc(0, &surfDesc);
	D3DXVECTOR2 texRes(1.0f/(float)surfDesc.Width, 1.0f/(float)surfDesc.Height);
	D3DXVECTOR2 chamberRes(1.0f/(float)CHAMBER_SIZE, 1.0f/(float)CHAMBER_SIZE);
	d3dDevice->SetPixelShaderConstantF(6, texRes, 1);
	d3dDevice->SetPixelShaderConstantF(7, chamberRes, 1);
	d3dDevice->SetVertexShader(gShader->GetVertexShader());
    d3dDevice->SetPixelShader(gShader->GetPixelShader());
	d3dDevice->SetTexture(0, texture);
    d3dDevice->SetFVF( D3DFVF_XYZ|D3DFVF_TEX1 );
    d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,quadVerts,5*sizeof(float));
    d3dDevice->EndScene();
    d3dDevice->Present( NULL, NULL, NULL, NULL );
}
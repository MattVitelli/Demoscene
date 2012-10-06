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
static float lightTheta;
#define CHAMBER_SIZE 4
#define MAZE_FLAG 15
#define LIGHT_PHI 0.70711
#define LIGHT_SPEED 0.05
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
	std::string output = densityFunctionsPS;
	output += "static inline float GetMazeWalls(float3 wp, float4 wallParams)";
	output += "{";
	output += "float t = 9999999;";
	
	for(int i = 0; i < size; i++)
	{
		char bufferX[256];
		char bufferX1[256];
		_itoa(i,bufferX, 10);
		_itoa(i+1,bufferX1, 10);
		for(int j = 0; j < size; j++)
		{
			char bufferY[256];
			char bufferY1[256];
			_itoa(j,bufferY, 10);
			_itoa(j+1,bufferY1, 10);
			//Flip right and down bits
			std::string offsetPosX = "-SCALE * (float3(";
			offsetPosX += bufferX1;
			offsetPosX += ",0,";
			offsetPosX += bufferY;
			offsetPosX += ")+float3(0,0,0.5))";

			std::string offsetPosY = "-SCALE * (float3(";
			offsetPosY += bufferX;
			offsetPosY += ",0,";
			offsetPosY += bufferY1;
			offsetPosY += ")+float3(0.5,0,0))";

			int idx = i + j * size;
			if(i < size-1 && (maze[idx] & 0x01)) //If right is sealed
			{
				output += "t = min(t, udRoundBox(wp";
				output += offsetPosX;
				output += ", wallParams));";
			}
			
			if(j < size-1 && (maze[idx] & 0x04)) //If down is sealed
			{
				output += "t = min(t, udRoundBox(wp";
				output += offsetPosY;
				output += ", wallParams.zyxw));";
			}
		}
	}
	
	output += "return t;";
	output += "}";
	return output;
}

void intro_init( IDirect3DDevice9 *d3dDevice )
{
	char buffer[256];
	_itoa(CHAMBER_SIZE, buffer, 10);
	D3DXMACRO macro[] =
	{
		{ "EPS", "0.001" },
		{ "CHAMBER_SIZE", buffer  },
		{ "SCALE", "15" },
		{ "SHIFT", "1024" },
		{ "TILES", "1.45" },
		{ "SAMPLES", "16" },
		{ "SHADOWSAMPLES", "8" },
		{ "REFLECTSAMPLES", "8" },
		{ "SHADOW_FALLOFF", "0.8" },
		{ "AO_PLANE", "0.36" },
		{ NULL, NULL }
	};
	std::string maze = create_random_chambers(CHAMBER_SIZE);
	maze += distanceFunctionPS;
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
		info.forward += 2;
	if(input->IsKeyDown(DIK_S))
		info.forward -= 2;
	if(input->IsKeyDown(DIK_D))
		info.strafe += 2;
	if(input->IsKeyDown(DIK_A))
		info.strafe -= 2;

	int xRel, yRel;
	input->GetRelativeMousePos(xRel, yRel);
	info.pitch -= 0.01f*(float)yRel;
	info.yaw -= 0.01f*(float)xRel;
	camera->UpdateMove(info, time);
	char            str[256];
	D3DXVECTOR3 pos = camera->GetPosition();
	int xP = (int)((pos.x+1024+5)*0.1) % CHAMBER_SIZE;
	int zP = (int)((pos.z+1024+5)*0.1) % CHAMBER_SIZE;
	
	sprintf( str, "Camera Pos: %d x, %d z\n", xP, zP);
	//sprintf( str, "Camera Pos: %4.2f x, %4.2f y, %4.2f z\n", pos.x, pos.y, pos.z);

    OutputDebugString(str);
}

void intro_do( IDirect3DDevice9 *d3dDevice, float time)
{	
    d3dDevice->BeginScene();
	camera->SetupRenderParameters(d3dDevice);
	D3DSURFACE_DESC surfDesc;
	texture->GetLevelDesc(0, &surfDesc);
	lightTheta += time * LIGHT_SPEED;
	const float twoPi = 2.0*D3DX_PI;
	if(lightTheta >= twoPi)
		lightTheta -= twoPi;
	D3DXVECTOR3 lightDir(cos(LIGHT_PHI)*cos(lightTheta), sin(LIGHT_PHI), cos(LIGHT_PHI)*sin(lightTheta));
	D3DXVECTOR2 texRes(1.0f/(float)surfDesc.Width, 1.0f/(float)surfDesc.Height);
	D3DXVECTOR2 chamberRes(1.0f/(float)CHAMBER_SIZE, 1.0f/(float)CHAMBER_SIZE);
	d3dDevice->SetPixelShaderConstantF(6, texRes, 1);
	d3dDevice->SetPixelShaderConstantF(7, lightDir, 1);
	d3dDevice->SetVertexShader(gShader->GetVertexShader());
    d3dDevice->SetPixelShader(gShader->GetPixelShader());
	d3dDevice->SetTexture(0, texture);
    d3dDevice->SetFVF( D3DFVF_XYZ|D3DFVF_TEX1 );
    d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,quadVerts,5*sizeof(float));
    d3dDevice->EndScene();
    d3dDevice->Present( NULL, NULL, NULL, NULL );
}
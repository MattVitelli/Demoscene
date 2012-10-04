#ifndef _CAMERA_H
#define _CAMERA_H

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <d3dx9.h>
#include <d3dx9math.h>

struct MoveInfo
{
	float forward;
	float strafe;
	float pitch;
	float yaw;
};

class Camera
{
public:
	Camera();
	~Camera();
	void UpdateMove(MoveInfo info, float dt);
	void SetupRenderParameters(IDirect3DDevice9 *d3dDevice);
	D3DXVECTOR3 GetPosition() { return position; }
private:
	void UpdateMatrices();
	D3DXMATRIX view;
	D3DXMATRIX projection;
	D3DXMATRIX viewProj;
	D3DXMATRIX invViewProj;
	D3DXVECTOR3 position;
	D3DXVECTOR3 forward;
	D3DXVECTOR3 strafe;
	float pitch;
	float yaw;
	float farPlane;
	float nearPlane;
	float fov;
};
#endif
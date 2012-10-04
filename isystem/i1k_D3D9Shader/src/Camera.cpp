#include "Camera.h"
#include "config.h"

Camera::Camera() 
{ 
	fov = 1.35f;
	nearPlane = 1.0;
	farPlane = 1000.0;
	memset(&position, 0, sizeof(D3DXVECTOR3));
	forward = D3DXVECTOR3(0,0,-1);
	strafe = D3DXVECTOR3(1,0,0);
	yaw = 0;
	pitch = 0;
}

Camera::~Camera() 
{ 

}

void Camera::UpdateMove(MoveInfo info, float dt)
{
	pitch += info.pitch;
	if(pitch < -1.4f)
		pitch = -1.4f;
	if(pitch > 1.4f)
		pitch = 1.4f;

	yaw += info.yaw;
	const float twoPi = 2.0*D3DX_PI;
	if(yaw >= twoPi)
		yaw -= twoPi;
	if(yaw <= 0)
		yaw += twoPi;

	D3DXMATRIX transform, transformX, transformY;
	D3DXMatrixRotationX(&transformX, pitch);
	D3DXMatrixRotationY(&transformY, yaw);
	D3DXMatrixMultiply(&transform, &transformX, &transformY);
	D3DXVECTOR3 fwdVec(0,0,-1);
	D3DXVec3TransformNormal(&forward, &fwdVec, &transform);
	D3DXVECTOR3 rightVec(1,0,0);
	D3DXVec3TransformNormal(&strafe, &rightVec, &transform);
	position += info.forward * dt * forward;
	position += info.strafe * dt * strafe;
	UpdateMatrices();
}

void Camera::UpdateMatrices()
{
	D3DXVECTOR3 lookAt = position + forward;
	D3DXVECTOR3 up(0,1,0);
	D3DXMatrixLookAtRH(&view, &position, &lookAt, &up);
	D3DXMatrixPerspectiveFovRH(&projection, fov, ASPECT_RATIO, nearPlane, farPlane);
	D3DXMatrixMultiply(&viewProj, &view, &projection);
	float det;
	D3DXMatrixInverse(&invViewProj, &det, &viewProj);
}

void Camera::SetupRenderParameters(IDirect3DDevice9 *d3dDevice)
{
	D3DXVECTOR2 planes(nearPlane, farPlane);
	d3dDevice->SetVertexShaderConstantF(0, (float *)&invViewProj, 4);
	d3dDevice->SetPixelShaderConstantF(0, (float *)&viewProj, 4);
	d3dDevice->SetPixelShaderConstantF(4, (float *)&position, 1);
	d3dDevice->SetPixelShaderConstantF(5, (float *)&planes, 1);
}


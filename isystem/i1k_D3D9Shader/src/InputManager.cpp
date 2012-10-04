#include "InputManager.h"

InputManager::InputManager(HINSTANCE hinst, HWND hwnd)
{
	HRESULT hr = DirectInput8Create(hinst, DIRECTINPUT_VERSION, 
        IID_IDirectInput8, (void**)&diObject, NULL);

	//Create the keyboard
	hr = diObject->CreateDevice(GUID_SysKeyboard, &keyboardDevice, NULL);
	hr = keyboardDevice->SetDataFormat( &c_dfDIKeyboard );
	hr = keyboardDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	//Create the mouse
	hr = diObject->CreateDevice(GUID_SysMouse, &mouseDevice, NULL);
	hr = mouseDevice->SetDataFormat( &c_dfDIMouse2 );
	hr = mouseDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	
	//Acquire devices
	ResetDevice();
}

InputManager::~InputManager()
{
	//Release the keyboard
	if (keyboardDevice)
	{
		keyboardDevice->Unacquire();
		keyboardDevice->Release();
	}

	//Release the mouse
	if (mouseDevice)
	{
		mouseDevice->Unacquire();
		mouseDevice->Release();
	}

	//Release DirectInput
	if (diObject)
		diObject->Release();
}

void InputManager::ResetDevice()
{
	keyboardDevice->Acquire();
	memset(prevKeys, 0, sizeof(prevKeys));
	memset(keys, 0, sizeof(keys));

	mouseDevice->Acquire();
	memset(&prevMouseState, 0, sizeof(DIMOUSESTATE2));
	memset(&mouseState, 0, sizeof(DIMOUSESTATE2));

	AcquireMousePos();
}

void InputManager::Update()
{
	HandleKeyboard();
	HandleMouse();
}

void InputManager::HandleKeyboard()
{
	// Get the input's device state, and put the state in keys - zero first
	memcpy(prevKeys, keys, sizeof(keys));
	memset(keys, 0, sizeof(keys));
	HRESULT hr = keyboardDevice->GetDeviceState(sizeof(keys), keys);
	if (FAILED(hr))
	{
		   // If input is lost then acquire and keep trying until we get it back 
		   hr=keyboardDevice->Acquire();
		   while( hr == DIERR_INPUTLOST ) 
		   {          
				 hr = keyboardDevice->Acquire();
		   }
		   // Could be we failed for some other reason
		   if (FAILED(hr))
			 return;
		   // Now read the state again
		   keyboardDevice->GetDeviceState( sizeof(keys), keys );
	}
}

void InputManager::HandleMouse()
{
	memcpy(&prevMouseState, &mouseState, sizeof(DIMOUSESTATE2));
	memset(&mouseState, 0, sizeof(DIMOUSESTATE2));

	HRESULT hr = mouseDevice->GetDeviceState( sizeof(DIMOUSESTATE2), &mouseState );
	if (FAILED(hr))
	{
		   // If input is lost then acquire and keep trying until we get it back 
		   hr=mouseDevice->Acquire();
		   while( hr == DIERR_INPUTLOST ) 
		   {          
				 hr = mouseDevice->Acquire();
		   }
		   // Could be we failed for some other reason
		   if (FAILED(hr))
			 return;
		   AcquireMousePos();
		   // Now read the state again
		   mouseDevice->GetDeviceState( sizeof(DIMOUSESTATE2), &mouseState );
	}

	oldX += mouseState.lX;
	oldY += mouseState.lY;
	oldZ += mouseState.lZ;
}

void InputManager::AcquireMousePos()
{
	tagPOINT mousePos;
	if(GetCursorPos(&mousePos))
	{
		oldX = mousePos.x;
		oldY = mousePos.y;
	}
	else
	{
		oldX = 0; 
		oldY = 0; 
	}
	oldZ = 0;
}

void InputManager::GetRelativeMousePos(int &xPos, int &yPos)
{
	xPos = mouseState.lX;
	yPos = mouseState.lY;
}

void InputManager::GetAbsoluteMousePos(int &xPos, int &yPos)
{
	xPos = oldX;
	yPos = oldY;
}

bool InputManager::IsKeyDown(int key)
{
	return ((keys[key] & 0x80) > 0);
}

bool InputManager::IsKeyDownOnce(int key)
{
	return (IsKeyDown(key) && !((prevKeys[key] & 0x80)>0));
}

bool InputManager::IsMouseKeyDown(int key)
{
	return ((mouseState.rgbButtons[key] & 0x80)>0);
}

bool InputManager::IsMouseKeyDownOnce(int key)
{
	return (IsMouseKeyDown(key) && !((prevMouseState.rgbButtons[key] & 0x80) > 0));
}
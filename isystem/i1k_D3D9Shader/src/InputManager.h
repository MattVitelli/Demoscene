#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class InputManager
{
public:
	InputManager(HINSTANCE hinst, HWND hwnd);
	~InputManager();
	void ResetDevice();
	void Update();
	bool IsKeyDown(int key);
	bool IsKeyDownOnce(int key);
	bool IsMouseKeyDown(int key);
	bool IsMouseKeyDownOnce(int key);

	void GetRelativeMousePos(int &xPos, int &yPos);
	void GetAbsoluteMousePos(int &xPos, int &yPos);

private:
	void HandleKeyboard();
	void HandleMouse();
	void AcquireMousePos();

	int oldX;
	int oldY;
	int oldZ;

	LPDIRECTINPUT8  diObject;
	LPDIRECTINPUTDEVICE8 keyboardDevice;
	LPDIRECTINPUTDEVICE8 mouseDevice;
	BYTE keys[256];
	BYTE prevKeys[256];
	DIMOUSESTATE2 mouseState;
	DIMOUSESTATE2 prevMouseState;

};


#endif
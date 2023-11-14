// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#include "Input.h"

void Input::MoveMouse(int x, int y, bool relative)
{
	if (relative)
	{
		int currentPosX, currentPosY;
		Input::GetMousePos(currentPosX, currentPosY);
		x += currentPosX;
		y += currentPosY;
	}
	SetCursorPos(x, y);
}

void Input::GetMousePos(int& x, int& y)
{
	POINT p;
	GetCursorPos(&p);
	x = p.x;
	y = p.y;
}

void Input::SendKey(WORD virtualKey, bool down)
{
	INPUT input{ };
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = virtualKey;
	input.ki.wScan = 0;
	input.ki.dwFlags = down ? 0 : KEYEVENTF_KEYUP;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;

	SendInput(1, &input, sizeof(INPUT));
}

void Input::SendMouseButton(EMouseButton button, bool down)
{
	INPUT input{ };

	input.type = INPUT_MOUSE;

	switch (button)
	{
		case Left:
			input.mi.dwFlags = down ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP;
			break;
		case Right:
			input.mi.dwFlags = down ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP;
			break;
		case Middle:
			input.mi.dwFlags = down ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP;
			break;
		default:
			break;
	}

	SendInput(2, &input, sizeof(INPUT));
}

void Input::Click(EMouseButton button)
{
	SendMouseButton(button, true);
	SendMouseButton(button, false);
}

void Input::Click(int x, int y, EMouseButton button)
{
	MoveMouse(x, y, false);
	Click(button);
}

void Input::PressKey(WORD key)
{
	SendKey(key, true);
	Sleep(150);
	SendKey(key, false);
}
// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#pragma once
#include <wtypes.h>
enum EMouseButton
{
	Left,
	Right,
	Middle
};
class Input
{
public:
	static void MoveMouse(int x, int y, bool relative);
	static void GetMousePos(int& x, int& y);
	static void SendKey(WORD key, bool down);
	static void SendMouseButton(EMouseButton button, bool down);
	static void Click(EMouseButton button);
	static void Click(int x, int y, EMouseButton button);
	static void PressKey(WORD key);
};
// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#pragma once
#include <Windows.h>
class SystemTray
{
private:
	HWND CreateHiddenWindow();
public:
	SystemTray();
	~SystemTray();
};

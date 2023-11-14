// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#include <Windows.h>
#include "SystemTray.h"
#include "Input.h"

int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//auto tray = new SystemTray();

	//Input::Click(500, 500, EMouseButton::Right);

	Input::SendKey(VK_SHIFT, true);
	Input::SendKey('A', true);

	Input::SendKey('A', false);
	Input::SendKey(VK_SHIFT, false);

	//delete(tray);
	return 0;
}
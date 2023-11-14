// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#include "SystemTray.h"
#include <shellapi.h>
#include "../resource.h"
#include <string>

#define IDM_EXIT 0x1
#define IDM_OPEN_GITHUB 0x2
#define NOTIFICATION_TRAY_ICON_MESSAGE (WM_USER + 0x89)
NOTIFYICONDATAW nid;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param)
{
	static HMENU hPopupMenu = nullptr;

	switch (message)
	{
		case NOTIFICATION_TRAY_ICON_MESSAGE:
		{
			switch (l_param)
			{
				case WM_RBUTTONUP:
				{
					POINT pt;
					GetCursorPos(&pt);

					hPopupMenu = CreatePopupMenu();
					AppendMenuW(hPopupMenu, MF_STRING, IDM_OPEN_GITHUB, L"Open GitHub");
					AppendMenuW(hPopupMenu, MF_STRING, IDM_EXIT, L"Exit");

					TrackPopupMenu(hPopupMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);

					break;
				}
			}
			break;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(w_param))
			{
				case IDM_OPEN_GITHUB:
				{
					// Handle Open GitHub option
					ShellExecuteW(NULL, L"open", L"https://github.com/drew-chase/windows-remote", NULL, NULL, SW_SHOWNORMAL);
					break;
				}
				case IDM_EXIT:
				{
					// Handle Exit option
					PostQuitMessage(0);
					break;
				}
			}

			// Close the menu after an item is selected
			if (hPopupMenu != nullptr)
			{
				DestroyMenu(hPopupMenu);
				hPopupMenu = nullptr;
			}
			break;
		}

		default:
			return DefWindowProcW(hwnd, message, w_param, l_param);
	}
}

HWND SystemTray::CreateHiddenWindow() // This is needed because windows is stupid and requires a window to be created to use the system tray.
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	const wchar_t* className = L"WindowsRemoteTrayWindowClass";
	// Register a window class for the hidden window
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	RegisterClass(&wc);

	HWND explorerHandle = FindWindowW(L"Shell_TrayWnd", NULL); // Sets the parent window to the taskbar so the context menu will get destroyed when the tray loses focus.

	// Create a hidden window
	return CreateWindowExW(0, className, L"", 0, 0, 0, 0, 0, explorerHandle /*HWND_MESSAGE*/, NULL, hInstance, NULL);
}

SystemTray::SystemTray()
{
	nid = { 0 };
	nid.cbSize = sizeof(NOTIFYICONDATAW);
	auto icon = LoadIconW(GetModuleHandle(NULL), MAKEINTRESOURCEW(IDI_MAINICON)); // Load the MAINICON resource

	if (icon == NULL)
	{
		MessageBoxW(NULL, L"Unable to load icon from application resources", L"Error", MB_OK | MB_ICONERROR);
	}

	nid.uID = 1066;
	nid.hWnd = CreateHiddenWindow();
	nid.uCallbackMessage = NOTIFICATION_TRAY_ICON_MESSAGE;
	nid.hIcon = icon;
	wcscpy_s(nid.szTip, L"Windows Remote");
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_SHOWTIP;

	if (!Shell_NotifyIconW(NIM_ADD, &nid))
	{
		auto error = GetLastError();
		MessageBoxW(NULL, (L"Unable to create the system tray icon. Error code: " + std::to_wstring(error)).c_str(), L"Error", MB_OK | MB_ICONERROR);
	}
}

SystemTray::~SystemTray()
{
	if (!Shell_NotifyIconW(NIM_DELETE, &nid))
	{
		MessageBoxW(NULL, L"Unable to create the system tray icon...", L"Error", MB_OK | MB_ICONERROR);
	}
}
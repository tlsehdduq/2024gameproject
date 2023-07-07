#include <windows.h>
#include <iostream>
#include "resource1.h"
HINSTANCE hInst;

TCHAR lpszClass[] = TEXT("크레이지 아케이드");

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{

	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	hInst = hInstance;

	if (!hPrevInstance) {
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		WndClass.hInstance = hInstance;
		WndClass.lpfnWndProc = (WNDPROC)WndProc;
		WndClass.lpszClassName = lpszClass;
		WndClass.lpszMenuName = NULL;
		WndClass.style = CS_HREDRAW | CS_VREDRAW;
		RegisterClass(&WndClass);
	}
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, 1200, 1100, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

bool IsGameStart = false;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = 0, memdc = 0;
	static HBITMAP helpbmp, introBmp, oldBit, runningBmp;
	static bool intro, help, game, unbeatable;
	static int px, py;
	static RECT player;
	TCHAR lpout[1000];
	TCHAR out[1000];
	static int score;
	static int num;
	HBRUSH MyBrush = 0, OldBrush = 0, bBrush = 0, pbrush = 0;
	HBRUSH hBrush = 0, oldBrush = 0;
	static HPEN wpen, bpen, oldpen, hPen, oldPen;
	static int ENEMY, ecount;
	static int level, linex, liney;

	switch (iMsg) {
	case WM_CREATE:
		introBmp = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		runningBmp = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps); 
		memdc = CreateCompatibleDC(hdc); 

		// 게임의 스타트 상태에 따라 출력되는 비트맵 달라지도록 함
		if (IsGameStart == false)
		{
			SelectObject(memdc, introBmp);
			StretchBlt(hdc, 0, 0, 1100, 900, memdc, 0, 0, 1200, 900, SRCCOPY);
		}
		else
		{
			SelectObject(memdc, runningBmp);
			StretchBlt(hdc, 0, 0, 1100, 900, memdc, 0, 0, 800, 600, SRCCOPY);
		}

		DeleteDC(memdc);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_F1)
		{
			IsGameStart = true;
			// 화면이 다시 그려지도록 하는 함수, WM_PAINT 다시 호출해줌
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
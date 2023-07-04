#include <windows.h>
#include <iostream>
#include "resource.h"
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
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, 1100, 900, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = 0, memdc = 0;
	static HBITMAP helpbmp, introbmp, oldBit;
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
		introbmp = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps); 
		memdc = CreateCompatibleDC(hdc); 
		SelectObject(memdc, introbmp); 
		StretchBlt(hdc, 0, 0, 1100,900, memdc, 0, 0, 1200,930, SRCCOPY);
		//--- 메모리 DC에 있는 그림에서 (0, 0)위치에서 (320, 240) 크기의 그림을
		//--- 화면의 (100, 0)위치에 (160, 120) 크기로 이미지 색 그대로 그리기
		DeleteDC(memdc);
		EndPaint(hwnd, &ps);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
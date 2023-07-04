#include <windows.h>
#include<iostream>
#include"resource.h"
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
		/** 더블버퍼링 시작처리입니다. **/
		static HDC hdc, MemDC, tmpDC;
		static HBITMAP BackBit, oldBackBit;
		static RECT bufferRT;
		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &bufferRT);
		MemDC = CreateCompatibleDC(hdc);
		BackBit = CreateCompatibleBitmap(hdc, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(MemDC, BackBit);
		PatBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
		tmpDC = hdc;
		hdc = MemDC;
		MemDC = tmpDC;
		memdc = CreateCompatibleDC(hdc);

		MyBrush = CreateSolidBrush(RGB(0, 0, 0));
		bBrush = CreateSolidBrush(RGB(255, 255, 255));
		bpen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		wpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

		SelectObject(memdc, introbmp);
		StretchBlt(hdc, 0, 0, 1000, 1000, memdc, 0, 0, 1440, 1440, SRCCOPY);

		DeleteObject(MyBrush);
		DeleteObject(OldBrush);
		DeleteObject(bBrush);
		DeleteObject(pbrush);

		/** 더블버퍼링 끝처리 입니다. **/
		tmpDC = hdc;
		hdc = MemDC;
		MemDC = tmpDC;
		GetClientRect(hwnd, &bufferRT);
		BitBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, MemDC, 0, 0, SRCCOPY);
		SelectObject(MemDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(MemDC);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:

		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_KEYUP:
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
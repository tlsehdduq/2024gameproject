#include <windows.h>
#include <iostream>
#include "resource1.h"

#define WIDTH 1100
#define HEIGHT 950

HINSTANCE hInst;
TCHAR lpszClass[] = TEXT("크레이지 아케이드");

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    // 콘솔 창 생성
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

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

    hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, WIDTH, HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }

    // 콘솔 창 닫기
    fclose(stdout);
    FreeConsole();

    return Message.wParam;
}

bool IsGameStart = false;

RECT buttonRect1 = { 92, 726, 515, 823 }; // 첫 번째 버튼의 영역
RECT buttonRect2 = { 575, 728, 998, 823 }; // 두 번째 버튼의 영역

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
            StretchBlt(hdc, 0, 0, WIDTH, HEIGHT, memdc, 0, 0, 1200, 900, SRCCOPY);
        }
        else
        {
            SelectObject(memdc, runningBmp);
            StretchBlt(hdc, 0, 0, WIDTH - 10, HEIGHT - 40, memdc, 0, 0, 800, 600, SRCCOPY);
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

    case WM_LBUTTONDOWN:
    {
        POINT cursorPos;
        cursorPos.x = LOWORD(lParam);
        cursorPos.y = HIWORD(lParam);

        if (PtInRect(&buttonRect1, cursorPos)) // 첫 번째 버튼 영역 내부를 클릭한 경우
        {
            std::cout << "게임 방법" << std::endl;
        }
        else if (PtInRect(&buttonRect2, cursorPos)) // 두 번째 버튼 영역 내부를 클릭한 경우
        {
            std::cout << "게임 시작" << std::endl;
            IsGameStart = true;
            // 화면이 다시 그려지도록 하는 함수, WM_PAINT 다시 호출해줌
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else // 어느 버튼의 영역도 클릭하지 않은 경우
        {
            std::cout << "X: " << cursorPos.x << " Y: " << cursorPos.y << std::endl;
        }
    }
    break;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

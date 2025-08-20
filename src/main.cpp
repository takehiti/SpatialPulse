#include <windows.h>
#include <windowsx.h> 
#include "WndProc.h"
#include <iostream>

// エントリーポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::cout << "[SpatialPulse] アプリ起動中..." << std::endl;

    // ウィンドウクラスの登録
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SpatialPulseWindowClass";

    RegisterClass(&wc);

    // ウィンドウの作成
    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        L"SpatialPulse",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, hInstance, nullptr
    );

    if (hwnd == nullptr) {
        std::cerr << "[SpatialPulse] ウィンドウ作成失敗" << std::endl;
        return -1;
    }

    ShowWindow(hwnd, nCmdShow);
    std::cout << "[SpatialPulse] ウィンドウ表示完了" << std::endl;

    // メッセージループ
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    std::cout << "[SpatialPulse] アプリ終了" << std::endl;
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_LBUTTONDOWN: {
        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam);

        HDC hdc = GetDC(hWnd);
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 120, 215)); // 青いペン
        HBRUSH hBrush = CreateSolidBrush(RGB(200, 230, 255)); // 薄い青のブラシ

        SelectObject(hdc, hPen);
        SelectObject(hdc, hBrush);

        Ellipse(hdc, x - 30, y - 30, x + 30, y + 30); // 波紋っぽい円

        DeleteObject(hPen);
        DeleteObject(hBrush);
        ReleaseDC(hWnd, hdc);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
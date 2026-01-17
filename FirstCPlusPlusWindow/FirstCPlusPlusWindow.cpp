#include <windows.h>
#include "Header.h"

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

    WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", SoftwareMainProcedure);

    if (!RegisterClassW(&SoftwareMainClass)) { return -1; }

    MSG SoftwareMainMessage = { 0 };

    CreateWindow(L"MainWndClass", L"First c++window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 600, NULL, NULL, NULL, NULL);

    while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
        TranslateMessage(&SoftwareMainMessage);
        DispatchMessage(&SoftwareMainMessage);
    }
    return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {

    WNDCLASS NWC = { 0 };

    NWC.hbrBackground = BGColor;
    NWC.hIcon = Icon;
    NWC.hInstance = hInst;
    NWC.lpszClassName = Name;
    NWC.hCursor = Cursor;
    NWC.lpfnWndProc = Procedure;

    return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_COMMAND:
        switch (wp) {
        case OnExitSoftware:
            PostQuitMessage(0);
            break;
        case OnMenuAction1:
            MessageBoxA(hWnd, "Menu 1 was clicked!", "Menu worked!", MB_OK);
            break;
        case OnMenuAction2:
            MessageBoxA(hWnd, "Menu 2 was clicked!", "Menu worked!", MB_OK);
            break;
        case OnMenuAction3:
            MessageBoxA(hWnd, "Menu 3 was clicked!", "Menu worked!", MB_OK);
            break;
        default: break;
        }
    case WM_CREATE:
        MainWndAddMenus(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default: return DefWindowProc(hWnd, msg, wp, lp);
    }
}

void MainWndAddMenus(HWND hWnd) {
    HMENU RootMenu = CreateMenu();
    HMENU SubMenu = CreateMenu();
    HMENU SubActionMenu = CreateMenu();

    AppendMenu(SubMenu, MF_POPUP, (UINT_PTR)SubActionMenu, L"Action");

    AppendMenu(SubActionMenu, MF_STRING, OnMenuAction1, L"Menu 1");
    AppendMenu(SubActionMenu, MF_SEPARATOR, NULL, NULL);

    AppendMenu(SubActionMenu, MF_STRING, OnMenuAction2, L"Menu 2");
    AppendMenu(SubActionMenu, MF_SEPARATOR, NULL, NULL);

    AppendMenu(SubActionMenu, MF_STRING, OnMenuAction3, L"Menu 3");

    AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");
    AppendMenu(RootMenu, MF_STRING, OnExitSoftware, L"Exit");

    SetMenu(hWnd, RootMenu);
}
#include <windows.h>
#include "Header.h"
#include "resource1.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

    WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)), L"MainWndClass", SoftwareMainProcedure);

    if (!RegisterClassW(&SoftwareMainClass)) { return -1; }

    MSG SoftwareMainMessage = { 0 };

    CreateWindow(L"MainWndClass", L"First c++window", WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX, 100, 100, 400, 300, NULL, NULL, NULL, NULL);

    while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
        TranslateMessage(&SoftwareMainMessage);
        DispatchMessage(&SoftwareMainMessage);
    }
    return 0;
}


// функция создания нового окна
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

// обработка событий
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_COMMAND:
        switch (wp) {
        case OnButtonClicked:
            MessageBoxA(hWnd, "Button is clicked!", "Thank you for click :)", MB_OK);
            break;
        case OnClearField:
            SetWindowTextA(hEditControl, ""); // очищает окно клсса edit
            break;
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
        break;
    case WM_CREATE:
        MainWndAddMenus(hWnd);
        MainWndAddWidgets(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default: return DefWindowProc(hWnd, msg, wp, lp);
    }
}

// реализация функции добавление верхнего меню
void MainWndAddMenus(HWND hWnd) {
    HMENU RootMenu = CreateMenu();
    HMENU SubMenu = CreateMenu();
    HMENU SubActionMenu = CreateMenu();

    AppendMenu(SubMenu, MF_POPUP, (UINT_PTR)SubActionMenu, L"Action");

    AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");
    AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"Help");
    AppendMenu(RootMenu, MF_STRING, OnExitSoftware, L"Exit");

    SetMenu(hWnd, RootMenu);
}

//реализация функции добавления виджетов

void MainWndAddWidgets(HWND hWnd) {

    // параметры :
    // 1. имя класса (static - позволяет вывести текст) (edit - позволяет вводить текст) (button - кнопка)
    // 2. текст виджета
    // 3. стиль окна
    // 4 и 5. расположение верхнего левого угла виджета в окне
    // 6 и 7. ширина и высота виджета в пикселях
    // 8. задаётся главное окно 
    // есть еще параметры, но их рассмотрим потом
    CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 120, 30, hWnd, HMENU(OnClearField), NULL, NULL);

    CreateWindowA("static", "STATUS: Hello window!", WS_VISIBLE | WS_CHILD , 200, 5, 490, 20, hWnd, NULL, NULL, NULL);

    hEditControl = CreateWindowA("edit", "This is EDIT control", WS_VISIBLE | WS_CHILD| ES_MULTILINE | WS_VSCROLL, 5, 50, 380, 80, hWnd, NULL, NULL, NULL);

    CreateWindowA("button", "Click me!", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 140, 120, 40, hWnd, HMENU(OnButtonClicked), NULL, NULL);
    // функция CreateWindowA возвращает созданное ей окно
}
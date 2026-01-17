#include <windows.h>
#include <string>
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
        case OnReadText:
            // функция для считывания текста (возвращает кол-во считанных символов)
            // 1. окно из которого требуется прочитать текст
            // 2. буффер из которого записываются считанные символы
            // 3. максимальное кол-во символов для считывания
            CharsRead = GetWindowTextA(hEditControl, Buffer, TextBufferSize);
            SetWindowTextA(hEditReadControl, ("Symbols read: " + std::to_string(CharsRead)).c_str());
            break;
        case OnReadNumber:
            // функция для считывания числа
            // 1. окно в котором находится виджет
            // 2. индекс окна
            // 3. ссылка на бул в которой будет результат успешности выполнения функции
            // 4. Задаем знаковое либо число
            num = GetDlgItemInt(hWnd, DlgIndexNumber, FALSE, false);
            SetWindowTextA(hNumberReadControl, std::to_string(num).c_str());
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

    // статичное поля для текста
    hEditReadControl = CreateWindowA("static", "STATUS: Hello window!", WS_VISIBLE | WS_CHILD , 200, 5, 490, 20, hWnd, NULL, NULL, NULL);
    // статичное поле для чисел
    hNumberReadControl = CreateWindowA("static", "", WS_VISIBLE | WS_CHILD, 200, 25, 490, 20, hWnd, NULL, NULL, NULL);
    // поле ввода для текста
    hEditControl = CreateWindowA("edit", "This is EDIT control", WS_VISIBLE | WS_CHILD| ES_MULTILINE | WS_VSCROLL, 5, 60, 380, 20, hWnd, NULL, NULL, NULL);
    // поле ввода для чисел
    hNumberControl = CreateWindowA("edit", "0", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, 5, 90, 380, 20, hWnd, (HMENU)DlgIndexNumber, NULL, NULL);

    // кнопка с вызовом окна
    CreateWindowA("button", "Click me!", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 140, 120, 40, hWnd, HMENU(OnButtonClicked), NULL, NULL);
    // кнопка для считывания числа из поля ввода для числа
    CreateWindowA("button", "Read the number", WS_VISIBLE | WS_CHILD | ES_CENTER, 160, 140, 120, 40, hWnd, (HMENU)OnReadNumber, NULL, NULL);
    // кнопка для считывания текста из поля ввода для текста
    CreateWindowA("button", "Read field", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 180, 120, 40, hWnd, HMENU(OnReadText), NULL, NULL);

    // функция CreateWindowA возвращает созданное ей окно
}
#define WIN32_LEAN_AND_MEAN 

#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include "IDCSettings.h"
#include "Binary.h"
#include "Decimal.h"
#include "HexaDecimal.h"
#include "BitCalculatorMachine.h"
#include "CWndCalculateMgr.h"

using namespace std;

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Calculator");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

CWndCalculateMgr* pWndCalculateMgr = CWndCalculateMgr::Instance();

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Calculator"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        356, 609,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Calculator"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        //create buttons here
        pWndCalculateMgr->CreateButtons(hWnd);
        //create the textbox here
        pWndCalculateMgr->CreateTextBox(hWnd);
        //set default environment
        pWndCalculateMgr->SetDefault(hWnd);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON_NUM_0:
        case IDC_BUTTON_NUM_1:
        case IDC_BUTTON_NUM_2:
        case IDC_BUTTON_NUM_3:
        case IDC_BUTTON_NUM_4:
        case IDC_BUTTON_NUM_5:
        case IDC_BUTTON_NUM_6:
        case IDC_BUTTON_NUM_7:
        case IDC_BUTTON_NUM_8:
        case IDC_BUTTON_NUM_9:
        case IDC_BUTTON_NUM_A:
        case IDC_BUTTON_NUM_B:
        case IDC_BUTTON_NUM_C:
        case IDC_BUTTON_NUM_D:
        case IDC_BUTTON_NUM_E:
        case IDC_BUTTON_NUM_F:
            pWndCalculateMgr->SetNumber(wParam);
            break;
        case IDC_BUTTON_PLUS:
        case IDC_BUTTON_MINUS:
        case IDC_BUTTON_MULTIPLE:
        case IDC_BUTTON_DIVIDE:
            pWndCalculateMgr->SetOperator(hWnd, wParam);
            break;
         case IDC_BUTTON_BINARY:
         case IDC_BUTTON_DECIMAL:
         case IDC_BUTTON_HEXADECIMAL:
             pWndCalculateMgr->SetConvert(hWnd, wParam);
             break;
         case IDC_BUTTON_PAREN:
             pWndCalculateMgr->SetParenthesis();
             break;
         case IDC_BUTTON_PAREN_LINE:
             pWndCalculateMgr->SetParenthesisLine();
             break;
         case IDC_BUTTON_UNARY:
             pWndCalculateMgr->SetUnary();
             break;
         case IDC_BUTTON_CLEAR:
             pWndCalculateMgr->ClearCurrent(hWnd);
             break;
         case IDC_BUTTON_CLEAR_ALL:
             pWndCalculateMgr->ClearAll(hWnd);
             break;
         case IDC_BUTTON_RUN:
             pWndCalculateMgr->Calculate();
             break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}
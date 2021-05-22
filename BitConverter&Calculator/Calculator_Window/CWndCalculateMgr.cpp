#include "CWndCalculateMgr.h"

unsigned int CWndCalculateMgr::m_IDC_button_ID[6][5] = {
    {IDC_BUTTON_CLEAR,       IDC_BUTTON_CLEAR_ALL,   IDC_BUTTON_NUM_D, IDC_BUTTON_NUM_E, IDC_BUTTON_NUM_F},
    {IDC_BUTTON_PAREN,       IDC_BUTTON_PAREN_LINE,  IDC_BUTTON_NUM_A, IDC_BUTTON_NUM_B, IDC_BUTTON_NUM_C},
    {IDC_BUTTON_UNARY,       IDC_BUTTON_PLUS,        IDC_BUTTON_NUM_7, IDC_BUTTON_NUM_8, IDC_BUTTON_NUM_9},
    {IDC_BUTTON_BINARY,      IDC_BUTTON_MINUS,       IDC_BUTTON_NUM_4, IDC_BUTTON_NUM_5, IDC_BUTTON_NUM_6},
    {IDC_BUTTON_DECIMAL,     IDC_BUTTON_MULTIPLE,    IDC_BUTTON_NUM_1, IDC_BUTTON_NUM_2, IDC_BUTTON_NUM_3},
    {IDC_BUTTON_HEXADECIMAL, IDC_BUTTON_DIVIDE,      IDC_BUTTON_NUM_0, IDC_BUTTON_RUN,   1100}
};

LPCWSTR CWndCalculateMgr::m_buttons[buttons_row][buttons_column] =
{   { _T("C"),      _T("CE"),   _T("D"),    _T("E"),    _T("F") },
    { _T("(_)"),    _T("(___)"),_T("A"),    _T("B"),    _T("C") },
    { _T("(-)"),    _T("+"),    _T("7"),    _T("8"),    _T("9") },
    { _T("B"),      _T("-"),    _T("4"),    _T("5"),    _T("6") },
    { _T("D"),      _T("*"),    _T("1"),    _T("2"),    _T("3") },
    { _T("H"),      _T("/"),    _T("0"),    _T("Run"),  _T("")  }
};

CWndCalculateMgr* CWndCalculateMgr::Instance()
{
    static CWndCalculateMgr* instance = new CWndCalculateMgr();

    return instance;
}

int CWndCalculateMgr::CreateButtons(HWND parentWnd)
{
    size_t button_width = 0u;
    size_t button_height = 0u;
    POINT button_start_pos = { 0, 150 };
    POINT button_pos = button_start_pos;

    for (int i = 0; i < buttons_column; i++)
    {
        for (int j = 0; j < buttons_row; j++)
        {
            if (j == 5 && i == 4)
            {
                /*relating to run button design*/
                continue;
            }

            if (i == 0 || i == 1)
            {
                /*button design except number buttons*/
                button_width = 80;
                button_height = 60;
            }
            else if (j == 5 && i == 3)
            {
                /*Run Button*/
                button_width = 120;
                button_height = 60;
            }
            else
            {
                /*number button design*/
                button_width = 60;
                button_height = 60;
            }

            button_pos.y += button_height;

            HWND hwndButton = CreateWindow(
                TEXT("button"),
                m_buttons[j][i],
                WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                button_pos.x,
                button_pos.y,
                button_width,
                button_height,
                parentWnd,
                (HMENU)m_IDC_button_ID[j][i],
                (HINSTANCE)GetWindowLongPtr(parentWnd, GWLP_HINSTANCE),
                NULL);

            if (j == 5 && i == 3)
            {
                /*modify inconsistent position of buttons by run button */
                button_width = 60;
            }

            if (hwndButton == NULL)
            {
                MessageBox(NULL, L"Failed to create buttons", L"Error", MB_ICONERROR | MB_OK);
                return 0;
            }
        }

        button_pos.x += button_width;
        button_pos.y = button_start_pos.y;
    }

    return 0;
}

int CWndCalculateMgr::CreateTextBox(HWND parentWnd)
{
    m_hWndTextBox = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        TEXT("edit"),
        NULL,
        WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE,
        0,
        0,
        340,
        210,
        parentWnd,
        (HMENU)IDC_TEXTBOX,
        (HINSTANCE)GetWindowLongPtr(parentWnd, GWLP_HINSTANCE),
        NULL);

    return 0;
}

int CWndCalculateMgr::SetDefault(HWND parentWnd)
{
    m_szTextBoxWorking = "0";
    ModifyingText();

    SetDecimalButtonControl(parentWnd);

    return 0;
}

int CWndCalculateMgr::SetParenthesis()
{
    if (m_szTextBoxWorking.length() == 0)
    {
        return 0;
    }

    if (m_szTextBoxWorking[0] == '(' && m_szTextBoxWorking[1] != '-')
    {
        m_szTextBoxWorking.erase(m_szTextBoxWorking.length() - 1, 1);
        m_szTextBoxWorking.erase(0, 1);
    }
    else
    {
        m_szTextBoxWorking = '(' + m_szTextBoxWorking + ')';
    }

    ModifyingText();

    return 0;
}

int CWndCalculateMgr::SetParenthesisLine()
{
    if (m_szTextBoxWorking.length() == 0)
    {
        return 0;
    }

    m_szTextBoxExpression += m_szTextBoxWorking;
    m_szTextBoxWorking = "";

    if (m_szTextBoxExpression[0] == '(' && m_szTextBoxExpression[m_szTextBoxExpression.length() - 1] == ')')
    {
        m_szTextBoxExpression.erase(m_szTextBoxExpression.length() - 1, 1);
        m_szTextBoxExpression.erase(0, 1);
    }
    else
    {
        m_szTextBoxExpression = '(' + m_szTextBoxExpression + ')';
    }


    ModifyingText();

    return 0;
}

int CWndCalculateMgr::SetUnary()
{
    if (m_szTextBoxWorking.length() == 0)
    {
        return 0;
    }

    if (m_szTextBoxWorking[0] == '(' && m_szTextBoxWorking[1] == '-')
    {
        m_szTextBoxWorking.erase(m_szTextBoxWorking.length() - 1, 1);
        m_szTextBoxWorking.erase(0, 2);
    }
    else if (m_szTextBoxWorking[0] == '-')
    {
        m_szTextBoxWorking.erase(0, 1);
    }
    else
    {
        m_szTextBoxWorking = "(-" + m_szTextBoxWorking + ')';
    }

    ModifyingText();

    return 0;
}

int CWndCalculateMgr::SetNumber(WPARAM wParam)
{
    /*adding operator must be next process*/
    if (HasParenthesis(m_szTextBoxWorking) || HasParenthesis(m_szTextBoxExpression))
    {
        return 0;
    }

    if (m_szTextBoxWorking == "0")
    {
        m_szTextBoxWorking = "";
    }

    UINT number = wParam - IDC_BUTTON_NUM_0;

    if (number >= 0 && number <= 9)
    {
        m_szTextBoxWorking += (number | 0b110000);
    }
    else if (number >= 10)
    {
        m_szTextBoxWorking += (number + 55);
    }

    ModifyingText();

    return 0;
}

int CWndCalculateMgr::SetConvert(HWND parentWnd, WPARAM wParam)
{
    if (m_szTextBoxWorking.length() == 0)
    {
        return 0;
    }

    string workingText = m_szTextBoxWorking;

    IDigitNumber* number;

    if (m_szTextBoxWorking[0] == 'b' || m_szTextBoxWorking[1] == 'b')
    {
        workingText.erase(0, 1);
        number = new Binary(workingText);
    }
    else if (m_szTextBoxWorking[0] == 'x' || m_szTextBoxWorking[1] == 'x')
    {
        workingText.erase(0, 1);
        number = new HexaDecimal(workingText);
    }
    else
    {
        number = new Decimal(workingText);
    }

    switch (wParam)
    {
    case IDC_BUTTON_BINARY:
        SetBinaryButtonControl(parentWnd);
        m_szTextBoxWorking = 'b' + number->ConvertToBinary();
        break;
    case IDC_BUTTON_DECIMAL:
        SetDecimalButtonControl(parentWnd);
        m_szTextBoxWorking = number->ConvertToDecimal();
        break;
    case IDC_BUTTON_HEXADECIMAL:
        SetHexaButtonControl(parentWnd);
        m_szTextBoxWorking = 'x' + number->ConvertToHexaDecimal();
        break;
    }

    ModifyingText();

    return 0;
}

int CWndCalculateMgr::SetOperator(HWND parentWnd, WPARAM wParam)
{
    SetDecimalButtonControl(parentWnd);

    if (m_szTextBoxWorking.length() == 0 && HasParenthesis(m_szTextBoxExpression) == false)
    {
        return 0;
    }

    switch (wParam)
    {
    case IDC_BUTTON_PLUS:
        m_szTextBoxWorking = m_szTextBoxWorking + " + ";
        break;
    case IDC_BUTTON_MINUS:
        m_szTextBoxWorking = m_szTextBoxWorking + " - ";
        break;
    case IDC_BUTTON_MULTIPLE:
        m_szTextBoxWorking = m_szTextBoxWorking + " * ";
        break;
    case IDC_BUTTON_DIVIDE:
        m_szTextBoxWorking = m_szTextBoxWorking + " / ";
        break;
    }

    m_szTextBoxExpression += m_szTextBoxWorking;
    m_szTextBoxWorking = "";

    ModifyingText();

    return 0;
}

int CWndCalculateMgr::ClearCurrent(HWND parentWnd)
{
    SetDecimalButtonControl(parentWnd);

    if (m_szTextBoxWorking.length() == 0)
    {
        return 0;
    }

    m_szTextBoxWorking = "";

    ModifyingText();

    return 0;
}

int CWndCalculateMgr::ClearAll(HWND parentWnd)
{
    SetDecimalButtonControl(parentWnd);

    m_szTextBoxWorking = "";
    m_szTextBoxExpression = "";
    m_szTextBoxResult = "";

    ModifyingText();

    return 0;
}

int CWndCalculateMgr::Calculate()
{
    m_szTextBoxExpression += m_szTextBoxWorking;
    m_szTextBoxWorking = "";

    BitCalculatorMachine* machine = new BitCalculatorMachine();

    m_szTextBoxResult = " = " +  machine->Calculation(m_szTextBoxExpression);

    ModifyingText();

    return 0;
}

int CWndCalculateMgr::ModifyingText()
{
    string text = m_szTextBoxExpression + "\r\n";
    text += m_szTextBoxWorking + "\r\n";
    text += m_szTextBoxResult;

    SetWindowText(m_hWndTextBox, s2ws(text).c_str());

    return 0;
}

wstring CWndCalculateMgr::s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

void CWndCalculateMgr::SetBinaryButtonControl(HWND parentWnd)
{
    /*(-)unary button*/
    HWND hUnaryButton = GetDlgItem(parentWnd, IDC_BUTTON_UNARY);
    EnableWindow(hUnaryButton, false);

    /*number buttons*/
    for (size_t IDC_idx = IDC_BUTTON_NUM_0; IDC_idx <= IDC_BUTTON_NUM_F; IDC_idx++)
    {
        HWND hButton = GetDlgItem(parentWnd, IDC_idx);
        EnableWindow(hButton, false);
    }

    for (size_t IDC_idx = IDC_BUTTON_NUM_0; IDC_idx < IDC_BUTTON_NUM_2; IDC_idx++)
    {
        HWND hButton = GetDlgItem(parentWnd, IDC_idx);
        EnableWindow(hButton, true);
    }
}

void CWndCalculateMgr::SetDecimalButtonControl(HWND parentWnd)
{
    /*(-)unary button*/
    HWND hUnaryButton = GetDlgItem(parentWnd, IDC_BUTTON_UNARY);
    EnableWindow(hUnaryButton, true);

    /*number buttons*/
    for (size_t IDC_idx = IDC_BUTTON_NUM_0; IDC_idx <= IDC_BUTTON_NUM_F; IDC_idx++)
    {
        HWND hButton = GetDlgItem(parentWnd, IDC_idx);
        EnableWindow(hButton, false);
    }

    for (size_t IDC_idx = IDC_BUTTON_NUM_0; IDC_idx < IDC_BUTTON_NUM_A; IDC_idx++)
    {
        HWND hButton = GetDlgItem(parentWnd, IDC_idx);
        EnableWindow(hButton, true);
    }
}

void CWndCalculateMgr::SetHexaButtonControl(HWND parentWnd)
{
    /*(-)unary button*/
    HWND hUnaryButton = GetDlgItem(parentWnd, IDC_BUTTON_UNARY);
    EnableWindow(hUnaryButton, false);

    /*number buttons*/
    for (size_t IDC_idx = IDC_BUTTON_NUM_0; IDC_idx <= IDC_BUTTON_NUM_F; IDC_idx++)
    {
        HWND hButton = GetDlgItem(parentWnd, IDC_idx);
        EnableWindow(hButton, true);
    }
}

bool CWndCalculateMgr::HasParenthesis(string str)
{
    if (str[0] == '(' && str[str.length() - 1] == ')')
    {
        return true;
    }

    return false;
}

#pragma once
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include "IDCSettings.h"
#include "Binary.h"
#include "Decimal.h"
#include "HexaDecimal.h"
#include "BitCalculatorMachine.h"
#include "Includes.h"

constexpr size_t buttons_row = 6;
constexpr size_t buttons_column = 5;

class CWndCalculateMgr
{
public:
	static CWndCalculateMgr* Instance();

	int CreateButtons(HWND parentWnd);
	int CreateTextBox(HWND parentWnd);
	int SetDefault(HWND parentWnd);
	int SetParenthesis();
	int SetParenthesisLine();
	int SetUnary();
	int SetNumber(WPARAM wParam);
	int SetConvert(HWND parentWnd, WPARAM wParam);
	int SetOperator(HWND parentWnd, WPARAM wParam);
	int ClearCurrent(HWND parentWnd);
	int ClearAll(HWND parentWnd);
	int Calculate();
	int ModifyingText();
	wstring s2ws(const std::string& s);

private:
	void SetBinaryButtonControl(HWND parentWnd);
	void SetDecimalButtonControl(HWND parentWnd);
	void SetHexaButtonControl(HWND parentWnd);

	bool HasParenthesis(string str);

private:
	HWND m_hWndTextBox;

	string m_szTextBoxWorking;
	string m_szTextBoxExpression;
	string m_szTextBoxResult;

	static unsigned int m_IDC_button_ID[buttons_row][buttons_column];
	static LPCWSTR m_buttons[buttons_row][buttons_column];
};


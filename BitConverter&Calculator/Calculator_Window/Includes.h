#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

#define MSG_BOX(text) MessageBox(NULL, TEXT(text), NULL, MB_OK)
#define PROPERTY(_get, _set) _declspec(property(get = _get, put = _set))
#define PROPERTY_S(_set) _declspec(property(put = _set))
#define PROPERTY_G(_get) _declspec(property(get = _get))

using namespace std;
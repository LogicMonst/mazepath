#pragma once
#include <windows.h>

class Test
{
public:
	Test();
	~Test();
	void doTest();
	static void SetConsoleWindowSize(SHORT width, SHORT height);
};

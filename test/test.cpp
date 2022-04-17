#include "test.h"
#include "../src/base/vec2.h"
#include "../src/base/commonFunc.h"
#include "../src/logic/nodemanager.h"
#include "../src/logic/mazemanager.h"
#include <iostream>
#include <vector>
#include "../src/base/myrandom.h"




Test::Test()
{

}

Test::~Test()
{

}



void Test::SetConsoleWindowSize(SHORT width, SHORT height)
{
	HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT wrt = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(hStdOutput, TRUE, &wrt); // ÉèÖÃ´°Ìå³ß´ç
	COORD coord = { width, height };
	SetConsoleScreenBufferSize(hStdOutput, coord); // ÉèÖÃ»º³å³ß´ç
}

void Test::doTest()
{
	//MyRandom::GetInstance()->resetSeed(46154);

	int tempArray[10];
	memset(tempArray, 1, sizeof(tempArray));
	int tempArray02[2][3] = { 1,2,3,4,5,6 };

	std::vector<Vec2<int>> tempVec01;
	std::vector<Vec2<int>> tempVec02;
	tempVec01.emplace_back(1, 1);
	tempVec01.emplace_back(Vec2<int>(1, 1));
	tempVec01.emplace_back(Vec2<int>(1, 1));
	tempVec01.emplace_back(Vec2<int>(1, 1));

	std::vector<Vec2<int>>& tempVec03 = tempVec01;


	tempVec02 = tempVec03;
	tempVec03[2] = Vec2<int>(2, 2);


	Vec2<int> Vec2_01;
	Vec2<int> Vec2_02(1, 1);
	Vec2<int> Vec2_03({ 2,2 });
	Vec2_01 = Vec2_02;


	Vec2<int> temp01 = CommonFunc::VecXAdd(Vec2_02, Vec2_03);
	auto temp02 = CommonFunc::VecXMinus(Vec2_02, Vec2_03);
	bool temp03 = Vec2_01 == Vec2_02;
	bool temp04 = temp01 == temp02;

	auto tempNodeM = NodeManager::GetInstance();
	auto tempMazeM = MazeManager::GetInstance();
	/*delete tempMazeM;*/
	tempMazeM->generateMazePath(36, 12, MazeMethod::Prim);
	//SetConsoleWindowSize(36*3+2, 12*3+5);

	std::string strString = tempMazeM->getMazePathStr();
	std::cout << strString << std::endl;

	std::vector<int> randVec;
	randVec.clear();
	for (int k = 0; k < 10; ++k)
	{
		randVec.emplace_back(MyRandom::GetInstance()->getRandom(4));
	}
	for (int k = 0; k < 10; ++k)
	{
		randVec.emplace_back(MyRandom::GetInstance()->getRandom(4));
	}

	int tempPause = 0;
}



#pragma once
#include <string>
#include "mydef.h"


class MazeManager
{
public:
	MazeManager();
	~MazeManager();
	static MazeManager* GetInstance();

	void generateMazePath(const int& nWidth, const int& nHeight, MazeMethod mazeMethod = MazeMethod::None);

	std::string getMazePathStr();
protected:
	bool init();

protected:
	static MazeManager* s_pMazeManager;
};

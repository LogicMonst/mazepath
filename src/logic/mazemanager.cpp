#include "mazemanager.h"
#include "nodemanager.h"

bool MazeManager::init()
{

	return true;
}

MazeManager* MazeManager::s_pMazeManager = nullptr;

MazeManager::MazeManager()
{

}

MazeManager::~MazeManager()
{
	s_pMazeManager = nullptr;
}

MazeManager* MazeManager::GetInstance()
{
	if (!s_pMazeManager)
	{
		s_pMazeManager = new MazeManager();
		s_pMazeManager->init();
	}
	return s_pMazeManager;
}

void MazeManager::generateMazePath(const int& nWidth, const int& nHeight, MazeMethod mazeMethod)
{
	if (nWidth < c_nMinMazeLength || nHeight < c_nMinMazeLength)
	{
		assert(false);
		return;
	}

	auto nodeM = NodeManager::GetInstance();
	nodeM->initMazePoints(nWidth, nHeight);

	switch (mazeMethod)
	{
	case MazeMethod::DepthFirst:
		nodeM->generateMazePath_DepthFirst();
		break;
	case MazeMethod::Kruskal:
		nodeM->generateMazePath_Kruskal();
		break;
	case MazeMethod::Prim:
		nodeM->generateMazePath_Prim();
		break;
	case MazeMethod::Recursion:
		break;
	default:
		break;
	}

}

std::string MazeManager::getMazePathStr()
{
	auto nodeM = NodeManager::GetInstance();
	return nodeM->getPointsString();
}


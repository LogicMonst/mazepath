#pragma once
#include "node.h"
#include <vector>


class NodeManager
{
public:
	NodeManager();
	~NodeManager();
	static NodeManager* GetInstance();
	void initMazePoints(const int& nWidth, const int& nHeight);
	std::string getPointsString();

	void generateMazePath_DepthFirst();
	void generateMazePath_Kruskal();
	void generateMazePath_Prim();
protected:
	bool init();
	void initBeforeGenerate();

	Vec2<int> loop_DepthFirst(Vec2<int> currPos, int& nCheckNum, std::vector<Vec2<int>>& pathVec);

	Vec2<int> nextNode_DepthFirst(Vec2<int> currPos, WallDirection& nWallDirection);

	std::vector<Vec2<int>> getPath(bool nCheckEndPos = false);

protected:
	static NodeManager* s_pNodeManager;

	int m_nWidth;
	int m_nHeight;

	Node** m_pPoints;

	Vec2<int> m_StartNodePos;
	Vec2<int> m_EndNodePos;
	std::vector<Vec2<int>> m_VecPath;


};

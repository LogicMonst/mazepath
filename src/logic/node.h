#pragma once
#include "mydef.h"
#include <string>
#include "../base/vec2.h"
#include <vector>
#include "../base/vec3.h"


class Node
{
public:
	Node();
	~Node();
	void setNodeBoundary(const NodeBoundary& nBoundary);
	std::string getWallString(WallDirection nDirection);
	void setPos(const int& nX, const int& nY);
	Vec2<int> getPos();
	void initCheckWalls();
	Vec2<int> nextNode_DepthFirst(WallDirection& nWallDirection);	//返回自己表示需要回溯
	void setWall(WallType nWallType, WallDirection nDirection, bool changeCheck = false);
	WallType getWall(WallDirection nDirection);
	void changeNoneToWall();
	void changeNoneToNoWall();
	void setState(NodeState nState);
	NodeState getState();
	bool isChecked();
	void setIsInPath(const int& nInPathIndex);
	int getInPathIndex();

	void setParentPos(Vec2<int> parentPos);
	Vec2<int> getParentPos();
	void setDepth(const int& nDepth);
	int getDepth();

	void addDefaultWallToVec(std::vector<Vec3<int>>& targetVec);

	//Kruskal
	void setAreaID(const int& nAreaID);
	int getAreaID();



protected:


protected:
	WallType m_nWalls[static_cast<int>(WallDirection::Num)];
	int m_nNodeBoundary;
	Vec2<int> m_nPos;
	std::vector<WallDirection> m_VecWaitCheckDirection;
	NodeState m_nState;
	int m_nInPathIndex;

	Vec2<int> m_nParentPos;
	int m_nDepth;	//根节点遍历到此的高度

	//Kruskal
	int m_nAreaID;
	std::vector<Vec2<int>>* m_pVecNodesInSameArea;
};

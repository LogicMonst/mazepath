#include "node.h"
#include <vcruntime_string.h>
#include "../base/commonFunc.h"
#include "../base/myrandom.h"
#include "mytools.h"



Node::Node()
	:m_nNodeBoundary(0)
	, m_nState(NodeState::None)
	, m_nInPathIndex(-1)
	, m_nAreaID(0)
	, m_pVecNodesInSameArea(nullptr)
	, m_nDepth(0)
{
	memset(m_nWalls, static_cast<int>(WallType::None), sizeof(m_nWalls));
	m_VecWaitCheckDirection.reserve(4);
	m_VecWaitCheckDirection.clear();

}

Node::~Node()
{

}

void Node::setNodeBoundary(const NodeBoundary& nBoundary)
{
	m_nNodeBoundary |= static_cast<int>(nBoundary);
	m_nWalls[static_cast<int>(MyTools::GetDirectionByBoundary(nBoundary))] = WallType::Wall;

}

std::string Node::getWallString(WallDirection nDirection)
{
	std::string tempStr = "";
	WallType tempType = m_nWalls[static_cast<int>(nDirection)];
	switch (nDirection)
	{
	case WallDirection::Up:
	case WallDirection::Down:
		if (tempType == WallType::None || tempType == WallType::Wall)
		{
			tempStr = "¡ª";
		}
		else
		{
			tempStr = "  ";
		}
		break;
	case WallDirection::Left:
		//case WallDirection::Right:
		if (tempType == WallType::None || tempType == WallType::Wall)
		{
			tempStr = "|";
		}
		else
		{
			tempStr = " ";
		}
		if (m_nInPathIndex >= 0)
		{
			tempStr += std::to_string(m_nInPathIndex % 10) + " ";
		}
		else
		{
			tempStr += "  ";
		}
		if (CommonFunc::HasFlag(m_nNodeBoundary, static_cast<int>(NodeBoundary::Right)))
		{
			tempStr += "|";
		}
		break;
	default:
		assert(false);
		break;
	}
	return tempStr;
}

void Node::setPos(const int& nX, const int& nY)
{
	m_nPos = Vec2<int>(nX, nY);

}

Vec2<int> Node::getPos()
{
	return m_nPos;
}

void Node::initCheckWalls()
{
	m_VecWaitCheckDirection.clear();
	for (int k = 0; k < static_cast<int>(WallDirection::Num); ++k)
	{
		if (m_nWalls[k] == WallType::None)
		{
			m_VecWaitCheckDirection.emplace_back((WallDirection)k);
		}
	}
}

Vec2<int> Node::nextNode_DepthFirst(WallDirection& nWallDirection)
{
	if (m_VecWaitCheckDirection.size() < 1)
	{
		return m_nPos;
	}
	int nIndex = MyRandom::GetInstance()->getRandom(m_VecWaitCheckDirection.size());
	nWallDirection = m_VecWaitCheckDirection[nIndex];
	//m_VecWaitCheckDirection.erase(m_VecWaitCheckDirection.begin() + nIndex);
	return MyTools::GetNextPosByDirection(m_nPos,nWallDirection);
}

void Node::setWall(WallType nWallType, WallDirection nDirection, bool changeCheck/* = false*/)
{
	m_nWalls[static_cast<int>(nDirection)] = nWallType;
	if (changeCheck)
	{
		initCheckWalls();
	}
}

WallType Node::getWall(WallDirection nDirection)
{
	assert(nDirection != WallDirection::Num);
	return m_nWalls[static_cast<int>(nDirection)];
}

void Node::changeNoneToWall()
{
	for (int k = 0; k < static_cast<int>(WallDirection::Num); ++k)
	{
		if (m_nWalls[k] == WallType::None)
		{
			m_nWalls[k] = WallType::Wall;
		}
	}
}

void Node::changeNoneToNoWall()
{
	for (int k = 0; k < static_cast<int>(WallDirection::Num); ++k)
	{
		if (m_nWalls[k] == WallType::None)
		{
			m_nWalls[k] = WallType::NoWall;
		}
	}
}

void Node::setState(NodeState nState)
{
	m_nState = nState;
}

NodeState Node::getState()
{
	return m_nState;
}

bool Node::isChecked()
{
	return m_nState == NodeState::Checked;
}


void Node::setIsInPath(const int& nInPathIndex)
{
	m_nInPathIndex = nInPathIndex;
}

int Node::getInPathIndex()
{
	return m_nInPathIndex;
}

void Node::setParentPos(Vec2<int> parentPos)
{
	m_nParentPos = parentPos;
}

Vec2<int> Node::getParentPos()
{
	return m_nParentPos;
}

void Node::setDepth(const int& nDepth)
{
	m_nDepth = nDepth;
}

int Node::getDepth()
{
	return m_nDepth;
}

void Node::addDefaultWallToVec(std::vector<Vec3<int>>& targetVec)
{
	for (int k = 0; k < static_cast<int>(WallDirection::Num); ++k)
	{
		if (m_nWalls[k] == WallType::None)
		{
			targetVec.emplace_back(m_nPos.x, m_nPos.y, k);
		}
	}
}

void Node::setAreaID(const int& nAreaID)
{
	m_nAreaID = nAreaID;
}

int Node::getAreaID()
{
	return m_nAreaID;
}


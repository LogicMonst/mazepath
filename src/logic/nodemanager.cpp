#include "nodemanager.h"
#include "../base/myrandom.h"
#include "mytools.h"
#include "../base/vec3.h"
#include "../base/commonFunc.h"
#include <map>


NodeManager* NodeManager::s_pNodeManager = nullptr;

NodeManager::NodeManager()
	:m_nWidth(0)
	, m_nHeight(0)
	, m_pPoints(nullptr)
{

}

NodeManager::~NodeManager()
{
	s_pNodeManager = nullptr;
}

NodeManager* NodeManager::GetInstance()
{
	if (!s_pNodeManager)
	{
		s_pNodeManager = new NodeManager();
		s_pNodeManager->init();
	}
	return s_pNodeManager;
}

bool NodeManager::init()
{

	return true;
}

void NodeManager::initBeforeGenerate()
{
	//m_StartNodePos.x = MyRandom::GetInstance()->getRandom(m_nWidth);
	m_StartNodePos.x = 0;
	m_StartNodePos.y = m_nHeight - 1;
	m_VecPath.reserve(m_nWidth * m_nHeight);
	m_VecPath.clear();
}

void NodeManager::initMazePoints(const int& nWidth, const int& nHeight)
{
	assert(nWidth > 0 && nHeight > 0);
	if (m_pPoints)
	{
		for (int k = 0; k < m_nHeight; ++k)
		{
			delete[] m_pPoints[k];
		}
		delete[] m_pPoints;
	}
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_pPoints = new Node * [m_nHeight];
	for (int k = 0; k < m_nHeight; ++k)
	{
		m_pPoints[k] = new Node[m_nWidth];
		for (int n = 0; n < m_nWidth; ++n)
		{
			m_pPoints[k][n].setPos(n, k);
		}
	}

	//初始化边界墙
	for (int k = 0; k < m_nHeight; ++k)
	{
		m_pPoints[k][0].setNodeBoundary(NodeBoundary::Left);
		m_pPoints[k][m_nWidth - 1].setNodeBoundary(NodeBoundary::Right);
	}
	for (int k = 0; k < m_nWidth; ++k)
	{
		m_pPoints[0][k].setNodeBoundary(NodeBoundary::Up);
		m_pPoints[m_nHeight - 1][k].setNodeBoundary(NodeBoundary::Down);
	}

	//初始化待检查墙
	for (int j = 0; j < m_nHeight; ++j)
	{
		for (int k = 0; k < m_nWidth; ++k)
		{
			m_pPoints[j][k].initCheckWalls();
		}

	}

}

std::string NodeManager::getPointsString()
{
	std::string strMazePath = "";
	for (int j = 0; j < m_nHeight; ++j)
	{
		for (int k = 0; k < m_nWidth; ++k)
		{
			strMazePath += ("*" + m_pPoints[j][k].getWallString(WallDirection::Up));
		}
		strMazePath += "*\r\n";
		for (int k = 0; k < m_nWidth; ++k)
		{
			strMazePath += m_pPoints[j][k].getWallString(WallDirection::Left);
		}
		strMazePath += "\r\n";
	}
	for (int k = 0; k < m_nWidth; ++k)
	{
		strMazePath += ("*" + m_pPoints[m_nHeight - 1][k].getWallString(WallDirection::Down));
	}
	strMazePath += "*\r\n";
	return strMazePath;
}

Vec2<int> NodeManager::loop_DepthFirst(Vec2<int> currPos, int& nCheckNum, std::vector<Vec2<int>>& pathVec)
{
	WallDirection tempDirection = WallDirection::Up;
	Vec2<int> nextPos = nextNode_DepthFirst(currPos, tempDirection);
	if (nextPos == currPos)
	{
		//回溯
		if (pathVec.size() < 2)
		{
			++nCheckNum;
			//assert(false);
			return currPos;
		}
		pathVec.pop_back();
		currPos = pathVec.back();
		return loop_DepthFirst(currPos, nCheckNum, pathVec);
	}
	pathVec.emplace_back(nextPos);
	++nCheckNum;
	m_pPoints[currPos.y][currPos.x].setWall(WallType::NoWall, tempDirection, true);
	m_pPoints[nextPos.y][nextPos.x].setWall(WallType::NoWall, MyTools::GetOppositeDirection(tempDirection), true);
	m_pPoints[nextPos.y][nextPos.x].setState(NodeState::Checked);
	m_pPoints[nextPos.y][nextPos.x].setParentPos(currPos);
	m_pPoints[nextPos.y][nextPos.x].setDepth(m_pPoints[currPos.y][currPos.x].getDepth() + 1);
	if (pathVec.size() > m_VecPath.size())
	{
		m_VecPath = pathVec;		//TODO 此处可优化省略，省略后路径需要根据最深节点的父节点逆向查找路径
	}
	return nextPos;

}

Vec2<int> NodeManager::nextNode_DepthFirst(Vec2<int> currPos, WallDirection& nWallDirection)
{
	Vec2<int> nextPos = m_pPoints[currPos.y][currPos.x].nextNode_DepthFirst(nWallDirection);
	if (nextPos != currPos)
	{
		if (m_pPoints[nextPos.y][nextPos.x].isChecked())
		{
			m_pPoints[currPos.y][currPos.x].setWall(WallType::Wall, nWallDirection, true);
			m_pPoints[nextPos.y][nextPos.x].setWall(WallType::Wall, MyTools::GetOppositeDirection(nWallDirection), true);
			return nextNode_DepthFirst(currPos, nWallDirection);
		}
		return nextPos;
	}
	else
	{
		return currPos;
	}
}

std::vector<Vec2<int>> NodeManager::getPath(bool nCheckEndPos /*= false*/)
{
	Vec2<int> nEndPos;
	int nDepthMax = 0;
	for (int j = 0; j < m_nHeight; ++j)
	{
		for (int k = 0; k < m_nWidth; ++k)
		{
			if (m_pPoints[j][k].getDepth() > nDepthMax)
			{
				nDepthMax = m_pPoints[j][k].getDepth();
				nEndPos = m_pPoints[j][k].getPos();
			}
		}

	}
	//可能存在多条相同深度的路径 校验m_EndPos
	if (nCheckEndPos && nEndPos != m_EndNodePos)
	{
		assert(m_pPoints[m_EndNodePos.y][m_EndNodePos.x].getDepth() == nDepthMax);
		nEndPos = m_EndNodePos;
	}
	std::vector<Vec2<int>> checkPathVec;
	checkPathVec.reserve(m_nWidth * m_nHeight);
	checkPathVec.clear();
	Vec2<int> nCheckPos = nEndPos;
	int nCheckDepth = nDepthMax;
	while (nCheckDepth > 0)
	{
		checkPathVec.emplace_back(m_pPoints[nCheckPos.y][nCheckPos.x].getPos());
		nCheckPos = m_pPoints[nCheckPos.y][nCheckPos.x].getParentPos();
		nCheckDepth = m_pPoints[nCheckPos.y][nCheckPos.x].getDepth();
	}
	checkPathVec.emplace_back(m_StartNodePos);
	reverse(checkPathVec.begin(), checkPathVec.end());

	if (nCheckEndPos)
	{
		assert(checkPathVec.size() == m_VecPath.size() && nEndPos == m_EndNodePos);
		for (int k = 0; k < checkPathVec.size(); ++k)
		{
			assert(checkPathVec[k] == m_VecPath[k]);
		}
	}

	return checkPathVec;
}

void NodeManager::generateMazePath_DepthFirst()
{
	initBeforeGenerate();

	std::vector<Vec2<int>> tempPathVec;
	tempPathVec.reserve(m_nWidth * m_nHeight);
	tempPathVec.clear();
	tempPathVec.emplace_back(m_StartNodePos);
	m_VecPath = tempPathVec;

	m_pPoints[m_StartNodePos.y][m_StartNodePos.x].setState(NodeState::Checked);

	int nCheckNum = 1;
	Vec2<int> currPos = m_StartNodePos;
	while (nCheckNum < m_nHeight * m_nWidth)
	{
		currPos = loop_DepthFirst(currPos, nCheckNum, tempPathVec);
	}
	m_EndNodePos = m_VecPath.back();

	for (int j = 0; j < m_nHeight; ++j)
	{
		for (int k = 0; k < m_nWidth; ++k)
		{
			m_pPoints[j][k].changeNoneToWall();
		}

	}
	for (int k = 0; k < m_VecPath.size(); ++k)
	{
		m_pPoints[m_VecPath[k].y][m_VecPath[k].x].setIsInPath(k);
	}

	//校验通过深度计算的路径		//TODO，经校验，方案可行，深度遍历时可不用记路径，减少vector的深copy操作
	getPath(true);

}

void NodeManager::generateMazePath_Kruskal()
{
	initBeforeGenerate();

	std::vector<Vec3<int>> vecAllWalls;
	vecAllWalls.reserve(m_nWidth * m_nHeight * 4);
	vecAllWalls.clear();

	std::map<int, std::vector<Vec2<int>>> mapAllAreass;
	mapAllAreass.clear();

	int nAreaID = 0;
	for (int j = 0; j < m_nHeight; ++j)
	{
		for (int k = 0; k < m_nWidth; ++k)
		{
			//无向图，所以每条边只算一次，即 vecAllWalls 不应该存在重复的边
			for (int m = 0; m < static_cast<int>(WallDirection::Down); ++m)
			{
				if (m_pPoints[j][k].getWall((WallDirection)m) == WallType::None)
				{
					vecAllWalls.emplace_back(k, j, m);
				}
			}
			m_pPoints[j][k].setAreaID(nAreaID++);
		}

	}
	//随机化vector
	int nAllWallLength = vecAllWalls.size();
	for (int k = nAllWallLength - 1; k > 0; --k)
	{
		int nChangeIndex = MyRandom::GetInstance()->getRandom(k + 1);
		Vec3<int> nTempVec3 = vecAllWalls[k];
		vecAllWalls[k] = vecAllWalls[nChangeIndex];
		vecAllWalls[nChangeIndex] = nTempVec3;
	}

	for (auto myIterator = vecAllWalls.begin(); myIterator != vecAllWalls.end(); ++myIterator)
	{
		Vec2<int> currPos(myIterator->x, myIterator->y);
		Vec2<int> nextPos = MyTools::GetNextPosByDirection(currPos, (WallDirection)(myIterator->z));

		int nCurrAreaID = m_pPoints[currPos.y][currPos.x].getAreaID();
		int nNextAreaID = m_pPoints[nextPos.y][nextPos.x].getAreaID();

		if (nCurrAreaID != nNextAreaID)
		{
			m_pPoints[currPos.y][currPos.x].setWall(WallType::NoWall, (WallDirection)(myIterator->z));
			m_pPoints[nextPos.y][nextPos.x].setWall(WallType::NoWall, MyTools::GetOppositeDirection((WallDirection)(myIterator->z)));
			if (mapAllAreass.find(nCurrAreaID) == mapAllAreass.end())
			{
				std::vector<Vec2<int>> vecCurrArea;
				vecCurrArea.reserve(32);
				vecCurrArea.clear();
				vecCurrArea.emplace_back(currPos);
				mapAllAreass.insert(std::pair<int, std::vector<Vec2<int>>>(nCurrAreaID, vecCurrArea));
			}
			m_pPoints[nextPos.y][nextPos.x].setAreaID(nCurrAreaID);
			mapAllAreass[nCurrAreaID].emplace_back(nextPos);
			if (mapAllAreass.find(nNextAreaID) != mapAllAreass.end())
			{
				for (auto tempItreator = mapAllAreass[nNextAreaID].begin(); tempItreator != mapAllAreass[nNextAreaID].end(); ++tempItreator)
				{
					if (nextPos != (*tempItreator))
					{
						m_pPoints[tempItreator->y][tempItreator->x].setAreaID(nCurrAreaID);
						mapAllAreass[nCurrAreaID].emplace_back(tempItreator->x, tempItreator->y);
					}

				}
				mapAllAreass.erase(mapAllAreass.find(nNextAreaID));
			}
		}

	}
	for (int j = 0; j < m_nHeight; ++j)
	{
		for (int k = 0; k < m_nWidth; ++k)
		{
			m_pPoints[j][k].changeNoneToWall();
		}

	}

	m_StartNodePos = Vec2<int>(0, m_nHeight - 1);
	m_EndNodePos = Vec2<int>(m_nWidth - 1, 0);

}

void NodeManager::generateMazePath_Prim()
{
	initBeforeGenerate();
	//这里可以是Vec2(先随机节点，再在节点里随机边)，也可以是Vec3(nPos.x,nPos.y,nDirection)，只要随机一次就行了
	//为了提高效率，采用随机一次的方式
	std::vector<Vec3<int>> allCheckedWalls;
	allCheckedWalls.reserve(m_nWidth * m_nHeight * 4);
	allCheckedWalls.clear();

	m_pPoints[m_StartNodePos.y][m_StartNodePos.x].addDefaultWallToVec(allCheckedWalls);
	m_pPoints[m_StartNodePos.y][m_StartNodePos.x].setState(NodeState::Checked);

	int nStartIndex = 0;
	do
	{
		int nCurrIndex = MyRandom::GetInstance()->getRandom(allCheckedWalls.size() - nStartIndex) + nStartIndex;
		Vec3<int> tempCurr = allCheckedWalls[nCurrIndex];
		Vec2<int> currPos = Vec2<int>(tempCurr.x, tempCurr.y);
		Vec2<int> nextPos = MyTools::GetNextPosByDirection(currPos, (WallDirection)(tempCurr.z));

		if (m_pPoints[nextPos.y][nextPos.x].getState() != NodeState::Checked)
		{
			m_pPoints[nextPos.y][nextPos.x].setState(NodeState::Checked);
			m_pPoints[currPos.y][currPos.x].setWall(WallType::NoWall, (WallDirection)tempCurr.z);
			m_pPoints[nextPos.y][nextPos.x].setWall(WallType::NoWall, MyTools::GetOppositeDirection((WallDirection)tempCurr.z));
			m_pPoints[nextPos.y][nextPos.x].addDefaultWallToVec(allCheckedWalls);
			m_pPoints[nextPos.y][nextPos.x].setParentPos(currPos);
			m_pPoints[nextPos.y][nextPos.x].setDepth(m_pPoints[currPos.y][currPos.x].getDepth() + 1);
		}
		allCheckedWalls[nCurrIndex] = allCheckedWalls[nStartIndex];
		allCheckedWalls[nStartIndex++] = tempCurr;
	} while (allCheckedWalls.size() > nStartIndex);

	for (int j = 0; j < m_nHeight; ++j)
	{
		for (int k = 0; k < m_nWidth; ++k)
		{
			m_pPoints[j][k].changeNoneToWall();
		}

	}

	m_VecPath = getPath();


	for (int k = 0; k < m_VecPath.size(); ++k)
	{
		m_pPoints[m_VecPath[k].y][m_VecPath[k].x].setIsInPath(k);
	}

}


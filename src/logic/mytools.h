#pragma once
#include <assert.h>
#include "mydef.h"
#include "../base/commonFunc.h"

class MyTools
{
public:
	static WallDirection GetDirectionByBoundary(NodeBoundary nBoundary)
	{
		WallDirection tempDirection = WallDirection::Up;
		switch (nBoundary)
		{
		case NodeBoundary::Up:
			tempDirection = WallDirection::Up;
			break;
		case NodeBoundary::Right:
			tempDirection = WallDirection::Right;
			break;
		case NodeBoundary::Down:
			tempDirection = WallDirection::Down;
			break;
		case NodeBoundary::Left:
			tempDirection = WallDirection::Left;
			break;
		default:
			assert(false);
			break;
		}
		return tempDirection;
	}

	static Vec2<int> GetNextPosByDirection(Vec2<int> nPos, WallDirection nDirection)
	{
		Vec2<int> tempVec2(0, 0);
		switch (nDirection)
		{
		case WallDirection::Up:
			tempVec2.y = -1;
			break;
		case WallDirection::Right:
			tempVec2.x = 1;
			break;
		case WallDirection::Down:
			tempVec2.y = 1;
			break;
		case WallDirection::Left:
			tempVec2.x = -1;
			break;
		default:
			break;
		}
		return CommonFunc::VecXAdd(nPos, tempVec2);
	}

	static WallDirection GetOppositeDirection(WallDirection nWallDirection)
	{
		int nDirecton = static_cast<int>(nWallDirection) + 2;
		if (nDirecton >= static_cast<int>(WallDirection::Num))
		{
			nDirecton -= static_cast<int>(WallDirection::Num);
		}
		return (WallDirection)(nDirecton);
	}

};

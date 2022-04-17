#pragma once

const int c_nTestMode = 1;			//测试模式
const int c_nMinMazeLength = 3;		//迷宫最小长宽长度
enum class WallType
{
	None = 0,	//未初始化的值
	Wall,
	NoWall,

	Num
};
enum class WallDirection
{
	Up = 0,
	Right,
	Down,
	Left,

	Num
};
enum class NodeBoundary
{
	None = 0,
	Up = 1,
	Right = 2,
	Down = 4,
	Left = 8,
};

enum class MazeMethod
{
	None = 0,
	DepthFirst,
	Kruskal,
	Prim,
	Recursion,

};

enum class NodeState
{
	None = 0,	//未初始化的值
	Checked,
};
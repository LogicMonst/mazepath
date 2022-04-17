#pragma once

const int c_nTestMode = 1;			//����ģʽ
const int c_nMinMazeLength = 3;		//�Թ���С������
enum class WallType
{
	None = 0,	//δ��ʼ����ֵ
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
	None = 0,	//δ��ʼ����ֵ
	Checked,
};
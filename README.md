# mazepath
几种生成迷宫的实现方式

<img src="https://github.com/LogicMonst/mazepath/raw/master/pic/unity.gif">

项目工程主要提供了 深度优先，Kruskal,Prim的生成迷宫方式。工程类型为导出dll库，同时提供控制台输出迷宫及功能，修改工程的 属性->属性配置->常规->配置类型 为exe即可。

导出的dll库，配合Unity，基本可以实现一款简单的迷宫游戏：

<img src="https://github.com/LogicMonst/mazepath/raw/master/pic/maze_unity.jpg">


以下为控制台输出的迷宫及路径（左下为起点，右上为终点）信息

深度优先：

<img src="https://github.com/LogicMonst/mazepath/raw/master/pic/depthFirst.jpg">

Kruskal:

<img src="https://github.com/LogicMonst/mazepath/raw/master/pic/kruskal.jpg">

算法思路来源于算法导论：

<img src="https://github.com/LogicMonst/mazepath/raw/master/pic/kruskal (2).jpg">

Prim:

<img src="https://github.com/LogicMonst/mazepath/raw/master/pic/prim.jpg">

算法思路来源于算法导论：

<img src="https://github.com/LogicMonst/mazepath/raw/master/pic/prim (2).jpg">

图片显示不正常，可以移步至CSDN:https://blog.csdn.net/aabbcc729/article/details/124245695

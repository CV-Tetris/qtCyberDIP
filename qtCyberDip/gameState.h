#pragma once
#include "gameBlock.h"
#include <vector>

struct DropLoc {
	int loc;
	int rotation;
	int del_row;
	DropLoc(int x = 0, int y = 0, int z = 0):loc(x),rotation(y),del_row(z) {}
};

class gameState {
private:
	vector<vector<int>> grid;
	vector<int> heights;
	bool gameover;
public:
	//构造函数，初始化
	gameState();
	//拷贝构造函数，用于赋值
	gameState(gameState& tmp);
	//清空所有状态
	void clear();
	//刷新高度信息
	void refreshHeights();
	//根据传入矩阵更新grid
	void refresh(vector<vector<int>> new_grid);
	//El-Tetris算法feature-行变换数
	double getRowTransitions();
	//El-Tetris算法feature-列变换数
	double getColumnTransitions();
	//El-Tetris算法feature-空洞数
	double getNumberofHoles();
	//El-Tetris算法feature-井数
	double getWellSums();
	//下坠，返回消行数
	int drop(gameBlock& b, int x);
	//用于PD（El-Tetris）算法的下坠，额外返回下坠后高度
	int drop_PD(gameBlock& b, int x, double& avg_land_height);
	//评估函数，用与双层搜索树
	double getReward(int del_row_cur = 0, int del_row_next = 0);
	//评估函数，用于PD（El-Tetris）
	double getReward_PD(int del_row_cur = 0, double land_height_cur = 19);
	//判断游戏是否结束
	bool isGameOver();
	//获取state布局信息
	int getState(int x, int y);
	//获取最佳落点，双层搜索树
	DropLoc getBestDropLoc(gameBlock& first, gameBlock& next);
	//获取最佳落点，El-Tetris
	DropLoc getBestDropLoc(gameBlock& first);
	/*for test*/
	//展示当前布局
	void show();
	/*end for test*/

};
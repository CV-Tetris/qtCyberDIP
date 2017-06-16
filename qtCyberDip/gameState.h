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
	//���캯������ʼ��
	gameState();
	//�������캯�������ڸ�ֵ
	gameState(gameState& tmp);
	//�������״̬
	void clear();
	//ˢ�¸߶���Ϣ
	void refreshHeights();
	//���ݴ���������grid
	void refresh(vector<vector<int>> new_grid);
	//El-Tetris�㷨feature-�б任��
	double getRowTransitions();
	//El-Tetris�㷨feature-�б任��
	double getColumnTransitions();
	//El-Tetris�㷨feature-�ն���
	double getNumberofHoles();
	//El-Tetris�㷨feature-����
	double getWellSums();
	//��׹������������
	int drop(gameBlock& b, int x);
	//����PD��El-Tetris���㷨����׹�����ⷵ����׹��߶�
	int drop_PD(gameBlock& b, int x, double& avg_land_height);
	//��������������˫��������
	double getReward(int del_row_cur = 0, int del_row_next = 0);
	//��������������PD��El-Tetris��
	double getReward_PD(int del_row_cur = 0, double land_height_cur = 19);
	//�ж���Ϸ�Ƿ����
	bool isGameOver();
	//��ȡstate������Ϣ
	int getState(int x, int y);
	//��ȡ�����㣬˫��������
	DropLoc getBestDropLoc(gameBlock& first, gameBlock& next);
	//��ȡ�����㣬El-Tetris
	DropLoc getBestDropLoc(gameBlock& first);
	/*for test*/
	//չʾ��ǰ����
	void show();
	/*end for test*/

};
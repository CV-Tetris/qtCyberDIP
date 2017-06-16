#pragma once
#include <vector>

using namespace std;
enum BlockType {
	SLIDE,
	SQUARE,
	FORWARDL,
	REVERSEL,
	FORWARDZ,
	REVERSEZ,
	FLATT,
	NONE
};

struct Pair {
	int height;
	int width;
	Pair(int x = 0, int y = 0):height(x),width(y) {}
};

class gameBlock {
private:
	BlockType type;
	int rotations;
	int current;
	vector<vector<vector<int>>> shapes;
	vector<vector<int>> bottom_locs;
	vector<Pair> hw_pairs;
public:
	friend class gameState;
	//构造函数，初始化
	gameBlock(BlockType t = BlockType::SQUARE, int c = 0);
	//拷贝构造函数，用于赋值
	gameBlock(gameBlock& tmp);
	//旋转
	void rotate();
	/*for test*/
	//展示当前造型
	void show();
	//展示当前类别的所有造型
	void showAll();
	/*end for test*/
};
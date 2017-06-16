#ifdef VIA_OPENCV

#ifndef USRGAMECONTROLLER_H
#define USRGAMECONTROLLER_H

#include "qtcyberdip.h"
#include "gameState.h"
#include <map>
#include <chrono>
#define WIN_NAME "Frame"

//游戏控制类
class usrGameController
{
private:
	struct Tmp {
		BlockType t;
		int r;
		int loc;
		bool clear;
		Tmp(BlockType tp=SLIDE, int rr = 0, int x=0, bool c=false):t(tp),r(rr),loc(x),clear(c) {}
	};

	enum BackgroundInformation {
		UP, DOWN, LEFT, RIGHT, WIDTH, HEIGHT
	};
	enum RecursiveState {
		MENU,
		INITIAL,
		NEWCYCLE,
		NEXTBLOCK,
		DELAY,
		REFRESH,
		FINDLOC,
		JUDGELOC,
		CHECK,
		DROP,
		GAMEOVER,
		NEWGAME
	};
	enum ButtonType {
		STARTB,
		LEFTB,
		RIGHTB,
		ROTATEB,
		DROPB
	};
	RecursiveState currentRecursiveState;
	RecursiveState lastState;
	deviceCyberDip* device;
	vector<double> menuFeature;
	vector<vector<double>> blockFeatures;
	vector<int> background;
	vector<int> next_background;
	//vector<int> buttons;
	vector<cv::Point> buttons;
	vector<int> start_button;
	map<int, Tmp> blockMap;
	int pt_cols, pt_rows;
	gameBlock currentBlock;
	gameBlock nextBlock;
	gameState currentState;
	DropLoc currentBestLoc;
	bool isFirstBlock;
	bool jump_flag;
	bool isGame;
	bool isInitialed;
	bool waitUp;
	int delay_count;
	int fail_count;
	int check_count;
	int Op_delay;
	chrono::steady_clock::time_point lastOp = chrono::steady_clock::now();

	//LSH特征提取
	vector<double> getFeature(cv::Mat& img);
	//获取Menu中开始键位置
	void getStartButton(cv::Mat& img);
	//判断总体界面是否为Menu
	bool isMenu(cv::Mat& img);
	//获取游戏功能区域和按键
	void initialLocation(cv::Mat& img);
	//点击操作按键
	void click(ButtonType bt, bool moveOnly = false);
	//获取下一块俄罗斯方块类型
	BlockType getBlockType(cv::Mat& img);
	//获取背景区域的布局情况
	vector<vector<int>> readFromImg(cv::Mat& img, bool isFirst = false);
	//从布局矩阵中获取正在下落的方块的位置
	Tmp readBlockFromMatrix(vector<vector<int>> grid, bool isFirst = false);
	/*for test*/
	//展示检测到的功能区域和按键
	void showDetection(cv::Mat& img);
	//展示检测出的背景区域的布局
	void combineAndshow(cv::Mat& img, cv::Mat& main_area);
	//展示gameState布局
	void showState(cv::Mat& img);
	//保存当前界面图像
	void savePicture(cv::Mat& img);
	//鼠标回调结构体
	struct MouseArgs {
		cv::Rect box;
		bool Drawing, Hit;
		// init
		MouseArgs() :Drawing(false), Hit(false)
		{
			box = cv::Rect(0, 0, -1, -1);
		}
	};
	//鼠标回调函数
	friend void  mouseCallback(int event, int x, int y, int flags, void*param);
	MouseArgs argM;
	/*end for test*/
	
public:
	//构造函数，所有变量的初始化都应在此完成
	usrGameController(void* qtCD);
	//析构函数，回收本类所有资源
	~usrGameController();
	//图像处理，逐帧接受图像
	int usrProcessImage(cv::Mat& img);
};

//鼠标回调函数
void  mouseCallback(int event, int x, int y, int flags, void*param);

#endif
#endif

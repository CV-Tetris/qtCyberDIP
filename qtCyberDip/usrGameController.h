#ifdef VIA_OPENCV

#ifndef USRGAMECONTROLLER_H
#define USRGAMECONTROLLER_H

#include "qtcyberdip.h"
#include "gameState.h"
#include <map>
#include <chrono>
#define WIN_NAME "Frame"

//��Ϸ������
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
		DROP
	};
	enum ButtonType {
		STARTB,
		LEFTB,
		RIGHTB,
		ROTATEB,
		DROPB
	};
	RecursiveState currentRecursiveState;
	deviceCyberDip* device;
	vector<double> menuFeature;
	vector<vector<double>> blockFeatures;
	vector<int> background;
	vector<int> next_background;
	vector<int> buttons;
	vector<int> start_button;
	map<int, Tmp> blockMap;
	int pt_cols, pt_rows;
	gameBlock currentBlock;
	gameBlock nextBlock;
	gameState currentState;
	DropLoc currentBestLoc;
	bool isFirstBlock;
	bool jump_flag;
	//bool doubleDetection;
	bool waitUp;
	int delay_count;
	int fail_count;
	int check_count;
	int Op_delay;
	chrono::steady_clock::time_point lastOp = chrono::steady_clock::now();
	
//������Ϊ��ʵ����ʾЧ�������ӵ�����
	//���ص��ṹ��
	struct MouseArgs{
		cv::Rect box;
		bool Drawing, Hit;
		// init
		MouseArgs() :Drawing(false), Hit(false)
		{
			box = cv::Rect(0, 0, -1, -1);
		}
	};
	//���ص�����
	friend void  mouseCallback(int event, int x, int y, int flags, void*param);
	MouseArgs argM;
//������Ϊ��ʵ�ֿ�����ʾЧ�������ӵ�����
	vector<double> getFeature(cv::Mat& img);
	void getStartButton(cv::Mat& img);
	bool isMenu(cv::Mat& img);
	void initialLocation(cv::Mat& img);
	void click(ButtonType bt, bool moveOnly = false);
	BlockType getBlockType(cv::Mat& img);
	vector<vector<int>> readFromImg(cv::Mat& img, bool isFirst = false);
	Tmp readBlockFromMatrix(vector<vector<int>> grid, bool isFirst = false);
	/*for test*/
	void showDetection(cv::Mat& img);
	void combineAndshow(cv::Mat& img, cv::Mat& main_area);
	void showState(cv::Mat& img);
	void savePicture(cv::Mat& img);
	/*end for test*/
	
public:
	//���캯�������б����ĳ�ʼ����Ӧ�ڴ����
	usrGameController(void* qtCD);
	//�������������ձ���������Դ
	~usrGameController();
	
	int usrProcessImage(cv::Mat& img);
};

//������Ϊ��ʵ����ʾЧ�������ӵ�����
//���ص�����
void  mouseCallback(int event, int x, int y, int flags, void*param);
//������Ϊ��ʵ�ֿ�����ʾЧ�������ӵ�����

#endif
#endif
#ifdef VIA_OPENCV

#ifndef USRGAMECONTROLLER_H
#define USRGAMECONTROLLER_H

#include "qtcyberdip.h"
#include "gameState.h"
#define WIN_NAME "Frame"

//��Ϸ������
class usrGameController
{
private:
	enum BackgroundInformation {
		UP, DOWN, LEFT, RIGHT, WIDTH, HEIGHT
	};
	enum RecursiveState {
		MENU,
		INITIAL,
		NEXTBLOCK,
		FINDLOC,
		JUDGELOC,
		DROP
	};
	RecursiveState currentRecursiveState;
	deviceCyberDip* device;
	vector<vector<double>> blockFeatures;
	vector<int> background;
	vector<int> next_background;
	vector<int> buttons;
	gameBlock currentBlock;
	gameBlock nextBlock;
	bool isFirstBlock;
	
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
	void initialLocation(cv::Mat& img);
	/*for test*/
	void showDetection(cv::Mat& img);
	/*end for test*/
	
public:
	//���캯�������б����ĳ�ʼ����Ӧ�ڴ����
	usrGameController(void* qtCD);
	//�������������ձ���������Դ
	~usrGameController();
	//����ͼ������ÿ���յ�ͼ��ʱ�������
	BlockType getBlockType(cv::Mat& img);
	int usrProcessImage(cv::Mat& img);
};

//������Ϊ��ʵ����ʾЧ�������ӵ�����
//���ص�����
void  mouseCallback(int event, int x, int y, int flags, void*param);
//������Ϊ��ʵ�ֿ�����ʾЧ�������ӵ�����

#endif
#endif
/**
* @file Game.h
* @brief 游戏类的头文件库
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#pragma once
#include"Player.h"
#include"Player2.h"
#include"AutoMonster.h"
#include"Prize.h"
#include"Crump.h"
#include<vector>
using namespace std;
/**
* @class CGame
* @brief 游侠从开始到结束的各项属性和功能
*
* 背景指针，玩家1，玩家2，小怪，地图，储存随机刷取的道具位置的数组，储存每个炸弹的动态数组，储存道具的数组，游戏状态的判断，显示HP有几条的字体，
欢迎图片，胜利图片，失败图片，初始化游戏，绘制道具，显示生命值，绘制炸弹，更新炸弹，更新游戏状态，所有的移动功能，鼠标操作，运行游戏，欢迎界面，
结束界面，游戏界面，释放资源，道具飞毛腿的作用，道具加血药剂的作用
*/
class CGame
{
public:
	CGame();
	~CGame();
	IplImage * bkImg;//*背景指针*/
	CPlayer Player1;//*玩家1*/
	CAPlayer Player2;/*玩家2*/
	CAutoMonster Monster;//*小怪*/
	CGameMap Map;//*地图*/
	CPrize m_Gifts[10];//*储存随机刷取道具的位置*/
	vector <CCrump *> m_Crumps;//*储存每个炸弹的动态数组*/
	int m_Gift[10];//*储存礼物*/
	int m_State;//*游戏状态判断*/
	CvFont m_GameFont;//*字体*/
	IplImage *m_WelcomeImg;//*欢迎图片*/
	IplImage *m_WinImg;//*胜利图片*/
	IplImage *m_LostImg;//*失败图片*/
	void InitGame();
	void DrawGift();
	void DrawMassage(IplImage * bkImg);
	void Player1Crump(int key);
	void Player2Crump(int key);
	void DrawCrump();
	void UpdateCrump();
	void UpdateState();
	void Move(int key, CGameMap *map);
	static void Mouse(int event, int x, int y, int flags, void* p);
	void RunGame();
	void Welcome();
	void GameOver();
	void Run();
	void Release();
	void Scud();
	void AddHP();
	void WMMP();
};
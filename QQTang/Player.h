/**
* @file Player.h
* @brief Player1所使用到的头文件库
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#pragma once 
#include "GameMap.h"
/**
* @class CPlayer
* @brief 玩家1
*
* 包含玩家1各项属性的初始化，玩家1按键移动的实现，以及释放其所占用的内存，将其绘制到背景板上的功能
*/
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	IplImage* m_Img[5][5];//*人物图片*/
	CvPoint m_pos;//*人物位置*/
	int m_speed;//*人物速度*/
	int m_ori;//*方向*/
	int m_way;//*腿部左右判断*/
	int m_aspeed;//*一步能走几个格子，用于“飞毛腿”的跳格子
	unsigned int m_HP;//*生命值*/
	int m_score;
	IplImage *m_HPImg;//*生命值图片*/
	void Init(CGameMap *map);
	void Release();
	void Move(int key, CGameMap * map);
	void CopyToBack(IplImage *back);
};
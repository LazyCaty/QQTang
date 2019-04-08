/**
* @file Player2.h
* @brief Player2所使用到的头文件库
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#pragma once 
#include"GameMap.h"
#include"Player.h"
/**
* @class CAPlayer
* @brief 玩家2
*
* 包含玩家2各项属性的初始化，玩家2按键移动的实现，以及释放其所占用的内存，将其绘制到背景板上的功能
*/
class CAPlayer : public CPlayer
{
public:
	CAPlayer();
	~CAPlayer();
	void Init(CGameMap *map);
	void Move(int key,CGameMap *map);
	void Release();
};

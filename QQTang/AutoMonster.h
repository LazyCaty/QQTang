/**
* @file AutoMonster.h
* @brief 自动移动小怪所使用到的头文件库
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#pragma once
#include"Player.h"
#include"GameMap.h"
/**
* @class CAutoMonster
* @brief 自动移动的小怪
*
* 包含小怪各项属性的初始化，小怪自动移动的实现，以及释放其所占用的内存的功能
*/
class CAutoMonster : public CPlayer
{
public:
	CAutoMonster();
	~CAutoMonster();
	void Automove(CGameMap *map);
	void Init(CGameMap *map);
	void Release();
};
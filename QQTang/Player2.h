/**
* @file Player2.h
* @brief Player2��ʹ�õ���ͷ�ļ���
* @author ����
* @date 20180712
* @version 1.0
*/
#pragma once 
#include"GameMap.h"
#include"Player.h"
/**
* @class CAPlayer
* @brief ���2
*
* �������2�������Եĳ�ʼ�������2�����ƶ���ʵ�֣��Լ��ͷ�����ռ�õ��ڴ棬������Ƶ��������ϵĹ���
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

/**
* @file AutoMonster.h
* @brief �Զ��ƶ�С����ʹ�õ���ͷ�ļ���
* @author ����
* @date 20180712
* @version 1.0
*/
#pragma once
#include"Player.h"
#include"GameMap.h"
/**
* @class CAutoMonster
* @brief �Զ��ƶ���С��
*
* ����С�ָ������Եĳ�ʼ����С���Զ��ƶ���ʵ�֣��Լ��ͷ�����ռ�õ��ڴ�Ĺ���
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
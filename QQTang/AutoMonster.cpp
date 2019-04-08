/**
* @file AutoMonster.cpp
* @brief �Զ��ƶ�С��
* @author ����
* @date 20180712
* @version 1.0
*/
#include "stdafx.h"
#include "Player.h"
#include "Tools.h"
#include"AutoMonster.h"
#include"time.h"
#include"math.h"
CAutoMonster::CAutoMonster()
{

}
CAutoMonster::~CAutoMonster()
{

}
/**
* @brief С�ֵĳ�ʼ��
*
* ʵ��С��m_way,m_HP,m_Img[][]�ĳ�ʼ��
* @param *map Ҫʶ�����ײ����С�ֵĳ�ʼ��λ��
*/
	void CAutoMonster::Init(CGameMap *map)
{

	m_ori = 1;
	m_way = 4;
	m_HP = 1;
	char name[] = "E:\\QQTang\\QQTang\\QQTang\\Resource\\Monster\\Knight_00.png";
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			sprintf_s(name, "E:\\QQTang\\QQTang\\QQTang\\Resource\\Monster\\Knight_%d%d.png", i, j);
			m_Img[i][j] = cvLoadImage(name);
		}
	}
	srand(2);
	while (1)
	{
		m_pos.x = (rand() % 16);
		m_pos.y = (rand() % 16);
		if (map->m_Map[m_pos.x][m_pos.y] == -1)
		{
			m_pos.x *= 40;
			m_pos.y *= 40;
			m_speed = 40;
			break;
		}
	}
	if (m_HP == 0)
	{
		return;
	}
}
/**
* @brief С���Զ��ƶ�����
*
* ʵ��С�ֵ��Զ��ƶ������Զ��жϵ�ͼ�ϵ���ײ��������ǰ���Ƿ����ͨ��
* @param *map Ҫʶ�����ײ����map�����С����һ���ƶ�����λ��
*/
void CAutoMonster::Automove(CGameMap *map)
{
	if (m_HP == 0)
	{
		return;
	}
	int x = m_pos.x;
	int y = m_pos.y;
	int step;
	srand(time(NULL));
	step = rand() % 4;
	switch (step)
	{
	case 0:
		m_ori = 4;
		m_way = m_way % 4 + 1;
		y -= m_speed;
		break;
	case 1:
		m_ori = 1;
		m_way = m_way % 4 + 1;
		y += m_speed;
		break;
	case 2:
		m_ori = 2;
		m_way = m_way % 4 + 1;
		x -= m_speed;
		break;
	case 3:
		m_ori = 3;
		m_way = m_way % 4 + 1;
		x += m_speed;
		break;
	}
	if (map->Collision(x, y))
	{
		m_pos.x = x;
		m_pos.y = y;
	}
}
/**
* @brief �ͷ�С����ռ�õ��ڴ�

* �ͷ�С��������ͼ��ռ�õ��ڴ�
*/
void CAutoMonster::Release()
{
	cvReleaseImage(&m_HPImg);
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			cvReleaseImage(&m_Img[i][j]);
		}
	}
}

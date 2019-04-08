/**
* @file Player2.cpp
* @brief Player2
* @author ����
* @date 20180712
* @version 1.0
*/
#include "stdafx.h" 
#include<windows.h> 
#pragma comment(lib,"winmm.lib")
#include "Player.h"
#include "Tools.h"
#include"Player2.h"
#include"time.h"
using namespace std;
CAPlayer::CAPlayer()
{

}
CAPlayer::~CAPlayer()
{

}
/**
* @brief ��ʼ������
*
* ��ʼ�����2�ĸ������ԣ��������ͼƬ����ˢһ�����λ�ð������2
*/
void CAPlayer::Init(CGameMap *map)
{
	m_ori = 1;
	m_way = 4;
	m_speed = 0;
	m_HP = 2;
	m_HPImg = cvLoadImage("E:\\QQTang\\QQTang\\QQTang\\Resource\\Interface\\HP2.png", 1);
	char name[] = "E:\\QQTang\\QQTang\\QQTang\\Resource\\Player\\Shel_00.png";
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			sprintf_s(name, "E:\\QQTang\\QQTang\\QQTang\\Resource\\Player\\Shel_%d%d.png", i, j);
			m_Img[i][j] = cvLoadImage(name);
		}
	}
	//����һ����-1�������ϵ����λ��
	srand(time(NULL));
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
* @brief �ƶ�����
*
* ʵ������İ����ƶ���ÿ���ƶ�������Ӧ���ƶ���Ч
* @param key ��ҵİ�������
* @*map ��ͼ��ָ�룬���ڷ��ʵ�ͼ�����ײ�庯���ﵽʶ����ײ���Ŀ��
*/
void CAPlayer::Move(int key,CGameMap *map)
{
	if (m_HP == 0)
	{
		return;
	}
	int x = m_pos.x;
	int y = m_pos.y;
	int x1 = m_pos.x;
	int y1 = m_pos.y;
	switch (key)
	{
	case'8':
		m_ori = 4;
		y -= m_speed;
		y1 -= m_speed * 2;
		m_way  = m_way %4 + 1;
		break;
	case'2':
	case'5':
		m_ori = 1;
		y += m_speed;
		y1 += m_speed * 2;
		m_way = m_way % 4 + 1;
		break;
	case'4':
		m_ori = 2;
		x -= m_speed;
		x1 -= m_speed * 2;
		m_way = m_way % 4 + 1;
		break;
	case'6':
		m_ori = 3;
		x += m_speed;
		x1 += m_speed * 2;
		m_way = m_way % 4 + 1;
		break;
	}
	if (m_aspeed == 0)
	{
		//��ײ����
		if (map->Collision(x, y))
		{
			m_pos.x = x;
			m_pos.y = y;
		}
	}
	if (m_aspeed == 1)
	{
		//��ײ����
		if (map->Collision(x, y))
		{
			m_pos.x = x;
			m_pos.y = y;
		}
		if (map->Collision(x, y) == false)
		{
			if (map->Collision(x1, y1))
			{
				m_pos.x = x1;
				m_pos.y = y1;
			}
		}
	}
	//ÿ�ƶ��ƶ�һ�������ƶ�����Ч
	if (key == '8' || key == '5' || key == '2' ||
		key == '4' || key == '6')
	{
		PlaySound(L"E:\\QQTang\\QQTang\\QQTang\\Resource\\sound\\move.wav", NULL, SND_FILENAME | SND_ASYNC);
	 
	}
	if (key == '0')
	{
		PlaySound(L"E:\\QQTang\\QQTang\\QQTang\\Resource\\sound\\crump.wav", NULL, SND_FILENAME | SND_ASYNC);
		 
	}
}
/**
* @brief ��������
*
* �ͷ�ÿһ��������ͼ��ռ�õ��ڴ�
*/
void CAPlayer:: Release()
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
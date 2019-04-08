/**
* @file Player.cpp
* @brief Player1
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#include "stdafx.h"
#include<windows.h> 
#pragma comment(lib,"winmm.lib")
#include "Player.h"
#include "Tools.h"
#include"time.h"
using namespace std;
CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

/**
* @brief 初始化人物
*
* 初始化玩家1的各项属性，加载玩家图片，并刷一个随机位置安放玩家1
*/
void CPlayer::Init(CGameMap *map)
{
	m_ori = 1;
	m_way = 4;
	m_aspeed = 0;
	m_HP = 2;
	m_HPImg = cvLoadImage("./HP1.png", 1);
	char name[] = "./player00.png";
	for (int i = 0; i <= 1; i++)
	{
		for (int j = 0; j <= 1; j++)
		{
			sprintf_s(name, "./player%d%d.png", i, j);
			m_Img[i][j] = cvLoadImage(name);
		}
	}
	//产生一个在-1背景板上的随机位置
	srand(0);
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
* @brief 绘制人物到背景板上
*
* 将由方向和左右确定的人物图片绘制到背景板上
*/
void CPlayer::CopyToBack(IplImage *back)
{
	if (m_HP == 0)
	{
		return;
	}
	CTools::CopyToBack(back, m_Img[m_ori][m_way], m_pos.x, m_pos.y, 225, 225, 225);
}
/**
* @brief 移动人物
*
* 实现人物的按键移动和每次移动播放相应的移动音效
* @param key 玩家的按键操作
* @*map 地图类指针，用于访问地图类的碰撞体函数达到识别碰撞体的目的
*/
void CPlayer::Move(int key, CGameMap * map)
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
	case'w':
	case 'W':
		m_ori = 4;
		y -= m_speed;
		y1 -= m_speed * 2;
		m_way = m_way % 4 + 1;
		break;
	case's':
	case 'S':
		m_ori = 1;
		y += m_speed;
		y1 += m_speed * 2;
		m_way = m_way % 4 + 1;
		break;
	case'a':
	case 'A':
		m_ori = 2;
		x -= m_speed;
		x1 -= m_speed * 2;
		m_way = m_way % 4 + 1;
		break;
	case'd':
	case 'D':
		m_ori = 3;
		x += m_speed;
		x1 += m_speed * 2; 
		m_way = m_way % 4 + 1;
		break;
	}
		if (m_aspeed == 0)
		{
			//碰撞体检测
			if (map->Collision(x, y))
			{
				m_pos.x = x;
				m_pos.y = y;
			}
		}
		if (m_aspeed == 1)
		{
			//碰撞体检测
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
		//每移动一步播放移动的音效
		if (key == 'W' || key == 'w' || key == 'S' || key == 's' ||
			key == 'A' || key == 'a' || key == 'D' || key == 'd')
		{
			PlaySound(L"E:\\QQTang\\QQTang\\QQTang\\Resource\\sound\\move.wav", NULL, SND_FILENAME | SND_ASYNC);
			 
		}
		if (key == ' ')
		{
			PlaySound(L"E:\\QQTang\\QQTang\\QQTang\\Resource\\sound\\crump.wav", NULL, SND_FILENAME | SND_ASYNC);			
		 
		}
}
/**
* @brief 销毁人物
*
* 释放每一张人物贴图所占用的内存
*/

void CPlayer::Release()
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
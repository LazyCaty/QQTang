/**
* @file GameMap.cpp
* @brief 游戏地图
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#include "stdafx.h"
#include "GameMap.h"
#include "Tools.h"
#include <fstream> 
using namespace std;

CGameMap::CGameMap()
{
}


CGameMap::~CGameMap()
{
}

/**
* @brief 地图初始化
*
* 加载地图背景，地图各个模块，进行地图背景的克隆和拷贝
*/
void CGameMap::Init()
{
	m_StaticBack = cvLoadImage("E:\\QQTang\\QQTang\\QQTang\\Resource\\Map\\back1.jpg", 1);
	m_Background = cvCloneImage(m_StaticBack);
	m_ShowImg = cvCloneImage(m_StaticBack);
	char name1[] = "E:\\QQTang\\QQTang\\QQTang\\Resource\\Map\\stone0.jpg";
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(name1, "E:\\QQTang\\QQTang\\QQTang\\Resource\\Map\\stone%d.jpg", i);
		m_ObstacleImg[i] = cvLoadImage(name1);
	}
}

/**
* @brief 读取地图信息
*
* 打开储存地图信息的文本框将里面的数据储存到地图模块的二维数组里
*/
void CGameMap::ReadMaptxt()
{
	ifstream txt;
		txt.open("Map1.txt");
	int k;
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			txt >> k;
			m_Map[i][j] = k;
		}
	}
}
/**
* @brief 创造地图
*
* 将地图模块数组里的地图模块信息绘制到背景板上
*/
void CGameMap::CreateMap()
{
	cvCopy(m_StaticBack, m_Background);
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			int x = i * 40;
			int y = j * 40;
			int k = m_Map[i][j];
			if (k != -1)
				//将每个地图模块绘制到背景上
				CTools::CopyToBack(m_Background, m_ObstacleImg[k], x, y, 235, 235, 235);
		}
	}
}
/**
* @brief 绘制实时地图
*
* 每当地图创建后就返还当前地图的图像
* @return 返还实时地图
*/
IplImage * CGameMap::GetBackShowImg()
{
	CreateMap();
	cvCopy(m_Background, m_ShowImg);
	return m_ShowImg;

}
/**
* @brief 地图碰撞体检测
*
* 通过判断人物所在位置是否位于地图碰撞体模块上确立一个返回值
* @param x 人物位置的横坐标
* @param y 人物位置的纵坐标
* @return 判断是否为碰撞体，是返回true，不是返回false
*/
bool CGameMap::Collision(int x, int y)//x,y：人物的当前位置
{
	int posx = x / 40;
	int posy = y / 40;
	if (m_Map[posx][posy] != -1)
		return false;
	else return true;
}
/**
* @brief 清理地图
*
* 将不为某种不改变的地图模块而又在炸弹爆炸范围内的贴图还原为原背景板
* @param x 炸弹爆炸所产生4个方向上的贴图位置的横坐标
* @param y 炸弹爆炸所产生4个方向上的贴图位置的纵坐标
*/
void CGameMap::ClearMap(int x, int y)
{
	int posx = x / 40;
	int posy = y / 40;
	if(m_Map[posx][posy]!=0)
	m_Map[posx][posy] = -1;

}
/**
* @brief 释放地图
*
* 释放地图原背景和克隆背景所占用的内存和每个地图模块所占用的内存
*/
void CGameMap::Release()
{
	cvReleaseImage(&m_StaticBack);
	cvReleaseImage(&m_Background);
	for (int i = 0; i < 3; i++)
	{
		cvReleaseImage(&m_ObstacleImg[i]);
	}
}
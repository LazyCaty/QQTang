/**
* @file Crump.cpp
* @brief 炸弹
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#include"stdafx.h"
#include"Crump.h"
#include"Tools.h"
#include"Game.h"
CCrump::CCrump()
{

}
CCrump::~CCrump()
{

}
/**
* @brief 炸弹位置的初始化
*
* 实现炸弹的m_Flag,m_Pos,*m_Image[],*m_ShockWaveImgs[][],m_TimeCount,m_frameid,m_Range的初始化
* @param x 传入当前人物位置的横坐标
* @param y 传入当前人物位置的纵坐标
*/
void CCrump::Init(int x, int y)
{
	m_Flag = 1;
	m_Range = 1;
	m_TimeCount = 20;
	m_Pos.x = x;
	m_Pos.y = y;
	m_frameid = 0;
	char name[] = "E:\\QQTang\\QQTang\\QQTang\\Resource\\Crump\\crump0.bmp";
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(name, "E:\\QQTang\\QQTang\\QQTang\\Resource\\Crump\\crump%d.bmp", i);
		m_Image[i] = cvLoadImage(name);
	}
	char name1[] = "E:\\QQTang\\QQTang\\QQTang\\Resource\\Crump\\shockwave01.bmp";
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sprintf_s(name1, "E:\\QQTang\\QQTang\\QQTang\\Resource\\Crump\\shockwave%d%d.bmp", i, j);
			m_ShockWavesImgs[i][j] = cvLoadImage(name1);
		}
	}
}
      
/**
* @brief 绘制炸弹贴图到背景
*
* 将所需要展示的炸弹题图绘制到背景板上
* @param *bkImg 传入所需要被绘制的背景图片指针
*/
void CCrump::CopyToBack(IplImage * bkImg)
{
	if (m_Flag == 0)
	{
		return;
	}
	CTools::CopyToBack(bkImg, m_Image[m_frameid], m_Pos.x, m_Pos.y, 255, 0, 0, true);
}
/**
* @brief 扩大炸弹范围的道具
*
* 当玩家吃到扩大炸弹范围道具时扩大炸弹的范围
*/
void CCrump::CrumpRange()  //当范围继续扩大时需要引入一个记录道具被吃几次的量
{
	m_Range = 2;
}
/**
* @brief 炸弹爆炸对地图的改变
*
* 产生未爆炸之前的炸弹动画，以及炸弹爆炸后对地图造成的改变
* @param *bkImg 传入所需要被绘制的背景图片指针
* @param *map 用于访问地图类某些属性和调用地图类某些函数的指针
*/
void CCrump::CrumpChange(IplImage * bkImg, CGameMap *map)
{
	if (m_Flag == 0)
	{
		return;
	}
	m_TimeCount--;
	if (m_TimeCount >= 5)
	{
		m_frameid++;
		if (m_frameid >1)
			m_frameid = 0;
	}
	else if (m_TimeCount < 5)
	{
		m_frameid = 2;
		//炸弹方向
		map->ClearMap(m_Pos.x, m_Pos.y);  
		//绘制炸弹未爆炸的动画
		CTools::CopyToBack(bkImg, m_Image[m_frameid], m_Pos.x, m_Pos.y, 255, 0, 0, true);
		int dir[4][2] = { -1, 0,  //左
			0, -1,  //上
			1, 0,   //右
			0, 1 }; //下 
		if (m_Range == 1)
		{
			for (int i = 0; i < 4; i++)
			{
				if (map->m_Map[m_Pos.x / 40][m_Pos.y / 40] < 5 && map->m_Map[m_Pos.x / 40 + dir[i][0]][m_Pos.y / 40 + dir[i][1]] != 0)
				{
					map->ClearMap(m_Pos.x + dir[i][0] * 40, m_Pos.y + dir[i][1] * 40); 
					//炸弹过处，寸草不生
					CTools::CopyToBack(bkImg, m_ShockWavesImgs[0][i], m_Pos.x + 40 * dir[i][0], m_Pos.y + 40 * dir[i][1], 255, 0, 0, true);
				}
			}
		}
		else if (m_Range == 2)
		{
			for (int i = 0; i < 4; i++)
			{
				if (map->m_Map[m_Pos.x / 40][m_Pos.y / 40] < 5 && map->m_Map[m_Pos.x / 40 + dir[i][0]][m_Pos.y / 40 + dir[i][1]] != 0 &&
					map->m_Map[m_Pos.x / 40 + 2 * dir[i][0]][m_Pos.y / 40 + 2 * dir[i][1]] == 0)
				{
					map->ClearMap(m_Pos.x + dir[i][0] * 40, m_Pos.y + dir[i][1] * 40);  
					//炸弹过处，寸草不生
					CTools::CopyToBack(bkImg, m_ShockWavesImgs[0][i], m_Pos.x + 40 * dir[i][0], m_Pos.y + 40 * dir[i][1], 255, 0, 0, true);
				}
				//炸弹范围2，捡到道具后
				if (map->m_Map[m_Pos.x / 40 + dir[i][0]][m_Pos.y / 40 + dir[i][1]] != 0
					&& map->m_Map[m_Pos.x / 40 + 2 * dir[i][0]][m_Pos.y / 40 + 2 * dir[i][1]] != 0)  
				{
					map->ClearMap(m_Pos.x + 2 * dir[i][0] * 40, m_Pos.y + 2 * dir[i][1] * 40);
					map->ClearMap(m_Pos.x + dir[i][0] * 40, m_Pos.y + dir[i][1] * 40);

					if (i < 2)
						CTools::CopyToBack(bkImg, m_ShockWavesImgs[1][i], m_Pos.x + 2 * 40 * dir[i][0], m_Pos.y + 2 * 40 * dir[i][1]
							, 255, 0, 0, true);
					else
						CTools::CopyToBack(bkImg, m_ShockWavesImgs[1][i], m_Pos.x + 40 * dir[i][0], m_Pos.y + 40 * dir[i][1]
							, 255, 0, 0, true);
				}
			}
		}
	}
	//炸完
	if (m_TimeCount == 0)  
	{
		m_Flag = 0;

		map->ClearMap(m_Pos.x / 40, m_Pos.y / 40);
	}
}
/**
* @brief 释放炸弹所占用的内存
*
* 释放炸弹所有贴图所占用的内存
*/
void CCrump::Release()
{

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cvReleaseImage(&m_ShockWavesImgs[i][j]);
		}
	}
}
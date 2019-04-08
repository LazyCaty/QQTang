/**
* @file Prize.cpp
* @brief 道具
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#include"stdafx.h"
#include"Prize.h"
#include"time.h"
CPrize::CPrize()
{
}


CPrize::~CPrize()
{
}
/**
* @brief 初始化道具
*
* 初始化道具的位置，贴图，使用状态
*/

void CPrize::Init()
{
	m_pos.x = (rand() % 14 + 1) * 40;
	m_pos.y = (rand() % 12 + 1) * 40;
	m_flag = 1;
	for (int i = 0; i < 3; i++)
	{
		srand(time(NULL));
		temp = rand() % 3;
		char filename[] = "E:\\QQTang\\QQTang\\QQTang\\Resource\\Prize\\gift0.jpg";
		sprintf_s(filename, "E:\\QQTang\\QQTang\\QQTang\\Resource\\Prize\\gift%d.jpg", temp);
		m_Img = cvLoadImage(filename, 1);
	}
}
/**
* @brief 销毁道具
*
* 释放每一张道具贴图所占用的内存
*/
	void CPrize::Release()
	{
		cvReleaseImage(&m_Img);
	}
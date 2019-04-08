/**
* @file GameMap.cpp
* @brief ��Ϸ��ͼ
* @author ����
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
* @brief ��ͼ��ʼ��
*
* ���ص�ͼ��������ͼ����ģ�飬���е�ͼ�����Ŀ�¡�Ϳ���
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
* @brief ��ȡ��ͼ��Ϣ
*
* �򿪴����ͼ��Ϣ���ı�����������ݴ��浽��ͼģ��Ķ�ά������
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
* @brief �����ͼ
*
* ����ͼģ��������ĵ�ͼģ����Ϣ���Ƶ���������
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
				//��ÿ����ͼģ����Ƶ�������
				CTools::CopyToBack(m_Background, m_ObstacleImg[k], x, y, 235, 235, 235);
		}
	}
}
/**
* @brief ����ʵʱ��ͼ
*
* ÿ����ͼ������ͷ�����ǰ��ͼ��ͼ��
* @return ����ʵʱ��ͼ
*/
IplImage * CGameMap::GetBackShowImg()
{
	CreateMap();
	cvCopy(m_Background, m_ShowImg);
	return m_ShowImg;

}
/**
* @brief ��ͼ��ײ����
*
* ͨ���ж���������λ���Ƿ�λ�ڵ�ͼ��ײ��ģ����ȷ��һ������ֵ
* @param x ����λ�õĺ�����
* @param y ����λ�õ�������
* @return �ж��Ƿ�Ϊ��ײ�壬�Ƿ���true�����Ƿ���false
*/
bool CGameMap::Collision(int x, int y)//x,y������ĵ�ǰλ��
{
	int posx = x / 40;
	int posy = y / 40;
	if (m_Map[posx][posy] != -1)
		return false;
	else return true;
}
/**
* @brief �����ͼ
*
* ����Ϊĳ�ֲ��ı�ĵ�ͼģ�������ը����ը��Χ�ڵ���ͼ��ԭΪԭ������
* @param x ը����ը������4�������ϵ���ͼλ�õĺ�����
* @param y ը����ը������4�������ϵ���ͼλ�õ�������
*/
void CGameMap::ClearMap(int x, int y)
{
	int posx = x / 40;
	int posy = y / 40;
	if(m_Map[posx][posy]!=0)
	m_Map[posx][posy] = -1;

}
/**
* @brief �ͷŵ�ͼ
*
* �ͷŵ�ͼԭ�����Ϳ�¡������ռ�õ��ڴ��ÿ����ͼģ����ռ�õ��ڴ�
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
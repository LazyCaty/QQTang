/**
* @file Crump.cpp
* @brief ը��
* @author ����
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
* @brief ը��λ�õĳ�ʼ��
*
* ʵ��ը����m_Flag,m_Pos,*m_Image[],*m_ShockWaveImgs[][],m_TimeCount,m_frameid,m_Range�ĳ�ʼ��
* @param x ���뵱ǰ����λ�õĺ�����
* @param y ���뵱ǰ����λ�õ�������
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
* @brief ����ը����ͼ������
*
* ������Ҫչʾ��ը����ͼ���Ƶ���������
* @param *bkImg ��������Ҫ�����Ƶı���ͼƬָ��
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
* @brief ����ը����Χ�ĵ���
*
* ����ҳԵ�����ը����Χ����ʱ����ը���ķ�Χ
*/
void CCrump::CrumpRange()  //����Χ��������ʱ��Ҫ����һ����¼���߱��Լ��ε���
{
	m_Range = 2;
}
/**
* @brief ը����ը�Ե�ͼ�ĸı�
*
* ����δ��ը֮ǰ��ը���������Լ�ը����ը��Ե�ͼ��ɵĸı�
* @param *bkImg ��������Ҫ�����Ƶı���ͼƬָ��
* @param *map ���ڷ��ʵ�ͼ��ĳЩ���Ժ͵��õ�ͼ��ĳЩ������ָ��
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
		//ը������
		map->ClearMap(m_Pos.x, m_Pos.y);  
		//����ը��δ��ը�Ķ���
		CTools::CopyToBack(bkImg, m_Image[m_frameid], m_Pos.x, m_Pos.y, 255, 0, 0, true);
		int dir[4][2] = { -1, 0,  //��
			0, -1,  //��
			1, 0,   //��
			0, 1 }; //�� 
		if (m_Range == 1)
		{
			for (int i = 0; i < 4; i++)
			{
				if (map->m_Map[m_Pos.x / 40][m_Pos.y / 40] < 5 && map->m_Map[m_Pos.x / 40 + dir[i][0]][m_Pos.y / 40 + dir[i][1]] != 0)
				{
					map->ClearMap(m_Pos.x + dir[i][0] * 40, m_Pos.y + dir[i][1] * 40); 
					//ը����������ݲ���
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
					//ը����������ݲ���
					CTools::CopyToBack(bkImg, m_ShockWavesImgs[0][i], m_Pos.x + 40 * dir[i][0], m_Pos.y + 40 * dir[i][1], 255, 0, 0, true);
				}
				//ը����Χ2���񵽵��ߺ�
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
	//ը��
	if (m_TimeCount == 0)  
	{
		m_Flag = 0;

		map->ClearMap(m_Pos.x / 40, m_Pos.y / 40);
	}
}
/**
* @brief �ͷ�ը����ռ�õ��ڴ�
*
* �ͷ�ը��������ͼ��ռ�õ��ڴ�
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
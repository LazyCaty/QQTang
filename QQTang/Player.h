/**
* @file Player.h
* @brief Player1��ʹ�õ���ͷ�ļ���
* @author ����
* @date 20180712
* @version 1.0
*/
#pragma once 
#include "GameMap.h"
/**
* @class CPlayer
* @brief ���1
*
* �������1�������Եĳ�ʼ�������1�����ƶ���ʵ�֣��Լ��ͷ�����ռ�õ��ڴ棬������Ƶ��������ϵĹ���
*/
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	IplImage* m_Img[5][5];//*����ͼƬ*/
	CvPoint m_pos;//*����λ��*/
	int m_speed;//*�����ٶ�*/
	int m_ori;//*����*/
	int m_way;//*�Ȳ������ж�*/
	int m_aspeed;//*һ�����߼������ӣ����ڡ���ë�ȡ���������
	unsigned int m_HP;//*����ֵ*/
	int m_score;
	IplImage *m_HPImg;//*����ֵͼƬ*/
	void Init(CGameMap *map);
	void Release();
	void Move(int key, CGameMap * map);
	void CopyToBack(IplImage *back);
};
/**
* @file Game.h
* @brief ��Ϸ���ͷ�ļ���
* @author ����
* @date 20180712
* @version 1.0
*/
#pragma once
#include"Player.h"
#include"Player2.h"
#include"AutoMonster.h"
#include"Prize.h"
#include"Crump.h"
#include<vector>
using namespace std;
/**
* @class CGame
* @brief �����ӿ�ʼ�������ĸ������Ժ͹���
*
* ����ָ�룬���1�����2��С�֣���ͼ���������ˢȡ�ĵ���λ�õ����飬����ÿ��ը���Ķ�̬���飬������ߵ����飬��Ϸ״̬���жϣ���ʾHP�м��������壬
��ӭͼƬ��ʤ��ͼƬ��ʧ��ͼƬ����ʼ����Ϸ�����Ƶ��ߣ���ʾ����ֵ������ը��������ը����������Ϸ״̬�����е��ƶ����ܣ���������������Ϸ����ӭ���棬
�������棬��Ϸ���棬�ͷ���Դ�����߷�ë�ȵ����ã����߼�Ѫҩ��������
*/
class CGame
{
public:
	CGame();
	~CGame();
	IplImage * bkImg;//*����ָ��*/
	CPlayer Player1;//*���1*/
	CAPlayer Player2;/*���2*/
	CAutoMonster Monster;//*С��*/
	CGameMap Map;//*��ͼ*/
	CPrize m_Gifts[10];//*�������ˢȡ���ߵ�λ��*/
	vector <CCrump *> m_Crumps;//*����ÿ��ը���Ķ�̬����*/
	int m_Gift[10];//*��������*/
	int m_State;//*��Ϸ״̬�ж�*/
	CvFont m_GameFont;//*����*/
	IplImage *m_WelcomeImg;//*��ӭͼƬ*/
	IplImage *m_WinImg;//*ʤ��ͼƬ*/
	IplImage *m_LostImg;//*ʧ��ͼƬ*/
	void InitGame();
	void DrawGift();
	void DrawMassage(IplImage * bkImg);
	void Player1Crump(int key);
	void Player2Crump(int key);
	void DrawCrump();
	void UpdateCrump();
	void UpdateState();
	void Move(int key, CGameMap *map);
	static void Mouse(int event, int x, int y, int flags, void* p);
	void RunGame();
	void Welcome();
	void GameOver();
	void Run();
	void Release();
	void Scud();
	void AddHP();
	void WMMP();
};
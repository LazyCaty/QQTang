/**
* @file Game.cpp
* @brief ��Ϸ����
* @author ����
* @date 20180712
* @version 1.0
*/
#include"stdafx.h"
#include<windows.h>
#include"Game.h"
#include"Tools.h" 
using namespace std;
#pragma comment(lib,"winmm.lib")
CGame::CGame()
{

}
CGame::~CGame()
{

}
/**
* @brief ������
*
* �����������ӭ���桱��Ŀ�ʼ��Ϸʱ���롰������Ϸ������
* @param event �����еĲ����������Ҽ��ĵ�������ֵĹ����ȣ�
* @param x ����¼�����λ�õĺ�����
* @param y ����¼�����λ�õ�������
* @param flags ����������ק�¼����Լ�������������¼�
* @param *p ���ݵ�cvSetMouseCallback�������õĲ���
*/
void CGame::Mouse(int event, int x, int y, int flags, void* p)
{
	CGame *game = (CGame *)p;
	CGameMap *map = (CGameMap *)p;
	switch (event) {
	case CV_EVENT_FLAG_LBUTTON:
	{
		if (game->m_State == 1) //welcome
		{
			if (x > 125 && x < 271 && y>400 && y < 443)
			{
				game->m_State = 2;
			}

		}
	}
	break;

	}
}
/**
* @brief When Moster Meet Player
*
* С��������ң���ҵ�Ѫ
*/
void CGame::WMMP()
{
	if (Monster.m_pos.x == Player1.m_pos.x && Monster.m_pos.y == Player1.m_pos.y)
	{
		Player1.m_HP--;
	}
	if (Monster.m_pos.x == Player2.m_pos.x && Monster.m_pos.y == Player2.m_pos.y)
	{
		Player2.m_HP--;
	}
}
/**
* @brief ��ʼ����Ϸ
*
* ������Ϸ���ڣ���ʼ��PLayer1,Player2,Monster,Map,m_Gifts[],m_State,m_GameFont,*m_WelcomeImg,*m_WinImg,*m_LostImg,������
*/
void CGame::InitGame()
{

	cvNamedWindow("QQTang", 1);
	m_WelcomeImg = cvLoadImage("E:\\QQTang\\QQTang\\QQTang\\Resource\\Interface\\welcome.jpg",1);
	m_WinImg = cvLoadImage("E:\\QQTang\\QQTang\\QQTang\\Resource\\Interface\\win.jpg", 1);
	m_LostImg = cvLoadImage("E:\\QQTang\\QQTang\\QQTang\\Resource\\Interface\\lost.jpg", 1);
	cvInitFont(&m_GameFont, CV_FONT_HERSHEY_DUPLEX, 1, 0.7, 1.0, 2, 7);  //����,ˮƽ����,Ǧֱ����,��б�̶�,�����ϸ,��������
	m_State = 1;
	Map.Init();
	Map.ReadMaptxt();
	Player1.Init(&Map);
	Player2.Init(&Map);
	Monster.Init(&Map);
	Map.CreateMap();
	//i:�������λ�õ��ߵĸ���
	for (int i = 0; i < 10; i++)
	{
		m_Gifts[i].Init();
		m_Gift[i] = m_Gifts[i].temp;
	}
	cvSetMouseCallback("QQTang", CGame::Mouse, this);
}
/**
* @brief �����С�ֵ��ƶ�
*
* �������ﰴ���ƶ���С���Զ��ƶ��Ĺ���
* @param key ��ȡ��ҵİ�������
* @param *map ��ײ���ʶ��
*/
void CGame::Move(int key,CGameMap *map)
{
	Player1.Move(key, &Map);
	Player2.Move(key, &Map);
	Monster.Automove(&Map);
}
/**
* @brief ��ӭ����
*
* ���롰��ӭ���桱��ͼƬ�������䱳�����֣�������Ϸ״̬�ж��Ƿ��˳���Ϸ,������Ϸ��ʼ��
*/
void CGame::Welcome()
{
	InitGame();
	//����Welcome����ı�����Ч
	PlaySound(L"E:\\QQTang\\QQTang\\QQTang\\Resource\\sound\\back_music2.wav", NULL, SND_FILENAME | SND_ASYNC);
		cvShowImage("QQTang", m_WelcomeImg);
		int key = cvWaitKey(50);
		while (true)
		{
			if (m_State == 1)
			{
				int key = cvWaitKey(50);
				if (key == 27)
				{
					m_State = 5;
					break;
				}
			}
			else
				break;
		}
}
/**
* @brief ������Ϸ״̬
*
* ͨ�����1�����2������ֵ���Խ�����Ϸ״̬�ĸ���
*/
void CGame::UpdateState()
{
	if (Player1.m_HP == 0)
	{
		m_State = 4;
	}
	if (Player2.m_HP == 0)
	{
		m_State = 3;
	}
}
/**
* @brief ��������
*
* ������Ϸ״̬�жϽ���ʤ�����滹��ʧ�ܽ���
*/
void CGame::GameOver()
{
	if (m_State == 3) 
	{
		//����ʤ���������Ч
		PlaySound(L"E:\\QQTang\\QQTang\\QQTang\\Resource\\sound\\lost.wav", NULL, SND_FILENAME | SND_ASYNC);
		 
		cvShowImage("QQTang", m_WinImg);
	}
	else if (m_State == 4)
	{
		//����ʧ�ܽ������Ч
		PlaySound(L"E:\\QQTang\\QQTang\\QQTang\\Resource\\sound\\win.wav", NULL, SND_FILENAME | SND_ASYNC);

		cvShowImage("QQTang", m_LostImg);
	}

	while (true)
	{
		if ((m_State == 3) || (m_State == 4))
		{
			int key = cvWaitKey(50);
			if (key == 27)
			{
				m_State = 1;
				break;
			}
		}
		else
			break;
	}
}
/**
* @brief ������Ϸ
*
* ����һ����QQtang���Ĵ��ڲ����Ʊ���ͼ�����š�������Ϸ������ı������֣������С�֣����ը��������ֵ���Ƶ������ϣ�����ը��״̬�ĸ��£�
������ҵİ������������С���ë�ȡ�����Ѫҩ��������ʹ��״̬���жϣ����ݰ��������������1���2�Ƿ���ը�����ƶ����жϣ����ݰ��������ж��Ƿ�
���˳��ý���
*/
void CGame::RunGame()
{
	//������Ϸ�������Ч
	PlaySound(L"E:\\QQTang\\QQTang\\QQTang\\Resource\\sound\\back_music1.wav", NULL, SND_FILENAME | SND_ASYNC);
	for (int num = 0;; num++)
	{
		bkImg = Map.GetBackShowImg();
		Player1.CopyToBack(bkImg);
		Player2.CopyToBack(bkImg);
		Monster.CopyToBack(bkImg);
		DrawGift();
		DrawCrump();
		DrawMassage(bkImg);
		UpdateCrump();
		cvShowImage("QQTang", bkImg);
		int key = 0;
   		key = cvWaitKey(50);
		Scud();
		AddHP();
   		Player1Crump(key);
		Player2Crump(key);
		WMMP();
		UpdateState();
		if (key == 27)
		{
			m_State = 1;
			break;
		}
		if (m_State != 2)
		{
			break;
		}
	}
}
/**
* @brief ��Ϸ����
*
* ��Ϸ�������壬���ø�����Ϸ����
*/
void CGame::Run()
{
	while (true) {
		if (m_State == 5)
			break;
		else {
			switch (m_State)
			{
			case 1:
				Welcome();
				break;
			case 2:
				RunGame();
				break;
			case 3:
			case 4:
				GameOver();
				break;
			default:
				break;
			}
		}
	}
}
/**
* @brief ���Ƶ���
*
* ������δ��ʹ��������Ƶ��������ϣ��������ѱ�ʹ���򲻻��Ʋ��ı���߽����Ƶ�һ���Ե��߰�鴦�����һ���Ե��ߣ�
*/
void CGame::DrawGift()
{
	for (int i = 0; i < 10; i++)
	{
		//�ж������Ƿ�񵽵���
		if (Player1.m_pos.x == m_Gifts[i].m_pos.x && Player1.m_pos.y == m_Gifts[i].m_pos.y )
		{
			m_Gifts[i].m_flag = 0;
			m_Gifts[i].m_pos.x = 18 * 40;
			m_Gifts[i].m_pos.y = 12* 40;
		}
		//�ж������Ƿ�񵽵���
		if (Player2.m_pos.x == m_Gifts[i].m_pos.x && Player2.m_pos.y == m_Gifts[i].m_pos.y)
		{
			m_Gifts[i].m_flag = 2;
			m_Gifts[i].m_pos.x = 18 * 40;
			m_Gifts[i].m_pos.y = 12 * 40;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (m_Gifts[i].m_flag == 1)
		{
			//����δ���񵽾ͻ��Ƶ���������
			CTools::CopyToBack(bkImg, m_Gifts[i].m_Img, m_Gifts[i].m_pos.x, m_Gifts[i].m_pos.y, 225, 225, 225);
		}
	}
}
/**
* @brief ���Ʋ���ʾ����ֵ������
*
* �����1�����2��HP������ơ�X n����ʾ��ǰ��ʣ������ֵ����
*/
void CGame::DrawMassage(IplImage * bkImg)
{
	char string[10];
	//��intת����char
	sprintf_s(string, "X %d", Player1.m_HP); 
	int x = 726, y = 52;
	CTools::CopyToBack(bkImg, Player1.m_HPImg, x, y, 0, 0, 0, true);    
	x += 26;
	y += 20;
	cvPutText(bkImg, string, cvPoint(x, y), &m_GameFont, CV_RGB(255, 0, 0));

	//��intת����char
	sprintf_s(string, "X %d", Player2.m_HP); 
	x = 726, y = 92;
	//��ʾѪ
	CTools::CopyToBack(bkImg, Player2.m_HPImg, x, y, 235, 235, 235);     
	x += 26;
	y += 20;
	cvPutText(bkImg, string, cvPoint(x, y), &m_GameFont, CV_RGB(255, 0, 0));

}
/**
* @brief ���߷�ë��
*
* �õ���Ϊ���õ��ߣ���øõ��߿��Խ���������
*/
void CGame::Scud()
{
	for (int i = 0; i < 10; i++)
	{
		//0��ʾ���߱����1ʹ��
		if (m_Gifts[i].m_flag == 0)
		{
			if (m_Gift[i] == 1)
			{
				Player1.m_aspeed = 1;
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		//2��ʾ���߱����2ʹ��
		if (m_Gifts[i].m_flag == 2)
		{
			if (m_Gift[i] == 1)
			{
				Player2.m_aspeed = 1;
			}
		}
	}
}
/**
* @brief ���߼�Ѫҩ��
*
* �õ���Ϊһ���Ե��ߣ���ú������������ֵ���Ƴ��õ��ߵ�һ���Ե��߰���
*/
void CGame::AddHP()
{
	for (int i = 0; i < 10; i++)
	{
		//0��ʾ���߱����1ʹ��
		if (m_Gifts[i].m_flag == 0)//
		{
			if (m_Gift[i] == 2)
			{
				Player1.m_HP++;
				m_Gifts[i].m_flag = 1;
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		//0��ʾ���߱����2ʹ��
		if (m_Gifts[i].m_flag == 2)
		{
			if (m_Gift[i] == 2)
			{
				Player2.m_HP++;
				m_Gifts[i].m_flag = 1;
			}
		}
	}
}
/**
* @brief �������1��ը��
*
* �ܹ���ʼ��һ��ը���浽��̬�����ﲢ�����Ƿ�ʹ������ը����Χ���ߵ��ж��Լ��Ƿ�ը����ҵ��ж�
* @param key ��ҴӼ��������һ��������Ϊ�ո������һ��ը������Ϊ��������ƶ���Ӧ����Ϸ����
*/
void CGame::Player1Crump(int key)
{
	CCrump * pcrump = NULL;
	pcrump = new CCrump;
	//��ը��
	if (key == ' ')    
	{
		pcrump->Init(Player1.m_pos.x, Player1.m_pos.y);
		m_Crumps.push_back(pcrump);
		for (int i = 0; i < 10; i++)
		{
			//0��ʾ���߱����1ʹ��
			if (m_Gifts[i].m_flag == 0)
			{
				if (m_Gift[i] == 0)
				{
					pcrump->CrumpRange();
				}
			}
		}
	}
	Move(key, &Map);
	//���1��Ѫû
	for (int i = 0; i < m_Crumps.size(); i++)  
	{
		if (m_Crumps[i]->m_Flag != 0)
			if (m_Crumps[i]->m_TimeCount < 2)
			{
				if (Player1.m_pos.x == m_Crumps[i]->m_Pos.x && abs(m_Crumps[i]->m_Pos.y - Player1.m_pos.y) <= m_Crumps[i]->m_Range * 40
					|| Player1.m_pos.y == m_Crumps[i]->m_Pos.y && abs(m_Crumps[i]->m_Pos.x - Player1.m_pos.x) <= m_Crumps[i]->m_Range * 40 ||
					Monster.m_pos.x == Player1.m_pos.x && Monster.m_pos.y == Player1.m_pos.y)
				{
					Player1.m_HP--;
				}
				if (Monster.m_pos.x == m_Crumps[i]->m_Pos.x && abs(m_Crumps[i]->m_Pos.y - Monster.m_pos.y) <= m_Crumps[i]->m_Range * 40
					|| Monster.m_pos.y == m_Crumps[i]->m_Pos.y && abs(m_Crumps[i]->m_Pos.x - Monster.m_pos.x) <= m_Crumps[i]->m_Range * 40)
				{
					Monster.m_HP--;
				}
			}
	}
}
/**
* @brief �������1��ը��
*
* �ܹ���ʼ��һ��ը���浽��̬�����ﲢ�����Ƿ�ʹ������ը����Χ���ߵ��ж��Լ��Ƿ�ը����ҵ��ж�
* @param key ��ҴӼ��������һ��������Ϊ�ո������һ��ը������Ϊ��������ƶ���Ӧ����Ϸ����
*/
void CGame::Player2Crump(int key)
{
	CCrump * pcrump = NULL;
	pcrump = new CCrump;
	//��ը��
	if (key == '0')    
	{
		pcrump->Init(Player2.m_pos.x, Player2.m_pos.y);
		m_Crumps.push_back(pcrump);
		for (int i = 0; i < 10; i++)
		{
			//2��ʾ���߱����2ʹ��
			if (m_Gifts[i].m_flag == 0)
			{
				if (m_Gift[i] == 0)
				{
					pcrump->CrumpRange();
				}
			}
		}
	}
	//���2��Ѫû��
	for (int i = 0; i < m_Crumps.size(); i++)  
	{
		if (m_Crumps[i]->m_Flag != 0)
			if (m_Crumps[i]->m_TimeCount < 2)
			{
				if (Player2.m_pos.x == m_Crumps[i]->m_Pos.x && abs(m_Crumps[i]->m_Pos.y - Player2.m_pos.y) <= m_Crumps[i]->m_Range * 40
					|| Player2.m_pos.y == m_Crumps[i]->m_Pos.y && abs(m_Crumps[i]->m_Pos.x - Player2.m_pos.x) <= m_Crumps[i]->m_Range * 40)
				{
					Player2.m_HP--;
				}
				if (Monster.m_pos.x == m_Crumps[i]->m_Pos.x && abs(m_Crumps[i]->m_Pos.y - Monster.m_pos.y) <= m_Crumps[i]->m_Range * 40
					|| Monster.m_pos.y == m_Crumps[i]->m_Pos.y && abs(m_Crumps[i]->m_Pos.x - Monster.m_pos.x) <= m_Crumps[i]->m_Range * 40)
				{
					Monster.m_HP--;
				}
			}
	}
}
/**
* @brief ����ը��
*
* ͨ����ʱ��TimeCount�ı仯���Ʊ�ըǰ�Ķ���
*/
void CGame::DrawCrump()
{
	for (int i = 0; i < m_Crumps.size(); i++)
	{
		//���Ʊ�ըǰ�ı�ը����
		if (m_Crumps[i]->m_TimeCount >= 5)
			m_Crumps[i]->CopyToBack(bkImg);
	}
}

/**
* @brief ����ը��״̬
*
* ͨ���ı��ʱ��TimeCount��ֵ����ը����״̬�Ӷ�������ը����Ч��
*/
void CGame::UpdateCrump()
{
	for (int i = 0; i < m_Crumps.size(); i++)
	{
		m_Crumps[i]->CrumpChange(bkImg, &Map);
	}
}



/**
* @brief �ͷ���Դ
*
* �ͷ���Ϸ���������ص�����ͼƬ��ռ�õ��ڴ�
*/
void CGame::Release()
{
	cvDestroyWindow("QQTang");
	cvReleaseImage(&bkImg);
	Player1.Release();
	Player2.Release();
	Map.Release();
	for (int i = 0; i < 10; i++)
	{
		m_Gifts[i].Release();
	}
	Monster.Release();
}

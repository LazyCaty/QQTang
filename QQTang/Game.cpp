/**
* @file Game.cpp
* @brief 游戏引擎
* @author 汪洋
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
* @brief 鼠标操作
*
* 当鼠标点击“欢迎界面”里的开始游戏时进入“运行游戏”界面
* @param event 鼠标进行的操作（如左右键的点击，滑轮的滚动等）
* @param x 鼠标事件作用位置的横坐标
* @param y 鼠标事件作用位置的纵坐标
* @param flags 代表鼠标的拖拽事件，以及键盘鼠标联合事件
* @param *p 传递到cvSetMouseCallback函数调用的参数
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
* 小怪碰到玩家，玩家掉血
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
* @brief 初始化游戏
*
* 建立游戏窗口，初始化PLayer1,Player2,Monster,Map,m_Gifts[],m_State,m_GameFont,*m_WelcomeImg,*m_WinImg,*m_LostImg,鼠标操作
*/
void CGame::InitGame()
{

	cvNamedWindow("QQTang", 1);
	m_WelcomeImg = cvLoadImage("E:\\QQTang\\QQTang\\QQTang\\Resource\\Interface\\welcome.jpg",1);
	m_WinImg = cvLoadImage("E:\\QQTang\\QQTang\\QQTang\\Resource\\Interface\\win.jpg", 1);
	m_LostImg = cvLoadImage("E:\\QQTang\\QQTang\\QQTang\\Resource\\Interface\\lost.jpg", 1);
	cvInitFont(&m_GameFont, CV_FONT_HERSHEY_DUPLEX, 1, 0.7, 1.0, 2, 7);  //字体,水平比例,铅直比例,倾斜程度,字体粗细,线条种类
	m_State = 1;
	Map.Init();
	Map.ReadMaptxt();
	Player1.Init(&Map);
	Player2.Init(&Map);
	Monster.Init(&Map);
	Map.CreateMap();
	//i:载入随机位置道具的个数
	for (int i = 0; i < 10; i++)
	{
		m_Gifts[i].Init();
		m_Gift[i] = m_Gifts[i].temp;
	}
	cvSetMouseCallback("QQTang", CGame::Mouse, this);
}
/**
* @brief 人物和小怪的移动
*
* 进行人物按键移动和小怪自动移动的功能
* @param key 读取玩家的按键操作
* @param *map 碰撞体的识别
*/
void CGame::Move(int key,CGameMap *map)
{
	Player1.Move(key, &Map);
	Player2.Move(key, &Map);
	Monster.Automove(&Map);
}
/**
* @brief 欢迎界面
*
* 载入“欢迎界面”的图片并播放其背景音乐，进行游戏状态判断是否退出游戏,进行游戏初始化
*/
void CGame::Welcome()
{
	InitGame();
	//播放Welcome界面的背景音效
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
* @brief 更新游戏状态
*
* 通过玩家1和玩家2的生命值属性进行游戏状态的更新
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
* @brief 结束界面
*
* 根据游戏状态判断进入胜利界面还是失败界面
*/
void CGame::GameOver()
{
	if (m_State == 3) 
	{
		//播放胜利界面的音效
		PlaySound(L"E:\\QQTang\\QQTang\\QQTang\\Resource\\sound\\lost.wav", NULL, SND_FILENAME | SND_ASYNC);
		 
		cvShowImage("QQTang", m_WinImg);
	}
	else if (m_State == 4)
	{
		//播放失败界面的音效
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
* @brief 运行游戏
*
* 创建一个“QQtang”的窗口并绘制背景图，播放“运行游戏”界面的背景音乐，将人物，小怪，礼物，炸弹，生命值绘制到背景上，进行炸弹状态的更新，
读入玩家的按键操作，进行“飞毛腿”“加血药剂”道具使用状态的判断，根据按键操作进行玩家1玩家2是否创造炸弹和移动的判断，根据按键操作判断是否
该退出该界面
*/
void CGame::RunGame()
{
	//播放游戏界面的音效
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
* @brief 游戏界面
*
* 游戏运行主体，调用各个游戏界面
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
* @brief 绘制道具
*
* 若道具未被使用则将其绘制到背景板上，若道具已被使用则不绘制并改变道具将其移到一次性道具板块处（针对一次性道具）
*/
void CGame::DrawGift()
{
	for (int i = 0; i < 10; i++)
	{
		//判断人物是否捡到道具
		if (Player1.m_pos.x == m_Gifts[i].m_pos.x && Player1.m_pos.y == m_Gifts[i].m_pos.y )
		{
			m_Gifts[i].m_flag = 0;
			m_Gifts[i].m_pos.x = 18 * 40;
			m_Gifts[i].m_pos.y = 12* 40;
		}
		//判断人物是否捡到道具
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
			//道具未被捡到就绘制到背景板上
			CTools::CopyToBack(bkImg, m_Gifts[i].m_Img, m_Gifts[i].m_pos.x, m_Gifts[i].m_pos.y, 225, 225, 225);
		}
	}
}
/**
* @brief 绘制并显示生命值的条数
*
* 在玩家1和玩家2的HP后面绘制“X n”表示当前所剩的生命值条数
*/
void CGame::DrawMassage(IplImage * bkImg)
{
	char string[10];
	//将int转化成char
	sprintf_s(string, "X %d", Player1.m_HP); 
	int x = 726, y = 52;
	CTools::CopyToBack(bkImg, Player1.m_HPImg, x, y, 0, 0, 0, true);    
	x += 26;
	y += 20;
	cvPutText(bkImg, string, cvPoint(x, y), &m_GameFont, CV_RGB(255, 0, 0));

	//将int转化成char
	sprintf_s(string, "X %d", Player2.m_HP); 
	x = 726, y = 92;
	//显示血
	CTools::CopyToBack(bkImg, Player2.m_HPImg, x, y, 235, 235, 235);     
	x += 26;
	y += 20;
	cvPutText(bkImg, string, cvPoint(x, y), &m_GameFont, CV_RGB(255, 0, 0));

}
/**
* @brief 道具飞毛腿
*
* 该道具为永久道具，获得该道具可以进行跳格子
*/
void CGame::Scud()
{
	for (int i = 0; i < 10; i++)
	{
		//0表示道具被玩家1使用
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
		//2表示道具被玩家2使用
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
* @brief 道具加血药剂
*
* 该道具为一次性道具，获得后增加玩家生命值并移除该道具到一次性道具版上
*/
void CGame::AddHP()
{
	for (int i = 0; i < 10; i++)
	{
		//0表示道具被玩家1使用
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
		//0表示道具被玩家2使用
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
* @brief 创造玩家1的炸弹
*
* 能够初始化一个炸弹存到动态数组里并进行是否使用扩大炸弹范围道具的判定以及是否炸到玩家的判定
* @param key 玩家从键盘输入的一个按键若为空格则产生一个炸弹，若为方向键则移动相应的游戏人物
*/
void CGame::Player1Crump(int key)
{
	CCrump * pcrump = NULL;
	pcrump = new CCrump;
	//放炸弹
	if (key == ' ')    
	{
		pcrump->Init(Player1.m_pos.x, Player1.m_pos.y);
		m_Crumps.push_back(pcrump);
		for (int i = 0; i < 10; i++)
		{
			//0表示道具被玩家1使用
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
	//玩家1扣血没
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
* @brief 创造玩家1的炸弹
*
* 能够初始化一个炸弹存到动态数组里并进行是否使用扩大炸弹范围道具的判定以及是否炸到玩家的判定
* @param key 玩家从键盘输入的一个按键若为空格则产生一个炸弹，若为方向键则移动相应的游戏人物
*/
void CGame::Player2Crump(int key)
{
	CCrump * pcrump = NULL;
	pcrump = new CCrump;
	//放炸弹
	if (key == '0')    
	{
		pcrump->Init(Player2.m_pos.x, Player2.m_pos.y);
		m_Crumps.push_back(pcrump);
		for (int i = 0; i < 10; i++)
		{
			//2表示道具被玩家2使用
			if (m_Gifts[i].m_flag == 0)
			{
				if (m_Gift[i] == 0)
				{
					pcrump->CrumpRange();
				}
			}
		}
	}
	//玩家2扣血没？
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
* @brief 绘制炸弹
*
* 通过计时器TimeCount的变化绘制爆炸前的动画
*/
void CGame::DrawCrump()
{
	for (int i = 0; i < m_Crumps.size(); i++)
	{
		//绘制爆炸前的爆炸动画
		if (m_Crumps[i]->m_TimeCount >= 5)
			m_Crumps[i]->CopyToBack(bkImg);
	}
}

/**
* @brief 更新炸弹状态
*
* 通过改变计时器TimeCount的值更新炸弹的状态从而做出爆炸动画效果
*/
void CGame::UpdateCrump()
{
	for (int i = 0; i < m_Crumps.size(); i++)
	{
		m_Crumps[i]->CrumpChange(bkImg, &Map);
	}
}



/**
* @brief 释放资源
*
* 释放游戏运行所加载的所有图片所占用的内存
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

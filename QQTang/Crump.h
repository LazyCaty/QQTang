/**
* @file Crump.h
* @brief 炸弹所用到的头文件库
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#pragma once
#include"GameMap.h"
/**
* @class CCrump
* @brief 炸弹的释放到爆炸结束
*
* 炸弹存在的标记，炸弹的位置，炸弹的计时器，炸弹的范围，炸弹的初始化，图片资源的释放，炸弹贴图的绘制，炸弹爆炸对地图的改变，扩大炸弹范围的道具
*/
class CCrump
{
public:
	CCrump();
	~CCrump(); 
	int m_Flag;	/**显示是否有炸弹的标志*/
	CvPoint m_Pos;/**位置信息*/
	IplImage* m_Image[4];	/**炸弹未爆炸的图片*/
	IplImage* m_ShockWavesImgs[2][4];	/**炸弹爆炸的图片*/
	int m_TimeCount;/**计时*/
	int m_frameid;/**用于判断该显示哪张炸弹图->制造爆炸前的动画效果*/
	int m_Range;/**炸弹爆炸的范围*/
	void Init(int x, int y); 
	void Release();	
	void CopyToBack(IplImage * bkImg);
	void CrumpChange(IplImage * bkImg, CGameMap * map);
	void CrumpRange();
};
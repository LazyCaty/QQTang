/**
* @file Crump.h
* @brief ը�����õ���ͷ�ļ���
* @author ����
* @date 20180712
* @version 1.0
*/
#pragma once
#include"GameMap.h"
/**
* @class CCrump
* @brief ը�����ͷŵ���ը����
*
* ը�����ڵı�ǣ�ը����λ�ã�ը���ļ�ʱ����ը���ķ�Χ��ը���ĳ�ʼ����ͼƬ��Դ���ͷţ�ը����ͼ�Ļ��ƣ�ը����ը�Ե�ͼ�ĸı䣬����ը����Χ�ĵ���
*/
class CCrump
{
public:
	CCrump();
	~CCrump(); 
	int m_Flag;	/**��ʾ�Ƿ���ը���ı�־*/
	CvPoint m_Pos;/**λ����Ϣ*/
	IplImage* m_Image[4];	/**ը��δ��ը��ͼƬ*/
	IplImage* m_ShockWavesImgs[2][4];	/**ը����ը��ͼƬ*/
	int m_TimeCount;/**��ʱ*/
	int m_frameid;/**�����жϸ���ʾ����ը��ͼ->���챬ըǰ�Ķ���Ч��*/
	int m_Range;/**ը����ը�ķ�Χ*/
	void Init(int x, int y); 
	void Release();	
	void CopyToBack(IplImage * bkImg);
	void CrumpChange(IplImage * bkImg, CGameMap * map);
	void CrumpRange();
};
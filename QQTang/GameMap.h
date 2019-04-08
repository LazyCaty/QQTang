/**
* @file GameMap.h
* @brief ��Ϸ��ͼ���ͷ�ļ���
* @author ����
* @date 20180712
* @version 1.0
*/
#pragma once
/**
* @class CGameMap
* @brief ��ͼ������
*
* ���������ͼͼƬ����ͼ����Ϣ������ͼģ����Ƶ������壬��ͼ�ϵ���ײ���⣬��ͼ������
*/
class CGameMap
{
public:
	CGameMap();
	~CGameMap();
	IplImage* m_ObstacleImg[3];//*�����ͼͼƬ*/
	IplImage * m_Background;//*ԭʼ�����Ŀ���*/
	IplImage * m_StaticBack;//*ÿһ֡�ı���*/
	IplImage * m_ShowImg;//*չʾÿһ֡�ı���*/
	int m_Map[MAP_SIZE][MAP_SIZE];//*�����ͼλ��*/
	IplImage * GetBackShowImg();
	void Init();
	void ReadMaptxt();
	void CreateMap();
	void Release();
	bool Collision(int x, int y);
	void ClearMap(int, int y);
};
/**
* @file GameMap.h
* @brief 游戏地图类的头文件库
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#pragma once
/**
* @class CGameMap
* @brief 地图的生成
*
* 包含载入地图图片，地图的信息，将地图模块绘制到背景板，地图上的碰撞体检测，地图的清理
*/
class CGameMap
{
public:
	CGameMap();
	~CGameMap();
	IplImage* m_ObstacleImg[3];//*储存地图图片*/
	IplImage * m_Background;//*原始背景的拷贝*/
	IplImage * m_StaticBack;//*每一帧的背景*/
	IplImage * m_ShowImg;//*展示每一帧的背景*/
	int m_Map[MAP_SIZE][MAP_SIZE];//*储存地图位置*/
	IplImage * GetBackShowImg();
	void Init();
	void ReadMaptxt();
	void CreateMap();
	void Release();
	bool Collision(int x, int y);
	void ClearMap(int, int y);
};
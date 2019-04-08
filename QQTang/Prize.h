/**
* @file Prize.h
* @brief 道具所使用到的头文件库
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#pragma once
/**
* @class CPrize
* @brief 道具
*
* 包含道具的位置，图片，道具的使用状态的初始化，以及道具贴图所占用内存的释放
*/
class CPrize
{
public:
	CPrize();
	~CPrize();
	CvPoint m_pos;//*道具的位置*/
	IplImage* m_Img;//*道具图*/
	int temp;//*产生一个随机道具*/
	int m_flag;//*记录道具是否被使用*/
	void Init();
	void Release();//销毁道具

};
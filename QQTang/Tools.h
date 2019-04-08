/**
* @file Tools.h
* @brief 工具所使用到的头文件库
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#pragma once
/**
* @class CPrize
* @brief 工具
*
* 将*img绘制到*back上
*/
class CTools
{
public:
	CTools();
	~CTools();
	static void CopyToBack(IplImage *back, IplImage *img, int x, int y, int keyR, int keyG, int keyB, bool equal = false);
};
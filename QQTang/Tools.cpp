/**
* @file Tools.cpp
* @brief 工具
* @author 汪洋
* @date 20180712
* @version 1.0
*/
#include "stdafx.h"
#include "Tools.h"


CTools::CTools()
{
}


CTools::~CTools()
{
}
/**
* @brief 拷贝到背景
*
* 将*img绘制到*back上
* @param *back 背景
* @param *img 绘制到背景上的图像
* @param x 绘制位置的横坐标
* @param y 绘制位置的纵坐标
* @param keyR 抠去背景的红色最大值
* @param keyB 抠去背景的蓝色最大值
* @param keyG 抠去背景的绿色最大值
* @param equal 判断是抠一个范围内的背景还是某一个特定值的背景
*/

void CTools::CopyToBack(IplImage *back, IplImage *img, int x, int y, int keyR, int keyG, int keyB, bool equal)
{
	for (int i = 0; i < img->height; i++)
	{
		for (int j = 0; j < img->width; j++)
		{
			int	b = CV_IMAGE_ELEM(img, uchar, i, j * 3 + 0);
			int g = CV_IMAGE_ELEM(img, uchar, i, j * 3 + 1);
			int	r = CV_IMAGE_ELEM(img, uchar, i, j * 3 + 2);
			bool flag;
			if (!equal)
				flag = !(b > keyB && g > keyG && r > keyR);
			else
				flag = !(b == keyB && g == keyG && r == keyR);
			if (flag)
			{
				CV_IMAGE_ELEM(back, uchar, i + y, (j + x) * 3 + 0) = b;
				CV_IMAGE_ELEM(back, uchar, i + y, (j + x) * 3 + 1) = g;
				CV_IMAGE_ELEM(back, uchar, i + y, (j + x) * 3 + 2) = r;
			}
		}
	}
}
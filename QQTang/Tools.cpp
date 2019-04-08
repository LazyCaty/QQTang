/**
* @file Tools.cpp
* @brief ����
* @author ����
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
* @brief ����������
*
* ��*img���Ƶ�*back��
* @param *back ����
* @param *img ���Ƶ������ϵ�ͼ��
* @param x ����λ�õĺ�����
* @param y ����λ�õ�������
* @param keyR ��ȥ�����ĺ�ɫ���ֵ
* @param keyB ��ȥ��������ɫ���ֵ
* @param keyG ��ȥ��������ɫ���ֵ
* @param equal �ж��ǿ�һ����Χ�ڵı�������ĳһ���ض�ֵ�ı���
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
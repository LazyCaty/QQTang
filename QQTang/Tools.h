/**
* @file Tools.h
* @brief ������ʹ�õ���ͷ�ļ���
* @author ����
* @date 20180712
* @version 1.0
*/
#pragma once
/**
* @class CPrize
* @brief ����
*
* ��*img���Ƶ�*back��
*/
class CTools
{
public:
	CTools();
	~CTools();
	static void CopyToBack(IplImage *back, IplImage *img, int x, int y, int keyR, int keyG, int keyB, bool equal = false);
};
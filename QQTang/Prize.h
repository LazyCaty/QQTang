/**
* @file Prize.h
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
* �������ߵ�λ�ã�ͼƬ�����ߵ�ʹ��״̬�ĳ�ʼ�����Լ�������ͼ��ռ���ڴ���ͷ�
*/
class CPrize
{
public:
	CPrize();
	~CPrize();
	CvPoint m_pos;//*���ߵ�λ��*/
	IplImage* m_Img;//*����ͼ*/
	int temp;//*����һ���������*/
	int m_flag;//*��¼�����Ƿ�ʹ��*/
	void Init();
	void Release();//���ٵ���

};
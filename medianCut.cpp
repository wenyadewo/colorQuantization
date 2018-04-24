/*------------------------------��λ�з��㷨-----------------------------*/
#include "main.h"
#include <tchar.h>
#include "openFileName.h"
#include "algorithm.h"

/*��ν��λ�з��㷨������ȡ��������ͼ�����أ�������ͼ��ռ䣬��ѹȡ���������ϵ�һ�������壬ȡ�ó�����
  ���һ���������������е�������ͼ��ռ䱻ѹ���ɹ�����һ������һά�ᣬ��ô����һ�����أ����Խ�����ͼ��ռ�
  ���֣������ϵض����зָ�������ͼ��ռ���֣����յõ���Ҫ��k��ͼ��ռ䣬ͼ��ռ�����ĵ���Ϊ����ɫ*/

//ȡ��������ͼ������
extern Mat m_imgSrc;
extern Mat m_imgDst[10];
extern unsigned char *m_pImgSrc;
extern unsigned char *m_pImgDst[10];


void medianCut(){

	m_pImgDst[3] = NULL;   //��ʼ���ع�ͼ��ָ��

	m_imgSrc.copyTo(m_imgDst[3]);	

	int i, j;
	int b_max = 0;
	int g_max = 0;
	int r_max = 0;
	int b_min = 255;
	int g_min = 255;
	int r_min = 255;
	int max_vector;

	typedef struct colorSpace{
		int rmax;
		int rmin;
		int bmax;
		int bmin;
		int cmax;
		int cmin;
	}cSpace;

	cSpace colorsp[256]; //k����ɫ�ռ�

	//���ȵõ�������ĸ��������ȣ�����Ҫr&g&b_min&max,��������
	for (i = 0; i < m_imgSrc.rows; i++)
	{
		for (j = 0; j < m_imgSrc.cols; j++)
		{
			if (m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3]>b_max){
				b_max = m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3];
			}
			if (m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3]<b_min){
				b_min = m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3];
			}
			if (m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3 + 1]>g_max){
				g_max = m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3 + 1];
			}
			if (m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3 + 1]<g_min){
				g_min = m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3 + 1];
			}
			if (m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3 + 2]>r_max){
				r_max = m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3 + 2];
			}
			if (m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3 + 2]<r_min){
				r_min = m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3 + 2];
			}
		}
	}
	//��ȡ�����������ݣ��ټ���������
	max_vector = searchMaxVec((b_max - b_min), (g_max - g_min), (r_max)-(r_min));

   //�����Ϊb����������b������Ϊһά��ѹ����ɫ�ռ�
		/*���ڵ���Ҫ������Ҫ�ҳ�����b��������λ�зֵ㣬Ҳ���ǵõ���������b����һά�������е���λ��
		���õķ����ǣ���Ϊ���ص�ֵ����0-255�����Խ���õ�0-255��ÿһ�������е�������Ŀ��Ȼ��˳��
		�ۺͣ��ȵ��ۺ˴���1/2���ü�����Ϊ��λ��*/
	if (max_vector == 0){
		//��ȡÿ����Ŀ����
		int sortArr[256] = { 0 };
		for (i = 0; i < m_imgSrc.rows; i++)
		{
			for (j = 0; j < m_imgSrc.cols; j++)
			{
				sortArr[(int)m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3]]++;
			}
		}

		//��ȡ��λ�е�		
		int cutPoint=0;
		cutPoint = searchMedian(sortArr, m_imgSrc.rows*m_imgSrc.cols);

		//������һ�����⣬��δ洢���ؿռ䣡��������ν���ؿռ�  ��ʵҲ���ǳ���ߣ���������������

		//��ô������� �����Ǹ�����һ�����ؿռ䣬�����k���ӿռ��������������k������ɫ



	}


}
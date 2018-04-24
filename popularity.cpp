/*--------------------------------------����ɫ�㷨-----------------------------------*/
#include "main.h"
#include <tchar.h>
#include "openFileName.h"
#include "algorithm.h"

/*��ν����ɫ�㷨����Ϊ��ԭʼͼ���������ɫֱ��ͼ���������Գ�������ߵ�K����ɫ����ɫ��
��ô����Ҫ������ͱ������ζ���ɫֱ��ͼ���п��ٵ����������ÿ�εõ���������ߵ���ɫ������K��
���ǣ����Թ��Ϊ��ͼ�����صı������⣬����ʱ�Ĵ�ſ��Կ���һ����ά���飬3����ΪRGB,1����Ϊ���ִ���
������Ϊ��ͬɫ*/

//ȡ��������ͼ������
extern Mat m_imgSrc;
extern Mat m_imgDst[10];
extern unsigned char *m_pImgSrc;
extern unsigned char *m_pImgDst[10];
int i, j , x, y;
int cIndex;  //storeColor�к�
const int MAX_cIndex = 1e+7;
//int quickArray[MAX_cIndex];

const int k=256; //kɫ

unsigned char m_Palette[1024];//��ɫ��

//�����洢��ɫ������
int storeColor[MAX_cIndex][4] = { 0 };   //3����ΪRGB,1����Ϊ���ִ���

void popularity(){

	m_pImgDst[2] = NULL;   //��ʼ���ع�ͼ��ָ��

	m_imgSrc.copyTo(m_imgDst[2]);

	//�Դ��������ݸ���m_imgDst[2]�����㷨����

	cIndex = 0;

	//���ˣ�ֱ���õ�ɫ���������

	for (i = 0; i < m_imgDst[2].rows; i++)	//������������ ΪstoreColor��ֵ
	{
		for (j = 0; j < m_imgDst[2].cols; j++)   //��ȡ˳��ΪBGR
		{
			/*for (x = 0; x < 3; x++){   */
			////���������ɫ�����ȶԸ���ɫ��������
			//storeColor[cIndex][x] = m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3 + x];
			for (y = 0; y < cIndex; y++){   //����ѭ�������ؽ�������
				/*int x = 0;*/
				if ((int)m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3] == storeColor[y][0]){
					//B����ƥ��� ����ƥ��G����
					if ((int)m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3 + 1] == storeColor[y][1]){
						//G����ƥ��� ����ƥ��R����
						if ((int)m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3 + 2] == storeColor[y][2]){
							//���سɹ�ֱ��  Ƶ��+1 ���˳�����ѭ��
							storeColor[y][3]++;
							break;
						}
					}
				}//���ز��ɹ�����y����������ȥ ֱ��cIndex��Ҳ�޷�ƥ����

			}
			if (y == cIndex){ //����ʧ�ܣ��洢�����أ�cIndex++

				for (x = 0; x < 3; x++){
					storeColor[cIndex][x] = m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3 + x];
				}
				cIndex++;
			}
		}
	}
	//�������storeColor��ֵ��ϣ����Ž�storeColor�г���Ƶ������Kɫ 

	//quickArray[MAX_cIndex] = { 0 };
	////̫�鷳�� ֱ�ӿ��������
	//for (i = 0; i < cIndex - 1; i++){
	//	quickArray[i] = storeColor[i][3];
	//}
	//quickSort(quickArray, 0, cIndex-2);

	////������ɺ� ѡ��

	//������Ҫ������Ԫ���������ֻ��Ҫ�ҳ����Ƶ��K�������� ð�ݰ�

	

	for (i = 0; i < k; i++){  //k������
		for (j = cIndex - 1; j>i; j--){
			if (storeColor[j][3] > storeColor[j - 1][3]){
				for (x = 0; x < 4; x++){//��������ȫ������
					swap(storeColor[j][x], storeColor[j - 1][x]);
				}
			}
		}
	}
	//������ɣ����Ƶ��k��Ԫ���Ѿ�������storeColor��ǰk������֮Ϊ���ݣ��ع�ͼ��

	//�ع�����--���������� �����Ƶ��Kɫ ����ŷʽ���� ��ѡ����С����ɫ ���������

	long distance[k] = {0};
	int min = k-1;

	for (i = 0; i < m_imgDst[2].rows; i++){
		for (j = 0; j < m_imgDst[2].cols; j++){
			for (x = 0; x < k; x++){
				distance[x] = calDist((int)m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3],
					(int)m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3 + 1],
					(int)m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3 + 2],
					storeColor[x][0], storeColor[x][1], storeColor[x][2]);
			}
			//�ҳ���С��distance���±�
			for (y = 0; y < k-1; y++){
				if (distance[y] < distance[min]){
					min = y;
				}
			}
			//��storeColor[min]�滻������
			m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3] = storeColor[min][0];
			m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3+1] = storeColor[min][1];
			m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3+2] = storeColor[min][2];
		}
	}

	//�ع����
	//��ʼ��m_pImgDst[2]
	if (m_pImgDst[2] != NULL)
		delete m_pImgDst[2];
	m_pImgDst[2] = new unsigned char[m_imgDst[2].rows*m_imgDst[2].cols * 4];
	//��m_imgDst[2]����ȡλͼ���ݣ���ʽBGRA,һ������4�ֽ�
	for (i = 0; i<m_imgSrc.rows; i++)
	{
		for (j = 0; j<m_imgSrc.cols; j++)
		{
			m_pImgDst[2][i*m_imgDst[2].cols * 4 + j * 4] = (m_imgDst[2].data)[i*m_imgDst[2].cols * 3 + j * 3];
			m_pImgDst[2][i*m_imgDst[2].cols * 4 + j * 4 + 1] = (m_imgDst[2].data)[i*m_imgDst[2].cols * 3 + j * 3 + 1];
			m_pImgDst[2][i*m_imgDst[2].cols * 4 + j * 4 + 2] = (m_imgDst[2].data)[i*m_imgDst[2].cols * 3 + j * 3 + 2];
			m_pImgDst[2][i*m_imgDst[2].cols * 4 + j * 4 + 3] = 0;
		}
	}
}

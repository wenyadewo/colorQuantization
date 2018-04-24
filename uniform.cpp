/*--------------------------------------统一量化法-----------------------------------*/
#include "main.h"
#include <tchar.h>
#include "openFileName.h"
#include "atlstr.h"
//首先需要获取需要处理的图像的路径
//LPWSTR filePath = setOS()->lpstrFile;
//strFilename = *(setOS()).lpstrFile ;//接收返回的文件名，注意第一个字符需要为NULL

extern TCHAR strFilename[MAX_PATH];

//OpenCV根据获取的路径读取图像
//Mat m_imgSrc;//源图像对象，OpenCV的Mat类型
////目标图像对象，OpenCV的Mat类型

string filename; 
Mat m_imgSrc;
Mat m_imgDst[10];

unsigned char *m_pImgSrc;//从m_imgSrc中提取图像位图数据并组织成BGRA形式：一个像素4个字节
unsigned char *m_pImgDst[10];//从m_imgDst[1]中提取图像位图数据并组织成BGRA形式：一个像素4个字节
//Mat img = imread("G:\\大三下\\数字图像\\图像\\airplane.jpg");



void uniform(){
	/*filename = strFilename;*/
	/*string filename(strFilename);*/
	//m_imgSrc = imread(filename);//OpenCV读入图像
	/*imshow("",img);*/
	/*imshow("", m_imgSrc);*/
	//m_pImgSrc = NULL;

	m_pImgDst[1] = NULL;

	//m_pImgSrc = new unsigned char[m_imgSrc.rows*m_imgSrc.cols * 4];
	////int i, j;
	////从m_imgSrc中提取位图数据，形式BGRA,一个像素4字节
	//for (int i = 0; i<m_imgSrc.rows; i++)
	//{
	//	for (int j = 0; j<m_imgSrc.cols; j++)
	//	{
	//		m_pImgSrc[i*m_imgSrc.cols * 4 + j * 4] = (m_imgSrc.data)[i*m_imgSrc.cols * 3 + j * 3];
	//		m_pImgSrc[i*m_imgSrc.cols * 4 + j * 4 + 1] = (m_imgSrc.data)[i*m_imgSrc.cols * 3 + j * 3 + 1];
	//		m_pImgSrc[i*m_imgSrc.cols * 4 + j * 4 + 2] = (m_imgSrc.data)[i*m_imgSrc.cols * 3 + j * 3 + 2];
	//		m_pImgSrc[i*m_imgSrc.cols * 4 + j * 4 + 3] = 0;
	//	}
	//}

	
	//任意一个调色板颜色的编号与其表示的颜色之间的关系如下(编号的位数从前往后依次为0,1,2，……，7)：
	//0位和1位表示B分量的前两位，B分量的其余位数为0；
	//2位，3位和4位表示G分量的前三位，G分量的其余位数为0；
	//5位，6位和7位表示R分量的前三位，R分量的其余位数为0。
	//for (i = 0; i<256; i++)
	//{
	//	m_Palette[i * 4] = i & 0xc0;
	//	m_Palette[i * 4 + 1] = (i & 0x38) << 2;
	//	m_Palette[i * 4 + 2] = (i & 0x07) << 5;
	//	m_Palette[i * 4 + 3] = 0;
	//}

	m_imgSrc.copyTo(m_imgDst[1]);
	int i, j;
	for (i = 0; i<m_imgDst[1].rows; i++)	
	{
		for (j = 0; j<m_imgDst[1].cols; j++)
		{
			m_imgDst[1].data[i*m_imgDst[1].cols * 3 + j * 3] = (m_imgDst[1].data[i*m_imgDst[1].cols * 3 + j * 3] >> 6) << 6;
			m_imgDst[1].data[i*m_imgDst[1].cols * 3 + j * 3 + 1] = (m_imgDst[1].data[i*m_imgDst[1].cols * 3 + j * 3 + 1] >> 5) << 5;
			m_imgDst[1].data[i*m_imgDst[1].cols * 3 + j * 3 + 2] = (m_imgDst[1].data[i*m_imgDst[1].cols * 3 + j * 3 + 2] >> 5) << 5;
		}
	}
	//初始化m_pImgDst[1]
	if (m_pImgDst[1] != NULL)
		delete m_pImgDst[1];
	m_pImgDst[1] = new unsigned char[m_imgDst[1].rows*m_imgDst[1].cols * 4];
	//从m_imgDst[1]中提取位图数据，形式BGRA,一个像素4字节
	for (i = 0; i<m_imgSrc.rows; i++)
	{
		for (j = 0; j<m_imgSrc.cols; j++)
		{
			m_pImgDst[1][i*m_imgDst[1].cols * 4 + j * 4] = (m_imgDst[1].data)[i*m_imgDst[1].cols * 3 + j * 3];
			m_pImgDst[1][i*m_imgDst[1].cols * 4 + j * 4 + 1] = (m_imgDst[1].data)[i*m_imgDst[1].cols * 3 + j * 3 + 1];
			m_pImgDst[1][i*m_imgDst[1].cols * 4 + j * 4 + 2] = (m_imgDst[1].data)[i*m_imgDst[1].cols * 3 + j * 3 + 2];
			m_pImgDst[1][i*m_imgDst[1].cols * 4 + j * 4 + 3] = 0;
		}
	}
}
/*------------------------------中位切分算法-----------------------------*/
#include "main.h"
#include <tchar.h>
#include "openFileName.h"
#include "algorithm.h"

/*所谓中位切分算法，对于取到的所有图像像素，关于其图像空间，内压取到紧紧贴合的一个长方体，取该长方体
  最长的一个分量，想象所有的像素在图像空间被压缩成关于这一分量的一维轴，那么必有一个像素，可以将整个图像空间
  二分，当不断地对所有分割下来的图像空间二分，最终得到需要的k个图像空间，图像空间的中心点作为代表色*/

//取到被处理图像数据
extern Mat m_imgSrc;
extern Mat m_imgDst[10];
extern unsigned char *m_pImgSrc;
extern unsigned char *m_pImgDst[10];


void medianCut(){

	m_pImgDst[3] = NULL;   //初始化重构图像指针

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

	cSpace colorsp[256]; //k个颜色空间

	//首先得到长方体的各分量长度，即需要r&g&b_min&max,六个数据
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
	//获取到这六个数据，再计算出最长分量
	max_vector = searchMaxVec((b_max - b_min), (g_max - g_min), (r_max)-(r_min));

   //最长分量为b分量，则以b分量作为一维轴压缩颜色空间
		/*现在的主要问题是要找出关于b分量的中位切分点，也就是得到各像素在b分量一维轴上排列的中位数
		采用的方法是，因为像素的值域是0-255，所以仅需得到0-255上每一级所具有的像素数目，然后按顺序
		累和，等到累核大于1/2，该级数即为中位数*/
	if (max_vector == 0){
		//求取每级数目数组
		int sortArr[256] = { 0 };
		for (i = 0; i < m_imgSrc.rows; i++)
		{
			for (j = 0; j < m_imgSrc.cols; j++)
			{
				sortArr[(int)m_imgDst[3].data[i*m_imgDst[3].cols * 3 + j * 3]]++;
			}
		}

		//获取中位切点		
		int cutPoint=0;
		cutPoint = searchMedian(sortArr, m_imgSrc.rows*m_imgSrc.cols);

		//现在有一个问题，如何存储像素空间！！！，所谓像素空间  其实也就是长宽高，由六个变量决定

		//那么这个问题 输入是给定的一个像素空间，输出是k个子空间的六个变量，即k个代表色



	}


}
/*--------------------------------------流行色算法-----------------------------------*/
#include "main.h"
#include <tchar.h>
#include "openFileName.h"
#include "algorithm.h"

/*所谓流行色算法，即为对原始图像的像素颜色直方图进行排序，以出现率最高的K中颜色填充调色板
那么最主要的问题就变成了如何对颜色直方图进行快速的排序，亦或者每次得到出现率最高的颜色，遍历K次
如是，可以归结为对图像像素的遍历问题，遍历时的存放可以考量一个二维数组，3列作为RGB,1列作为出现次数
行数则为不同色*/

//取到被处理图像数据
extern Mat m_imgSrc;
extern Mat m_imgDst[10];
extern unsigned char *m_pImgSrc;
extern unsigned char *m_pImgDst[10];
int i, j , x, y;
int cIndex;  //storeColor行号
const int MAX_cIndex = 1e+7;
//int quickArray[MAX_cIndex];

const int k=256; //k色

unsigned char m_Palette[1024];//调色板

//声明存储颜色的数组
int storeColor[MAX_cIndex][4] = { 0 };   //3列作为RGB,1列作为出现次数

void popularity(){

	m_pImgDst[2] = NULL;   //初始化重构图像指针

	m_imgSrc.copyTo(m_imgDst[2]);

	//对待处理数据副本m_imgDst[2]进行算法处理

	cIndex = 0;

	//算了，直接用调色板进行排序

	for (i = 0; i < m_imgDst[2].rows; i++)	//遍历所有像素 为storeColor赋值
	{
		for (j = 0; j < m_imgDst[2].cols; j++)   //读取顺序为BGR
		{
			/*for (x = 0; x < 3; x++){   */
			////处理读入颜色，首先对该颜色进行判重
			//storeColor[cIndex][x] = m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3 + x];
			for (y = 0; y < cIndex; y++){   //此重循环对像素进行判重
				/*int x = 0;*/
				if ((int)m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3] == storeColor[y][0]){
					//B分量匹配后 继续匹配G分量
					if ((int)m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3 + 1] == storeColor[y][1]){
						//G分量匹配后 继续匹配R分量
						if ((int)m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3 + 2] == storeColor[y][2]){
							//判重成功直接  频率+1 并退出该重循环
							storeColor[y][3]++;
							break;
						}
					}
				}//判重不成功任由y继续增加下去 直至cIndex行也无法匹配上

			}
			if (y == cIndex){ //判重失败，存储该像素，cIndex++

				for (x = 0; x < 3; x++){
					storeColor[cIndex][x] = m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3 + x];
				}
				cIndex++;
			}
		}
	}
	//遍历完成storeColor赋值完毕，接着将storeColor中出现频率最多的K色 

	//quickArray[MAX_cIndex] = { 0 };
	////太麻烦了 直接快速排序吧
	//for (i = 0; i < cIndex - 1; i++){
	//	quickArray[i] = storeColor[i][3];
	//}
	//quickSort(quickArray, 0, cIndex-2);

	////排序完成后 选择

	//并不需要对所有元素完成排序，只需要找出最高频的K个，所以 冒泡吧

	

	for (i = 0; i < k; i++){  //k轮排序
		for (j = cIndex - 1; j>i; j--){
			if (storeColor[j][3] > storeColor[j - 1][3]){
				for (x = 0; x < 4; x++){//交换像素全部数据
					swap(storeColor[j][x], storeColor[j - 1][x]);
				}
			}
		}
	}
	//排序完成，最高频的k个元素已经排在了storeColor的前k个，以之为依据，重构图像

	//重构过程--将处理像素 与最高频的K色 演算欧式距离 ，选择最小的那色 替代该像素

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
			//找出最小的distance的下标
			for (y = 0; y < k-1; y++){
				if (distance[y] < distance[min]){
					min = y;
				}
			}
			//用storeColor[min]替换该像素
			m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3] = storeColor[min][0];
			m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3+1] = storeColor[min][1];
			m_imgDst[2].data[i*m_imgDst[2].cols * 3 + j * 3+2] = storeColor[min][2];
		}
	}

	//重构完毕
	//初始化m_pImgDst[2]
	if (m_pImgDst[2] != NULL)
		delete m_pImgDst[2];
	m_pImgDst[2] = new unsigned char[m_imgDst[2].rows*m_imgDst[2].cols * 4];
	//从m_imgDst[2]中提取位图数据，形式BGRA,一个像素4字节
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

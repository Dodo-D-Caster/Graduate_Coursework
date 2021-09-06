//ReadBitMap
//
#include<math.h>   
#include<stdio.h>   
#include<stdlib.h>   
#include <malloc.h>
#include <memory.h>
#include <math.h>


#define   WIDTHBYTES(bits) (((bits)+31)/32*4)
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

#pragma pack(1) //强制内存以1字节为单位对齐

//位图文件头信息结构定义
//其中不包含文件类型信息（由于结构体的内存结构决定，要是加了的话将不能正确读取文件信息）
typedef struct tagBITMAPFILEHEADER {
WORD   bfType;
DWORD  bfSize;               //文件大小
WORD   bfReserved1; //保留字，不考虑
WORD   bfReserved2; //保留字，同上
DWORD bfOffBits;         //实际位图数据的偏移字节数，即前三个部分长度之和
} BITMAPFILEHEADER; 

//信息头BITMAPINFOHEADER，也是一个结构，其定义如下：
typedef struct tagBITMAPINFOHEADER{
//public:
DWORD   biSize;                  //指定此结构体的长度，为40
LONG    biWidth;        //位图宽
LONG    biHeight;       //位图高
WORD    biPlanes;        //平面数，为1
WORD    biBitCount;       //采用颜色位数，可以是1，2，4，8，16，24，新的可以是32
DWORD   biCompression;           //压缩方式，可以是0，1，2，其中0表示不压缩
DWORD   biSizeImage;             //实际位图数据占用的字节数
LONG    biXPelsPerMeter;   //X方向分辨率
LONG    biYPelsPerMeter;   //Y方向分辨率
DWORD   biClrUsed;                  //使用的颜色数，如果为0，则表示默认值(2^颜色位数)
DWORD   biClrImportant;             //重要颜色数，如果为0，则表示所有颜色都是重要的
} BITMAPINFOHEADER; 

//调色板Palette，当然，这里是对那些需要调色板的位图文件而言的。24位和32位是不需要调色板的。
//（似乎是调色板结构体个数等于使用的颜色数。）
typedef struct tagRGBQUAD { 
//public:
BYTE     rgbBlue; //该颜色的蓝色分量
BYTE     rgbGreen; //该颜色的绿色分量
BYTE     rgbRed; //该颜色的红色分量
BYTE     rgbReserved; //保留值
} RGBQUAD;


/*函数功能：位图文件头显示
  输入参数：BITMAPFILEHEADER* pBmpHead 指向位图文件头结构的指针
（即内存地址，实现主调函数实参和被调函数形参的内存共享）
  输出值：没有
*/

void showBmpHead(BITMAPFILEHEADER* pBmpHead)
{
	printf("位图文件头:\n");
	printf("文件类型:%x\n",pBmpHead->bfType);
	printf("文件大小:%d\n",pBmpHead->bfSize);
	printf("保留字:%d\n",pBmpHead->bfReserved1);
	printf("保留字:%d\n",pBmpHead->bfReserved2);
	printf("实际位图数据的偏移字节数:%d\n",pBmpHead->bfOffBits);
}

/*函数功能：位图信息头显示
输入参数：BITMAPINFOHEADER* pBmpInforHead 指向位图文件信息头结构的指针
（即内存地址，实现主调函数实参和被调函数形参的内存共享）
  输出值：没有
*/
void showBmpInforHead(BITMAPINFOHEADER* pBmpInforHead)
{
	printf("位图信息头:\n");
	printf("结构体的长度:%d\n",pBmpInforHead->biSize);
	printf("位图宽:%d\n",pBmpInforHead->biWidth);
	printf("位图高:%d\n",pBmpInforHead->biHeight);
	printf("biPlanes平面数:%d\n",pBmpInforHead->biPlanes);
	printf("biBitCount采用颜色位数:%d\n",pBmpInforHead->biBitCount);
	printf("压缩方式:%d\n",pBmpInforHead->biCompression);
	printf("biSizeImage实际位图数据占用的字节数:%d\n",pBmpInforHead->biSizeImage);
	printf("X方向分辨率:%d\n",pBmpInforHead->biXPelsPerMeter);
	printf("Y方向分辨率:%d\n",pBmpInforHead->biYPelsPerMeter);
	printf("使用的颜色数:%d\n",pBmpInforHead->biClrUsed);
	printf("重要颜色数:%d\n",pBmpInforHead->biClrImportant);
}

/*函数功能：颜色表（索引模式）或位图数据区各像素RGB值（真彩模式）显示
  输入参数：RGBQUAD* pRGB --- RGBAlpha 四元素结构体指针变量
            DWORD num --- 要显示的RGBAlpha 四元素结构体个数，
	    即颜色表长度或要显示的像素个数
  输出值：  没有
*/
void showRgbQuan(RGBQUAD* pRGB, DWORD num)
{ 
	for (DWORD i=0; i<num; i++)
	{
	   if (i%5==0)
	   {
		printf("\n");
	   }
	   printf("(%-3d,%-3d,%-3d)   ",(pRGB+i)->rgbRed,(pRGB+i)->rgbGreen,(pRGB+i)->rgbBlue);
	}
	printf("\n");

}

/*函数功能：图像反色
  输入参数：RGBQUAD* dataOfBmp_src --- 原图像所有像素（以行为序）对应的
            RGBAlpha 四元素结构体指针；
	        RGBQUAD* dataOfBmp_dst --- 反色后的图像所有像素（以行为序）对应的
            RGBAlpha 四元素结构体指针；
            DWORD width, DWORD height --- 原图像和输出图像的宽度和高度
            （以像素为单位）
  输出值：  没有
*/
void reverseColor(RGBQUAD** dataOfBmp_src, RGBQUAD** dataOfBmp_dst, DWORD width, DWORD height)
{
	   for(DWORD i=0;i<height;i++)
		for(DWORD j=0;j<width;j++)
		{
		 dataOfBmp_dst[i][j].rgbRed = 255-dataOfBmp_src[i][j].rgbRed;   
		 dataOfBmp_dst[i][j].rgbGreen = 255-dataOfBmp_src[i][j].rgbGreen;   
		 dataOfBmp_dst[i][j].rgbBlue = 255-dataOfBmp_src[i][j].rgbBlue;    
		}            
}

/*函数功能：彩色图像转化为灰度图象
  输入参数：RGBQUAD** dataOfBmp_src --- 原图像所有像素（以行为序）对应的
            RGBAlpha 四元素结构体指针；
	        RGBQUAD** dataOfBmp_dst --- 转化为灰度图象后的图像所有像素（以行为序）对应的RGBAlpha 四元素结构体指针；
	        BYTE** dataOfBmp_gray --- 转化为灰度图象后的图像所有像素（以行为序）对应的灰度值；
            DWORD width, DWORD height --- 原图像和输出图像的宽度和高度
            （以像素为单位）
  输出值：  没有
*/
void RGB2Gray(RGBQUAD** dataOfBmp_src, RGBQUAD** dataOfBmp_dst, BYTE** dataOfBmp_gray, DWORD width, DWORD height)
{
	double gray;
	   
	for(DWORD i=0;i<height;i++)
	{
		for(DWORD j=0;j<width;j++)
		{
		 gray = 0.299*dataOfBmp_src[i][j].rgbRed+0.587*dataOfBmp_src[i][j].rgbGreen+0.114*dataOfBmp_src[i][j].rgbBlue;
		 dataOfBmp_gray[i][j] = (BYTE)gray;
		 dataOfBmp_dst[i][j].rgbRed = (BYTE)gray;   
		 dataOfBmp_dst[i][j].rgbGreen = (BYTE)gray;   
		 dataOfBmp_dst[i][j].rgbBlue = (BYTE)gray;    
		} 
	}	           
}

/*函数功能：灰度图象四近邻（flag=0）或八近邻（flag=1）对比度
  输入参数：BYTE* dataOfBmp_gray --- 灰度图像所有像素（以行为序）对应的灰度值；
            DWORD width, DWORD height --- 原图像和输出图像的宽度和高度
            （以像素为单位）
			bool flag --- 四近邻或八近邻标志， flag=0为四近邻，flag=1为八近邻
  输出值：  四近邻（flag=0）或八近邻（flag=1）对比度
*/
double contrast(BYTE** dataOfBmp_gray, DWORD width, DWORD height, bool flag)
{
	DWORD i, j;
	double contrast_sum = 0;
	int tmp0 = 2, tmp1 = 3, tmp2 = 4;
	int num = 0;
	
	if(flag)
	{
		tmp0 = 3;
		tmp1 = 5;
		tmp2 = 8;
	}
	num = 4*tmp0+((width-2)+(height-2))*2*tmp1+((width-2)*(height-2))*tmp2; 

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			 if(i>0)
			 {
				 contrast_sum += pow((dataOfBmp_gray[i-1][j]-dataOfBmp_gray[i][j]),2.0);
				 if(flag)
				 {
					if(j>0)
					{
						contrast_sum += pow((dataOfBmp_gray[i-1][j-1]-dataOfBmp_gray[i][j]),2.0);
					}
					if(j<width-1)
					{
						contrast_sum += pow((dataOfBmp_gray[i-1][j+1]-dataOfBmp_gray[i][j]),2.0);
					}
				 }
			 }
			 if(i<height-1)
			 {
				 contrast_sum += pow((dataOfBmp_gray[i+1][j]-dataOfBmp_gray[i][j]),2.0);
				 if(flag)
				 {
					if(j>0)
					{
						contrast_sum += pow((dataOfBmp_gray[i+1][j-1]-dataOfBmp_gray[i][j]),2.0);
					}
					if(j<width-1)
					{
						contrast_sum += pow((dataOfBmp_gray[i+1][j+1]-dataOfBmp_gray[i][j]),2.0);
					}
				 }
			 }
			 
			 if(j>0)
			 {
				 contrast_sum += pow((dataOfBmp_gray[i][j-1]-dataOfBmp_gray[i][j]),2.0); 
			 }

			 if(j<width-1)
			 {
				 contrast_sum += pow((dataOfBmp_gray[i][j+1]-dataOfBmp_gray[i][j]),2.0); 
			 }

		}
	}
		
	return contrast_sum/num;
}


/*函数功能：写（32位）位图（即保存）
  输入参数：RGBQUAD* dataOfBmp --- 待存储图像所有像素（以行为序）对应的
            RGBAlpha 四元素结构体指针；
            DWORD width, DWORD height --- 待存储图像的宽度和高度
            （以像素为单位）
  输出值：  没有
*/
void saveBmp(RGBQUAD** dataOfBmp, DWORD width, DWORD height)
{
	DWORD i, j;
	BITMAPFILEHEADER   bitHead;
	BITMAPINFOHEADER bitInfoHead; 
	WORD biBitCount = 32;
	FILE* pfile;
	char strFile[50];
	printf("please input the .bmp destination file name:\n");
	scanf("%s",strFile);
	pfile = fopen(strFile,"wb");//打开文件
	if(pfile!=NULL)
	{
	   printf("file %s open success.\n", strFile);
	   //写位图文件头信息
	   bitHead.bfType = 0x4d42;
	   bitHead.bfSize = 0;
	   bitHead.bfReserved1 = 0;
	   bitHead.bfReserved2 = 0;
	   bitHead.bfOffBits = 54;
	   if(biBitCount<=8)
			bitHead.bfOffBits += (DWORD)pow(2, biBitCount)*4;
	   fwrite(&bitHead,1,sizeof(tagBITMAPFILEHEADER),pfile);

	   bitInfoHead.biSize = 40;
	   bitInfoHead.biWidth = width;
	   bitInfoHead.biHeight = height;
	   bitInfoHead.biPlanes = 1;
	   bitInfoHead.biBitCount = biBitCount;
	   bitInfoHead.biCompression = 0;
	   bitInfoHead.biSizeImage = 0;
	   bitInfoHead.biXPelsPerMeter = 0;
	   bitInfoHead.biYPelsPerMeter = 0;
	   bitInfoHead.biClrImportant = 0;
	   bitInfoHead.biClrUsed = 0;
	   fwrite(&bitInfoHead,1,sizeof(tagBITMAPINFOHEADER),pfile);

	   if(biBitCount<=8)
	   {
		   BYTE tmp=0;

		   for(i=0; i<(DWORD)pow(2, biBitCount); i++)
		   {
			   tmp = (BYTE)i;
			   fwrite(&tmp,1,4,pfile);
		   }
	   }

	   int l_width   = WIDTHBYTES(width * biBitCount)-width*4;//计算为确保位图数据区的实际宽度为32字节的整数倍需添加的0字节个数
	   for( i=0; i<height; i++)
	   {
		   for( j=0; j<width; j+=1) 
		   {
			   fwrite(&dataOfBmp[height-i-1][j],1,4,pfile);
			   
		   }

		   BYTE tmp=0;
		   for(j=0; j<l_width; j++)
			   fwrite(&tmp,1,1,pfile);

	   }
	}

	fclose(pfile);

}

void main()
{
	BITMAPFILEHEADER   bitHead;
	BITMAPINFOHEADER bitInfoHead; 
	int i, j;

	FILE* pfile;
	char strFile[50];
	printf("please input the .bmp source file name:\n");
	scanf("%s",strFile);
	pfile = fopen(strFile,"rb");//打开文件
	if(pfile!=NULL)
	{
	   printf("file %s open success.\n", strFile);
	   //读取位图文件头信息
	   fread(&bitHead,1,sizeof(BITMAPFILEHEADER),pfile);
	   if(bitHead.bfType != 0x4d42)
	   {
		printf("file is not .bmp file!");
		return;
	   }
  
	   showBmpHead(&bitHead);
	   printf("\n\n");
	   //读取位图信息头信息
	   fread(&bitInfoHead,1,sizeof(BITMAPINFOHEADER),pfile);
	   showBmpInforHead(&bitInfoHead);
	   printf("\n");
	}
	else
	{
	   printf("file open fail!\n");
	   return;
	}
	
	RGBQUAD* pRgb=NULL;

	if(bitInfoHead.biBitCount < 24)//有调色板
	{ 
	   //读取调色盘结信息
	   long nPlantNum = bitInfoHead.biClrUsed;
       if(!nPlantNum)
           	nPlantNum = long(pow(2,double(bitInfoHead.biBitCount)));    //   Mix color Plant Number;
	   pRgb=new RGBQUAD[nPlantNum*sizeof(RGBQUAD)]; 
	   memset(pRgb,0,nPlantNum*sizeof(RGBQUAD));
	   int num = fread(pRgb,4,nPlantNum,pfile);
  
	   printf("Color Plate Number: %d\n",nPlantNum);
	   printf("颜色板信息:\n");
	   showRgbQuan(pRgb, nPlantNum);
  
	}

	int width = bitInfoHead.biWidth;
	int height = bitInfoHead.biHeight;
	//分配内存空间把源图存入内存   
	int l_width   = WIDTHBYTES(width* bitInfoHead.biBitCount);//计算位图的实际宽度并确保它为32的倍数
	long nData = height*l_width;
	BYTE    *pColorData= new BYTE[nData];   
	memset(pColorData,0,nData);   

	//把位图数据信息读到数组里   
	fread(pColorData,1,nData,pfile); 

	//将位图数据转化为RGB数据
	RGBQUAD** dataOfBmp_src=NULL; //用于保存各像素对应的RGB数据
	
	dataOfBmp_src = new RGBQUAD*[height]; 
	for(i=0; i < height;i++) 
	   dataOfBmp_src[i] =new RGBQUAD[width]; 

	if(bitInfoHead.biBitCount<24)//有调色板，即位图为非真彩色 
	{
	   int k;

	   if(bitInfoHead.biBitCount <= 8 && !bitInfoHead.biCompression)
	   {
    
		   int pnum = 8/bitInfoHead.biBitCount;
		   int mbnum = 8-bitInfoHead.biBitCount;
		
		   for(int i=0;i<height;i++)
		   {
				int k0 = (height-i-1)*l_width;//k:取得该像素颜色数据在实际数据数组中的序号
				for(int j=0;j<width;j++)
				{
					  BYTE mixIndex= 0;
					  k = k0+(j/pnum);
					  mixIndex = pColorData[k];
					  //mixIndex:提取当前像素的颜色的在颜色表中的索引值    
					  if(bitInfoHead.biBitCount < 8)
					  {
						  mixIndex = mixIndex<<((j%pnum)*bitInfoHead.biBitCount);
						  mixIndex = mixIndex>>mbnum;
					  }

					  //将像素颜色数据（RGBA）保存到数组中对应的位置
					  dataOfBmp_src[i][j].rgbRed = pRgb[mixIndex].rgbRed;
					  dataOfBmp_src[i][j].rgbGreen = pRgb[mixIndex].rgbGreen;
					  dataOfBmp_src[i][j].rgbBlue = pRgb[mixIndex].rgbBlue;
					  dataOfBmp_src[i][j].rgbReserved = pRgb[mixIndex].rgbReserved;
				}

			}
	   }

 
	   if(bitInfoHead.biBitCount == 16)
	   {
			   if(!bitInfoHead.biCompression)
			   {
					for( i=0;i<height;i++)
					{
						int k0 = (height-i-1)*l_width;
						for( j=0;j<width;j++)
						{
							WORD mixIndex= 0;
							k = k0+j*2;
							WORD shortTemp;
							shortTemp = pColorData[k+1];
							shortTemp = shortTemp<<8;
    
							mixIndex = pColorData[k] + shortTemp;
							dataOfBmp_src[i][j].rgbRed = pRgb[mixIndex].rgbRed;
							dataOfBmp_src[i][j].rgbGreen = pRgb[mixIndex].rgbGreen;
							dataOfBmp_src[i][j].rgbBlue = pRgb[mixIndex].rgbBlue;
							dataOfBmp_src[i][j].rgbReserved = pRgb[mixIndex].rgbReserved;
						}
					}
			   }
		 }
	}
	else//位图为24/32位真彩色
	{
	   int k;
	   int index = 0;
	   
       if(bitInfoHead.biBitCount == 16)
	   {
			for( i=0;i<height;i++)
			{
				int k0 = (height-i-1)*l_width;
				for( j=0;j<width;j++)
				{
					k = k0+j*2;		
					if(!bitInfoHead.biCompression)//555格式
					{
						dataOfBmp_src[i][j].rgbBlue=pColorData[k]&0x1F; 
						dataOfBmp_src[i][j].rgbGreen=(((pColorData[k+1]<<6)&0xFF)>>3)+(pColorData[k]>>5); 
						dataOfBmp_src[i][j].rgbRed=(pColorData[k+1]<<1)>>3;			
						dataOfBmp_src[i][j].rgbReserved = 0;
			
	   				}
				}
			}
       }
	   if(bitInfoHead.biBitCount == 24 && !bitInfoHead.biCompression)
	   {
			for( i=0;i<height;i++)
			{
				int k0 = (height-i-1)*l_width;
				for( j=0;j<width;j++)
				{
					 k = k0+(j*3);
					 dataOfBmp_src[i][j].rgbRed = pColorData[k+2];   
					 dataOfBmp_src[i][j].rgbGreen = pColorData[k+1];   
					 dataOfBmp_src[i][j].rgbBlue = pColorData[k];    
					 dataOfBmp_src[i][j].rgbReserved = 0;    
				 
				} 
			}
	   }
	   if(bitInfoHead.biBitCount == 32 && !bitInfoHead.biCompression)
	   {
			for( i=0;i<height;i++)
			{
				int k0 = (height-i-1)*l_width;
				for( j=0;j<width;j++)
				{
					 k = k0+(j*4);
					 dataOfBmp_src[i][j].rgbRed = pColorData[k+2];   
					 dataOfBmp_src[i][j].rgbGreen = pColorData[k+1];   
					 dataOfBmp_src[i][j].rgbBlue = pColorData[k];    
					 dataOfBmp_src[i][j].rgbReserved = pColorData[k+3];    
				 
				} 
			}

	   }

	}

	//printf("像素数据信息:\n");
	RGBQUAD** dataOfBmp_dst=NULL;
	dataOfBmp_dst = new RGBQUAD*[height]; //反色后的图象中每个像素的RGBAlpha
	for(i=0; i<height; i++)
		dataOfBmp_dst[i] = new RGBQUAD[width];

	BYTE** dataOfBmp_gray=NULL;
	dataOfBmp_gray = new BYTE*[height];
	for(i=0; i<height; i++)
		dataOfBmp_gray[i] = new BYTE[width];

	//reverseColor(dataOfBmp_src, dataOfBmp_dst, width, height);

	//RGB2Gray(dataOfBmp_src, dataOfBmp_dst, dataOfBmp_gray, width, height);
	//double contrast8nn = contrast(dataOfBmp_gray, width, height, 1);

	//printf("the 8nn contrast of the gray image is %f\n", contrast8nn);

	saveBmp(dataOfBmp_dst, width, height);

	fclose(pfile); 
	if (bitInfoHead.biBitCount<24 && pRgb)
	{
	   delete []pRgb;
	}
	for(i=0; i<height; i++)
		if(dataOfBmp_src[i])
			delete dataOfBmp_src[i];
	if(dataOfBmp_src)
		delete dataOfBmp_src;

	for(i=0; i<height; i++)
		if(dataOfBmp_dst[i])
			delete dataOfBmp_dst[i];
	if(dataOfBmp_dst)
		delete dataOfBmp_dst;

	for(i=0; i<height; i++)
		if(dataOfBmp_gray[i])
			delete dataOfBmp_gray[i];
	if(dataOfBmp_gray)
		delete dataOfBmp_gray;

	if(pColorData)
		delete []pColorData;


}

//ReadBitMap
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <algorithm>
#include <memory.h>
#include <math.h>

#define WIDTHBYTES(bits) (((bits) + 31) / 32 * 4)
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

#pragma pack(1) //ǿ���ڴ���1�ֽ�Ϊ��λ����

//λͼ�ļ�ͷ��Ϣ�ṹ����
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������Ҫ�Ǽ��˵Ļ���������ȷ��ȡ�ļ���Ϣ��
typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;
    DWORD bfSize;     //�ļ���С
    WORD bfReserved1; //�����֣�������
    WORD bfReserved2; //�����֣�ͬ��
    DWORD bfOffBits;  //ʵ��λͼ���ݵ�ƫ���ֽ�������ǰ�������ֳ���֮��
} BITMAPFILEHEADER;

//��ϢͷBITMAPINFOHEADER��Ҳ��һ���ṹ���䶨�����£�
typedef struct tagBITMAPINFOHEADER
{
    //public:
    DWORD biSize;         //ָ���˽ṹ��ĳ��ȣ�Ϊ40
    LONG biWidth;         //λͼ��
    LONG biHeight;        //λͼ��
    WORD biPlanes;        //ƽ������Ϊ1
    WORD biBitCount;      //������ɫλ����������1��2��4��8��16��24���µĿ�����32
    DWORD biCompression;  //ѹ����ʽ��������0��1��2������0��ʾ��ѹ��
    DWORD biSizeImage;    //ʵ��λͼ����ռ�õ��ֽ���
    LONG biXPelsPerMeter; //X����ֱ���
    LONG biYPelsPerMeter; //Y����ֱ���
    DWORD biClrUsed;      //ʹ�õ���ɫ�������Ϊ0�����ʾĬ��ֵ(2^��ɫλ��)
    DWORD biClrImportant; //��Ҫ��ɫ�������Ϊ0�����ʾ������ɫ������Ҫ��
} BITMAPINFOHEADER;

//��ɫ��Palette����Ȼ�������Ƕ���Щ��Ҫ��ɫ���λͼ�ļ����Եġ�24λ��32λ�ǲ���Ҫ��ɫ��ġ�
//���ƺ��ǵ�ɫ��ṹ���������ʹ�õ���ɫ������
typedef struct tagRGBQUAD
{
    //public:
    BYTE rgbBlue;     //����ɫ����ɫ����
    BYTE rgbGreen;    //����ɫ����ɫ����
    BYTE rgbRed;      //����ɫ�ĺ�ɫ����
    BYTE rgbReserved; //����ֵ
} RGBQUAD;

/*�������ܣ�λͼ�ļ�ͷ��ʾ
  ���������BITMAPFILEHEADER* pBmpHead ָ��λͼ�ļ�ͷ�ṹ��ָ��
�����ڴ��ַ��ʵ����������ʵ�κͱ��������βε��ڴ湲��
  ���ֵ��û��
*/

void showBmpHead(BITMAPFILEHEADER *pBmpHead)
{
    printf("λͼ�ļ�ͷ:\n");
    printf("�ļ�����:%x\n", pBmpHead->bfType);
    printf("�ļ���С:%d\n", pBmpHead->bfSize);
    printf("������:%d\n", pBmpHead->bfReserved1);
    printf("������:%d\n", pBmpHead->bfReserved2);
    printf("ʵ��λͼ���ݵ�ƫ���ֽ���:%d\n", pBmpHead->bfOffBits);
}

/*�������ܣ�λͼ��Ϣͷ��ʾ
���������BITMAPINFOHEADER* pBmpInforHead ָ��λͼ�ļ���Ϣͷ�ṹ��ָ��
�����ڴ��ַ��ʵ����������ʵ�κͱ��������βε��ڴ湲��
  ���ֵ��û��
*/
void showBmpInforHead(BITMAPINFOHEADER *pBmpInforHead)
{
    printf("λͼ��Ϣͷ:\n");
    printf("�ṹ��ĳ���:%d\n", pBmpInforHead->biSize);
    printf("λͼ��:%d\n", pBmpInforHead->biWidth);
    printf("λͼ��:%d\n", pBmpInforHead->biHeight);
    printf("biPlanesƽ����:%d\n", pBmpInforHead->biPlanes);
    printf("biBitCount������ɫλ��:%d\n", pBmpInforHead->biBitCount);
    printf("ѹ����ʽ:%d\n", pBmpInforHead->biCompression);
    printf("biSizeImageʵ��λͼ����ռ�õ��ֽ���:%d\n", pBmpInforHead->biSizeImage);
    printf("X����ֱ���:%d\n", pBmpInforHead->biXPelsPerMeter);
    printf("Y����ֱ���:%d\n", pBmpInforHead->biYPelsPerMeter);
    printf("ʹ�õ���ɫ��:%d\n", pBmpInforHead->biClrUsed);
    printf("��Ҫ��ɫ��:%d\n", pBmpInforHead->biClrImportant);
}

/*�������ܣ���ɫ������ģʽ����λͼ������������RGBֵ�����ģʽ����ʾ
  ���������RGBQUAD* pRGB --- RGBAlpha ��Ԫ�ؽṹ��ָ�����
            DWORD num --- Ҫ��ʾ��RGBAlpha ��Ԫ�ؽṹ�������
	    ����ɫ���Ȼ�Ҫ��ʾ�����ظ���
  ���ֵ��  û��
*/
void showRgbQuan(RGBQUAD *pRGB, DWORD num)
{
    for (DWORD i = 0; i < num; i++)
    {
        if (i % 5 == 0)
        {
            printf("\n");
        }
        printf("(%-3d,%-3d,%-3d)   ", (pRGB + i)->rgbRed, (pRGB + i)->rgbGreen, (pRGB + i)->rgbBlue);
    }
    printf("\n");
}

/*�������ܣ�ͼ��ɫ
  ���������RGBQUAD* dataOfBmp_src --- ԭͼ���������أ�����Ϊ�򣩶�Ӧ��
            RGBAlpha ��Ԫ�ؽṹ��ָ�룻
	        RGBQUAD* dataOfBmp_dst --- ��ɫ���ͼ���������أ�����Ϊ�򣩶�Ӧ��
            RGBAlpha ��Ԫ�ؽṹ��ָ�룻
            DWORD width, DWORD height --- ԭͼ������ͼ��Ŀ�Ⱥ͸߶�
            ��������Ϊ��λ��
  ���ֵ��  û��
*/
void reverseColor(RGBQUAD **dataOfBmp_src, RGBQUAD **dataOfBmp_dst, DWORD width, DWORD height)
{
    for (DWORD i = 0; i < height; i++)
        for (DWORD j = 0; j < width; j++)
        {
            dataOfBmp_dst[i][j].rgbRed = 255 - dataOfBmp_src[i][j].rgbRed;
            dataOfBmp_dst[i][j].rgbGreen = 255 - dataOfBmp_src[i][j].rgbGreen;
            dataOfBmp_dst[i][j].rgbBlue = 255 - dataOfBmp_src[i][j].rgbBlue;
        }
}

/*�������ܣ���ɫͼ��ת��Ϊ�Ҷ�ͼ��
  ���������RGBQUAD** dataOfBmp_src --- ԭͼ���������أ�����Ϊ�򣩶�Ӧ��
            RGBAlpha ��Ԫ�ؽṹ��ָ�룻
	        RGBQUAD** dataOfBmp_dst --- ת��Ϊ�Ҷ�ͼ����ͼ���������أ�����Ϊ�򣩶�Ӧ��RGBAlpha ��Ԫ�ؽṹ��ָ�룻
	        BYTE** dataOfBmp_gray --- ת��Ϊ�Ҷ�ͼ����ͼ���������أ�����Ϊ�򣩶�Ӧ�ĻҶ�ֵ��
            DWORD width, DWORD height --- ԭͼ������ͼ��Ŀ�Ⱥ͸߶�
            ��������Ϊ��λ��
  ���ֵ��  û��
*/
void RGB2Gray(RGBQUAD **dataOfBmp_src, RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD width, DWORD height)
{
    double gray;

    for (DWORD i = 0; i < height; i++)
    {
        for (DWORD j = 0; j < width; j++)
        {
            gray = 0.299 * dataOfBmp_src[i][j].rgbRed + 0.587 * dataOfBmp_src[i][j].rgbGreen + 0.114 * dataOfBmp_src[i][j].rgbBlue;
            dataOfBmp_gray[i][j] = (BYTE)gray;
            dataOfBmp_dst[i][j].rgbRed = (BYTE)gray;
            dataOfBmp_dst[i][j].rgbGreen = (BYTE)gray;
            dataOfBmp_dst[i][j].rgbBlue = (BYTE)gray;
        }
    }
}

/*�������ܣ��Ҷ�ͼ���Ľ��ڣ�flag=0����˽��ڣ�flag=1���Աȶ�
  ���������BYTE* dataOfBmp_gray --- �Ҷ�ͼ���������أ�����Ϊ�򣩶�Ӧ�ĻҶ�ֵ��
            DWORD width, DWORD height --- ԭͼ������ͼ��Ŀ�Ⱥ͸߶�
            ��������Ϊ��λ��
			bool flag --- �Ľ��ڻ�˽��ڱ�־�� flag=0Ϊ�Ľ��ڣ�flag=1Ϊ�˽���
  ���ֵ��  �Ľ��ڣ�flag=0����˽��ڣ�flag=1���Աȶ�
*/
double contrast(BYTE **dataOfBmp_gray, DWORD width, DWORD height, bool flag)
{
    DWORD i, j;
    double contrast_sum = 0;
    int tmp0 = 2, tmp1 = 3, tmp2 = 4;
    int num = 0;

    if (flag)
    {
        tmp0 = 3;
        tmp1 = 5;
        tmp2 = 8;
    }
    num = 4 * tmp0 + ((width - 2) + (height - 2)) * 2 * tmp1 + ((width - 2) * (height - 2)) * tmp2;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i > 0)
            {
                contrast_sum += pow((dataOfBmp_gray[i - 1][j] - dataOfBmp_gray[i][j]), 2.0);
                if (flag)
                {
                    if (j > 0)
                    {
                        contrast_sum += pow((dataOfBmp_gray[i - 1][j - 1] - dataOfBmp_gray[i][j]), 2.0);
                    }
                    if (j < width - 1)
                    {
                        contrast_sum += pow((dataOfBmp_gray[i - 1][j + 1] - dataOfBmp_gray[i][j]), 2.0);
                    }
                }
            }
            if (i < height - 1)
            {
                contrast_sum += pow((dataOfBmp_gray[i + 1][j] - dataOfBmp_gray[i][j]), 2.0);
                if (flag)
                {
                    if (j > 0)
                    {
                        contrast_sum += pow((dataOfBmp_gray[i + 1][j - 1] - dataOfBmp_gray[i][j]), 2.0);
                    }
                    if (j < width - 1)
                    {
                        contrast_sum += pow((dataOfBmp_gray[i + 1][j + 1] - dataOfBmp_gray[i][j]), 2.0);
                    }
                }
            }

            if (j > 0)
            {
                contrast_sum += pow((dataOfBmp_gray[i][j - 1] - dataOfBmp_gray[i][j]), 2.0);
            }

            if (j < width - 1)
            {
                contrast_sum += pow((dataOfBmp_gray[i][j + 1] - dataOfBmp_gray[i][j]), 2.0);
            }
        }
    }

    return contrast_sum / num;
}

/*�������ܣ�д��32λ��λͼ�������棩
  ���������RGBQUAD* dataOfBmp --- ���洢ͼ���������أ�����Ϊ�򣩶�Ӧ��
            RGBAlpha ��Ԫ�ؽṹ��ָ�룻
            DWORD width, DWORD height --- ���洢ͼ��Ŀ�Ⱥ͸߶�
            ��������Ϊ��λ��
  ���ֵ��  û��
*/
void saveBmp(RGBQUAD **dataOfBmp, DWORD width, DWORD height)
{
    DWORD i, j;
    BITMAPFILEHEADER bitHead;
    BITMAPINFOHEADER bitInfoHead;
    WORD biBitCount = 32;
    FILE *pfile;
    char strFile[50];
    printf("please input the .bmp destination file name:\n");
    scanf("%s", strFile);
    pfile = fopen(strFile, "wb"); //���ļ�
    if (pfile != NULL)
    {
        printf("file %s open success.\n", strFile);
        //дλͼ�ļ�ͷ��Ϣ
        bitHead.bfType = 0x4d42;
        bitHead.bfSize = 0;
        bitHead.bfReserved1 = 0;
        bitHead.bfReserved2 = 0;
        bitHead.bfOffBits = 54;
        if (biBitCount <= 8)
            bitHead.bfOffBits += (DWORD)pow(2, biBitCount) * 4;
        fwrite(&bitHead, 1, sizeof(tagBITMAPFILEHEADER), pfile);

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
        fwrite(&bitInfoHead, 1, sizeof(tagBITMAPINFOHEADER), pfile);

        if (biBitCount <= 8)
        {
            BYTE tmp = 0;

            for (i = 0; i < (DWORD)pow(2, biBitCount); i++)
            {
                tmp = (BYTE)i;
                fwrite(&tmp, 1, 4, pfile);
            }
        }

        int l_width = WIDTHBYTES(width * biBitCount) - width * 4; //����Ϊȷ��λͼ��������ʵ�ʿ��Ϊ32�ֽڵ�����������ӵ�0�ֽڸ���
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j += 1)
            {
                fwrite(&dataOfBmp[height - i - 1][j], 1, 4, pfile);
            }

            BYTE tmp = 0;
            for (j = 0; j < l_width; j++)
                fwrite(&tmp, 1, 1, pfile);
        }
    }

    fclose(pfile);
}

// �Ŵ���С
void bigSmall(RGBQUAD **dataOfBmp_src, RGBQUAD **dataOfBmp_dst, double k1, double k2, DWORD width, DWORD height)
{
    //���󻭲�
    if (k1 > 1 && k2 > 1)
    {
        dataOfBmp_dst = new RGBQUAD *[DWORD(height * k2 + 0.5)]; //��ɫ���ͼ����ÿ�����ص�RGBAlpha
        for (DWORD i = 0; i < DWORD(height * k2 + 0.5); i++)
            dataOfBmp_dst[i] = new RGBQUAD[DWORD(width * k1 + 0.5)];
    }

    //��������
    DWORD x0, y0;
    for (DWORD i = 0; i < height * k2; ++i)
        for (DWORD j = 0; j < width * k1; ++j)
        {
            x0 = DWORD(j / k1);
            y0 = DWORD(i / k2);
            if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)
            {
                dataOfBmp_dst[i][j] = dataOfBmp_src[y0][x0];
                dataOfBmp_dst[i][j + 1] = dataOfBmp_src[y0][x0 + 1];
                dataOfBmp_dst[i][j + 2] = dataOfBmp_src[y0][x0 + 2];
            }
        }

    //����
    saveBmp(dataOfBmp_dst, DWORD(width * k1 + 0.5), DWORD(height * k2 + 0.5));
}

// ����
void cuoQie(RGBQUAD **dataOfBmp_src, RGBQUAD **dataOfBmp_dst, DWORD dx, DWORD dy, DWORD width, DWORD height)
{
    //���󻭲�
    dataOfBmp_dst = new RGBQUAD *[height + width * 2]; //��ɫ���ͼ����ÿ�����ص�RGBAlpha
    for (DWORD i = 0; i < height + width * 2; i++)
        dataOfBmp_dst[i] = new RGBQUAD[width];

    //���в���
    for (DWORD i = 0; i < height; i++)
        for (DWORD j = 0; j < width; j++)
        {
            dataOfBmp_dst[i + dx * j][j] = dataOfBmp_src[i][j];
        }

    //����
    saveBmp(dataOfBmp_dst, width, height + width * 2);
}

// ƽ��
void move(RGBQUAD **dataOfBmp_src, RGBQUAD **dataOfBmp_dst, int xOffset, int yOffset, DWORD width, DWORD height)
{
    //���󻭲�
    dataOfBmp_dst = new RGBQUAD *[height + yOffset]; //��ɫ���ͼ����ÿ�����ص�RGBAlpha
    for (DWORD i = 0; i < height + yOffset; i++)
        dataOfBmp_dst[i] = new RGBQUAD[width + xOffset];

    //ƽ�Ʋ���
    if (width < xOffset || height < yOffset)
        return;
    for (DWORD i = 0; i < height; i++)
    {
        for (DWORD j = 0; j < width; j++)
        {
            dataOfBmp_dst[DWORD(i + yOffset + 0.5)][DWORD(j + xOffset + 0.5)] = dataOfBmp_src[i][j];
        }
    }

    //����
    saveBmp(dataOfBmp_dst, width + xOffset, height + yOffset);
}

// ����
void mirror(RGBQUAD **dataOfBmp_src, RGBQUAD **dataOfBmp_dst, bool flag, DWORD width, DWORD height)
{
    //����
    if (flag = 0)
    {
        for (DWORD i = 0; i < height; ++i)
            for (DWORD j = 0; j < width; ++j)
            {
                dataOfBmp_dst[i][j] = dataOfBmp_src[i][DWORD(width - 1 - j + 0.5)];
            }
    }
    //����
    else
    {
        for (DWORD i = 0; i < height; ++i)
            for (DWORD j = 0; j < width; ++j)
            {
                dataOfBmp_dst[i][j] = dataOfBmp_src[DWORD(height - 1 - i + 0.5)][j];
            }
    }

    //����
    saveBmp(dataOfBmp_dst, width, height);
}

// ��ת
void rotate(RGBQUAD **dataOfBmp_src, RGBQUAD **dataOfBmp_dst, double angle, DWORD width, DWORD height)
{
    height = height;
    width = width;
    double angleValue = (angle / 180.0) * 3.1415926;
    int max_x = 0, min_x = 0, max_y = 0, min_y = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int dis_x = int(i * cos(angleValue) - j * sin(angleValue) + 0.5);
            int dis_y = int(i * sin(angleValue) + j * cos(angleValue) + 0.5);
            if (dis_x > max_x)
            {
                max_x = dis_x;
            }
            if (dis_x < min_x)
            {
                min_x = dis_x;
            }
            if (dis_y > max_y)
            {
                max_y = dis_y;
            }
            if (dis_y < min_y)
            {
                min_y = dis_y;
            }
        }
    }

    //���󻭲�
    dataOfBmp_dst = new RGBQUAD *[width + height];
    for (DWORD i = 0; i < width + height; i++)
        dataOfBmp_dst[i] = new RGBQUAD[width + height];

    //����ƽ��
    int x_offset = 0 - min_x;
    int y_offset = 0 - min_y;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int dis_x = int(i * cos(angleValue) - j * sin(angleValue) + 0.5);
            dis_x += x_offset;
            int dis_y = int(i * sin(angleValue) + j * cos(angleValue) + 0.5);
            dis_y += y_offset;
            if (dis_x >= 0 && dis_x < max_x - min_x && dis_y >= 0 && dis_y <= max_y - min_y)
            {
                dataOfBmp_dst[dis_x][dis_y] = dataOfBmp_src[i][j];
            }
        }
    }

    //����
    saveBmp(dataOfBmp_dst, max_y - min_y, max_x - min_x);
}

// ���ԶԱ�չ��
void linearContrast(RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD width, DWORD height)
{
    for (DWORD i = 0; i < height; i++)
    {
        for (DWORD j = 0; j < width; j++)
        {
            if (dataOfBmp_gray[i][j] < 100)
            {
                dataOfBmp_dst[i][j].rgbRed = 0.5 * (BYTE)dataOfBmp_gray[i][j];
                dataOfBmp_dst[i][j].rgbGreen = 0.5 * (BYTE)dataOfBmp_gray[i][j];
                dataOfBmp_dst[i][j].rgbBlue = 0.5 * (BYTE)dataOfBmp_gray[i][j];
            }
            else if (dataOfBmp_gray[i][j] < 130 && dataOfBmp_gray[i][j] >= 100)
            {
                dataOfBmp_dst[i][j].rgbRed = 1.2 * (BYTE)dataOfBmp_gray[i][j];
                dataOfBmp_dst[i][j].rgbGreen = 1.2 * (BYTE)dataOfBmp_gray[i][j];
                dataOfBmp_dst[i][j].rgbBlue = 1.2 * (BYTE)dataOfBmp_gray[i][j];
            }
            else
            {
                dataOfBmp_dst[i][j].rgbRed = 0.5 * (BYTE)dataOfBmp_gray[i][j];
                dataOfBmp_dst[i][j].rgbGreen = 0.5 * (BYTE)dataOfBmp_gray[i][j];
                dataOfBmp_dst[i][j].rgbBlue = 0.5 * (BYTE)dataOfBmp_gray[i][j];
            }
        }
    }

    // ����
    saveBmp(dataOfBmp_dst, width, height);
}

// �����Զ�̬��Χ����
void noLinear(RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD width, DWORD height)
{
    double c = 255 / log10(256);
    for (DWORD i = 0; i < height; i++)
    {
        for (DWORD j = 0; j < width; j++)
        {
            dataOfBmp_dst[i][j].rgbRed = c * log10(1 + (BYTE)dataOfBmp_gray[i][j]);
            dataOfBmp_dst[i][j].rgbGreen = c * log10(1 + (BYTE)dataOfBmp_gray[i][j]);
            dataOfBmp_dst[i][j].rgbBlue = c * log10(1 + (BYTE)dataOfBmp_gray[i][j]);
        }
    }

    // ����
    saveBmp(dataOfBmp_dst, width, height);
}

// ֱ��ͼ���⻯
void histogramEqualize(RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD width, DWORD height)
{
    DWORD gray[256] = {0};               //��¼ÿ���Ҷȼ����µ����ظ���
    double gray_prob[256] = {0};         //��¼�Ҷȷֲ��ܶ�
    double gray_distribution[256] = {0}; //��¼�ۼ��ܶ�
    DWORD total = width * height;        //���������ظ���
    for (DWORD i = 0; i < height; i++)
    {
        for (DWORD j = 0; j < width; j++)
        {
            gray[dataOfBmp_gray[i][j]]++;
        }
    }
    for (DWORD i = 0; i < 256; i++)
    {
        gray_prob[i] = 1.0 * gray[i] / total;
    }
    for (DWORD i = 0; i < 256; i++)
        for (DWORD j = 0; j <= i; j++)
        {
            gray_distribution[i] += 1.0 * gray[j] / total;
        }

    for (DWORD i = 0; i < height; i++)
    {
        for (DWORD j = 0; j < width; j++)
        {
            dataOfBmp_dst[i][j].rgbRed = DWORD(gray_distribution[dataOfBmp_gray[i][j]] * 255 + 0.5);
            dataOfBmp_dst[i][j].rgbGreen = DWORD(gray_distribution[dataOfBmp_gray[i][j]] * 255 + 0.5);
            dataOfBmp_dst[i][j].rgbBlue = DWORD(gray_distribution[dataOfBmp_gray[i][j]] * 255 + 0.5);
        }
    }

    // ����
    saveBmp(dataOfBmp_dst, width, height);
}

// ��ֵ�˲�
void meanFilter(RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD width, DWORD height)
{
    for (DWORD i = 1; i < height - 1; i++)
    {
        for (DWORD j = 1; j < width - 1; j++)
        {
            BYTE tmp = ((BYTE)dataOfBmp_gray[i - 1][j - 1] + (BYTE)dataOfBmp_gray[i - 1][j] +
                        (BYTE)dataOfBmp_gray[i - 1][j + 1] + (BYTE)dataOfBmp_gray[i][j - 1] +
                        (BYTE)dataOfBmp_gray[i][j] + (BYTE)dataOfBmp_gray[i][j + 1] +
                        (BYTE)dataOfBmp_gray[i + 1][j - 1] + (BYTE)dataOfBmp_gray[i + 1][j] +
                        (BYTE)dataOfBmp_gray[i + 1][j + 1]) /
                       9;
            dataOfBmp_dst[i][j].rgbBlue = tmp;
            dataOfBmp_dst[i][j].rgbGreen = tmp;
            dataOfBmp_dst[i][j].rgbRed = tmp;
        }
    }

    // ����
    saveBmp(dataOfBmp_dst, width, height);
}

// ��Ȩ��ֵ�˲�
void weightedMeanFilter(RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD width, DWORD height)
{
    // ������ͬ��Ȩ
    double H[3][3] = {{1, 1, 1}, {1, 2, 1}, {1, 1, 1}};
    DWORD div = 10;

    // double H[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
    // DWORD div = 16;

    // double H[3][3] = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    // DWORD div = 8;

    // double H[3][3] = {{0, 0.25, 0}, {0.25, 1, 0.25}, {0, 0.25, 0}};
    // DWORD div = 2;

    for (DWORD i = 1; i < height - 1; i++)
    {
        for (DWORD j = 1; j < width - 1; j++)
        {
            BYTE tmp = ((BYTE)dataOfBmp_gray[i - 1][j - 1] * H[0][0] + (BYTE)dataOfBmp_gray[i - 1][j] * H[0][1] +
                        (BYTE)dataOfBmp_gray[i - 1][j + 1] * H[0][2] + (BYTE)dataOfBmp_gray[i][j - 1] * H[1][0] +
                        (BYTE)dataOfBmp_gray[i][j] * H[1][1] + (BYTE)dataOfBmp_gray[i][j + 1] * H[1][2] +
                        (BYTE)dataOfBmp_gray[i + 1][j - 1] * H[2][0] + (BYTE)dataOfBmp_gray[i + 1][j] * H[2][1] +
                        (BYTE)dataOfBmp_gray[i + 1][j + 1] * H[2][2]) /
                       div;
            dataOfBmp_dst[i][j].rgbBlue = tmp;
            dataOfBmp_dst[i][j].rgbGreen = tmp;
            dataOfBmp_dst[i][j].rgbRed = tmp;
        }
    }

    // ����
    saveBmp(dataOfBmp_dst, width, height);
}

// ��ֵ�˲�
void medianFilter(RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD width, DWORD height)
{
    for (DWORD i = 1; i < height - 1; i++)
    {
        for (DWORD j = 1; j < width - 1; j++)
        {
            BYTE tmp[9] = {(BYTE)dataOfBmp_gray[i - 1][j - 1], (BYTE)dataOfBmp_gray[i - 1][j],
                           (BYTE)dataOfBmp_gray[i - 1][j + 1], (BYTE)dataOfBmp_gray[i][j - 1],
                           (BYTE)dataOfBmp_gray[i][j], (BYTE)dataOfBmp_gray[i][j + 1],
                           (BYTE)dataOfBmp_gray[i + 1][j - 1], (BYTE)dataOfBmp_gray[i + 1][j],
                           (BYTE)dataOfBmp_gray[i + 1][j + 1]};
            std::sort(tmp, tmp + 9);
            dataOfBmp_dst[i][j].rgbBlue = tmp[4];
            dataOfBmp_dst[i][j].rgbGreen = tmp[4];
            dataOfBmp_dst[i][j].rgbRed = tmp[4];
        }
    }

    // ����
    saveBmp(dataOfBmp_dst, width, height);
}

// KNNƽ���˲�
void KNN(RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD m, DWORD k, DWORD width, DWORD height)
{
    for (DWORD i = m; i < height - m; i++)
    {
        for (DWORD j = m; j < width - m; j++)
        {
            int mat[(2 * m + 1) * (2 * m + 1)][2] = {0};
            int count = 0;
            for (int x = i - m; x <= i + m; x++)
                for (int y = j - m; y <= j + m; y++)
                {
                    mat[count][0] = dataOfBmp_gray[x][y];
                    mat[count][1] = abs(dataOfBmp_gray[i][j] - dataOfBmp_gray[x][y]);
                    count++;
                }
            for (int x = 0; x < (2 * m + 1) * (2 * m + 1) - 1; x++)
            {
                for (int y = 0; y < (2 * m + 1) * (2 * m + 1) - 1 - x; y++)
                {
                    if (mat[y][1] > mat[y + 1][1])
                    {
                        std::swap(mat[y][0], mat[y + 1][0]);
                        std::swap(mat[y][1], mat[y + 1][1]);
                    }
                }
            }
            int res = 0;
            for (int i = 0; i < k; i++)
                res += mat[i][0];
            res = res / k;
            dataOfBmp_dst[i][j].rgbRed = BYTE(res);
            dataOfBmp_dst[i][j].rgbGreen = BYTE(res);
            dataOfBmp_dst[i][j].rgbBlue = BYTE(res);
        }
    }

    // ����
    saveBmp(dataOfBmp_dst, width, height);
}

// ˮƽ��
void horSharpen(RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD width, DWORD height)
{
    // Ȩ
    double H[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

    for (DWORD i = 0; i < height; i++)
    {
        for (DWORD j = 0; j < width; j++)
        {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
            {
                dataOfBmp_dst[i][j].rgbBlue = 0;
                dataOfBmp_dst[i][j].rgbGreen = 0;
                dataOfBmp_dst[i][j].rgbRed = 0;
            }
            else
            {
                BYTE tmp = ((BYTE)dataOfBmp_gray[i - 1][j - 1] * H[0][0] + (BYTE)dataOfBmp_gray[i - 1][j] * H[0][1] +
                            (BYTE)dataOfBmp_gray[i - 1][j + 1] * H[0][2] + (BYTE)dataOfBmp_gray[i][j - 1] * H[1][0] +
                            (BYTE)dataOfBmp_gray[i][j] * H[1][1] + (BYTE)dataOfBmp_gray[i][j + 1] * H[1][2] +
                            (BYTE)dataOfBmp_gray[i + 1][j - 1] * H[2][0] + (BYTE)dataOfBmp_gray[i + 1][j] * H[2][1] +
                            (BYTE)dataOfBmp_gray[i + 1][j + 1] * H[2][2]);
                tmp = fabs(tmp);
                dataOfBmp_dst[i][j].rgbBlue = tmp;
                dataOfBmp_dst[i][j].rgbGreen = tmp;
                dataOfBmp_dst[i][j].rgbRed = tmp;
            }
        }
    }

    // ����
    saveBmp(dataOfBmp_dst, width, height);
}

// ��ֱ��
void verSharpen(RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD width, DWORD height)
{
    // Ȩ
    double H[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};

    for (DWORD i = 0; i < height; i++)
    {
        for (DWORD j = 0; j < width; j++)
        {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
            {
                dataOfBmp_dst[i][j].rgbBlue = 0;
                dataOfBmp_dst[i][j].rgbGreen = 0;
                dataOfBmp_dst[i][j].rgbRed = 0;
            }
            else
            {
                BYTE tmp = ((BYTE)dataOfBmp_gray[i - 1][j - 1] * H[0][0] + (BYTE)dataOfBmp_gray[i - 1][j] * H[0][1] +
                            (BYTE)dataOfBmp_gray[i - 1][j + 1] * H[0][2] + (BYTE)dataOfBmp_gray[i][j - 1] * H[1][0] +
                            (BYTE)dataOfBmp_gray[i][j] * H[1][1] + (BYTE)dataOfBmp_gray[i][j + 1] * H[1][2] +
                            (BYTE)dataOfBmp_gray[i + 1][j - 1] * H[2][0] + (BYTE)dataOfBmp_gray[i + 1][j] * H[2][1] +
                            (BYTE)dataOfBmp_gray[i + 1][j + 1] * H[2][2]);
                tmp = fabs(tmp);
                dataOfBmp_dst[i][j].rgbBlue = tmp;
                dataOfBmp_dst[i][j].rgbGreen = tmp;
                dataOfBmp_dst[i][j].rgbRed = tmp;
            }
        }
    }

    // ����
    saveBmp(dataOfBmp_dst, width, height);
}

// Roberts�㷨 ����΢���㷨
void roberts(RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD width, DWORD height)
{
    for (DWORD i = 0; i < height - 1; i++)
    {
        for (DWORD j = 0; j < width - 1; j++)
        {
            BYTE tmp = fabs((BYTE)dataOfBmp_gray[i + 1][j + 1] - (BYTE)dataOfBmp_gray[i][j]) +
                       fabs((BYTE)dataOfBmp_gray[i + 1][j] - (BYTE)dataOfBmp_gray[i][j + 1]);

            dataOfBmp_dst[i][j].rgbBlue = tmp;
            dataOfBmp_dst[i][j].rgbGreen = tmp;
            dataOfBmp_dst[i][j].rgbRed = tmp;
        }
    }

    // ����
    saveBmp(dataOfBmp_dst, width, height);
}

// Sobel��
void sobel(RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD width, DWORD height)
{
    int dx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int dy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (DWORD i = 0; i < height; i++)
    {
        for (DWORD j = 0; j < width; j++)
        {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
            {
                dataOfBmp_dst[i][j].rgbBlue = 0;
                dataOfBmp_dst[i][j].rgbGreen = 0;
                dataOfBmp_dst[i][j].rgbRed = 0;
            }
            else
            {
                BYTE dxV = fabs((BYTE)dataOfBmp_gray[i - 1][j - 1] * dx[0][0] + (BYTE)dataOfBmp_gray[i - 1][j] * dx[0][1] +
                                (BYTE)dataOfBmp_gray[i - 1][j + 1] * dx[0][2] + (BYTE)dataOfBmp_gray[i][j - 1] * dx[1][0] +
                                (BYTE)dataOfBmp_gray[i][j] * dx[1][1] + (BYTE)dataOfBmp_gray[i][j + 1] * dx[1][2] +
                                (BYTE)dataOfBmp_gray[i + 1][j - 1] * dx[2][0] + (BYTE)dataOfBmp_gray[i + 1][j] * dx[2][1] +
                                (BYTE)dataOfBmp_gray[i + 1][j + 1] * dx[2][2]);
                BYTE dyV = fabs((BYTE)dataOfBmp_gray[i - 1][j - 1] * dy[0][0] + (BYTE)dataOfBmp_gray[i - 1][j] * dy[0][1] +
                                (BYTE)dataOfBmp_gray[i - 1][j + 1] * dy[0][2] + (BYTE)dataOfBmp_gray[i][j - 1] * dy[1][0] +
                                (BYTE)dataOfBmp_gray[i][j] * dy[1][1] + (BYTE)dataOfBmp_gray[i][j + 1] * dy[1][2] +
                                (BYTE)dataOfBmp_gray[i + 1][j - 1] * dy[2][0] + (BYTE)dataOfBmp_gray[i + 1][j] * dy[2][1] +
                                (BYTE)dataOfBmp_gray[i + 1][j + 1] * dy[2][2]);
                BYTE tmp = sqrt(dxV * dxV + dyV * dyV);
                // BYTE tmp = dxV + dyV;

                dataOfBmp_dst[i][j].rgbBlue = tmp;
                dataOfBmp_dst[i][j].rgbGreen = tmp;
                dataOfBmp_dst[i][j].rgbRed = tmp;
            }
        }
    }

    // ����
    saveBmp(dataOfBmp_dst, width, height);
}

// Priwitt��
void priwitt(RGBQUAD **dataOfBmp_dst, BYTE **dataOfBmp_gray, DWORD width, DWORD height)
{
    int dx[3][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};
    int dy[3][3] = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}};
    for (DWORD i = 0; i < height; i++)
    {
        for (DWORD j = 0; j < width; j++)
        {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
            {
                dataOfBmp_dst[i][j].rgbBlue = 0;
                dataOfBmp_dst[i][j].rgbGreen = 0;
                dataOfBmp_dst[i][j].rgbRed = 0;
            }
            else
            {
                BYTE dxV = fabs((BYTE)dataOfBmp_gray[i - 1][j - 1] * dx[0][0] + (BYTE)dataOfBmp_gray[i - 1][j] * dx[0][1] +
                                (BYTE)dataOfBmp_gray[i - 1][j + 1] * dx[0][2] + (BYTE)dataOfBmp_gray[i][j - 1] * dx[1][0] +
                                (BYTE)dataOfBmp_gray[i][j] * dx[1][1] + (BYTE)dataOfBmp_gray[i][j + 1] * dx[1][2] +
                                (BYTE)dataOfBmp_gray[i + 1][j - 1] * dx[2][0] + (BYTE)dataOfBmp_gray[i + 1][j] * dx[2][1] +
                                (BYTE)dataOfBmp_gray[i + 1][j + 1] * dx[2][2]);
                BYTE dyV = fabs((BYTE)dataOfBmp_gray[i - 1][j - 1] * dy[0][0] + (BYTE)dataOfBmp_gray[i - 1][j] * dy[0][1] +
                                (BYTE)dataOfBmp_gray[i - 1][j + 1] * dy[0][2] + (BYTE)dataOfBmp_gray[i][j - 1] * dy[1][0] +
                                (BYTE)dataOfBmp_gray[i][j] * dy[1][1] + (BYTE)dataOfBmp_gray[i][j + 1] * dy[1][2] +
                                (BYTE)dataOfBmp_gray[i + 1][j - 1] * dy[2][0] + (BYTE)dataOfBmp_gray[i + 1][j] * dy[2][1] +
                                (BYTE)dataOfBmp_gray[i + 1][j + 1] * dy[2][2]);
                BYTE tmp = sqrt(dxV * dxV + dyV * dyV);
                // BYTE tmp = dxV + dyV;

                dataOfBmp_dst[i][j].rgbBlue = tmp;
                dataOfBmp_dst[i][j].rgbGreen = tmp;
                dataOfBmp_dst[i][j].rgbRed = tmp;
            }
        }
    }

    // ����
    saveBmp(dataOfBmp_dst, width, height);
}

int main()
{
    BITMAPFILEHEADER bitHead;
    BITMAPINFOHEADER bitInfoHead;
    int i, j;

    FILE *pfile;
    char strFile[50];
    printf("please input the .bmp source file name:\n");
    scanf("%s", strFile);
    pfile = fopen(strFile, "rb"); //���ļ�
    if (pfile != NULL)
    {
        printf("file %s open success.\n", strFile);
        //��ȡλͼ�ļ�ͷ��Ϣ
        fread(&bitHead, 1, sizeof(BITMAPFILEHEADER), pfile);
        if (bitHead.bfType != 0x4d42)
        {
            printf("file is not .bmp file!");
            return 0;
        }

        showBmpHead(&bitHead);
        printf("\n\n");
        //��ȡλͼ��Ϣͷ��Ϣ
        fread(&bitInfoHead, 1, sizeof(BITMAPINFOHEADER), pfile);
        showBmpInforHead(&bitInfoHead);
        printf("\n");
    }
    else
    {
        printf("file open fail!\n");
        return 0;
    }

    RGBQUAD *pRgb = NULL;

    if (bitInfoHead.biBitCount < 24) //�е�ɫ��
    {
        //��ȡ��ɫ�̽���Ϣ
        long nPlantNum = bitInfoHead.biClrUsed;
        if (!nPlantNum)
            nPlantNum = long(pow(2, double(bitInfoHead.biBitCount))); //   Mix color Plant Number;
        pRgb = new RGBQUAD[nPlantNum * sizeof(RGBQUAD)];
        memset(pRgb, 0, nPlantNum * sizeof(RGBQUAD));
        int num = fread(pRgb, 4, nPlantNum, pfile);

        printf("Color Plate Number: %d\n", nPlantNum);
        printf("��ɫ����Ϣ:\n");
        showRgbQuan(pRgb, nPlantNum);
    }

    int width = bitInfoHead.biWidth;
    int height = bitInfoHead.biHeight;
    //�����ڴ�ռ��Դͼ�����ڴ�
    int l_width = WIDTHBYTES(width * bitInfoHead.biBitCount); //����λͼ��ʵ�ʿ�Ȳ�ȷ����Ϊ32�ı���
    long nData = height * l_width;
    BYTE *pColorData = new BYTE[nData];
    memset(pColorData, 0, nData);

    //��λͼ������Ϣ����������
    fread(pColorData, 1, nData, pfile);

    //��λͼ����ת��ΪRGB����
    RGBQUAD **dataOfBmp_src = NULL; //���ڱ�������ض�Ӧ��RGB����

    dataOfBmp_src = new RGBQUAD *[height];
    for (i = 0; i < height; i++)
        dataOfBmp_src[i] = new RGBQUAD[width];

    if (bitInfoHead.biBitCount < 24) //�е�ɫ�壬��λͼΪ�����ɫ
    {
        int k;

        if (bitInfoHead.biBitCount <= 8 && !bitInfoHead.biCompression)
        {

            int pnum = 8 / bitInfoHead.biBitCount;
            int mbnum = 8 - bitInfoHead.biBitCount;

            for (int i = 0; i < height; i++)
            {
                int k0 = (height - i - 1) * l_width; //k:ȡ�ø�������ɫ������ʵ�����������е����
                for (int j = 0; j < width; j++)
                {
                    BYTE mixIndex = 0;
                    k = k0 + (j / pnum);
                    mixIndex = pColorData[k];
                    //mixIndex:��ȡ��ǰ���ص���ɫ������ɫ���е�����ֵ
                    if (bitInfoHead.biBitCount < 8)
                    {
                        mixIndex = mixIndex << ((j % pnum) * bitInfoHead.biBitCount);
                        mixIndex = mixIndex >> mbnum;
                    }

                    //��������ɫ���ݣ�RGBA�����浽�����ж�Ӧ��λ��
                    dataOfBmp_src[i][j].rgbRed = pRgb[mixIndex].rgbRed;
                    dataOfBmp_src[i][j].rgbGreen = pRgb[mixIndex].rgbGreen;
                    dataOfBmp_src[i][j].rgbBlue = pRgb[mixIndex].rgbBlue;
                    dataOfBmp_src[i][j].rgbReserved = pRgb[mixIndex].rgbReserved;
                }
            }
        }

        if (bitInfoHead.biBitCount == 16)
        {
            if (!bitInfoHead.biCompression)
            {
                for (i = 0; i < height; i++)
                {
                    int k0 = (height - i - 1) * l_width;
                    for (j = 0; j < width; j++)
                    {
                        WORD mixIndex = 0;
                        k = k0 + j * 2;
                        WORD shortTemp;
                        shortTemp = pColorData[k + 1];
                        shortTemp = shortTemp << 8;

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
    else //λͼΪ24/32λ���ɫ
    {
        int k;
        int index = 0;

        if (bitInfoHead.biBitCount == 16)
        {
            for (i = 0; i < height; i++)
            {
                int k0 = (height - i - 1) * l_width;
                for (j = 0; j < width; j++)
                {
                    k = k0 + j * 2;
                    if (!bitInfoHead.biCompression) //555��ʽ
                    {
                        dataOfBmp_src[i][j].rgbBlue = pColorData[k] & 0x1F;
                        dataOfBmp_src[i][j].rgbGreen = (((pColorData[k + 1] << 6) & 0xFF) >> 3) + (pColorData[k] >> 5);
                        dataOfBmp_src[i][j].rgbRed = (pColorData[k + 1] << 1) >> 3;
                        dataOfBmp_src[i][j].rgbReserved = 0;
                    }
                }
            }
        }
        if (bitInfoHead.biBitCount == 24 && !bitInfoHead.biCompression)
        {
            for (i = 0; i < height; i++)
            {
                int k0 = (height - i - 1) * l_width;
                for (j = 0; j < width; j++)
                {
                    k = k0 + (j * 3);
                    dataOfBmp_src[i][j].rgbRed = pColorData[k + 2];
                    dataOfBmp_src[i][j].rgbGreen = pColorData[k + 1];
                    dataOfBmp_src[i][j].rgbBlue = pColorData[k];
                    dataOfBmp_src[i][j].rgbReserved = 0;
                }
            }
        }
        if (bitInfoHead.biBitCount == 32 && !bitInfoHead.biCompression)
        {
            for (i = 0; i < height; i++)
            {
                int k0 = (height - i - 1) * l_width;
                for (j = 0; j < width; j++)
                {
                    k = k0 + (j * 4);
                    dataOfBmp_src[i][j].rgbRed = pColorData[k + 2];
                    dataOfBmp_src[i][j].rgbGreen = pColorData[k + 1];
                    dataOfBmp_src[i][j].rgbBlue = pColorData[k];
                    dataOfBmp_src[i][j].rgbReserved = pColorData[k + 3];
                }
            }
        }
    }

    //printf("����������Ϣ:\n");
    RGBQUAD **dataOfBmp_dst = NULL;
    dataOfBmp_dst = new RGBQUAD *[height + width * 2]; //��ɫ���ͼ����ÿ�����ص�RGBAlpha
    for (i = 0; i < height + width * 2; i++)
        dataOfBmp_dst[i] = new RGBQUAD[width];

    BYTE **dataOfBmp_gray = NULL;
    dataOfBmp_gray = new BYTE *[height];
    for (i = 0; i < height; i++)
        dataOfBmp_gray[i] = new BYTE[width];

    // reverseColor(dataOfBmp_src, dataOfBmp_dst, width, height);             //��ɫ
    // RGB2Gray(dataOfBmp_src, dataOfBmp_dst, dataOfBmp_gray, width, height); //�Ҷ�
    // double contrast8nn = contrast(dataOfBmp_gray, width, height, 1);
    // saveBmp(dataOfBmp_dst, width, height);
    // printf("the 8nn contrast of the gray image is %f\n", contrast8nn);

    // ����ͼ��任
    // bigSmall(dataOfBmp_src, dataOfBmp_dst, 2, 2, width, height);     //�Ŵ�
    // bigSmall(dataOfBmp_src, dataOfBmp_dst, 0.5, 0.5, width, height); //��С
    // cuoQie(dataOfBmp_src, dataOfBmp_dst, 2, 0, width, height);       //����
    // mirror(dataOfBmp_src, dataOfBmp_dst, 1, width, height);          //����
    // rotate(dataOfBmp_src, dataOfBmp_dst, 60, width, height);         //��ת
    // move(dataOfBmp_src, dataOfBmp_dst, 100, 100, width, height);     //ƽ��

    // ���²����ȱ�Ҷ��ٽ���
    RGB2Gray(dataOfBmp_src, dataOfBmp_dst, dataOfBmp_gray, width, height); //�Ҷ�
    saveBmp(dataOfBmp_dst, width, height);

    // ͼ����ǿ
    // linearContrast(dataOfBmp_dst, dataOfBmp_gray, width, height);    //���ԶԱ�չ��
    // noLinear(dataOfBmp_dst, dataOfBmp_gray, width, height);          //�����Զ�̬��Χ����
    // histogramEqualize(dataOfBmp_dst, dataOfBmp_gray, width, height); //ֱ��ͼ���⻯

    // ͼ��ƽ��
    // meanFilter(dataOfBmp_dst, dataOfBmp_gray, width, height);         //��ֵ�˲���
    // weightedMeanFilter(dataOfBmp_dst, dataOfBmp_gray, width, height); //��Ȩ���⻯�˲���
    // medianFilter(dataOfBmp_dst, dataOfBmp_gray, width, height);       //��ֵ�˲���
    // KNN(dataOfBmp_dst, dataOfBmp_gray, 3, 4, width, height);          //KNNƽ���˲�

    // ͼ����
    // horSharpen(dataOfBmp_dst, dataOfBmp_gray, width, height); //ˮƽ��
    // verSharpen(dataOfBmp_dst, dataOfBmp_gray, width, height); //��ֱ��
    // roberts(dataOfBmp_dst, dataOfBmp_gray, width, height);    //����΢���㷨
    // sobel(dataOfBmp_dst, dataOfBmp_gray, width, height);      //sobel��
    // priwitt(dataOfBmp_dst, dataOfBmp_gray, width, height);    //priwitt��

    fclose(pfile);
    if (bitInfoHead.biBitCount < 24 && pRgb)
    {
        delete[] pRgb;
    }
    for (i = 0; i < height; i++)
        if (dataOfBmp_src[i])
            delete dataOfBmp_src[i];
    if (dataOfBmp_src)
        delete dataOfBmp_src;

    for (i = 0; i < height; i++)
        if (dataOfBmp_dst[i])
            delete dataOfBmp_dst[i];
    if (dataOfBmp_dst)
        delete dataOfBmp_dst;

    for (i = 0; i < height; i++)
        if (dataOfBmp_gray[i])
            delete dataOfBmp_gray[i];
    if (dataOfBmp_gray)
        delete dataOfBmp_gray;

    if (pColorData)
        delete[] pColorData;
}

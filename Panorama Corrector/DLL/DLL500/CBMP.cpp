/*#include "Windows.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h" */
#include "stdafx.h"
#include "CBMP.h"

unsigned char *pBmpBuf;//����ͼ�����ݵ�ָ��  
int bmpWidth;//ͼ��Ŀ�  
int bmpHeight;//ͼ��ĸ�  
RGBQUAD *pColorTable;//��ɫ��ָ��  
int biBitCount;//ͼ�����ͣ�ÿ����λ��   

bool readBmp(char *bmpName)
{
	//�����ƶ���ʽ��ָ����ͼ���ļ�  
	FILE *fp = fopen(bmpName, "rb");
	if (fp == 0) return 0;


	//����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER  
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);
	//����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��  
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	//��ȡͼ����ߡ�ÿ������ռλ������Ϣ  
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;
	//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����  
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	//�Ҷ�ͼ������ɫ������ɫ�����Ϊ256  
	if (biBitCount == 8) {
		//������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�  
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}
	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�  
	pBmpBuf = new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);
	//�ر��ļ�  
	fclose(fp);
	return 1;
}

bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height,
	int biBitCount, RGBQUAD *pColorTable)
{
	//���λͼ����ָ��Ϊ0����û�����ݴ��룬��������  
	if (!imgBuf)
		return 0;
	//��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024�ֽڣ���ɫͼ����ɫ���СΪ0  
	int colorTablesize = 0;
	if (biBitCount == 8)
		colorTablesize = 1024;
	//���洢ͼ������ÿ���ֽ���Ϊ4�ı���  
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
	//�Զ�����д�ķ�ʽ���ļ�  
	FILE *fp = fopen(bmpName, "wb");
	if (fp == 0) return 0;
	//����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ  
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp����  
							 //bfSize��ͼ���ļ�4����ɲ���֮��  
	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		+ colorTablesize + lineByte*height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	//bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��  
	fileHead.bfOffBits = 54 + colorTablesize;
	//д�ļ�ͷ���ļ�  
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	//����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ  
	BITMAPINFOHEADER head;
	head.biBitCount = biBitCount;
	head.biClrImportant = 0;
	head.biClrUsed = 0;
	head.biCompression = 0;
	head.biHeight = height;
	head.biPlanes = 1;
	head.biSize = 40;
	head.biSizeImage = lineByte*height;
	head.biWidth = width;
	head.biXPelsPerMeter = 0;
	head.biYPelsPerMeter = 0;
	//дλͼ��Ϣͷ���ڴ�  
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	//����Ҷ�ͼ������ɫ��д���ļ�    
	if (biBitCount == 8)
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	//дλͼ���ݽ��ļ�  
	fwrite(imgBuf, height*lineByte, 1, fp);
	//�ر��ļ�  
	fclose(fp);
	return 1;
}

//void main()
//{
//	char inFileName[90], outFileName[90];
//	printf("������ԭʼλͼ�ļ����ļ���:");
//	scanf("%s", inFileName);
//	printf("��������ܳ����������λͼ�ļ����ļ���:");
//	scanf("%s", outFileName);
//	//����ָ��BMP�ļ����ڴ�  
//	readBmp(inFileName);
//	//���ͼ�����Ϣ  
//	printf("width=%d,height=%d, biBitCount=%d\n", bmpWidth, bmpHeight, biBitCount);
//	//��ͼ�����ݴ���  
//	saveBmp(outFileName, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
//	//�����������pBmpBuf��pColorTable��ȫ�ֱ��������ļ�����ʱ����Ŀռ�  
//	delete[]pBmpBuf;
//	if (biBitCount == 8)
//		delete[]pColorTable;
//}
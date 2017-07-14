#include <stdio.h>
#include <stdlib.h>

typedef struct {
	long imageSize;
	long blank;
	long startPosition;
} BmpHead;

typedef struct {
	long  Length;
	long  width;
	long  height;
	unsigned short  colorPlane;
	unsigned short  bitColor;
	long  zipFormat;
	long  realSize;
	long  xPels;
	long  yPels;
	long  colorUse;
	long  colorImportant;
} InfoHead;

void rgb24_2_bmp(int width, int height){
	int i=0,j=0;

	BmpHead m_BMPHeader={0};
    InfoHead m_BMPInfoHeader={0};
	char bfType[2]={'B','M'};
	int header_size = sizeof(bfType) + sizeof(BmpHead) + sizeof(InfoHead);
	
	unsigned char *rgb24_buffer = NULL;
	FILE *fp_rgb24=NULL,*fp_bmp=NULL;

    fp_rgb24 = fopen("../source/RGB_24bit_500x500.rgb","rb");
	fp_bmp = fopen("../source/RGB_24bit_500x500.bmp","wb");
    
	rgb24_buffer = (unsigned char *)malloc(width * height * 3);

	fread(rgb24_buffer, 1, width * height * 3, fp_rgb24);
	
	//拼装头部的信息数据
	m_BMPHeader.imageSize=3*width*height+header_size;  
    m_BMPHeader.startPosition=header_size; 
	
	m_BMPInfoHeader.Length=sizeof(InfoHead);
	m_BMPInfoHeader.width=width;
	//说明图象的高度，以象素为单位。
	//注：这个值除了用于描述图像的高度之外，它还有另一个用处，就是指明该图像是倒向的位图，还是正向的位图。
	//如果该值是一个正数，说明图像是倒向的，
	//即：数据的第一行其实是图像的最后一行，如果该值是一个负数，则说明图像是正向的。
	//大多数的BMP文件都是倒向的位图，也就是时，高度值是一个正数。
	//我们这里是正图，所以需要要用取反
	m_BMPInfoHeader.height=-height;
    m_BMPInfoHeader.colorPlane=1;
    m_BMPInfoHeader.bitColor=24;
    m_BMPInfoHeader.realSize=3*width*height;
	
	//写出保存
	fwrite(bfType, 1, sizeof(bfType), fp_bmp);
	fwrite(&m_BMPHeader, 1, sizeof(m_BMPHeader), fp_bmp);
	fwrite(&m_BMPInfoHeader, 1, sizeof(m_BMPInfoHeader), fp_bmp);


	for(j =0;j<height;j++){
        for(i=0;i<width;i++){
            char temp=rgb24_buffer[(j*width+i)*3+2];  
            rgb24_buffer[(j*width+i)*3+2]=rgb24_buffer[(j*width+i)*3+0];  
            rgb24_buffer[(j*width+i)*3+0]=temp;  
        }
    }
	

	//写出保存
	fwrite(rgb24_buffer, 3 * width * height, 1,fp_bmp);

    free(rgb24_buffer);
	fclose(fp_bmp);
    fclose(fp_rgb24);
}


int main(){
    rgb24_2_bmp(500, 500);
    return 0;
}

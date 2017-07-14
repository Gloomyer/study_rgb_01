#include <stdio.h>
#include <stdlib.h>

unsigned char clip_value(unsigned char x,unsigned char min_val,unsigned char  max_val){
    if(x > max_val){
        return max_val;
    }else if(x<min_val){
        return min_val;
    }else{
        return x;
    }
}

void rgb_2_yuv420(int width, int height, int num){

	FILE *fp_rgb = fopen("../source/RGB_24bit_500x500.rgb","rb");
	FILE *fp_yuv = fopen("../source/RGB_24bit_500x500.yuv","wb");

	unsigned char *pic_rgb24 = (unsigned char *)malloc(width * height * 3);  
    unsigned char *pic_yuv420 = (unsigned char *)malloc(width * height * 3 / 2);  

	
	for(int i=0;i<num;i++){
		fread(pic_rgb24, 1, width * height * 3, fp_rgb);
		
		unsigned char*ptrY, *ptrU, *ptrV, *ptrRGB;
		for(int j = 0; j < width * height * 3 / 2; j++){
			pic_yuv420[j] = 0;
		}

		ptrY = pic_yuv420;
		ptrU = pic_yuv420 + width * height;
		ptrV = ptrU + (width * height * 1 / 4);

		unsigned char y, u, v, r, g, b;


		for (int k = 0; k < height ; k++){  
			ptrRGB = pic_rgb24 + width * k * 3 ;  
			for (int l = 0; l < width; l++){  
				r = *(ptrRGB++);  
				g = *(ptrRGB++);  
				b = *(ptrRGB++);  
				y = (unsigned char)( ( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16  ;            
				u = (unsigned char)( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128 ;            
				v = (unsigned char)( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128 ;  
				*(ptrY++) = clip_value(y, 0, 255);  
				if (k % 2 == 0 && l % 2 == 0){  
					*(ptrU++) = clip_value(u, 0, 255);  
				}  
				else{  
					if (l % 2 == 0){  
						*(ptrV++) = clip_value(v, 0, 255);  
					}  
				}  
			}  
		}

		fwrite(pic_yuv420, 1, width * height * 3 / 2, fp_yuv);
	}

    free(pic_rgb24);
	free(pic_yuv420);
	fclose(fp_yuv);
    fclose(fp_rgb);
}


int main(){
    rgb_2_yuv420(500, 500, 1);//¿í¡¢¸ß¡¢Ö¡Êý
    return 0;
}

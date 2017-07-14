#include <stdio.h>
#include <stdlib.h>

void create_rgb(int width, int height){
	unsigned char *data = (unsigned char *)malloc(width*height*3);
	int barwidth= width / 8;
	FILE *fp = fopen("../source/rgb_test.rgb", "wb");

	for(int j=0;j<height;j++){
        for(int i=0;i<width;i++){
            int barnum=i/barwidth;
            switch(barnum){
				case 0:{
					data[(j*width+i)*3+0]=255;
					data[(j*width+i)*3+1]=255;
					data[(j*width+i)*3+2]=255;
					break;
				}
				case 1:{
					data[(j*width+i)*3+0]=255;
					data[(j*width+i)*3+1]=255;
					data[(j*width+i)*3+2]=0;
					break;
				}  
				case 2:{  
					data[(j*width+i)*3+0]=0;
					data[(j*width+i)*3+1]=255;
					data[(j*width+i)*3+2]=255;
					break;
				}  
				case 3:{
					data[(j*width+i)*3+0]=0;
					data[(j*width+i)*3+1]=255;
					data[(j*width+i)*3+2]=0;
					break;
				}
				case 4:{
					data[(j*width+i)*3+0]=255;
					data[(j*width+i)*3+1]=0;
					data[(j*width+i)*3+2]=255;
					break;
				}  
				case 5:{
					data[(j*width+i)*3+0]=255;
					data[(j*width+i)*3+1]=0;
					data[(j*width+i)*3+2]=0;
					break;
				}
				case 6:{  
					data[(j*width+i)*3+0]=0;  
					data[(j*width+i)*3+1]=0;  
					data[(j*width+i)*3+2]=255;
					break;  
				}  
				case 7:{  
					data[(j*width+i)*3+0]=0;  
					data[(j*width+i)*3+1]=0;  
					data[(j*width+i)*3+2]=0;  
					break;  
				}
            }
			
        }
    }

    fwrite(data,width*height*3,1,fp);

	free(data);
	fclose(fp);
}


int main(){
    create_rgb(500, 500);
    return 0;
}

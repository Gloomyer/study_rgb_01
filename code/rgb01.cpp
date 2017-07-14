#include <stdio.h>
#include <stdlib.h>

void rgb24_split(int w, int h, int num){
    FILE *fp  = fopen("../source/RGB_24bit_500x500.rgb","rb+");
    FILE *fp1 = fopen("../source/RGB_24bit_500x500_r.y","wb+");
    FILE *fp2 = fopen("../source/RGB_24bit_500x500_g.y","wb+");
    FILE *fp3 = fopen("../source/RGB_24bit_500x500_b.y","wb+");

    unsigned char *pic=(unsigned char *)malloc(w*h*3);

    for(int i = 0; i < num; i ++){
        fread(pic, 1, w * h * 3, fp);

        for(int j = 0; j < w * h * 3; j+=3){
            fwrite(pic + j, 1, 1, fp1);//R
            fwrite(pic + j + 1, 1, 1, fp2);//G
            fwrite(pic + j + 2, 1, 1, fp3);//B
        }
    }

    free(pic);
    fclose(fp3);
    fclose(fp2);
    fclose(fp1);
    fclose(fp);
}

int main(){

    rgb24_split(500, 500, 1);

    return 0;
}
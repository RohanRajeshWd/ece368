#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//Function declaraions------------------------------------------------
void bin2txt(char *infile, char* outfile);
//FILE I/0-----------------------------------------------------------
void bin2txt(char *infile, char* outfile){
  FILE*fp1 = fopen(infile,"rb");
  unsigned char str[256];
  unsigned int num;
  int len;
  FILE *fp2 = fopen(outfile, "w");
  while (len = fgetc(fp1) != EOF){
    fread(str, len, 1, fp1);
    num = (unsigned int)fgetc(fp1) << 24;
    num |= fgetc(fp1) << 16;
    num |= fgetc(fp1) << 8;
    num |= fgetc(fp1);
    fprintf(fp2, "%s %d\n", (char*)str, num);
  }
  fclose(fp1);
  fclose(fp2);
}


//--------------------------------------------------------------------

int main(char* argv[], int argc){
  bin2txt(argv[1], "t1");
}

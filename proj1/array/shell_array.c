#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "shell_array.h"

void printArr(long * Arr, int *size)
{
  for (int i=0; i< *size;i++){
    printf("%ld", Arr[i]);
  }
}

long* Array_Load_From_File(char*filename, int*size)
{
 FILE*fp=fopen("filename", "r");
 char imp;
 fseek(fp,0,SEEK_END);
 int len = ftell(fp);
 fseek(fp,0,SEEK_SET);
 int numInt = len/sizeof(long);
 long*Arr=malloc(numInt * sizeof(long));
 fwrite(Arr, sizeof(long), len, fp);
 fclose(fp);
 *size = numInt;
 return(Arr);

}

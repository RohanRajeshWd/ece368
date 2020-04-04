#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "shell_array.h"

static long startSeq(int size){
  long start = 1;
  while(start<size){
    if (start*3+1 >= size)
      return(start);
    start = start*3+1;
  }
  return (start);
}

long* Array_Load_From_File(char*filename, int*size)
{
  FILE*fp;
  fp=fopen(filename, "rb");
  if (fp ==NULL){
    *size = 0;
    return (NULL);//null adress
  } 
  fseek(fp,0,SEEK_END);
  int len = ftell(fp);
  *size = len/sizeof(long);
  fseek(fp,0, SEEK_SET);
  long * Arr = (long*)malloc(len);
  //printf("length:%ld numIn estimated:%ld ", len, (len/4));  
  fread(Arr, sizeof(long), *size, fp);
  fclose(fp);
  return (Arr);
}



void Array_Shellsort(long*array, int size, long *n_comp){
  long start = startSeq(size);
  long temp; //temp value  
  long j;
  long Ncomp = 0;
  for(long g = start; g > 0; g=(g-1)/3){
    for(long i = g; i<size; i++){
      temp = array[i];
      for(j = i; (j >=g) && (array[j-g] >temp);  j -= g){
        array[j] = array[j-g];
        Ncomp++;
      }
      array[j] = temp;
    }
  }
  *n_comp = Ncomp;
}









int Array_Save_To_File(char*filename, long *array, int size){
  FILE *fp = fopen (filename, "wb");
  if  ((array == NULL)||(size ==0)){
    fclose(fp);
  }
  int retvalue = fwrite(array, sizeof(long), size, fp);
  fclose(fp);
  return(retvalue);
}









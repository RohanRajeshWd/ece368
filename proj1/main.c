
#include "shell_array.h"
#include<stdio.h>
#include<a.out.h>
#include<stdlib.h>
#include <string.h>

int main(int argc, char ** argv){

  //argv[1] is input file name
  //argv[2] is an output

  //if (strcmp(argv[1], "-a")==0) {
  int size;
  long  n_comp = 0;
  long * Arr = Array_Load_From_File(argv[1], &size);
  FILE * fp = fopen(argv[2], "w");
  int numSaved;
  fprintf(fp, "len: %d size: %d\n",size *4, size);
  // fclose(fp);                                                                                                   
  for(int i =0; i < (size); i++){
    fprintf(fp , " num %d : %ld \n ",i+1  , Arr[i]);
  }
  Array_Shellsort(Arr, size, &n_comp);
  fprintf(fp, "sorted with n_comp : %ld-----------------------------\n", n_comp);
  for(int i=0;i<size; i++)
    fprintf(fp, " num %d : %ld \n", i+1, Arr[i]);
  fclose(fp);
}
































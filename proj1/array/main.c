
#include "shell_array.h"
#include<stdio.h>
void printArr(long *Arr, int * size);
long* Array_Load_From_File(char*filename, int*size);



int main(int argc, char ** argv){

  //argv[1] is input file name
  //argv[2] is an output
  int *size;
  long * Arr = Array_Load_From_File(argv[1], size);
  printArr(Arr, size);
  
}



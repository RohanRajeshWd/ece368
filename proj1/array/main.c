
#include "shell_array.h"
#include<stdio.h>
#include<a.out.h>
#include<stdlib.h>
#include <string.h>
//void printArr(long *Arr, int * size);
/*long* Array_Load_From_File(char*filename, int*size);
void Array_Shellsort(long array, int size, long *n_comp);
int Array_Save_To_File(char*filename, long *array, int size);
*/

int main(int argc, char ** argv){

  //argv[1] is input file name
  //argv[2] is an output
  
  if (strcmp(argv[1], "-a")==0) {
  int size;
  long * n_comp;
  long * Arr = Array_Load_From_File(argv[2], &size);
  //printArr(Arr, size);
  Array_Shellsort(Arr,size,  n_comp);
  //printArr(Arr, size);
  int numSaved;
  printf("%ld\n",n_comp);
  numSaved = Array_Save_To_File( argv[3] , Arr, size);
 if (numSaved ==0) {
   return (0);
 }
  //wouldnt compile without a warning unless i added this line
 
 free(Arr);
  return(0);  
  }
} 
  
  
 



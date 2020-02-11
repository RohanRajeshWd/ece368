#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "shell_array.h"

static void sorting( long *array, int k, long * n_comp, int size){
  //k = number of subarray elements (13 sort for example)
  //temp = temp storage for value 
  int temp;
  int i;
  for (int j=k; j<(size); j++){
    temp = array[j];
    i=j;
    while((i>=k) && (array[i-k] >temp)){
     array[i] = array[i-k];
     n_comp++;
     i = i-k;
    }
    array[i] = temp;
  }
  if (k != 1){
    sorting(array, (k-1)/3, n_comp, size);
  }
  else{
    return; 
  } 
}  

/* void printArr(long * Arr, int *size)
{
  for (int i=0; i< *size;i++){
    printf("%ld", Arr[i]);
  }
}*/

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
 fseek(fp,0,SEEK_SET);
 int numInt = len/sizeof(long int);
 long*Arr=malloc(numInt * sizeof(long));
 if (Arr == NULL) {
   fclose(fp);
   *size = 0;
   return NULL;
 }
 if (*size == 0){
   fclose(fp);
   return Arr;
 }  
 

int check = fread(&Arr, sizeof(long), numInt , fp);
if (check == 0) {
  return NULL;
}
 fclose(fp);
 *size = numInt;
 fclose(fp);
 return(Arr);
}



void Array_Shellsort(long*array, int size, long *n_comp){
  //k = number of subarray elements
  //temp = temp storage for value
  long k = size-1;
  //long temp;
  //int i;
  // k = 13 because of 13 compare
  /*
  for ( int j=k; j<(size); j++){
    temp = array[j];
    i = j;
    while (i>=k && array[i-k] >temp){
      array[i] = array [i-k];
      i = i-k;
    }
    array[i] = temp;
  }
  */
  sorting( array, k, n_comp, size);
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



    
    
    
    
    

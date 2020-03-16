#include <stdio.h>
#include<stdlib.h>

struct huffNode{
  char value; //input char
  unsigned freq; //freq of char
  struct huffNode *left; //recursive children of node
  struct huffNode *right; //right child
};
struct huFor {
  //collection of huffnodes
  unsigned size; //size of nodes
  unsigned cap;  // freq in node
  struct MinHeapNode ** arr; //array
};

int readFile(char *filename,  int * fArr);

int readFile(char *filename,  int * fArr){
  //ascii only
  FILE *fp;
  //FILE *fp2;
  char c; 
  fp = fopen(filename, "w");
  do{
    c = fgetc(fp);
    if (c == EOF){
      break;
    }
    if (c == '\n'){
      c - fgetc(fp);//skip forwards by a step
    }
    fArr[c]++;
  }while(c != EOF )

    
}
int main(char * argv, int argc){
  int *fArr =(int*)calloc(256*sizeof(int));
  readFile(argv[1],fArr);
  for (int i =0; i++; i<255){
    if (fArr[i] != 0){
      printf("char:%c ct:%d",(char)i, fArr[i]);
    }
  }
}



}

#include <stdio.h>
#include<stdlib.h>
//STRUCTS---------------------------------------
struct Node{
  char value; //input char
  int freq; //freq of char
  struct Node *left; //recursive children of node
  struct Node *right; //right child
};
struct frst {
  //collection of huffnodes
  //size of nodes
  int capacity;
  int * fArr; // array of freq in node
  struct Node ** nArr; //array
};
//-----------------------------------------------------
//FUNCTION DECLARATIONS
//-----------------------------------------------------------//
int readFile(char *filename,  int * fArr); //input
struct frst * createFor(int *fArr, int numEl); void fillFor(int * fArr, struct frst * forest); struct Node * makeNode(int Freq, int chr); //making forest

//-----------------------------------------------------------//
//FUNCTIONS
//-----------------------------------------------------------//
int readFile(char *filename,  int * fArr){//debug with 40, 25, 26, 42
  //ascii only
  FILE *fp;
  //FILE *fp2;
  char c; 
  fp = fopen(filename, "r");

  do{
    c = fgetc(fp);
    if (c == EOF){
      break;
    }
    if(c == ' '){
      c = fgetc(fp);
    }
    if (c == '\n'){
      c =fgetc(fp);//skip forwards by a step
    }
    fArr[c]++;
  }while(c != EOF );

  fclose(fp);


}
struct frst * createFor(int *fArr, int numEl){
  struct frst * forest  = (struct frst *)malloc(sizeof (struct frst));
  forest->capacity= numEl;
  forest->nArr = (struct Node**)malloc(numEl * sizeof(struct node*));
  forest->fArr = (int *)calloc(numEl,sizeof(int));
  return forest;
}
void fillFor(int * fArr, struct frst * forest){
  //create node to add
  int j=0;
  int i=0;
  while(i<=255){
    //printf("%d", i);
    if (fArr[i] != 0){

      forest->nArr[j] = makeNode(fArr[i], i);
      j++;
    }
    i++;
  }
}
struct Node * makeNode(int Freq, int chr){
  struct Node *node = (struct Node*)malloc(sizeof(struct Node));
  node->left = node->right = NULL;
  node->value = (char)chr;
  node->freq = Freq;
  return(node);
}

//----------------------------------------------------------//
int main(int argc, char *argv[]){
  //FILE INPUT//
  //----------------------------------------//
  int *fArr =(int*)calloc(256,sizeof(int));
  readFile(argv[1],fArr);
  int j =0;
  //TESTCODE-------------------------
  FILE *f2= fopen(argv[3], "w"); 
  while(j<=255){//print Arr
    if (fArr[j]!=0){
      fprintf(f2,"index: %d char: %c freq: %d \n",j, j, fArr[j]);
    }
    j++;
  }
  fclose(f2);
  //--------------------------------------------

  //MAKING FOREST// b 108 63 72 67
  //-------------------------------------// 
  int i = 0;
  int numEl = 0;
  while (i<=255){ 
    if (fArr[i] != 0){
      numEl++;
    }
    i++;
  }
  struct frst *forest = createFor(fArr, numEl);
  fillFor(fArr, forest);
  //-------------------------------------------//

  j = 0;
  //TESTCODE--------------------------------------------------------
  FILE*f1= fopen(argv[2], "w");

  while (j<numEl){//print forest
    fprintf(f1,"node #: %d char: %c freq: %d\n",j+1, forest->nArr[j]->value, forest->nArr[j]->freq );  
    j++;
  }
  j=0;

  fclose(f1);
  //---------------------------------------------------------------
  //CONDENSE FOREST



}





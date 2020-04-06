#include <stdio.h>
#include<stdlib.h>
//STRUCTS---------------------------------------
struct Node{
  char value; //input char
  int freq; //freq of char
  int type; //0 is combo, 1 is leaf
  struct Node *left; //recursive children of node
  struct Node *right; //right child
};
struct frst {
  //collection of huffnodes
  //size of nodes
  int * tArr;//array of types: 0 is empty, 1 is  a leaf that is usable in tree, 2 is already used in tree
  int capacity;
  int * fArr; // array of freq in node
  struct Node ** nArr; //array
};
//-----------------------------------------------------
//FUNCTION DECLARATIONS
//-----------------------------------------------------------//
int readFile(char *filename,  int * fArr); //input
struct frst * createFor(int *fArr, int numEl); void fillFor(int * fArr, struct frst * forest); struct Node * makeNode(int Freq, char chr, int type); //making forest
void condense(struct frst * forest, int nComp); int smallNodes(struct frst *forest, int nComp); void combine( struct frst *forest, int s1, int s2, int nComp);//compressing forest into 1 tree
void Ppo(struct Node *node, FILE * fp); void printBook(struct Node *node, FILE *fp, char direction, int path[]); void reset(int *path);//output
//-----------------------------------------------------------//
//FUNCTIONS
//------------------------------input-----------------------------------------------------------//
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
    
    fArr[c]++;
  }while(c != EOF );

  fclose(fp);


}
//create forest---------------------------------------------------
struct frst * createFor(int *fArr, int numEl){
  struct frst * forest  = (struct frst *)malloc(sizeof (struct frst));
  forest->capacity= 2*numEl-1 ;
  forest->nArr = (struct Node**)malloc((forest->capacity) * sizeof(struct node*));
  forest->fArr = (int *)calloc(numEl*2,sizeof(int));
  forest->tArr = (int *)calloc(numEl*2,sizeof(int));
  return forest;
}
void fillFor(int * fArr, struct frst * forest){
  //create node to add
  int j=0;

  for (int i=0; i<=255; i++){
    //printf("%d", i);
    if (fArr[i] != 0){

      forest->nArr[j] = makeNode(fArr[i], (char)i,1);
      forest->tArr[j] = 1;
      forest->fArr[j] = fArr[i];
      j++;
    }

  }
  for (int l = j; l<=forest->capacity;l++){
    forest->fArr[l]=-1;
    forest->nArr[l] = makeNode(-1, '0', 0);
    forest->tArr[l]= 0;
  }
}
struct Node * makeNode(int Freq, char chr, int type){
  struct Node *node = (struct Node*)malloc(sizeof(struct Node));
  node->left = node->right = NULL;
  node->value = chr;
  node->freq = Freq;
  node->type = type;
  return(node);
}
//---------------------condense forest into one tree---------------------------------------

void condense(struct frst * forest, int nComp){
  if (nComp == (forest->capacity)){
    return;
  } // nComp is the place in the array 
  //find smallest 2 nodes
  int s1 = smallNodes(forest, nComp);
  int s2 = smallNodes(forest, nComp);
  int temp;
  if (forest->nArr[s2]->freq < forest->nArr[s1]->freq){
    temp = s1;
    s1 = s2;
    s2 = temp;
  }
  //combine 2 nodes in an empty location, mark cells for deletion
  combine(forest, s1, s2, nComp);
  condense(forest, nComp+1);

}
int smallNodes(struct frst *forest, int nComp){
  //one left
  if(nComp == forest->capacity){
    for(int i =0; i < nComp; i++){
      if(forest->tArr[i] == 1)
        return i;
    } 
  }
  int largest = 0; 
  int index = 0;
  for (int i = 0; i<nComp;i++){
    if ((forest->nArr[i]->freq >largest) && (forest->tArr[i] == 1)){
      largest = forest->nArr[i]->freq;
      index = i;
    }
  }

  int smallest = largest;
  for (int i =0; i<nComp; i++){
    if((forest->nArr[i]->freq <= smallest) && (forest->tArr[i] == 1)){
      smallest = forest->nArr[i]->freq;
      index = i;
    }
  }
  forest->tArr[index] = 2;
  return index; 
}
void combine(struct frst *forest, int s1, int s2, int nComp){
  //combine both nodes into the empty one
  forest->nArr[nComp]->freq = forest->nArr[s1]->freq+forest->nArr[s2]->freq;//combine freqs
  forest->nArr[nComp]->type = 0;
  forest->tArr[nComp] = 1;
  //assign left and right 
  forest->nArr[nComp]->left = forest->nArr[s2]; 
  forest->nArr[nComp]->right = forest->nArr[s1];

}

///----------------------------------------------------------//
//----------------------------OUTPUT----------------------------------------------
void Ppo(struct Node *node, FILE * fp){
  if (node == NULL)
    return;
  if (node->type == 0){
    fprintf(fp, "0");
  }
  if (node->type == 1){
    fprintf(fp,"1%c", node->value);
  }
  Ppo(node->left, fp);
  Ppo(node->right, fp);
}
void reset(int *path){
  for (int i=0; i <256; i++)
    path[i] = 2;
}
void printBook(struct Node *node, FILE *fp, char direction, int path[]){
  int i =0;
  while(path[i] != 2){
    i++;
  }
  if(direction == 'r'){
    path[i] = 1;
  }
  else{
    path[i] = 0;
  }
  if (node->type == 1){
    fprintf(fp, "%c:", node->value);
    i=0;
    while(path[i] != 2){
      fprintf(fp, "%d", path[i]);
      i++;
    }
    fprintf(fp,"\n");
    return;
  }
  printBook(node->left, fp, 'l', path);
  printBook(node->right, fp, 'r', path);
}
//------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
  //FILE INPUT//
  //----------------------------------------//
  int *fArr =(int*)calloc(256,sizeof(int));
  readFile(argv[1],fArr);
  int j =0;

  //TESTCODE-------------------------
  /*
     FILE *f2= fopen(argv[2], "w"); 
     while(j<=255){//print Arr
     if (fArr[j]!=0&&fArr[j]!=-1){
     fprintf(f2,"index: %d char: %c freq: %d \n",j, j, fArr[j]);

     }

     j++;
     }
     fclose(f2);*/
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


  //TESTCODE--------------------------------------------------------
  /*FILE*f1= fopen(argv[3], "w");
    j=0;
    for(int i =0;i<forest->capacity;i++){//print forest
    if(forest->tArr[i]==1){
    fprintf(f1,"leaf, node #: %d char: %c freq: %d\n",i+1, forest->nArr[i]->value, forest->nArr[i]->freq );  
    }
    if (forest->tArr[i]==0){
    fprintf(f1,"empty node #: %d\n", i+1);
    }   

    }
    j=0;

    fclose(f1);*/
  //---------------------------------------------------------------
  //CONDENSE FOREST
  int numCt = forest->capacity /2;
  condense(forest, numEl);
  //TESTCODE----------------------------------------------------------
  FILE * fp3 = fopen(argv[2], "w");

  //Ppo(forest->nArr[numEl*2-2], fp3);

  //-----------------------------------------------------------------
  //FILE OUTPUT
  int path[256];
  reset(path);
  /*printBook(forest->nArr[numEl*2-2]->left, fp3, 'l', path);
  printBook(forest->nArr[numEl*2-2]->right, fp3, 'r', path);*/
  Ppo(forest->nArr[numEl*2-2], fp3);
  fclose(fp3);  

}





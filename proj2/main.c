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
void condense(struct frst * forest, int nCt); void smallNodes(struct frst *forest, int smallest[]); int emptyNode(struct frst*forest); void combine(struct frst*forest, int empty, int smallest[] ); //compressing forest into 1 tree
void Ppo(struct Node *node, FILE * fp);//output
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
//create forest---------------------------------------------------
struct frst * createFor(int *fArr, int numEl){
  struct frst * forest  = (struct frst *)malloc(sizeof (struct frst));
  forest->capacity= 2*numEl;
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

void condense(struct frst * forest, int nCt){
  if (nCt == 0){
    return;
  }
  //find smallest 2 nodes
  int smallest[2];
  smallNodes(forest, smallest);
  //find an empty location
  int empty = emptyNode(forest);
  //combine 2 nodes in an empty location, delete the cells
  combine(forest, empty, smallest);
  condense(forest, nCt-1);
  
}
void smallNodes(struct frst *forest, int smallest[]){
  int j =0;
  
  //case first few nodes are empty
  if (forest->nArr[j]->type!=1){
    while(forest->nArr[j]->type != 1)
      j++;
  }
  smallest[0]=j++;
  j=0;
  if (forest->nArr[j]->type != 1){
    while(forest->nArr[j]->type != 1)
      j++;
  }
  smallest[1]=j++;
  
  while(j<forest->capacity){
    if (forest->nArr[j]->type != 1){
      while(forest->nArr[j]->type != 1)
      j++;
      
    }
    if(forest->fArr[j]<smallest[0]){
      smallest[0] == j;
    }
    else{
      if(forest->fArr[j]<smallest[1]){
      smallest[1] == j;
    }
  }
  j++;
  }

}
int emptyNode(struct frst*forest){//finds an empty node
  int i =0;
  while (forest->tArr[i] != 0){
    i++;
  }
    return(i);
}
void combine(struct frst*forest, int empty, int smallest[] ){
 //combine smallest into empty 
 int mini1 = smallest[0];
 int mini2 = smallest[1];
 forest->fArr[empty] = forest->fArr[mini1]+forest->fArr[mini2];
 forest->tArr[empty] = 2;
 forest-> nArr[empty]->type= 0; 
 forest->nArr[empty]->freq = forest->fArr[empty];
 //clear the 2 leafs
 forest->tArr[mini1]= 2;
 forest->tArr[mini2]= 2;
  
}
/*
int istwo(forest){
  int j = 0;
  for (int i= 0; i<forest->capacity;i++){
    if (forest->tArr[i]==1){
      j++;
    }
  }
  if (j>2)
    return 0;
  if (j = 2){
    int l =0;
    for (int i= 0; i<forest->capacity;i++){
    if (forest->tArr[i]==1){
      smallest[l];
      l++
    }
  }
  }
  if (j = 1){
    for (int i= 0; i<forest->capacity;i++){
    if (forest->tArr[i]==1){
     smallest[l]
    }
  }
    
  }
    
}
*/
//----------------------------------------------------------//
//----------------------------OUTPUT----------------------------------------------
void Ppo(struct Node *node, FILE * fp){
  if (node == NULL)
    return;
  if (node->type == 0){
    fprintf(fp, "combo Node, Freq = %d\n", node->freq);
  }
  if (node->type == 1){
    fprintf(fp,"leaf node: %c, freq = %d\n", node->value, node->freq);
  }
  Ppo(node->left, fp);
  Ppo(node->right, fp);
}
//------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
  //FILE INPUT//
  //----------------------------------------//
  int *fArr =(int*)calloc(256,sizeof(int));
  readFile(argv[1],fArr);
  int j =0;
 
  //TESTCODE-------------------------
  FILE *f2= fopen(argv[2], "w"); 
  while(j<=255){//print Arr
    if (fArr[j]!=0&&fArr[j]!=-1){
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

  
  //TESTCODE--------------------------------------------------------
  FILE*f1= fopen(argv[3], "w");
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

  fclose(f1);
  //---------------------------------------------------------------
  //CONDENSE FOREST
  int numCt = forest->capacity /2;
  condense(forest, numCt);
  //TESTCODE----------------------------------------------------------
  FILE * fp3 = fopen(argv[4], "w");
  Ppo(forest->nArr[numCt*2-2], fp3);
  fclose(fp3);


}





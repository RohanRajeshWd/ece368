#include <stdio.h>
#include<stdlib.h>
//STRUCTS---------------------------------------
struct Node{
  char value; //input char
  int freq; //freq of char
  int type; //0 is empty, 1 is char leaf, 2 is combo
  struct Node *left; //recursive children of node
  struct Node *right; //right child
};
struct frst {
  //collection of huffnodes
  //size of nodes
  int * tArr//array of types: 0 is empty, 1 is char leaf, 2 is combo
  int capacity;
  int * fArr; // array of freq in node
  struct Node ** nArr; //array
};
//-----------------------------------------------------
//FUNCTION DECLARATIONS
//-----------------------------------------------------------//
int readFile(char *filename,  int * fArr); //input
struct frst * createFor(int *fArr, int numEl); void fillFor(int * fArr, struct frst * forest); struct Node * makeNode(int Freq, int chr, int type); //making forest

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
  int i=0;
  while(i<=255){
    //printf("%d", i);
    if (fArr[i] != 0){

      forest->nArr[j] = makeNode(fArr[i], (char)i,1);
      forest->tArr[j] = 1;
      forest->fArr[j] = fArr[i];
      j++;
    }
    i++;
  }
  for (int i; i<=forest->capacity;i++){
  forest->fArr[j+i]=-1;
  forest->nArr[j+i] = makeNode(-1, '0', 0);
  forest->tArr[i+j]= 0;
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
void condense(struct frst * forest, int nCt, int numEl+1){
  if (nCt == 1){
    return;
  }
  //find smallest 2 nodes
  int smallest[2] = smallNodes(forest);
  //find an empty location
  int empty = emptyNode(forest);
  //combine 2 nodes in an empty location
  combine(forest, empty, smallest)
  // delete those cells
}
int * smallNodes(frst *forest){
  int j =0;
  int smallest[2];
  //case first few nodes are empty
  if (forest->nArr[j]->type==0){
    while(forest->nArr[j]->type == 0)
      j++;
  }
  smallest[0]=j++;
  if (forest->nArr[j]->type == 0){
    while(forest->nArr[j]->type == 0)
      j++;
  }
  smallest[1]=j++;
  while(j<forest->capacity){
    if (forest->nArr[j]->type == 0){
      while(forest->nArr[j]->type == 0)
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
  return(smallest);
}
int emptyNode(frst*forest){
  int i =0
  while (forest->nArr[j]->type != 0){
    i++
  }
    return(i)
}
void combine(frst*forest, int empty, smallest[] ){
  int freq = forest->fArr[smallest[0]]+forest->fArr[smallest[1]];
  
  struct Node * nNode = (struct Node *)malloc(sizeof(struct Node));
  
  t1 = 
  makeNode(int Freq)
  nNode->type = 2;
  nNode->value ='0';
  nNode->freq = freq;
  forest->fArr[empty] = freq;
  forest->nArr[empty] = nNode;
  //empty the 2 nodes that have been combined
  forest->nArr[smallest[1]]->type = 0
  forest->nArr[smallest[0]]->type = 0
  
}
//----------------------------------------------------------//
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

  j = 0;
  //TESTCODE--------------------------------------------------------
  FILE*f1= fopen(argv[3], "w");

  while (j<numEl+1){//print forest
    if(forest->fArr[j]!=-1){
    fprintf(f1,"node #: %d char: %c freq: %d\n",j+1, forest->nArr[j]->value, forest->nArr[j]->freq );  
    };
    else{
      fprintf(f1,"empty");
    }   
    j++;
  }
  j=0;

  fclose(f1);
  //---------------------------------------------------------------
  //CONDENSE FOREST



}





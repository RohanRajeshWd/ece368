#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include "packing.h"
//declarations

//declarations
int input(char*filename,  int* postIndex);
struct Node * makeTree(int *wArr, int *hArr,int* typeArr, int *postIndex);
struct Node* buildTree(struct Node *node, int *wArr, int *hArr, int* typeArr, int*postIndex, int size );
struct Node * newNode(int* hArr, int* wArr, int* typeArr, int * postIndex);
int Space(struct Node*node);
void printPre(struct Node*node);
struct Node{
  int height;
  int width;
  
  int type;  //1 = V, 2= H, 3= LEAF
  struct Node * left;
  struct Node * right;
} ;
int input(char*filename,  int* postIndex){
  FILE*fp;
  int size;
  size = 0;
  int inPar = 0;
  int comma = 0;
  int num = 0;
  fp= fopen(filename, "r");
  //size = countLine(fp);
  if (fp ==NULL){
    //*size = 0;
    //return NULL; kys gcc you wothless piece of shit
  }

  char c;
  for ( c = fgetc(fp); c !=EOF; c = fgetc(fp)){
    if( c == '\n')
      size++;
  }
  fseek(fp,0,SEEK_SET);
  
  int *typeArr = (int*)calloc(size, sizeof(int));
  int *hArr = (int*)calloc(size, sizeof(int));
  int *wArr = (int*)calloc(size, sizeof(int));
  
  fseek(fp,0,SEEK_SET);
  int line = 1;
  int i;
  
  for ( c = fgetc(fp); c !=EOF; c = fgetc(fp)){
   
    
    if(c == 'V'){ //case vert 
      typeArr[size-line] = -1;
      wArr[size-line] = hArr[size-line] = 0;
    }
    if(c == 'H'){ //case horiz
      typeArr[size-line] = -2;
      wArr[size-line] = hArr[size-line] = 0;
    }
    if(c == '\n'){
      //newLine
      line++;
    }
    
    if (isdigit(c) && inPar ==0){//label of leaf
        num = (c-'0');
        c = fgetc(fp);
        while(c !='('){
            
            num = 10*num+(c-'0');
            c=fgetc(fp);
        }
    typeArr[size-line] = num;
    num = 0;
        
    }
     if(c == '('){
    inPar = 1;//open parenthises
    }
    if((isdigit(c))&& inPar ==1 && comma == 0){//length
    num = (c-'0');
    c = fgetc(fp);
        while(c !=','){
            
            num = 10*num+(c-'0');
            c=fgetc(fp);
        }
    wArr[size-line] = num;
    num = 0;
        
    }
    if( c == ','){
      comma = 1;
    }
    if((isdigit(c))&& inPar ==1 && comma == 1){//width
        num = (c-'0');
        c = fgetc(fp);
        while(c !=')'){
            
            num = 10*num+(c-'0');
            c=fgetc(fp);
        }
    hArr[size-line] = num;
    num = 0;
    }
    if(c ==')'){
      inPar = 0;//close parenthises
      comma = 0;//close comma
    }

  
  }



  fclose(fp);
  /*printf("\n%d\n",size);
  for (int j =0; j<size; j++){
      printf("%d %d %d",typeArr[j], wArr[j], hArr[j]);
      printf("\n");
      
  }*/
  *postIndex = size-1;
  
 struct Node * root = makeTree(wArr, hArr, typeArr, postIndex);
}
struct Node * makeTree(int *wArr, int *hArr,int* typeArr, int *postIndex){
  int size = *postIndex;
  *postIndex= 0;
  struct Node * root = newNode(hArr, wArr, typeArr, postIndex);
  
  buildTree(root->right, wArr, hArr, typeArr, postIndex, size);
  buildTree(root->left, wArr, hArr, typeArr, postIndex, size);
  printPre(root);
  return root;
}
struct Node* buildTree(struct Node *node, int* wArr, int *hArr, int *typeArr, int*postIndex, int size ){
  if (size<*postIndex){ //BASE CASE
    return node;
  }
    
   Node * node = newNode(hArr, wArr, typeArr, postIndex);
  
  if(Space(node) == 1){//empty
   
    
    buildTree(node->right, wArr, hArr, typeArr, postIndex, size);//right
      
    buildTree(node->left, wArr, hArr, typeArr, postIndex, size);//left
    return node;
      


  }
  
  else{
    return NULL;
  }
  
}

int Space(struct Node*node){
    //return 0 if empty
    //return 1 if left is full
    //return 2 if both are full
    /*if(node->left == NULL){
      return 1;
    }*/
    if(node == NULL)
      return 1;
    if(node->type >0){
      return 0;
    }
    return 1;
    
  }
struct Node * newNode(int* hArr, int* wArr, int* typeArr, int * postIndex){
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->height = hArr[*postIndex];
    node->width = wArr[*postIndex];
    //node->label = label;
    node->type = typeArr[*postIndex];
    node->left = NULL;
    node->right = NULL;
    *postIndex=*postIndex+1;
    //printf("   type: %d index = %d",typeArr[*postIndex-1],*postIndex);
    return node;
    
  }  
void printPre(struct Node*node){
  if (node ==NULL){
    return;
  }
  printf("%d \n",node->type);
  printPre(node->left);
  printPre(node->right);
}
int main(int argc, char *argv[]){ 
  int postIndex;
  
  input(argv[1], &postIndex);
  //printf("\n %d", bigness);
  /*
  FILE*fp;
  int size;
  size = 0;
  int inPar = 0;
  int comma = 0;
  int num = 0;
  fp= fopen(argv[1], "r");
  //size = countLine(fp);
  if (fp ==NULL){
    //*size = 0;
    return(0);
  }

  char c;
  for ( c = fgetc(fp); c !=EOF; c = fgetc(fp)){
    if( c == '\n')
      size++;
  }
  fseek(fp,0,SEEK_SET);
  
  int *typeArr = (int*)calloc(size, sizeof(int));
  int *hArr = (int*)calloc(size, sizeof(int));
  int *wArr = (int*)calloc(size, sizeof(int));
  
  fseek(fp,0,SEEK_SET);
  int line = 1;
  int i;
  
  for ( c = fgetc(fp); c !=EOF; c = fgetc(fp)){
   
    
    if(c == 'V'){ //case vert 
      typeArr[size-line] = -1;
      wArr[size-line] = hArr[size-line] = 0;
    }
    if(c == 'H'){ //case horiz
      typeArr[size-line] = -2;
      wArr[size-line] = hArr[size-line] = 0;
    }
    if(c == '\n'){
      //newLine
      line++;
    }
    
    if (isdigit(c) && inPar ==0){//label of leaf
        num = (c-'0');
        c = fgetc(fp);
        while(c !='('){
            
            num = 10*num+(c-'0');
            c=fgetc(fp);
        }
    typeArr[size-line] = num;
    num = 0;
        
    }
     if(c == '('){
    inPar = 1;//open parenthises
    }
    if((isdigit(c))&& inPar ==1 && comma == 0){//length
    num = (c-'0');
    c = fgetc(fp);
        while(c !=','){
            
            num = 10*num+(c-'0');
            c=fgetc(fp);
        }
    wArr[size-line] = num;
    num = 0;
        
    }
    if( c == ','){
      comma = 1;
    }
    if((isdigit(c))&& inPar ==1 && comma == 1){//width
        num = (c-'0');
        c = fgetc(fp);
        while(c !=')'){
            
            num = 10*num+(c-'0');
            c=fgetc(fp);
        }
    hArr[size-line] = num;
    num = 0;
    }
    if(c ==')'){
      inPar = 0;//close parenthises
      comma = 0;//close comma
    }

  
  }



  fclose(fp);
  printf("\n%d\n",size);
  for (int j =0; j<size; j++){
      printf("%d %d %d",typeArr[j], wArr[j], hArr[j]);
      printf("\n");
      
      
  }
  */
}


/*
struct Node{
  int height;
  int width;
  
  int type;  //1 = V, 2= H, 3= LEAF
  struct Node * left;
  struct Node * right;
} ;
int input(char*filename,  int* postIndex){
  FILE*fp;
  int size;
  size = 0;
  int inPar = 0;
  int comma = 0;
  int num = 0;
  fp= fopen(filename, "r");
  //size = countLine(fp);
  if (fp ==NULL){
    //*size = 0;
    //return NULL; kys gcc you wothless piece of shit
  }

  char c;
  for ( c = fgetc(fp); c !=EOF; c = fgetc(fp)){
    if( c == '\n')
      size++;
  }
  fseek(fp,0,SEEK_SET);
  
  int *typeArr = (int*)calloc(size, sizeof(int));
  int *hArr = (int*)calloc(size, sizeof(int));
  int *wArr = (int*)calloc(size, sizeof(int));
  
  fseek(fp,0,SEEK_SET);
  int line = 1;
  int i;
  
  for ( c = fgetc(fp); c !=EOF; c = fgetc(fp)){
   
    
    if(c == 'V'){ //case vert 
      typeArr[size-line] = -1;
      wArr[size-line] = hArr[size-line] = 0;
    }
    if(c == 'H'){ //case horiz
      typeArr[size-line] = -2;
      wArr[size-line] = hArr[size-line] = 0;
    }
    if(c == '\n'){
      //newLine
      line++;
    }
    
    if (isdigit(c) && inPar ==0){//label of leaf
        num = (c-'0');
        c = fgetc(fp);
        while(c !='('){
            
            num = 10*num+(c-'0');
            c=fgetc(fp);
        }
    typeArr[size-line] = num;
    num = 0;
        
    }
     if(c == '('){
    inPar = 1;//open parenthises
    }
    if((isdigit(c))&& inPar ==1 && comma == 0){//length
    num = (c-'0');
    c = fgetc(fp);
        while(c !=','){
            
            num = 10*num+(c-'0');
            c=fgetc(fp);
        }
    wArr[size-line] = num;
    num = 0;
        
    }
    if( c == ','){
      comma = 1;
    }
    if((isdigit(c))&& inPar ==1 && comma == 1){//width
        num = (c-'0');
        c = fgetc(fp);
        while(c !=')'){
            
            num = 10*num+(c-'0');
            c=fgetc(fp);
        }
    hArr[size-line] = num;
    num = 0;
    }
    if(c ==')'){
      inPar = 0;//close parenthises
      comma = 0;//close comma
    }

  
  }



  fclose(fp);
  /*printf("\n%d\n",size);
  for (int j =0; j<size; j++){
      printf("%d %d %d",typeArr[j], wArr[j], hArr[j]);
      printf("\n");
      
  }*/
  *postIndex = size-1;
  
   struct Node * root = makeTree(wArr, hArr, typeArr, postIndex);
}
  struct Node * makeTree(int *wArr, int *hArr,int* typeArr, int *postIndex){
  int size = *postIndex;
  *postIndex= 0;
    struct Node * root = newNode(hArr, wArr, typeArr, postIndex);
  
  buildTree(root->right, wArr, hArr, typeArr, postIndex, size);
  buildTree(root->left, wArr, hArr, typeArr, postIndex, size);
  printPre(root);
  return root;
}
  struct Node* buildTree(  struct Node *node, int* wArr, int *hArr, int *typeArr, int*postIndex, int size ){
  if (size<*postIndex){ //BASE CASE
    return node;
  }
    
    struct Node * node = newNode(hArr, wArr, typeArr, postIndex);
  
  if(Space(node) == 1){//empty
   
    
    buildTree(node->right, wArr, hArr, typeArr, postIndex, size);//right
      
    buildTree(node->left, wArr, hArr, typeArr, postIndex, size);//left
    return node;
      


  }
  
  else{
    return NULL;
  }
  
}

int Space(  struct Node*node){
    //return 0 if empty
    //return 1 if left is full
    //return 2 if both are full
    /*if(node->left == NULL){
      return 1;
    }*/
    if(node == NULL)
      return 1;
    if(node->type >0){
      return 0;
    }
    return 1;
    
  }
  struct Node * newNode(int* hArr, int* wArr, int* typeArr, int * postIndex){
      struct Node *node = (  struct Node*)malloc(sizeof( Node));
    node->height = hArr[*postIndex];
    node->width = wArr[*postIndex];
    //node->label = label;
    node->type = typeArr[*postIndex];
    node->left = NULL;
    node->right = NULL;
    *postIndex=*postIndex+1;
    //printf("   type: %d index = %d",typeArr[*postIndex-1],*postIndex);
    return node;
    
  }  
void printPre(  struct Node*node){
  if (node ==NULL){
    return;
  }
  printf("%d \n",node->type);
  printPre(node->left);
  printPre(node->right);
}
int main(int argc, char *argv[]){ 
  int postIndex;
  
  input(argv[1], &postIndex);
  //printf("\n %d", bigness);
  /*
  FILE*fp;
  int size;
  size = 0;
  int inPar = 0;
  int comma = 0;
  int num = 0;
  fp= fopen(argv[1], "r");
  //size = countLine(fp);
  if (fp ==NULL){
    //*size = 0;
    return(0);
  }

  char c;
  for ( c = fgetc(fp); c !=EOF; c = fgetc(fp)){
    if( c == '\n')
      size++;
  }
  fseek(fp,0,SEEK_SET);
  
  int *typeArr = (int*)calloc(size, sizeof(int));
  int *hArr = (int*)calloc(size, sizeof(int));
  int *wArr = (int*)calloc(size, sizeof(int));
  
  fseek(fp,0,SEEK_SET);
  int line = 1;
  int i;
  
  for ( c = fgetc(fp); c !=EOF; c = fgetc(fp)){
   
    
    if(c == 'V'){ //case vert 
      typeArr[size-line] = -1;
      wArr[size-line] = hArr[size-line] = 0;
    }
    if(c == 'H'){ //case horiz
      typeArr[size-line] = -2;
      wArr[size-line] = hArr[size-line] = 0;
    }
    if(c == '\n'){
      //newLine
      line++;
    }
    
    if (isdigit(c) && inPar ==0){//label of leaf
        num = (c-'0');
        c = fgetc(fp);
        while(c !='('){
            
            num = 10*num+(c-'0');
            c=fgetc(fp);
        }
    typeArr[size-line] = num;
    num = 0;
        
    }
     if(c == '('){
    inPar = 1;//open parenthises
    }
    if((isdigit(c))&& inPar ==1 && comma == 0){//length
    num = (c-'0');
    c = fgetc(fp);
        while(c !=','){
            
            num = 10*num+(c-'0');
            c=fgetc(fp);
        }
    wArr[size-line] = num;
    num = 0;
        
    }
    if( c == ','){
      comma = 1;
    }
    if((isdigit(c))&& inPar ==1 && comma == 1){//width
        num = (c-'0');
        c = fgetc(fp);
        while(c !=')'){
            
            num = 10*num+(c-'0');
            c=fgetc(fp);
        }
    hArr[size-line] = num;
    num = 0;
    }
    if(c ==')'){
      inPar = 0;//close parenthises
      comma = 0;//close comma
    }

  
  }



  fclose(fp);
  printf("\n%d\n",size);
  for (int j =0; j<size; j++){
      printf("%d %d %d",typeArr[j], wArr[j], hArr[j]);
      printf("\n");
      
      
  }
  */
}

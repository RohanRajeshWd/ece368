#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
struct Node{
  int height;
  int width;
  
  int type;  //1 = V, 2= H, 3= LEAF
  struct recNode * left;
  struct recNode * right;
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
    return NULL;
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
  *PostIndex = size-1;
  
 Node * root = makeTree(wArr, hArr, typeArr, &PostIndex);
}
Node * makeTree(int *wArr[], int *hArr[],int* typeArr[], int *PostIndex){
  int size = *PostIndex;
  *PostIndex= 0;
  Node * root = newNode(hArr, wArr, typeArr, PostIndex);
  
  builtTree(root->right, wArr, hArr, typeArr, PostIndex, size)
  builtTree(root->left, wArr, hArr, typeArr, PostIndex, size)
  printPre(root);
  return root;
}
Node* buildTree(node, int wArr, int hArr, int typeArr, int*PostIndex, int size ){
  if (size<PostIndex){ //BASE CASE
    return NULL
  }
    
  
  
  if(Space(node) == 1){//empty
    Node * root = newNode(hArr, wArr, typeArr, PostIndex);
    
    builtTree(root->right, wArr, hArr, typeArr, &PostIndex, size);//right
      
    builtTree(root->left, wArr, hArr, typeArr, &PostIndex, size);//left
      


  }
  
  else{
    return NULL;
  }
  return root;
}
int Space(Node*node){
    //return 0 if empty
    //return 1 if left is full
    //return 2 if both are full
    if(node->type >0){
      return 0;
    }
    if(node->left == NULL){
      return 1;
    }
  }
Node * newNode(int* hArr, int* wArr, int* typeArr, int * PostIndex){
    Node *node = (Node*)malloc(sizeof(Node));
    node->height = hArr[PostIndex];
    node->width = wArr[PostIndex];
    //node->label = label;
    node->type = typeArr[PostIndex];
    node->left = NULL;
    node->right = NULL;
    *PostIndex++;
    printf("   index = %d",PostIndex)
    return node;
    
  }  
void printPre(Node*node){
  if (node ==NULL){
    return;
  }
  printf("%d",node->type);
  printPre(node->left);
  printPre(node->right);
}
int main(int argc, char *argv[]){ 
  int postIndex;
  
  input(argv[1], &postIndex);
  printf("\n %d", bigness);
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

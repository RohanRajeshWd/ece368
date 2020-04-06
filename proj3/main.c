#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

//#include "packing.h"
//declarations
int input(char*filename,  int* postIndex, char *file1, char* file2);
void makeTree(int *wArr, int *hArr,int* typeArr, int *postIndex, char *f1, char * f2);
struct Node* buildTree(struct Node *node, int *wArr, int *hArr, int* typeArr, int*postIndex, int size );
struct Node * newNode(int* hArr, int* wArr, int* typeArr, int * postIndex, struct Node *node);
void printPoD(struct Node*node, FILE*fp);
 
int Space(struct Node*node);
//void printPre(struct Node*node);
void printPreD(struct Node*node, FILE*fp);
void addStuff( struct Node * node);
void deleteTree(struct Node* node); 
struct Node{
  int height;
  int width;
  
  int type;  //1 = V, 2= H, 3= LEAF
  struct Node * left;
  struct Node * right;
} ;
void deleteTree(struct Node* node)  
{ 
    if (node == NULL) return; 
  
    /* first delete both subtrees */
    deleteTree(node->left); 
    deleteTree(node->right); 
    
    /* then delete the node */
    //printf("\n Deleting node: %d", node->data); 
    free(node); 
}  
void addStuff( struct Node * node){
  if(node->type>0){
   return;
}
addStuff(node->right);
addStuff(node->left);
 if (node->type == -1) //v
 {
  node->width = node->left->width+node->right->width;
  if (node->left->height>node->right->height){
    node->height = node->left->height;
  }
  else{
    node->height= node->right->height;
  }
  
}
if (node->type == -2)//h
 {
   node->height = node->left->height +node -> right -> height;
   if (node->left->width>node->right->width){
    node->width = node->left->width;
   }
   else{
    node->width = node->right->width;
  }
  
   }
 
 
 


 
  
}
int input(char*filename,  int* postIndex, char *file1, char* file2){
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
    return EXIT_FAILURE; //kys gcc you wothless piece of shit
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
  //FILE *fp1 = fopen(file1, "w");
  //FILE *fp2 = fopen(file2, "w");
  
 
 //fclose(fp);
 makeTree(wArr, hArr, typeArr, postIndex, file1, file2);
 //fclose(fp1);
 //fclose(fp2);
 
 free(typeArr);
 free(wArr);
 free(hArr);

 return 0;
}
void makeTree(int *wArr, int *hArr,int* typeArr, int *postIndex, char * f1, char *f2){
  int size = *postIndex;
  *postIndex= 0;
  //root = (struct Node*)malloc(sizeof(struct Node));
  struct Node * root; //= newNode(hArr, wArr, typeArr, postIndex);
  root = (struct Node*)malloc(sizeof(struct Node));
  root = buildTree(root, wArr, hArr, typeArr, postIndex, size);
  //buildTree(root->left, wArr, hArr, typeArr, postIndex, size);
  //printf("before\n");
  FILE *fp1 = fopen(f1, "w");
  printPreD(root, fp1);
  fclose(fp1);
  addStuff(root);
  //printf("after\n");
  FILE *fp2 = fopen(f2, "w");
  printPoD(root, fp2);
  fclose(fp2);
  deleteTree(root);  
  if (root == NULL){
    printf("NULL");
  }
  //printf("%d \n", root->type);
 
}
struct Node* buildTree(struct Node *node, int* wArr, int *hArr, int *typeArr, int*postIndex, int size ){
  if (size<*postIndex){ //BASE CASE
    return node;
  }
    
   node = newNode(hArr, wArr, typeArr, postIndex, node);
  
  if(Space(node) == 1){//empty
   
    node->right = (struct Node*)malloc(sizeof(struct Node));
    buildTree(node->right, wArr, hArr, typeArr, postIndex, size);//right
    node->left = (struct Node*)malloc(sizeof(struct Node));
    buildTree(node->left, wArr, hArr, typeArr, postIndex, size);//left
    return node;
      


  }
  
  else{
    return node;
  }
  
}

int Space(struct Node * node){
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
struct Node * newNode(int* hArr, int* wArr, int* typeArr, int * postIndex, struct Node *node){
    //struct Node *node = (struct Node*)malloc(sizeof(struct Node));
   int ind = *postIndex;
    node->height = hArr[ind];
    node->width = wArr[ind];
    //node->label = label;
    node->type = typeArr[ind];
    node->left = NULL;
    node->right = NULL;
    *postIndex=*postIndex+1;
    //printf("   type: %d index = %d",typeArr[*postIndex-1],*postIndex);
    return node;
    
  }  

void printPreD(struct Node*node, FILE *fp1){
  if (node == NULL){
    return;
  }
  //printf("\ntype:%d   width:%d  height:%d\n",node->type, node->width, node->height);
  int type= node->type;
  int width = node->width;
  int height = node->height;
  if (node->type == -1){
    fprintf(fp1,"V\n");
  }
  if (node->type == -2){
    fprintf(fp1,"H\n");
  }
  if(node->type>0){
  fprintf(fp1, "%d(%d,%d)\n", type,width, height);
  }
  printPreD(node->left, fp1);
  printPreD(node->right, fp1);
  
}
void printPoD(struct Node*node, FILE *fp){
  if (node == NULL){
    return;
  }
  
  printPoD(node->left,fp);
  printPoD(node->right,fp);
  if (node->type == -1){
    fprintf(fp,"V(%d,%d)\n", node->width, node->height);
  }
  if (node->type == -2){
    fprintf(fp,"H(%d,%d)\n", node->width, node->height);
  }
  if (node->type > 0){
  fprintf(fp, "%d(%d,%d)\n", node->type,node->width,node-> height);
  }
  //fprintf(fp, "%d(%d,%d)\n", node->type, node->width, node->height);
}
int main(int argc, char *argv[]){ 
  int postIndex;
  
  int x = input(argv[1], &postIndex, argv[2], argv[3]);
  if(argc != 5){
    return EXIT_FAILURE;
  }
}

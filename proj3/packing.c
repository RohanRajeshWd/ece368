//packing functions use an array to bring in the function


#include<stdio.h>
void input(filename){
}

Node* buildTree(int lenArr, int widthArr, int typeArr, int labelArr, Node* node, int loc ){
  newNode(len[loc], width[loc],label[loc],type[loc]);
  *loc++;
  if(Space == 1){
    buildTree(lenArr, widthArr, typeArr, labelArr, node->right, &loc);
    buildTree(lenArr, widthArr, typeArr, labelArr, node->left, &loc);
  }
  return node;
  
  
int Space(Node*node){
//return 0 if empty
//return 1 if left is full
//return 2 if both are full
  if(node->type == 3){
    return 0;
  }
  if(node->left == NULL){
    return 1;
  }
}
Node * newNode(int len, int width, int label, int type){
  Node *node = (Node*)malloc(sizeof(Node));
  node->len = len;
  node->width = width;
  node->label = label;
  node->type = type;
  node->left = NULL;
  node->right = NULL;
}



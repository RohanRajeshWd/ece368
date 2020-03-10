
/*struct Node{
  int len;
  int width;
  int label;
  int type;  //1 = V, 2= H, 3= LEAF
  struct Node * left;
  struct Node * right;
} ;
*/

int input(char*filename,  int* postIndex);
 struct Node* makeTree(int *wArr, int *hArr,int* typeArr, int *postIndex);
 struct Node* buildTree( struct Node *node, int *wArr, int *hArr, int* typeArr, int*postIndex, int size );
 struct Node* newNode(int* hArr, int* wArr, int* typeArr, int * postIndex);
int Space( struct Node*node);
void printPre( struct Node*node);

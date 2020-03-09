#define PACKING_H

struct Node{
  int len;
  int width;
  int label;
  int type;  //1 = V, 2= H, 3= LEAF
  struct recNode * left;
  struct recNode * right;
} treenode;

void input(char*filename, int *size);

i//this is my .h file

struct huffNode{
  char value; //input char
  unsigned freq; //freq of char
  struct huffNode *left; //recursive children of node
  struct huffNode *right; //right child
}
struct huFor {
  //collection of huffnodes
  unsigned size; //size of nodes
  unsigned cap;  // freq in node
  struct MinHeapNode ** arr; //array
}


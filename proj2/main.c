#include <stdio.h>
#include<stdlib.h>

  struct huffNode{
    char value; //input char
    unsigned freq; //freq of char
    struct huffNode *left; //recursive children of node
    struct huffNode *right; //right child
  };
  struct huFor {
    //collection of huffnodes
    unsigned size; //size of nodes
    unsigned cap;  // freq in node
    struct MinHeapNode ** arr; //array
  };
  
          

int readFile(char *filename, char *Freq, char *Traversal, char *Cbook){
  FILE *fp;
  FILE *fp2;
  fp = fopen(Freq, "w");
  fseek(fp,0,SEEK_END);
  if ftell(fp)==0){
  return EXIT_FAILURE;
  }
  fseek(fp,0 , SEEK_SET);
  int charct[256] = 0; array of all character's counts
  
    fp = fopen(filename,"r");
  if FP == NULL {
    return EXIT_FAILURE;
  }

  while(1){
    c = fgetc(fp);
    if ( feof(fp)){
      break;
    }
    charct[(int)c]++;
  }
  fwrite(charct, sizeof(int), 256, fp2);
  free(fp2);
  int element=0;
  for( int i = 0; i<256; i++){//find how many elements
    if (charct[i] !=0){
      element++;
    }
  }
 //fwrite(charct

  
  long *freqArr = malloc(element *sizeof(long));
  int * elArr = malloc(element *sizeof(int));
  int elArrCt = 0;
    for( int i = 0; i<256; i++){
      if (charct[i] != 0){
        elArr[elArrCt]= i;
        freqArr[elArrCt++] = charct[i];
      }
 
    }
    makeCode(elArr,freqArr, element, Traversal, Cbook );
fclose(fp);
fclose(fp2);
return EXIT_SUCCESS;
}
void makeCode(int *elArr, long *freqArr, int element, char *travFile, char *bookFile){
  //make tree
  struct huffNode *root = makeTree(elArr, freqArr, element);
  int arr[10000], top =0;
  FILE*fp = fopen(bookFile,"w");
  FILE*fp = fopen(travFile,"w");
  bookPrint(root, arr, top, fpBook);
  fclose(fpBook);
  output(root, arr, top, travFile);
  freeing(root);
}
struct huffNode * makeTree(int * elArr, long *freqArr, int size){
  struct huffNode *left, *right, *top;
  struct huffFor *forest = makeFor(elArr, freqArr, size);
  while(sizing(forest) !=1){
    left = minRem(forest);
    right - minRem(forest);
    top =newNode('new', right->freq+left->freq);
    top->left = left;
      top->right = right;
    insertMinHeap(forest,top);
  }
  return minRem(forest);
}
void makeFor(int * elArr, long* freqArr, int size){
  struct huFor *forest = malocFor(size);
  int i = 0;
  while (i<size){
    forest->arr[i] = newNode(elArr[i], freqArr[i]);
    i++;
  }
  forest->size = size;
  buildFor(forest);
  return forest;
}
//alloc mem for a forest of trees to sort
struct huFor * malocFor( unsigned count){
  struct huFor * forest = (struct huFor *)malloc(sizeof(struct huFor);
  forest->size = 0;
  forest->cap = count;
  forest->arr = (struct huffNode**)malloc(forest->cap *sizeof(struct huffNode));
  return forest;
  }
void buildFor (struct huFor * forest){
  for (int i = (forest->size-2)/2; i>=0;--i){
    helper(forest, i);
    }
    }
void helper(struct huFor *forest, int i){
  int l = 2 *i+1;
  int c = i;
  int r = 2*i+2;
  if((l<forest->size) && (forest->arr[l]->freq<forest->arr[c]->freq)){
  c=l;
  }
  if((r<forest->size) && (forest->arr[r]->freq<forest->arr[c]->freq)){
  c=r;
  }
  if (i != c){
    swapNodeM(&forest->arr[c], &forest->arr[i]);
    helper(forest, c);
  }
}
void swapNodeM(struct huffNode **A, struct huffNode **B){
  struct huffNode *temp = *A;
  *A = * B;
  *B = temp;
}
struct huffNode * newNode (int elements, unsigned freq){
  struct huffNode * temp = (struct huffNode*)malloc(sizeof(struct huffNode);  temp->left = NULL;
  temp->right = NULL;
  temp->value = elements;
  temp->freq= freq;
  return temp;
  }
  
int isSizeOne(struct huFor * forest){
return (forest->size == 1);
}


struct *minRem(struct huFor * forest){
  struct huffNode * temp = forest->array[0];
  forest->array[0]= forest->array[forest->size-1];
  forest->size = forest->size-1;
  helper(forest, 0);
  return temp;
  }
void insertMinHeap(struct huFor* forest, struct huffNode *HuffNode){
  ++forest->size;
  int i = forest->size-1;
  while (i && HuffNode->freq < forest->array[(i - 1) / 2]->freq) { 
  
        forest->array[i] = forest->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    forest->array[i] = huffNode; 
} 
  
int LeafBool (struct huffNode * root){
  

    return !(root->left) && !(root->right);
}

void output(struct huffNode * root, int arr, int top, char *TravFile, char *BookFile){
  FILE*fpTrav;
  fopen(fpTrav);
  travprint(root, fpTrav);
  fclose(fpTrav);
  //bookprint
}
void freeing(struct huffNode *root){
  if (root ==NULL){
  return;
  }
  deallocate(root->left);
  deallocate(root->right);
  free(root);
  }
void travprint(struct huffNode *root, File * fp){
    //root-left-right
  if(LeafBool(root) == 1){
    fprintf(fp,"1");
    fprintf(fp,root->value);
    // go right
   return;
  }
  else{
    fprintf(fp,"0");
    travprint(root->left, fp);
    travprint(root->right, fp);
  }
}
void bookPrint(struct huffNode * root, int arr, int top, fp){
  if (root->left) {
    arr[top] = 0;
      bookPrint(root->left, arr, top+1);
  }
  if (root->right){
    arr[top]=1;
    printcodes(root->right, arr, top+1);
  }
  if (LeafBool(root) ==1){
    fprintf(arr[top], fp);
  }
}
//function declarations

int main(argv, argc){
return (readfile(argv[1],argv[2], argv[3], argv[4]));
}

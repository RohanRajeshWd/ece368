#include "heap.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
minHeap *mallocHeap(int rows, int cols){
  int size = rows*cols; 
  minHeap * heap = (minHeap*) malloc(sizeof(minHeap));
  heap ->d = malloc(sizeof(short)* size);
  heap ->el = malloc(sizeof(int)*size);
  for(int i = 0; i< size; i++){
    if(i >= (rows-1)*cols){
      heap->d[i] = 0;
    }
    heap->d[i] = SHRT_MAX;
    heap->el[i] = i;
  }
  heap->cap = size;
  heap->ct = size;
  //heap->end = 0; 
  return heap;
}
void heapUp(minHeap *h, int ind, int index[]){
  int tmp;
  int tmpEl;
  int tmpInd;
  int parent = (ind-1)/2;
  if(h->d[parent]> h->d[ind]){
    tmp = h->d[parent];
    tmpEl = h->el[parent];
    h->d[parent] = h->d[ind];
    h->el[parent] = h->el[ind];
    h->d[ind] = tmp;
    h->el[ind] = tmpEl;
    //update index
    tmpInd = index[h->el[parent]];
    index[h->el[parent]] = index[h->el[ind]];
    index[h->el[ind]] = tmpInd;
    //recurse
    heapUp(h, parent, index);
  }
}/*
    void insert(minHeap*heap, short value){
    if(heap->d[0] == SHRT_MAX){
    heap->d[0] = value;
//heap->x[0] = x;
//heap->y[0] = y;
heap->ct++;
return;
}
//int key;
heap->d[heap->ct] = value;
heapUp(heap, heap->ct);
heap->ct++;
}*/
void heapDown(minHeap * h, int p, int ind[]){
  int l = p *2+1;
  int r = l+1;
  int min;
  short tmp;
  int inTmp;
  int tmpEl;
  if(l <0 || l >= h->ct)
    l = -1;
  if(r<0 || r >= h->ct)
    r = -1;
  if(l != -1 && h->d[l] < h->d[p])
    min = l;
  else
    min = p;
  if(r != -1 && h->d[r] < h->d[min])
    min = r;
  if(min != p){
    tmp = h->d[min];
    tmpEl = h->el[min];
    h->d[min] = h->d[p];
    h->el[min] = h->el[p];
    h->d[p] = tmp;
    h->el[p] = tmpEl;
    //update index
    
    inTmp = ind[h->el[min]];
    ind[h->el[min]] = ind[h->el[p]];
    ind[h->el[p]] = inTmp;
    //recurse
    heapDown(h, min, ind);
  }
}

short pop(minHeap*heap, int index[], int *el, int *p){
  
  //int popInd = index[heap->el[0]];
  int repInd = index[heap->el[heap->ct-1]]; 
  int origRoot = heap->el[0];
  int origRootD = heap->d[0];
  
  if(heap->ct == 0){
    return -1;
  }
  *el = heap->el[0];
  *p = heap->d[0];

  heap->el[0] = heap->el[heap->ct-1];
  heap->d[0] = heap->d[heap->ct-1];
  heap->el[heap->ct-1] = origRoot;
  heap->d[heap->ct-1] = origRootD;
  //update index
  index[origRoot] = repInd;
  index[heap->el[0]] = 0;
  heap->ct--;

  heapDown(heap, 0, index);
  return 0;
}
int  twoOne (int x, int y, int row, int col){
  int ret;
  ret = col*(y)+(x);
  return(ret);
}
void oneTwo(int num , int*xc, int*yc, int *x, int *y){
  *xc = x[num];
  *yc = y[num];
}

void genAdj(short ** arr, int coords,int *xc, int * yc, short rows, short cols, int *adj){
  int x,y;
 // adj = {-1,-1,-1,-1};

  oneTwo(coords, &x, &y, xc, yc );
  //int * specAdj = (int*)malloc(sizeof(int)*cols+1);
  int borderX;// 1 = upper/left edge // 2 = bottom/right edge // 3 = middle
  int borderY;
  if (x == 0 )
    borderX = 1;
  else if (x == cols -1)
    borderX = 2;
  else
    borderX = 3;
  if (y ==0)
    borderY = 1;
  else if( y == rows-1)
    borderY = 2;
  else
    borderY = 3;

  short xLst[4] = {-1,-1,-1,-1};
  short yLst[4] = {-1,-1,-1,-1};
 /*if(flag){
   
   for(int i = (rows-1)*cols; i < rows*cols; i++){
     specAdj[j++] = i;
     
   }
   specAdj[j] = -1;
   free(adj);
   return specAdj;
 }*/
 //free(specAdj);
  //now, generate list
  // cases:top edge, bottom edge, middle, and 4 corners
  //4 corners
  if (borderX ==1 && borderY == 1){ // top left corner
    xLst[0] = x+1;
    yLst[0] = y;
    xLst[1] = x;
    yLst[1] = y+1;
  }
  if (borderX == 2 && borderY == 1){ //top right corner
    xLst[0] = x-1;
    yLst[0] = y;
    xLst[1] = x;
    yLst[1] = y+1;
  }
  if (borderX == 1 && borderY == 2){ //bot left corner
    xLst[0] = x+1;
    yLst[0] = y;
    xLst[1] = x;
    yLst[1] = y-1;
  }
  if (borderX == 2 && borderY == 2){ //bot right corner
    xLst[0] = x-1;
    yLst[0] = y;
    xLst[1] = x;
    yLst[1] = y-1;
  } //edges
  if(borderX == 3 && borderY == 1){ //top edge
    xLst[0] = x-1;
    yLst[0] = y;
    xLst[1] = x+1;
    yLst[1] = y;
    xLst[2] = x;
    yLst[2] = y+1;
  }
  if(borderX == 3 && borderY == 2){ //bot edge
    xLst[0] = x-1;
    yLst[0] = y;
    xLst[1] = x+1;
    yLst[1] = y;
    xLst[2] = x;
    yLst[2] = y-1;
  }
  if(borderX == 1 && borderY == 3){ //left edge
    xLst[0] = x;
    yLst[0] = y+1;
    xLst[1] = x;
    yLst[1] = y-1;
    xLst[2] = x+1;
    yLst[2] = y;
  }
  if(borderX == 2 && borderY == 3){ //right edge
    xLst[0] = x;
    yLst[0] = y+1;
    xLst[1] = x;
    yLst[1] = y-1;
    xLst[2] = x-1;
    yLst[2] = y;
  }
  //mid 
  if(borderX == 3 && borderY == 3){
    xLst[0] = x-1;
    yLst[0] = y;
    xLst[1] = x+1;
    yLst[1] = y;
    xLst[2] = x;
    yLst[2] = y+1;
    xLst[3] = x;
    yLst[3] = y-1;
}
//int i = 0;
  for (int i = 0; i <4; i++){
    if (xLst[i] != -1)
      adj[i] = twoOne(xLst[i], yLst[i], rows, cols);
    else 
      adj[i] = -1;
    
  }
  
}

void djik(minHeap *h, short **arr, short rows, short cols, int *ind, int *prev, int *x, int *y){
  int uEl;
  int uD;
  int uC;
  int adj[4]= {-1,-1,-1,-1};
  //int megaFlag = 1;
  int vEl;
  int vD;
  int yc, xc;
  while (h->ct > 0){
    pop(h, ind, &uEl, &uD); //extract min
    oneTwo(uEl, &xc,&yc, x, y);
    uC = arr[yc][xc];
    
    genAdj(arr, uEl, x, y, rows, cols, adj); //generate adjacency
    for (int i= 0; i<4; i++){
    
    vEl = adj[i];
    if(vEl >=0 ){
    vD = h->d[ind[vEl]];
    if (ind[vEl] < h->ct && vD > (uD+uC)){
      h->d[ind[vEl]] = uD+uC;
      prev[vEl] = uEl;
      heapUp(h, ind[vEl], ind);
    }
    }

    }
  }

}
void set(minHeap *heap, int start, short rows,short cols, int *ind, int *prev) {
  //free(heap->d);
  //free(heap->el);
  for (int i = 0; i<rows*cols; i++){
    prev[i] = -2;
  }
  for(int i = 0; i< rows*cols; i++){
    heap->d[i] = SHRT_MAX;
    heap->el[i] = i;
    ind[i] = i;
  }
  
  heap->ct = rows*cols;
  heap->d[start] = 0;
  heapUp(heap, ind[start], ind);
}
int fastestEnd(minHeap *heap, int *ind, int rows, int cols, short **arr, int *x, int *y, int *time){
  int start = cols*(rows-1);
  int size = rows*cols;
  short fastest = SHRT_MAX;
  short d;
  int index;
  int retNode;
  int xc;
  int yc;
  short uC;
  for(int i = start;i < size; i++){
    index = ind[i];
    oneTwo(i, &xc,&yc, x, y);
    uC = arr[yc][xc];
    d = heap->d[index]+uC;
    if (d < fastest){
      fastest= d;
      retNode = i;
    }
  }
  *time = fastest;
  return retNode;
}
//void printPath()
int main(int argc, char ** argv){
  //printf("1\n");
  
  if (argc != 5){
    return EXIT_FAILURE;
  }
  FILE*fp5 = fopen(argv[2], "w");
  fclose(fp5);
  fp5 = fopen(argv[3], "w");
  fclose(fp5);
  fp5 = fopen(argv[4], "w");
  fclose(fp5);
  //printf("2\n");
  FILE*fp = fopen(argv[1], "r");
  if  (fp == NULL){
    return EXIT_FAILURE;
  }
  //printf("3\n");
  short rows;
  short num;
  short cols;
  fread(&rows, sizeof(short), 1, fp);
  fread(&cols, sizeof(short), 1, fp);
  //printf("4\n");
  short* arr[cols];
  for (int i = 0; i < rows+1; i++){
    arr[i] = (short *) malloc(cols *sizeof(short));
  } 
    //printf("5\n");

  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      fread(&num, sizeof(short), 1, fp);
      arr[i][j] = num;
    }
  }
    //printf("6\n");

  for (int i = 0; i< cols; i++){
    arr[rows][i] = SHRT_MAX;
  }
  //pq create
  printf("6\n");
  FILE*fp2 = fopen(argv[2], "w");
  if (fp2 == NULL) {
    return EXIT_FAILURE;
  }
  printf("7\n");
  fprintf(fp2,"%hd %hd\n", rows, cols);
  
  for (int i = 0; i< rows; i++){
    for (int j = 0; j< cols; j++){
      fprintf(fp2,"%hd", arr[i][j]);
      if(j != cols-1){
        fprintf(fp2," ");
      }
    }
    fprintf(fp2,"\n");
  }
  fclose(fp2);
  //init;
  int *ind = (int *) malloc (sizeof(int)*rows*cols);
  int *prev = (int *)malloc(sizeof(int)*rows*cols);
  //set prev index
  int ctCols= 0;
  int ctRows= 0;

  int * x = (int*)malloc(sizeof(int)*rows*cols);
  int * y = (int*)malloc(sizeof(int)*rows*cols);
  for (int i = 0; i< (rows*cols); i++){
    prev[i] = -2;
    ind[i] = i;
   if(ctCols == cols){
     ctCols = 0;
     ctRows++;
   }
   x[i] = ctCols++;
   y[i] = ctRows;
    
  }
  //int el, p;
  //int xc, yc;
  minHeap *heap = mallocHeap(rows,cols);
  //heap->d[0] = 0;
  //prev[0] = -1;
  //pop(heap, ind, &el,&p );
  //int endNode;
  //int pred= endNode;
  //set(heap, 1, rows, cols, ind, prev );
  //djik(heap, arr, rows, cols, ind, prev, x, y);
  //short end = fastestEnd( heap, ind, rows, cols, arr, x, y, &time);
  for (int i = (rows-1)*cols; i < rows*cols; i++){
    heap->d[i] = 0;
    heapUp(heap, i, ind);
  }
  djik(heap, arr, rows, cols, ind, prev, x, y);
  /*while(pred != -1){
    pred = prev[pred]
  }
*/

  //driver
  //FILE*fp2 = fopen(argv[2], "w");
  //FILE*fp3 = fopen(argv[3], "w");
  //fwrite(&cols, sizeof(short),1, fp2);


  //free
  //file writing::
  FILE*fp3 = fopen(argv[3], "w");
  int value;
  fwrite(&cols, sizeof(short), 1, fp3);
  //int current;
  //int next;
  int shortest = SHRT_MAX;
  int shortestInd;
  for(int i = 0; i < cols; i++){
    value = heap->d[ind[i]]+arr[0][i];
    //heap->d[ind[i]] = heap->d[ind[i]]+arr[0][i];
    
    fwrite(&value, sizeof(int), 1, fp3);
   if (value<shortest){
    shortestInd = i;
    shortest = value;}
    
  }
  
  fclose(fp3);

  FILE*fp4 = fopen(argv[4], "w");
  int i=0;
  int* pathInd = (int*) malloc(sizeof(int) * rows*cols);
  //pathInd[0] = shortestInd;
  while(prev[shortestInd] != -2){
    pathInd[i++] = shortestInd;
    shortestInd = prev[shortestInd];
  }
  int iplusone = i+1;
  pathInd[i] = shortestInd;
  int xcoord, ycoord;
  fwrite(&shortest, sizeof(int), 1, fp4);
  //printf("%d\n", shortest );
  //printf("%d\n", iplusone);
  fwrite(&iplusone, sizeof(int), 1, fp4);
  //int numb;

  for(int j = 0; j <= i; j++){
    //i//nt numb = heap->el[pathInd[j]];
    oneTwo(pathInd[j], &xcoord, &ycoord, x, y);
    fwrite(&ycoord, sizeof(short), 1, fp4);
    //printf("%d %d \n", ycoord, xcoord);
    fwrite(&xcoord, sizeof(short), 1, fp4);
  }
  fclose(fp4);
  free(pathInd);
  free(x);
  free(y);
  free(ind);
  free(prev);
  for (int i = 0; i< rows+1; i++){
    free(arr[i]);
  }
  free(heap->d);
  free(heap->el);
  free(heap);
  fclose(fp);
  return EXIT_SUCCESS;
}


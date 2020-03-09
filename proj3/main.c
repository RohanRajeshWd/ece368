#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
int main(int argc, char *argv[]){
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
  /*calloc = typeArr[size-1] = wArr[size-1] = hArr[size-1] = lArr[size-1]=fgetc(fp); //malloc this*/
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
      /*printf(" %d  ", wArr[j]);
      printf("\n");
      printf(" %d  ", hArr[j]);
      */
  }
}

#include <stdio.h>

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
  //typeArr[size-1] = lenArr[size-1] = wArr[size-1] = lArr[size-1]=fgetc(fp); //malloc this
  fseek(fp,0,SEEK_SET);
  int line = 1;
  int i;
  
  for ( c = fgetc(fp); c !=EOF; c = fgetc(fp)){
    if(c == '('){
    inPar = 1;//open parenthises
    }
    if(c ==')'){
      inPar = 0;//close parenthises
      comma = 0;
    }
    if(c == 'V'){ //case vert 
      typeArr[size-line] = 1;
      lenArr[size-line] = wArr[size-line] = lArr[size-line]= 
    }
    if(c == 'H'){ //case horiz
      typeArr[size-line] = 2;
      lenArr[size-line] = wArr[size-line] = lArr[size-line]= 
    }
    if(c == '\n'){
      //newLine
      line++;
    }
    if( c == ','){
      comma = 1;
    }
    if (isdigit(c) && inPar ==0){//label of leaf
        num = stoi(c);
        while(c !='('){
            i++
            num = 10*num+stoi(c);
        }
    typeArr[size-line] = num;
    num = 0;
        
    }   
    if((isdigit(c))&& inPar ==1 && comma == 0){//length
    
        
    }
    if((isdigit(c))&& inPar ==1 && comma == 1){//width
    }


  
  }



  fclose(fp);
  printf("%d \n",size);

}

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<shell_array.h>


long* Array_Load_From_File(char*filename, int*size)
{
 FILE*fp=fopen("filename", "r");
 char imp;
 fseek(fp,0,SEEK_END);
 int len = ftell(fp);
 fseek(fp,0,SEEK_SET);
 int numInt = len/32;
 malloc(

 

}

#include <stdio.h>
int main(int argc,char ** argv){
  FILE *fp =fopen("demo","r");
  char pinaks[500];
  int kati=1;
  int i=0;
  if(!fp)
    printf("gamoto\n");
  else
    while(kati!=0){
      kati=fread(pinaks,sizeof(char),499,fp);
      if(i%10==0)
	printf("kati ginente \n");
      i++;
    }
  fclose(fp);  
  return 0;
}

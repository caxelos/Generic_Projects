#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
void check(){
	long mnimi;
	mnimi=syscall(353);                                  
        printf("i mnimi einai %lu \t",mnimi);
        mnimi=syscall(354);
        printf("i eleutheri mimi einai %lu\n",mnimi);

}

#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
using namespace std;
int main(int argc,char* argv[])
{
    FILE* fp=fopen(argv[1],"r+");
    //文件流的底层是依赖于文件类型FILE的
    //write(fp->_fileno,"hello",5);

    //面向接口编程
    write(fileno(fp),"hello",5);//fileno(fp)可以把文件流的FILE*转换为它对应的文件描述法
    fclose(fp);
    return 0;
}
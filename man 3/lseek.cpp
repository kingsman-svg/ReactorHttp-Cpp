#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
using namespace std;

int main(int argc,char* argv[])
{
    int fd = open(argv[1],O_RDWR);
    write(fd,"hello",5);
    //lseek：偏移
    //SEEK_SET文件开头    SEEK_CUR文件当前位置     SEEK_END文件结尾
    lseek(fd,-1,SEEK_CUR);
    write(fd,"0",1);
    return 0;
}
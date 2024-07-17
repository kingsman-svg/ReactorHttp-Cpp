#include<iostream>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
using namespace std;

int main(int argc,char* argv[])
{
    int fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0644);
    if(fd==-1){
        perror("open");
        exit(1);
    }

    ftruncate(fd,4);
    //建立共享内存映射
    char* memp;
    memp = (char*)mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(memp==MAP_FAILED){
        perror("mmap");
        exit(1);
    }

    strcpy(memp,"xxxxxxx"); //写mmap文件
    cout<<memp<<endl;   //读mmap文件

    if(munmap(memp,4) == -1)
    {
        //释放内存映射
        perror("munmap");
        exit(0);
    }

    close(fd);

    return 0;
}

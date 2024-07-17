#include<sys/mman.h>
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

using namespace std;

//mmap与munmap:在磁盘和内存之间建立和释放映射

//void* mmap(void* addr,size_t length,int prot,int flags,int fd,off_t offset);
//int munmap(void* addr,size_t length)

int main(int argc,char* argv[])
{
    int fd = open(argv[1],O_RDWR);
    if(fd==-1) perror("open");
    //建立映射
    char* p = static_cast <char*> (mmap(NULL,5,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0));
    if(p==MAP_FAILED) perror("mmap");//mmap失败返回的不是NULL,是MAP_FAILED 
    for(int i=0;i<5;i++)
    {
        cout<<*(p+i)<<" ";
    }
    cout<<endl;
    munmap(p,5);
    close(fd);
    return 0;
}
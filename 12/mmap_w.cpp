#include<iostream>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/fcntl.h>
#include<string.h>
using namespace std;
struct student {
    int id;
    char name[256];
    int age;
};

int main(int argc,char* argv[])
{
    student stu = {1,"xiaoming",16};

    int fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0644);

    ftruncate(fd,sizeof(stu));

    student* p;

    p = (student*) mmap(NULL,sizeof(stu),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(p==MAP_FAILED){
        perror("mmap");
        exit(0);
    }

    close(fd);

    while(1)
    {
        memcpy(p,&stu,sizeof(stu));
        stu.id++;
        sleep(2);
    }
    munmap(p,sizeof(stu));

    return 0;
}
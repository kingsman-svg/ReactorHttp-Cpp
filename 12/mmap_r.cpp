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
    student stu;

    int fd = open(argv[1],O_RDONLY);

    student* p;

    p = (student*) mmap(NULL,sizeof(stu),PROT_READ,MAP_SHARED,fd,0);
    if(p==MAP_FAILED){
        perror("mmap");
        exit(0);
    }

    close(fd);

    while(1)
    {
        cout<<p->name<<" "<<p->age<<" "<<p->id<<endl;
        sleep(2);
    }
    munmap(p,sizeof(stu));

    return 0;
}
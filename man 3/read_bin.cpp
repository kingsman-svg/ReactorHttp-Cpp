#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

using namespace std;
int main(int argc,char* argv[])
{
    int fd = open(argv[1],O_RDWR);
    int data;
    ssize_t sret= read(fd,&data,sizeof(int));
    cout<<sret<<endl;
    return 0;
}
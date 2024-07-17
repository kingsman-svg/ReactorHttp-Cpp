#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<iostream>
using namespace std;

int main(int argc,char* argv[])
{
    int fd = open(argv[1],O_WRONLY);
    if(fd==-1) perror("open");
    else cout<<"fd=="<<fd;
    return 0;
}
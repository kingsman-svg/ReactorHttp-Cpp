#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
using namespace std;
int main(int argc,char* argv[])
{
    int fd = open(argv[1],O_RDWR);
    if(fd==-1) perror("open");
    char buf[8]={0};
    ssize_t sret = read(fd,buf,5);
    if(sret==-1) perror("read");
    else cout<<sret<<" "<<buf<<endl;

    close(fd);
    return 0;
    
}
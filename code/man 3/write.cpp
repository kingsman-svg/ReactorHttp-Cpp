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
    if(fd==-1)
    {
   	    perror("open");
    }
    char buf[]="hello world";
    ssize_t sret = write(fd,buf,strlen(buf));
    if(sret==-1)
    {
        perror("write");
    }
    else{
        cout<<"sret="<<sret<<endl;
    }
    
    close(fd);
    return 0;
}




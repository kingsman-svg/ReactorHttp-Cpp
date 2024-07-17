#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<iostream>
using namespace std;

int main(int argc,char* argv[])
{
    int fd = open(argv[1],O_WRONLY|O_CREAT,0666);
    if(fd==-1)
    {
        perror("open failure");
        return 1;
    }
    else{
        cout<<fd<<endl;
    }
    return 0;
}
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
using namespace std;

int main(int argc,char* argv[])
{
    int fdw=open(argv[1],O_WRONLY);
    if(fdw==-1)perror("open");
    cout<<"write side is open !"<<"\n";
    sleep(5);
    cout<<"sleep over!"<<endl;
    write(fdw,"hello",5);
    close(fdw);
    return 0;
}
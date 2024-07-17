#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
using namespace std;

int main(int argc,char* argv[])
{
    int fdr = open(argv[1],O_RDONLY);
    if(fdr==-1) perror("open");
    cout<<"read side is open!"<<"\n";
    char buf[4096]={0};
    ssize_t sret = read(fdr,buf,sizeof(buf));
    if(sret==-1) perror("read");
    else cout<<"sret="<<sret<<endl;
    close(fdr);
    return 0;
}

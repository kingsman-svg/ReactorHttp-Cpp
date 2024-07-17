#include<sys/select.h>
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;

// ./1.out 1.pipe
int main(int argc,char* argv[])
{
    int fdr = open(argv[1],O_RDWR);//read
    if(fdr==-1) perror("open fdr");
    int fdw = open(argv[1],O_RDWR);
    if(fdw==-1) perror("open fdw");

    char buf[4096];
    fd_set rdset,wrset;
    int cnt=0;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_ZERO(&wrset);
        FD_SET(fdr,&rdset);
        FD_SET(fdw,&wrset);
        int ret = select(fdw+1,&rdset,&wrset,NULL,NULL);
        cout<<"ret="<<ret<<endl;
        if(FD_ISSET(fdr,&rdset))
        {
            read(fdr,buf,2048);
            cout<<"read ready,cnt="<<cnt<<endl;
            cnt++;
        }
        if(FD_ISSET(fdw,&wrset))
        {
            write(fdw,buf,4096);
            cout<<"write ready,cnt="<<cnt<<endl;
            cnt++;
        }
        sleep(1);
    }

    return 0;
}

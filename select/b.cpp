#include<sys/select.h>
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
using namespace std;

// ./a.out 1.pipe 2.pipe
int main(int argc,char* argv[])
{
    int fdw = open(argv[1],O_WRONLY);
    int fdr = open(argv[2],O_RDONLY);
    fd_set rset;
    //fd_set wset;
    char buf[4096];
    struct timeval timeout;
    while(1)
    {
        memset(buf,0,sizeof(buf));
        FD_ZERO(&rset);
        //FD_ZERO(&wset);
        FD_SET(fdr,&rset);
        FD_SET(STDIN_FILENO,&rset);
        timeout.tv_sec=1;
        timeout.tv_usec=0;
        int sret = select(fdr+1,&rset,NULL,NULL,NULL);
        if(sret)
        {
            if(FD_ISSET(fdr,&rset))
            {
                read(fdr,buf,sizeof(buf));
                cout<<buf<<endl;
            }

            if(FD_ISSET(STDIN_FILENO,&rset))
            {
                int rret=read(STDIN_FILENO,buf,sizeof(buf));
                if(rret)
                {
                    write(fdw,buf,strlen(buf));
                }
            }
        }
    }
    return 0;

}
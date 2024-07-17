#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<iostream>
using namespace std;
//ftruncate可以产生文件空洞
int main(int argc,char* argv[])
{
    int fd = open(argv[1],O_RDWR);
    int ret = ftruncate(fd,5);
    cout<<ret<<endl;
    return 0;

}
#include<iostream>
#include<sys/types.h>
#include<unistd.h>
using namespace std;

int main()
{
    cout<<"pid="<<getpid()<<",pgid="<<getpgid(0)<<endl;
    return 0;
}
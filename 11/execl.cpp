#include<iostream>
#include<unistd.h>
using namespace std;

int main(int argc,char* argv[])
{
    cout<<"running..."<<endl;
    execl("add.out","./add.out","3","4",NULL);
    perror("execl");
    return 0;
}

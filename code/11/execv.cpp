#include<iostream>
#include<unistd.h>
using namespace std;

int main(int argc,char* argv[])
{
    cout<<"execv is runnning..."<<endl;
    char* const args[]={(char* const)"./add.out",(char* const)"4",(char* const)"5",NULL};
    execv("add.out",args);
    return 0;
}

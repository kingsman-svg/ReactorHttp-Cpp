#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

using namespace std;
int main()
{
    cout<<"stdin fileno = "<<fileno(stdin)<<endl;
    cout<<"stdout fileno = "<<fileno(stdout)<<endl;
    cout<<"stderr fileno = "<<fileno(stderr)<<endl;
    return 0;
}

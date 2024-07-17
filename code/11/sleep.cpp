#include<iostream>
#include<unistd.h>
using namespace std;
int main()
{
    cout<<"sleeping!"<<endl;
    sleep(5);
    cout<<"wake up!"<<endl;
    return 0;
}
#include<pthread.h>
#include<iostream>
using namespace std;

int main()
{
    pthread_t id;
    id = pthread_self();
    cout<<"pthread id = "<<id<<endl;
    return 0;
    
}
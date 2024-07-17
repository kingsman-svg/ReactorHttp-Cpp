#include<iostream>
#include<unistd.h>
#include<pthread.h>
using namespace std;

pthread_mutex_t mutex;
pthread_t tid;


void* pthread_func(void* arg)
{
    cout<<"child pthread!"<<endl;
    return nullptr;
}



int main()
{
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&tid,nullptr,pthread_func,nullptr);
    while(1){
        pthread_mutex_lock(&mutex);
        cout<<"parent!"<<endl;
        pthread_mutex_unlock(&mutex);
        sleep(2);

    }
    pthread_join(tid,nullptr);

}
#include<pthread.h>
#include<iostream>
#include<unistd.h>
#include<string.h>
using namespace std;

void* tfun(void* arg)
{
    int i = (int) arg;
    sleep(i);

    if(i==2){
        //exit(0);退出当前进程
        //return NULL;  表示回到调用者那里去
        pthread_exit(NULL);
    }    
    cout<<"thread num:"<<i<<endl;
}


int main()
{
    int i,ret;
    pthread_t tid;

    for(i=0;i<5;i++)
    {
        ret = pthread_create(&tid,NULL,tfun,(void*)i);//最好不要用解引用，地址空间会出问题
        if(ret!=0){
            cout<<"pthread_create err:"<<strerror(ret)<<endl;
        }
    }
}

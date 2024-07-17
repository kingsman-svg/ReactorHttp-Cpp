#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1, mutex2;
int shared_data = 0;

void *thread_func1(void *arg) {
    printf("Thread 1 started\n");

    // 获取 mutex1 锁
    pthread_mutex_lock(&mutex1);
    printf("Thread 1 acquired lock 1\n");

    // 更新共享数据
    shared_data++;
    printf("Thread 1 updated shared data: %d\n", shared_data);

    // 试图获取 mutex2 锁
    pthread_mutex_lock(&mutex2);
    printf("Thread 1 acquired lock 2\n");

    // 解锁
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    printf("Thread 1 finished\n");
    return NULL;
}

void *thread_func2(void *arg) {
    printf("Thread 2 started\n");

    // 获取 mutex2 锁
    pthread_mutex_lock(&mutex2);
    printf("Thread 2 acquired lock 2\n");

    // 更新共享数据
    shared_data++;
    printf("Thread 2 updated shared data: %d\n", shared_data);

    // 试图获取 mutex1 锁
    pthread_mutex_lock(&mutex1);
    printf("Thread 2 acquired lock 1\n");

    // 解锁
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    printf("Thread 2 finished\n");
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    // 初始化两个互斥锁
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);

    // 创建两个线程
    pthread_create(&tid1, NULL, thread_func1, NULL);
    pthread_create(&tid2, NULL, thread_func2, NULL);

    // 等待线程结束
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // 销毁互斥锁
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}
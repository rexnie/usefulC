/*
 * One example to demo flamegraph
 *
 * Copyright (c) Barry Song
 *
 * Licensed under GPLv2
 * ref: https://mp.weixin.qq.com/s?__biz=MzAwMDUwNDgxOA==&mid=2652662668&idx=1&sn=3f0ff6c6028037be7115f80e215f39e7&scene=21#wechat_redirect
 */
#include <stdio.h>
#include <pthread.h>

int func_d(void)
{
    int i;
    for(i=0;i<50000;i++)
        ;
}

int func_a(void)
{
    int i;
    for(i=0;i<100000;i++)
        ;
    func_d();
}

int func_b(void)
{
    int i;
    for(i=0;i<200000;i++)
        ;
}

int func_c(void)
{
    int i;
    for(i=0;i<300000;i++);
}

void* thread_fun(void* param)
{
    while(1) {
        int i;
        for(i=0;i<100000;i++);

        func_a();
        func_b();
        func_c();
    }
}

int main(void)
{
    pthread_t tid1,tid2;
    int ret;

    ret=pthread_create(&tid1,NULL,thread_fun,NULL);
    if(ret==-1) {
        perror("pthread_create tid1");
        return -1;
    }

    ret=pthread_create(&tid2,NULL,thread_fun,NULL);
    if(ret==-1) {
        perror("pthread_create tid2");
        return -1;
    }

    if(pthread_join(tid1,NULL)!=0){
        perror("pthread_join tid1");
    }

    if(pthread_join(tid2,NULL)!=0){
        perror("pthread_join tid2");
        return -1;
    }

    return 0;
}

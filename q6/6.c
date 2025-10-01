/*
==============================================================================================================================
Name: 6.c
Author: Suchir Okram
Description: Write a simple program to create three threads.
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<pthread.h>
void show_thread(void) {
    printf("This is a thread\n");
}

int main(){
    pthread_t thrd1, thrd2, thrd3;
    pthread_create(&thrd1, NULL, (void *)show_thread, NULL);
    pthread_create(&thrd2, NULL, (void *)show_thread, NULL);
    pthread_create(&thrd3, NULL, (void *)show_thread, NULL);
    pthread_join(thrd1, NULL);
    pthread_join(thrd2, NULL);
    pthread_join(thrd3, NULL);
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q6$ gcc 6.c -o 6
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q6$ ./6
    This is a thread
    This is a thread
    This is a thread
==============================================================================================================================
*/
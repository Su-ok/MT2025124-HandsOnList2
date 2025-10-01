/*
==============================================================================================================================
Name: 7.c
Author: Suchir Okram
Description: Write a simple program to print the created thread ids.
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<pthread.h>
#include<stdio.h>
void show_thread(void) {
    printf("This is a thread: %ld\n", pthread_self());
}

int main(){
    pthread_t thrd1, thrd2, thrd3;

    pthread_create(&thrd1, NULL, (void*)show_thread, NULL);
    pthread_create(&thrd2, NULL, (void*)show_thread, NULL);
    pthread_create(&thrd3, NULL, (void*)show_thread, NULL);
    pthread_join(thrd1, NULL);
    pthread_join(thrd2, NULL);
    pthread_join(thrd3, NULL);
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q7$ gcc 7.c -o 7
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q7$ ./7
    This is a thread: 129631529203392
    This is a thread: 129631512417984
    This is a thread: 129631520810688

==============================================================================================================================
*/
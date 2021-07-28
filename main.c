#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kfifo.h"


int main(){
    
    unsigned char a[100];
    unsigned char b[200];

    for(int i = 0; i != 100; i++){
        a[i] = i;
    }

    struct kfifo* q = kfifo_alloc(100);

    kfifo_put(q,a,100);

    kfifo_get(q,b,200);

    if(memcmp(a,b,100))  printf("not equal 1\n");
    
    kfifo_put(q,a,100);

    kfifo_get(q,b,200);

    if(memcmp(a,b,100))  printf("not equal 2\n");

    q->in = q->out = -10;

    kfifo_put(q,a,100);

    kfifo_get(q,b,200);

    if(memcmp(a,b,100))  printf("not equal 3\n");

    printf("done %d  %d  %d\n", q->in,q->out, q->size);

}
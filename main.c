#include"heap.h"
#include<stdio.h>
#include<stdlib.h>
void main()
{
    void* heap=make_heap();
    int *p=(int*)my_malloc(10,heap);
    int *t=(int*)my_malloc(25,heap);
    my_free(t,heap);    //it is the responsibilty of programmer to make t point to null
    t=NULL;
    int *q=(int*)my_malloc(5,heap);
    int *s=(int*)my_malloc(20,heap);
    display_heap(heap);
    free(heap);    //deallocating the space which was used to implement the heap
}
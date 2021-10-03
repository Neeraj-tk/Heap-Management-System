#include<stdio.h>
#include<stdlib.h>
#include"heap.h"
void* make_heap()
{
    block *head=malloc(HEAP_SIZE);
    head->size=HEAP_SIZE-sizeof(block);
    head->free=1;
    head->prev=NULL;
    head->next=NULL;
    return head;
}
void split_memory(block* ptr,int req_size)
{
    block *new_block=(void*)((void*)ptr+req_size+sizeof(block));
    new_block->prev=ptr;
    new_block->next=ptr->next;
    new_block->size=ptr->size-req_size-sizeof(block);
    new_block->free=1;
    ptr->next=new_block;
    ptr->size=req_size;
    ptr->free=0;
}
void* my_malloc(int req_size,void* heap)
{
    block *ptr=heap;
    void* result;
    while(ptr && (ptr->size < req_size || ptr->free==0))
    {
        ptr=ptr->next;
    }
    if(ptr==NULL)
    {
        printf("\nMEMORY IS FULL");
    }
    else
    {
        ptr->free=0;
        if(ptr->size-req_size>sizeof(block))   // we only split the block if space remaining is sufficient enough to accomodate another block
        {
            split_memory(ptr,req_size);
        }
        result=(void*)++ptr;   //by incrementing we make it point to the location beyond metadata and allows user to access that part(i.e pointer arithmetic)
        printf("\nSUCCESSFULLY ALLOCATED MEMORY OF SIZE %d",req_size);
    }
    return ptr;

}
block* merge(block *ptr1,block *ptr2)
{
    ptr1->next=ptr2->next;
    if(ptr2->next)
    {
        ptr2->next->prev=ptr1;
    }
    ptr1->size+=(ptr2->size+sizeof(block));
    return ptr1;
}
void my_free(void *ptr,void *heap)
{
    if(ptr>=heap && ptr<=heap+HEAP_SIZE)   //checking whether the address given by user lies within the heap created by us.
    {
        block *blk=ptr;
        --blk;     //by decrementing blk we make it point to the metadata part(i.e pointer arithmetic)
        blk->free=1;
        int size=blk->size;
        if(blk->prev && blk->next && blk->prev->free==1 && blk->next->free==1)
        {
            blk=merge(blk->prev,blk);
            merge(blk,blk->next);
        }
        else if(blk->prev && blk->prev->free==1)
        {
            merge(blk->prev,blk);
        }
        else if(blk->next && blk->next->free==1)
        {
            merge(blk,blk->next);
            
        }
        printf("\nSUCCESSFULLY FREED MEMORY OF SIZE %d ",size);
    }
    else
    {
        printf("\nTHIS MEMORY IS NOT WITHIN THE HEAP");
    }
}
void display_heap(void*heap)
{
    block *ptr=heap;
    printf("\nBLOCK-SIZE\tAVAILABILITY\tADDRESS");
    while(ptr)
    {
        printf("\n%d\t\t%d\t\t%p",ptr->size,ptr->free,ptr);
        ptr=ptr->next;
    }
}
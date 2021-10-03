#define HEAP_SIZE 200
// structure defintion of metadata
typedef struct block_tag{
    int size;  //size of the block
    int free;  //tells whether block is allocated or not
    struct block_tag *next;  // points to the metadata of next block
    struct block_tag *prev;  //points to the metadata of prev block
}block;
void* make_heap(); //function used to create heap by calling the malloc function
void display_heap(void *heap); //function used to display how many blocks are inthe heap and their allocation status
void split_memory(block *ptr,int req_size);  //function used to divide a block into 2
block* merge(block *ptr1,block *ptr2); //function used to free a particular block
void* my_malloc(int req_size,void *heap);  //function used to allocate memory inthe heap created
void my_free(void *ptr,void *heap);

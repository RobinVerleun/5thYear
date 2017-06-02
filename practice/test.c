#include <pthread.h>
#include <stdio.h>
// a simple pthread example 
// compile with -lpthreads

pthread_t threads[3];
// create the function to be executed as a thread
void *thread(void *ptr)
{
    int type = (int) ptr;
    fprintf(stderr,"Thread - %d\n",type);
    return  ptr;
}

int main(int argc, char **argv)
{
    // create the thread objs
    int i;
    for(i = 0; i < 3; i++) {
      pthread_create(&threads[i], NULL, *thread, (void *) i);
    }
    // wait for threads to finish
    for (i =0; i < 3; i++) {
      pthread_join(threads[i], NULL);
    }
    return 0;
}
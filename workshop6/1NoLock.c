#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <omp.h>

int booksAvailable = 3;
omp_lock_t lock;

void borrower(int p)
{
    for (int i = 0; i < 10; i++)
    {
        omp_set_lock(&lock);
        printf("Borrower %d wants to borrow a book. ", p);
        printf("Books available = %d\n", booksAvailable);
        if (booksAvailable > 0)
        {
            printf("Borrower %d gets a book. ", p);
            booksAvailable--;
            printf("Books available = %d\n", booksAvailable);
            usleep(10000); // Reading book
            printf("Borrower %d is returning a book. ", p);
            booksAvailable++;
            printf("Books available = %d\n", booksAvailable);
        }
        else
        {
            printf("No books available for Borrower %d.\n", p);
        }
        omp_unset_lock(&lock);
        usleep(10000);
    }
}

int main()
{
    // omp_init_lock(&lock);

#pragma omp parallel num_threads(6)
    {
        int tid = omp_get_thread_num() + 1;
        borrower(tid);
    }

    // omp_destroy_lock(&lock);

    return 0;
}

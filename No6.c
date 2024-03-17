#include <stdio.h>
#include <mpi.h>

int prime(int num)
{
    if (num <= 1)
        return 0;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    int rank, size;
    int rangestart = 1, rangefinish = 10000;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int partialsize = (rangefinish - rangestart + 1) / size;
    int remainder = (rangefinish - rangestart + 1) % size;
    int start = rangestart + rank * partialsize + (rank < remainder ? rank : remainder);
    int end = start + partialsize + (rank < remainder ? 1 : 0) - 1;

    printf("%s : Prime numbers between %d and %d are :\n", argv[0], rangestart, rangefinish);

    for (int i = start; i <= end; i++)
    {
        if (prime(i))
        {
            printf("%s : %d\n", argv[0], i);
        }
    }

    MPI_Finalize();

    return 0;
}

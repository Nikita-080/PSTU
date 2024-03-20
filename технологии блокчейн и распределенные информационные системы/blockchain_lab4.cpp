#include <mpi.h>
#include <iostream>
#include <chrono>

const int N = 2000;
const int RND_START = 1;
const int RND_END = 9;

void PrintArr(int* arr)
{
    std::cout << "=====\n";
    for (int i = 0; i < N * N; i++)
    {
        std::cout << arr[i] << ' ';
        if ((i + 1) % N == 0) std::cout << std::endl;
    }
    std::cout << "=====\n";
}

int main(int argc, char** argv)
{
    int size, rank, block;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    block = (N * N) / (size - 1) + 1;
    int* a = new int[N * N] {};
    int* b = new int[N * N] {};
    int* c = new int[N * N] {};
    int* data = new int[block] {};

    if (rank == 0)
    {
        for (int i = 0; i < N * N; i++)
        {
            a[i] = rand() % (RND_END - RND_START + 1) + RND_START;
            b[i] = rand() % (RND_END - RND_START + 1) + RND_START;
        }

        if (N < 10)
        {
            PrintArr(a);
            PrintArr(b);
        }

        auto start_time = std::chrono::steady_clock::now();

        for (int i = 1; i < size; i++)
        {
            MPI_Send(a, N * N, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(b, N * N, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(data, block, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int j = (i - 1) * block; j < std::min(N * N, (i - 1) * block + block); j++) c[j] = data[j-(i-1)*block];
        }

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

        if (N < 10) PrintArr(c);

        std::cout << "Time " << elapsed_ns.count() << " s\n";
    }
    else
    {
        MPI_Recv(a, N * N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(b, N * N, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = (rank - 1) * block; i < std::min(N * N, (rank - 1) * block + block); i++)
        {
            int sum = 0;
            int row = i / N;
            int col = i % N;
            for (int j = 0; j < N; j++) sum += a[N * row + j] * b[N * j + col];
            data[i-(rank-1)*block] = sum;
        }

        MPI_Send(data, block, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}


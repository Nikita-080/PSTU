#include <mpi.h>
#include <iostream>
#include <chrono>

const int N = 2000;
const int RND_START = 1;
const int RND_END = 9;

void Print(double* a, double* b)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cout << a[i*N+j] << "*x" << j;
            if (j < N - 1)
                std::cout << " + ";
        }
        std::cout << " = " << b[i] << std::endl;
    }
}

int main(int argc, char** argv)
{
    int size, rank;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    size = std::min(size - 1, N) + 1;
    int num_lines = N % (size-1) == 0 ? N / (size-1) : N / (size-1) + 1;
    
    double* A = new double[N * N] {};
    double* X = new double[N] {};
    double* B = new double[N] {};
    double* Result = new double[N] {};

    if (rank == 0)
    {
        for (int i = 0; i < N * N; i++) A[i] = rand() % (RND_END - RND_START + 1) + RND_START;
        for (int i = 0; i < N; i++) X[i] = rand() % (RND_END - RND_START + 1) + RND_START;

        for (int i = 0; i < N; i++)
        {
            double sum = 0;
            for (int j = 0; j < N; j++) sum += A[i * N + j] * X[j];
            B[i] = sum;
        }

        if (N < 10) Print(A, B);
        
        auto start_time = std::chrono::steady_clock::now();
        
        double* block_a = new double[num_lines * N] {};
        double* block_b = new double[num_lines] {};
        
        for (int i = 1; i < size; i++)
        {
            int current_num_lines = num_lines;
            if (N % (size-1) != 0 && i == size - 1) current_num_lines = N % num_lines;
            for (int j = 0; j < current_num_lines * N; j++) block_a[j] = A[(i - 1) * (N * num_lines) + j];
            for (int j = 0; j < current_num_lines; j++) block_b[j] = B[(i - 1) * num_lines + j];
            MPI_Send(block_a, N * num_lines, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(block_b, num_lines, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
        }
        MPI_Recv(Result, N, MPI_DOUBLE, 1, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);

        if (N < 10)
        {
            std::cout << "Expected:\n";
            for (int i = 0; i < N; i++) std::cout << X[i] << ' ';
            std::cout << std::endl;
            std::cout << "Recieved:\n";
            for (int i = 0; i < N; i++) std::cout << Result[i] << ' ';
            std::cout << std::endl;
        }
        std::cout << "Time " << elapsed_ns.count() << " s\n";
    }
    else
    {
        if (rank < size)
        {
            int current_num_lines = num_lines;
            if (N % (size-1) != 0 && rank == size - 1) current_num_lines = N % num_lines;

            double** arr{ new double* [current_num_lines] {} };
            double* block_a = new double[num_lines * N] {};
            double* block_b = new double[num_lines] {};
            double* main_line = new double[N + 1] {};

            int block_start = (rank - 1) * num_lines;
            int block_end = block_start + current_num_lines;

            MPI_Recv(block_a, N * num_lines, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(block_b, num_lines, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int i = 0; i < current_num_lines; i++)
            {
                arr[i] = new double[N + 1] {};
                for (int j = 0; j < N; j++) arr[i][j] = block_a[i * N + j];
                arr[i][N] = block_b[i];
            }
            for (int i = 0; i < N - 1; i++)
            {
                if (i < block_start) MPI_Recv(main_line, N + 1, MPI_DOUBLE, i / num_lines + 1, 100 + i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                else if (i >= block_end) break;
                else
                {
                    main_line = arr[i - block_start];
                    for (int address = rank + 1; address < size; address++) MPI_Send(main_line, N + 1, MPI_DOUBLE, address, 100 + i, MPI_COMM_WORLD);
                }
                int start = i < block_start ? 0 : i - block_start + 1;
                double pivot = main_line[i];
                for (int j = start; j < current_num_lines; j++)
                {
                    double lik = arr[j][i] / pivot;
                    for (int k = i; k < N; k++) arr[j][k] -= lik * main_line[k];
                    arr[j][N] -= lik * main_line[N];
                }
            }

            double* x = new double[N] {};
            if (rank != size - 1) MPI_Recv(x, N, MPI_DOUBLE, rank + 1, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int k = current_num_lines - 1; k >= 0; k--)
            {
                double s = 0;
                for (int i = block_start + k + 1; i < N; i++) s += arr[k][i] * x[i];
                x[k + block_start] = (arr[k][N] - s) / arr[k][k + block_start];
            }
            MPI_Send(x, N, MPI_DOUBLE, rank - 1, 3, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
}


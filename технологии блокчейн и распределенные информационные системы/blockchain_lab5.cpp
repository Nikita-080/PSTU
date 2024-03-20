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
    int size, rank, block;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double* A = new double[N * N];
    double* X = new double[N];
    double* B = new double[N];
    double* Result = new double[N];

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

        for (int k = 0; k < N - 1; k++)
        {
            double pivot = A[k * N + k];
            int block = (N - k - 1) / (size - 1) + 1;
            double* data_a = new double[block * N] {};
            double* data_b = new double[block] {};

            for (int i = 1; i < size; i++)
            {
                if (block * (i - 1) + k + 1 < N)
                {
                    MPI_Send(A, N * N, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
                    MPI_Send(B, N, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
                    MPI_Send(&pivot, 1, MPI_DOUBLE, i, 2, MPI_COMM_WORLD);
                }
            }
            for (int i = 1; i < std::min(size, N - k); i++)
            {
                if (block * (i - 1) + k + 1 < N)
                {
                    MPI_Recv(data_a, block * N, MPI_DOUBLE, i, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    MPI_Recv(data_b, block, MPI_DOUBLE, i, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    for (int j = 0; j < block * N; j++)
                    {
                        int row = (i - 1) * block + j / N + k + 1;
                        if (row < N)
                        {
                            int col = j % N;
                            A[row * N + col] = data_a[j];
                        }
                    }
                    for (int j = 0; j < block; j++)
                    {
                        int row = (i - 1) * block + j + k + 1;
                        if (row < N)
                        {
                            B[row] = data_b[j];
                        }
                    }
                }
            }
            delete[] data_a;
            delete[] data_b;
        }
        for (int k = N - 1; k >= 0; k--)
        {
            double s = 0;
            for (int i = k + 1; i < N; i++) s += A[k * N + i] * Result[i];
            Result[k] = (B[k] - s) / A[k * N + k];
        }

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
        for (int i = 0; i < N - 1; i++)
        {
            int block = (N - i - 1) / (size - 1) + 1;
            if (block * (rank - 1) + i + 1 < N)
            {
                double pivot;
                double* data_a = new double[block * N] {};
                double* data_b = new double[block] {};
                MPI_Recv(A, N * N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(B, N, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&pivot, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (int j = 0; j < block; j++)
                {
                    int work_row = block * (rank - 1) + j + i + 1;
                    if (work_row < N)
                    {
                        double lik = A[work_row * N + i] / pivot;
                        for (int k = 0; k < N; k++)
                        {
                            data_a[j * N + k] = A[work_row * N + k];
                            if (k >= i) data_a[j * N + k] -= lik * A[i * N + k];
                        }
                        data_b[j] = B[work_row] - lik * B[i];
                    }
                }
                MPI_Send(data_a, block * N, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD);
                MPI_Send(data_b, block, MPI_DOUBLE, 0, 4, MPI_COMM_WORLD);
                delete[] data_a;
                delete[] data_b;
            }
        }

    }
    MPI_Finalize();
}


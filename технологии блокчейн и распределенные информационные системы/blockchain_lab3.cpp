
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <omp.h>

const int RND_START = 1;
const int RND_END = 10;
const int N = 1000;
const int MAX_THREADS = 16;
const long double EPS = 0.00001;


void Print(long double** a, long double* b)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cout << a[i][j] << "*x" << j;
            if (j < N - 1)
                std::cout << " + ";
        }
        std::cout << " = " << b[i] << std::endl;
    }
}


void FillRand2D(long double** arr)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) arr[i][j] = rand() % (RND_END - RND_START + 1) + RND_START;
    }
}
void FillRand1D(long double* arr)
{
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % (RND_END - RND_START + 1) + RND_START;
    }
}

long double* Solve(long double** A, long double* B, int t)
{
    long double* X = new long double[N];
    for (int k = 0; k < N - 1; k++) 
    {
        long double pivot = A[k][k];
#pragma omp parallel for num_threads(t)
        for (int i = k + 1; i < N; i++) 
        {
            long double lik = A[i][k] / pivot;
            for (int j = k; j < N; j++) A[i][j] -= lik * A[k][j];
            B[i] -= lik * B[k];
        }
    }
    for (int k = N - 1; k >= 0; k--) 
    {
        long double s = 0;
        int i;
        for (i = k + 1; i < N; i++) s+= A[k][i] * X[i];
        X[k] = (B[k] - s) / A[k][k];
    }
    return X;
}
int main()
{
    long double** A{ new long double* [N] {} };
    long double* X = new long double[N];
    long double* B = new long double[N];

    long double** A_copy{ new long double* [N] {} };
    long double* B_copy = new long double[N];
    long double* S = new long double[N];

    for (unsigned i{}; i < N; i++)
    {
        A[i] = new long double[N] {};
        A_copy[i] = new long double[N] {};
    }

    FillRand2D(A);
    FillRand1D(X);

    for (int i = 0; i < N; i++)
    {
        long double sum = 0;
        for (int j = 0; j < N; j++) sum += A[i][j] * X[j];
        B[i] = sum;
    }

    for (int t = 1; t <= MAX_THREADS; t++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                A_copy[i][j] = A[i][j];
            }
        }
        for (int i = 0; i < N; i++) B_copy[i] = B[i];

        auto start_time = std::chrono::steady_clock::now();
        S = Solve(A_copy, B_copy, t);
        auto end_time = std::chrono::steady_clock::now();

        auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        bool result = true;
        for (int i = 0; i < N; i++)
        {
            long double sum = 0;
            for (int j = 0; j < N; j++) sum += A[i][j] * S[j];
            if (abs(sum - B[i]) > EPS)
            {
                std::cout << "Error!!! " << sum << " " << B[i] << std::endl;
                result = false;
                break;
            }
        }
        std::cout << "Threads " << t << " time " << elapsed_ns.count() << " ms result " << std::boolalpha << result << "\n";
    }
}

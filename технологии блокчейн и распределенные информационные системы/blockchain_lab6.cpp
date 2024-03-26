#include <oneapi/tbb.h>
#include <iostream>
#include <chrono>
#include <cstdlib>

const int RND_START = 1;
const int RND_END = 9;
const int N = 4000;

void LineHandler(double* A, double* main_line, int current_k)
{
    double lik = A[current_k] / main_line[current_k];
    for (int j = current_k; j < N+1; j++) A[j] -= lik * main_line[j]; 
}

class TableHandler {
    double** arr_A;
    double* arr_main_line;
    int current_k;
public:
    void operator()(const oneapi::tbb::blocked_range<size_t>& r) const {
        for (int i = r.begin(); i < r.end(); i++)
            LineHandler(arr_A[i],arr_main_line,current_k);
    }
    TableHandler(double** A, double* main_line,int k)
    {
        arr_A = A;
        arr_main_line = main_line;
        current_k = k;
    }
};

void Print(std::string label, double** a)
{
    std::cout << "----------" << label << "----------" << std::endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cout << a[i][j] << "*x" << j;
            if (j < N - 1)
                std::cout << " + ";
        }
        std::cout << " = " << a[i][N] << std::endl;
    }
    for (int i = 0; i < 20 + label.size(); i++) std::cout << '-';
    std::cout << std::endl;
}


void FillRand2D(double** arr)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) arr[i][j] = rand() % (RND_END - RND_START + 1) + RND_START;
    }
}
void FillRand1D(double* arr)
{
    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % (RND_END - RND_START + 1) + RND_START;
    }
}

double* Solve(double** A)
{
    double* X = new double[N];
    for (int k = 0; k < N - 1; k++)
    {
        oneapi::tbb::parallel_for(oneapi::tbb::blocked_range<size_t>(k+1, N), TableHandler(A,A[k],k));
    }
    for (int k = N - 1; k >= 0; k--)
    {
        double s = 0;
        int i;
        for (i = k + 1; i < N; i++) s += A[k][i] * X[i];
        X[k] = (A[k][N] - s) / A[k][k];
    }
    return X;
}
int main()
{
    double** A{ new double* [N] {} };
    double* X = new double[N];
    double* Result = new double[N];

    for (int i=0; i < N; i++) A[i] = new double[N+1] {};

    FillRand2D(A);
    FillRand1D(X);

    for (int i = 0; i < N; i++)
    {
        double sum = 0;
        for (int j = 0; j < N; j++) sum += A[i][j] * X[j];
        A[i][N] = sum;
    }

    if (N < 10) Print("data",A);

    auto start_time = std::chrono::steady_clock::now();
    Result = Solve(A);
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    if (N < 10)
    {
        std::cout << "Expected:\n";
        for (int i = 0; i < N; i++) std::cout << X[i] << ' ';
        std::cout << std::endl;
        std::cout << "Recieved:\n";
        for (int i = 0; i < N; i++) std::cout << Result[i] << ' ';
        std::cout << std::endl;
    }

    std::cout << "Time " << elapsed_ns.count() << " ms\n";
}

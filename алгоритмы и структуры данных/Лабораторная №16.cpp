#include <iostream>
#include <vector>
using namespace std;
void PrintVector(vector<int> vec)
{
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;
}
void PrintSeries(vector<vector<int>> series)
{
	for (int i = 0; i < series.size(); i++)
	{
		cout << "(";
		for (int j = 0; j < series[i].size(); j++) cout << series[i][j] << " ";
		cout << ")";
	}
	cout << endl;
}
vector<int> MergeSeries(vector<int> ser1, vector<int> ser2)
{
	int i = 0, j = 0;
	vector<int> res;
	while (i < ser1.size() && j < ser2.size())
	{
	    if (ser1[i]<ser2[j])
        {
            res.push_back(ser1[i]);
			i++;
        }
        else
        {
            res.push_back(ser2[j]);
			j++;
        }
	}
	if (i < ser1.size()) for (int k=i;k<ser1.size();k++) res.push_back(ser1[k]);
	else if (j < ser2.size()) for (int k=j;k<ser2.size();k++) res.push_back(ser2[k]);
	return res;
}
vector<vector<int>> SplitToSeries(vector<int> vec)
{
	int i = 0;
	vector<vector<int>> res;
	while (i < vec.size())
	{
		vector<int> newSerie;
		newSerie.push_back(vec[i]);
		i++;
		while (i < vec.size() && vec[i - 1] < vec[i])
		{
			newSerie.push_back(vec[i]);
			i++;
		}
		res.push_back(newSerie);
	}
	return res;
}
vector<int> NaturalMergeSort(vector<int> vec)
{
	vector<vector<int>> series = SplitToSeries(vec);
	PrintSeries(series);
	while (series.size() > 1)
	{
		series.push_back(MergeSeries(series[0], series[1]));
		series.erase(series.begin(), series.begin() + 2);
		PrintSeries(series);
	}
	return series[0];
}
vector<int> BalancedMergeSort(vector<int> vec)
{
    if (vec.size()==1) return vec;
    else if (vec.size()==2)
    {
        if (vec[0]>vec[1]) swap(vec[0],vec[1]);
        return vec;
    }
    else
    {
        vector <int> new_vec1;
        vector <int> new_vec2;
        for (int i=0;i<vec.size()/2+1;i++) new_vec1.push_back(vec[i]);
        for (int i=vec.size()/2+1;i<vec.size();i++) new_vec2.push_back(vec[i]);
        return MergeSeries(BalancedMergeSort(new_vec1),BalancedMergeSort(new_vec2));
    }
}
void PrintFiles(vector<vector<int>> f1, vector<vector<int>> f2, vector<vector<int>>f3)
{
	cout << "F1 : ";
	PrintSeries(f1);
	cout << "F2 : ";
	PrintSeries(f2);
	cout << "F3 : ";
	PrintSeries(f3);
	cout << endl;
}
vector<int> DeleteEmptyElements(vector<int> vec,int num)
{
	for (int i = 0; i <num; i++) vec.pop_back();
	return vec;
}
void Fibbonachi(int numberOfSeries, int& size1, int& size2)
{
	size1 = 0;
	size2 = 1;
	while (size1 + size2 < numberOfSeries)
	{
		int t = size2;
		size2 = size2 + size1;
		size1 = t;
	}
}
vector<vector<int>> SplitToEqualSeries(vector<int> vec)
{
	int num=2; //кол-во элементов в серии
	vector<vector<int>> res;
	int i=0;
	vector<int> newSerie;
	while (i<vec.size())
    {
        if ((i+1)%num==0 || i==vec.size()-1)
        {
            newSerie.push_back(vec[i]);
            res.push_back(newSerie);
            newSerie.clear();
        }
        else newSerie.push_back(vec[i]);
        i++;
    }
	return res;
}
vector<vector<int>> MergeFiles(vector<vector<int>>& f1, vector<vector<int>>& f2)
{
	vector<vector<int>> res;
	int minimum = f1.size() < f2.size() ? f1.size() : f2.size();
	for (int i = 0; i < minimum; i++)
	{
		res.push_back(MergeSeries(f1[i], f2[i]));
	}
	f1.erase(f1.begin(), f1.begin() + minimum);
	f2.erase(f2.begin(), f2.begin() + minimum);
	return res;
}
vector<int> PolyphaseMergeSort(vector<int> vec)
{
	vector<vector<int>> series = SplitToEqualSeries(vec);
	int size1, size2;
	Fibbonachi(series.size(), size1, size2);
	vector<vector<int>> F1, F2, F3; // files
	cout << "Разделение на серии" << endl;
	PrintSeries(series);
	for (int i = 0; i < size1; i++) F1.push_back(series[i]);
	for (int i = size1; i < series.size(); i++) F2.push_back(series[i]);
	for (int i = series.size(); i < size1 + size2; i++)
	{
		vector<int> serie;
		for (int j = 0; j < F2[0].size(); j++)
			serie.push_back(INT32_MAX);
		F2.push_back(serie);
	}
	cout << "Разделение серий на файлы" << endl;
	PrintFiles(F1, F2, F3);
	cout << "Сортировка элементов внутри файлов" << endl;
	for (int i = 0; i < F1.size(); i++) F1[i] = NaturalMergeSort(F1[i]);
	for (int i = 0; i < F2.size(); i++) F2[i] = NaturalMergeSort(F2[i]);
	PrintFiles(F1, F2, F3);
	cout << "Слияние файлов" << endl;
	int countEmptyFiles = 1;
	while (countEmptyFiles < 2)
	{
		int num = 1;
		if (F2.size() == 0) num = 2;
		if (F3.size() == 0) num = 3;
		switch (num)
		{
		case 1:
		    F1 = MergeFiles(F2, F3);
		    break;
		case 2:
		    F2 = MergeFiles(F1, F3);
		    break;
		case 3:
		    F3 = MergeFiles(F1, F2);
		    break;
		}
		countEmptyFiles = 0;
		if (F1.size() == 0) countEmptyFiles++;
		if (F2.size() == 0) countEmptyFiles++;
		if (F3.size() == 0) countEmptyFiles++;
		PrintFiles(F1, F2, F3);
	}
	if (F1.size() != 0) return DeleteEmptyElements(F1[0],size1+size2-series.size());
	if (F2.size() != 0) return DeleteEmptyElements(F2[0],size1+size2-series.size());
	return DeleteEmptyElements(F3[0],size1+size2-series.size());
}
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Исходный вектор" << endl;
	vector<int> vec = {9,3,1,6,4,2,8,7,0,5};
	PrintVector(vec);
	cout << endl << "Сортировка методом естественного слияния" << endl;
	PrintVector(NaturalMergeSort(vec));
	cout << endl << "Сортировка методом сбалансированного слияния" << endl;
	PrintVector(BalancedMergeSort(vec));
	cout << endl << "Сортировка методом многофазного слияния" << endl;
	PrintVector(PolyphaseMergeSort(vec));
	system("pause");
}

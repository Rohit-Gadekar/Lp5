#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

int parallelMinVal(int arr[], int n)
{
    int mini = arr[0];
    #pragma omp parallel for reduction(min:mini)
    for(int i=1; i<n; i++)
    {
        if(arr[i]<mini)mini = arr[i];
    }
    return mini;
}

int seqMinVal(int arr[], int n)
{
    int mini = arr[0];
    for(int i=1; i<n; i++)
    {
        if(arr[i]<mini)mini = arr[i];
    }
    return mini;
}

int parallelMaxVal(int arr[], int n)
{
    int maxi = arr[0];
    #pragma omp parallel for reduction(max:maxi)
    for(int i=1; i<n; i++)
    {
        if(arr[i]>maxi)maxi = arr[i];
    }
    return maxi;
}

int seqMaxVal(int arr[], int n)
{
    int maxi = arr[0];
    for(int i=1; i<n; i++)
    {
        if(arr[i]>maxi)maxi = arr[i];
    }
    return maxi;
}

long long parallelSum(int arr[], int n)
{
    long long summ = 0;
    #pragma omp parallel for reduction(+:summ)
    for(int i=0; i<n; i++)
    {
        summ+=arr[i];
    }
    return summ;
}

long long seqSum(int arr[], int n)
{
    long long summ = 0;
    for(int i=0; i<n; i++)
    {
        summ+=arr[i];
    }
    return summ;
}

double parallelAvg(int arr[], int n)
{
    return parallelSum(arr,n)/n;
}

double seqAvg(int arr[], int n)
{
    return seqSum(arr,n)/n;
}

int main()
{
    int n = 100000;
    int arr1[n], arr2[n];

    for(int i=0; i<n; i++)
    {
        arr1[i] = rand();
        arr2[i] = rand();
    }

    double start_time1 = omp_get_wtime();
    cout<<"MinVal (parallel): "<<parallelMinVal(arr1, n)<<endl;
    cout<<"MaxVal (parallel): "<<parallelMaxVal(arr1, n)<<endl;
    cout<<"Sum (parallel): "<<parallelSum(arr1, n)<<endl;
    cout<<"Average (parallel): "<<parallelAvg(arr1, n)<<endl;
    double end_time1 = omp_get_wtime();
    cout<<"Time required for parallel processes: "<<end_time1-start_time1<<endl;

    double start_time2 = omp_get_wtime();
    cout<<"MinVal (seq): "<<seqMinVal(arr2, n)<<endl;
    cout<<"MaxVal (seq): "<<seqMaxVal(arr2, n)<<endl;
    cout<<"Sum (seq): "<<seqSum(arr2, n)<<endl;
    cout<<"Average (seq): "<<seqAvg(arr2, n)<<endl;
    double end_time2 = omp_get_wtime();
    cout<<"Time required for sequential processes: "<<end_time2-start_time2<<endl;

    if((end_time2-start_time2)>(end_time1-start_time1))
    {
        cout<<"\nParallel is better"<<endl;
    }
    else
    {
        cout<<"\nSequential is better"<<endl;
    }
}
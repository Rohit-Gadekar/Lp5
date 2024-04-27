#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void bubble(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

void pBubble(int arr[], int n)
{
    // Sort odd indexed numbers  
    for (int i = 0; i < n; ++i)
    {
#pragma omp for
        for (int j = 1; j < n; j += 2)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(arr[j], arr[j - 1]);
            }
        }

// Synchronize
#pragma omp barrier

// Sort even indexed numbers
#pragma omp for
        for (int j = 2; j < n; j += 2)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(arr[j], arr[j - 1]);
            }
        }
    }
}

void merge(int arr[], int low, int mid, int high)
{
    // Create arrs of left and right partitions
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1];
    int right[n2];

    // Copy all left elements
    for (int i = 0; i < n1; i++)
        left[i] = arr[low + i];

    // Copy all right elements
    for (int j = 0; j < n2; j++)
        right[j] = arr[mid + 1 + j];

    // Compare and place elements
    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // If any elements are left out
    while (i < n1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void parallelMergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }

#pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }
        merge(arr, low, mid, high);
    }
}

void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {   
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main()
{
    int n;
    cout << "Enter the number of elements of array: ";
    cin >> n;
    int arr1[n];
    int arr2[n];
    double start_time, end_time;
    int choice;

    while (true)
    {
        cout << "Menu:\n";
        cout << "1. Bubble Sort\n";
        cout << "2. Merge Sort\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            for (int i = 0; i < n; i++)
            {
                arr1[i] = rand();
                arr2[i] = rand();
            }

            // Sequential time
            start_time = omp_get_wtime();
            bubble(arr1, n);
            end_time = omp_get_wtime();
            cout << "Sequential Bubble Sort took : " << end_time - start_time << " seconds.\n";

            // Parallel time
            start_time = omp_get_wtime();
            pBubble(arr2, n);
            end_time = omp_get_wtime();
            cout << "Parallel Bubble Sort took : " << end_time - start_time << " seconds.\n";
            break;

        case 2:
            for (int i = 0; i < n; i++)
            {
                arr1[i] = rand();
                arr2[i] = rand();
            }
            // Measure Sequential Time
            start_time = omp_get_wtime();
            mergeSort(arr1, 0, n - 1);
            end_time = omp_get_wtime();
            cout << "Time taken by sequential Merge Sort: " << end_time - start_time << " seconds\n";

            // Measure Parallel time
            start_time = omp_get_wtime();
            parallelMergeSort(arr2, 0, n - 1);
            end_time = omp_get_wtime();
            cout << "Time taken by parallel Merge Sort: " << end_time - start_time << " seconds\n";
            break;
        case 3:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

/*

In OpenMP, #pragma omp barrier is a directive used to synchronize the execution of threads in a parallel region.

When multiple threads are executing parallel code, there may be situations where one thread needs to wait for all other threads
to reach a certain point before proceeding. This is where barriers come into play.

The #pragma omp barrier directive creates a synchronization point where each thread waits until all threads in the
team (those executing within the same parallel region) have reached this point before any of them are allowed to
continue execution past the barrier.



The #pragma omp parallel sections directive in OpenMP is used to divide the work among multiple parallel sections, 
each of which can be executed concurrently by different threads. This directive is often used when different parts 
of a program can be executed independently and in parallel.

Here's how it works:

Division of Work: The code block following #pragma omp parallel sections is divided into sections, each marked by the 
#pragma omp section directive.
Concurrency: Each section is executed concurrently by a separate team of threads. The number of threads in each team may vary 
depending on the OpenMP implementation and the runtime environment.
Implicit Barrier: After executing its section, each team of threads waits implicitly at the end of the sections construct until 
all other teams have completed their sections.

*/
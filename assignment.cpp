#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

// ========== Bubble Sort ==========
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]); }

// ========== Merge Sort ==========
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R; }
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r); }}

// ========== Quick Sort ==========
int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]);
    swap(arr[i + 1], arr[high]);
    return i + 1; }
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);  }}

// ========== Data Generation ==========
void generateRandom(int arr[], int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = rand() % 10000; }
void generatePartiallySorted(int arr[], int size, int sortedRatio = 70) {
    generateRandom(arr, size);
    int sortedSize = size * sortedRatio / 100;
    sort(arr, arr + sortedSize);
}void generateReverseSorted(int arr[], int size) {
    generatePartiallySorted (arr, size);
    reverse(arr, arr + size); }

// ========== Array Copy ==========
void copyArray(int from[], int to[], int size) {
    for (int i = 0; i < size; ++i)
        to[i] = from[i]; }

// ========== Test One Type of Data ==========
void testSorts(const string& label, int input[], int size, int repeats) {
    int arr[size];
    cout << "\n=== " << label << " (Size = " << size << ") ===\n";

    double bubbleTotal = 0, mergeTotal = 0, quickTotal = 0;

    for (int rep = 1; rep <= repeats; ++rep) {
        // Bubble Sort
        copyArray(input, arr, size);
        clock_t start = clock();
        bubbleSort(arr, size);
        clock_t end = clock();
        double bubbleTime = double(end - start) / CLOCKS_PER_SEC;
        bubbleTotal += bubbleTime;
        cout << "Run " << rep << " - Bubble Sort: " << bubbleTime << " sec\n";

        // Merge Sort
        copyArray(input, arr, size);
        start = clock();
        mergeSort(arr, 0, size - 1);
        end = clock();
        double mergeTime = double(end - start) / CLOCKS_PER_SEC;
        mergeTotal += mergeTime;
        cout << "Run " << rep << " - Merge Sort: " << mergeTime << " sec\n";

        // Quick Sort
        copyArray(input, arr, size);
        start = clock();
        quickSort(arr, 0, size - 1);
        end = clock();
        double quickTime = double(end - start) / CLOCKS_PER_SEC;
        quickTotal += quickTime;
        cout << "Run " << rep << " - Quick Sort: " << quickTime << " sec\n";   }

    cout << "--- Average over " << repeats << " runs ---\n";
    cout << "Bubble Sort Average: " << bubbleTotal / repeats << " sec\n";
    cout << "Merge Sort Average: " << mergeTotal / repeats << " sec\n";
    cout << "Quick Sort Average: " << quickTotal / repeats << " sec\n"; }

// ========== Main ==========
int main() {
    const int sizes[] = {100, 500, 1000, 2000, 5000, 10000, 20000, 30000, 50000, 100000};  // Different input sizes
    const int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    const int repeats = 10;  // Number of repetitions
    srand(time(0));

    for (int i = 0; i < numSizes; ++i) {
        int size = sizes[i];
        int* data = new int[size];

        generateRandom(data, size);
        testSorts("Random Data", data, size, repeats);

        generatePartiallySorted (data, size);
        testSorts("Partially Sorted Data", data, size, repeats);

        generateReverseSorted(data, size);
        testSorts("Reverse Sorted Data", data, size, repeats);

        delete[] data;  }
    return 0;
}


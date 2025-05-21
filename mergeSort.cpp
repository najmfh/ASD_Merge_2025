#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

void mergeSort(vector<double>& arr, int start, int end);
void merge(vector<double>& arr, int start, int mid, int end);

int main(){
    int sizeArr;
    cout << "==== Merge Sort Method's Program ====\n";
    cout << "Masukkan jumlah data : ";
    cin >> sizeArr;

    // Buat array dinamis
    vector<double> unsortedArr(sizeArr);

    cout << "\nMasukkan nilai-data : " << endl;

    // Masukkan nilai data yang ingin diurutkan
    for (int i = 0; i < sizeArr; i++){
        cout << "Nilai ke-" << i + 1 << " : ";
        cin >> unsortedArr[i];
    }

    cout << "\nNilai-nilai yang dimasukkan : \n";
    
    // Menampilkan data yang sudah diinput
    for (int i = 0; i < sizeArr; i++){
        cout << unsortedArr[i] << " ";
    }
    cout << endl;

    int sizeData = unsortedArr.size();
    auto now = chrono::high_resolution_clock::now();

    mergeSort(unsortedArr, 0, sizeData - 1);

    cout << "\nData setelah diurutkan : ";
    for (int i = 0; i < sizeArr; i++){
        cout << unsortedArr[i] << " ";
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - now;

    cout << "\n\nWaktu eksekusi : " << duration.count() << " detik\n" << endl;
    return 0;
}

void mergeSort(vector<double>& arr, int start, int end){
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

void merge(vector<double>& arr, int start, int mid, int end){
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;

    double left[n1], right[n2];

    for (i = 0; i < n1; i++){
        left[i] = arr[start + i];
    }
    for (j = 0; j < n2; j++){
        right[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = start;

    while (i < n1 && j < n2){
        if (left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2){
        arr[k] = right[j];
        j++;
        k++;
    }
}
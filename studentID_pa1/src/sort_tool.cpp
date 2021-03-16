// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2021/02/26 Hsien-Chia Chen]
//             [2021/03/16 Chih-Yuan Chuang (student id = r09921006)]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    // Reference: textbook p.18
    for (int i = 0; i < data.size(); i++) {
        int key = data[i];
        int j;
        for (j = i - 1; j >= 0 && key <= data[j]; j--) {
            data[j+1] = data[j];
        }
        data[j+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    int mid = (low + high) / 2;
    if (low < high) {
        int pivot = Partition(data, low, high);
        QuickSortSubVector(data, low, pivot - 1);
        QuickSortSubVector(data, pivot + 1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    // Reference: Textbook page 171
    int smallRight = low - 1; // the most right index of the smaller-half sequence
    int check = low; // the next index to be evaluated
    int pivot = data[high];
    for ( ; check <= high - 1; check++) {
        if (data[check] <= pivot) {
            smallRight = smallRight + 1; // move smallLeftest left one
            // swap the [most left larger half] with [most right smaller half]
            int tmp = data[smallRight];
            data[smallRight] = data[check];
            data[check] = tmp;
            //
        }
    }
    // swap the pivot with [most left larger half]
    int tmp = data[smallRight+1];
    data[smallRight+1] = data[high];
    data[high] = tmp;
    //
    return smallRight + 1; // return pivot index
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    // Reference: Handout unit1b.pdf
    int mid = (low + high) / 2;
    if (low < high) {
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid+1, high);
        Merge(data, low, mid, mid+1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    // Reference: Handout unit1b.pdf
    vector<int> subLeft, subRight;
    for (int i = low; i <= middle1; i++)
        subLeft.push_back(data[i]);
    subLeft.push_back(1000001); // 1000001 as infinite
    for (int i = middle2; i <= high; i++)
        subRight.push_back(data[i]);
    subRight.push_back(1000001); // 1000001 as infinite
    int l = 0, r = 0;
    for (int i = low; i <= high; i++) {
        if (subLeft[l] <= subRight[r]) {
            data[i] = subLeft[l];
            l++;
        } else {
            data[i] = subRight[r];
            r++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
	int tmp = 0;
    for (int i = data.size() - 1; i >= 1; i--) {
		tmp = data[i];
		data[i] = data[0];
		data[0] = tmp;
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    // Reference: Textbook page 154
    int target; // to be compared with its left and right children
    int l = (root + 1) * 2 - 1; // left child of root
    int r = (root + 1) * 2 + 1 - 1; // right child of root
    if (data[root] < data[l] && l < data.size()) {
        target = l;
    } else if (data[root] < data[r] && r < data.size()) {
        target = r;
    } else {
        target = root;
    }
    if (target != root) {
        int tmp = data[target];
        data[target] = data[root];
        data[root] = tmp;
        MaxHeapify(data, target);
    }

}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    // Reference: Textbook page 157
    // level-ordered traversal
    for (int i = ((heapSize + 1) / 2 - 1); i >= 0; i--) {
        MaxHeapify(data, i);
    }
}

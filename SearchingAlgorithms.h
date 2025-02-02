#pragma once
class SearchingAlgorithms
{
	enum SearchAlgorithm { BINARY_ITERATIVE, BINARY_RECURSIVE, SEQUENTIAL_SORTED, SEQUENTIAL_UNSORTED };

	// Iterative Binary Search -------------------------------------------------------------------------
	template <typename T>
	int binarySearchIterative(T arr[], int size, T key) {
		int left = 0, right = size - 1;
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (arr[mid] == key) return mid;
			if (arr[mid] < key) left = mid + 1;
			else right = mid - 1;
		}
		return -1;
	}


	// Recursive Binary Search -------------------------------------------------------------------------
	template <typename T>
	int binarySearchRecursive(T arr[], int left, int right, T key) {
		if (left > right) return -1;
		int mid = left + (right - left) / 2;
		if (arr[mid] == key) return mid;
		if (arr[mid] < key) return binarySearchRecursive(arr, mid + 1, right, key);
		return binarySearchRecursive(arr, left, mid - 1, key);
	}


	// Unsorted Sequential Search ----------------------------------------------------------------------
	template <typename T>
	int sequentialSearchUnsorted(T arr[], int size, T key) {
		for (int i = 0; i < size; i++) {
			if (arr[i] == key) return i;
		}
		return -1;
	}


	// Sorted Sequential Search ------------------------------------------------------------------------
	template <typename T>
	int sequentialSearchSorted(T arr[], int size, T key) {
		for (int i = 0; i < size; i++) {
			if (arr[i] == key) return i;
			if (arr[i] > key) return -1;
		}
		return -1;
	}


	// Search Functions (Wrapper for all the different types of searches) ------------------------------
	template <typename T>
	int search(T arr[], int size, T key, SearchAlgorithm algo) {
		switch (algo) {
		case BINARY_ITERATIVE: return binarySearchIterative(arr, size, key);
		case BINARY_RECURSIVE: return binarySearchRecursive(arr, 0, size - 1, key);
		case SEQUENTIAL_SORTED: return sequentialSearchSorted(arr, size, key);
		case SEQUENTIAL_UNSORTED: return sequentialSearchUnsorted(arr, size, key);
		default: return -1;
		}
	}
};


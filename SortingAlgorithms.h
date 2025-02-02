#pragma once

class SortingAlgorithms
{
	enum SortAlgorithm { QUICK_SORT, MERGE_SORT, BUBBLE_SORT, SELECTION_SORT };

	// Quick Sort -----------------------------------------------------------------------------------------------------
	template <typename T>
	int partition(T arr[], int low, int high) {
		T pivot = arr[high];
		int i = (low - 1);

		for (int j = low; j < high; j++) {
			if (arr[j] < pivot) {
				i++;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[high]);
		return (i + 1);
	}

	template <typename T>
	void quickSort(T arr[], int low, int high) {
		if (low < high) {
			int pi = partition(arr, low, high);
			quickSort(arr, low, pi - 1);
			quickSort(arr, pi + 1, high);
		}
	}

	// Merge Sort -----------------------------------------------------------------------------------------------------
	template <typename T>
	void merge(T arr[], int left, int mid, int right) {
		int n1 = mid - left + 1;
		int n2 = right - mid;

		T* L = new T[n1], * R = new T[n2];

		for (int i = 0; i < n1; i++) L[i] = arr[left + i];
		for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

		int i = 0, j = 0, k = left;

		while (i < n1 && j < n2) {
			if (L[i] <= R[j]) arr[k++] = L[i++];
			else arr[k++] = R[j++];
		}

		while (i < n1) arr[k++] = L[i++];
		while (j < n2) arr[k++] = R[j++];

		delete[] L;
		delete[] R;
	}
	template <typename T>
	void mergeSort(T arr[], int left, int right) {
		if (left < right) {
			int mid = left + (right - left) / 2;
			mergeSort(arr, left, mid);
			mergeSort(arr, mid + 1, right);
			merge(arr, left, mid, right);
		}
	}


	// Bubble Sort ----------------------------------------------------------------------------------------------------
	template <typename T>
	void bubbleSort(T arr[], int n) {
		for (int i = 0; i < n - 1; i++) {
			bool swapped = false;
			for (int j = 0; j < n - i - 1; j++) {
				if (arr[j] > arr[j + 1]) {
					swap(arr[j], arr[j + 1]);
					swapped = true;
				}
			}
			if (!swapped) break;
		}
	}


	// Selection Sort -------------------------------------------------------------------------------------------------
	template <typename T>
	void selectionSort(T arr[], int n) {
		for (int i = 0; i < n - 1; i++) {
			int minIndex = i;
			for (int j = i + 1; j < n; j++) {
				if (arr[j] < arr[minIndex]) minIndex = j;
			}
			swap(arr[minIndex], arr[i]);
		}
	}

	// Sort function (Wrapper for all the different types of sorting algo) --------------------------------------------
	template <typename T>
	void sort(T arr[], int size, SortAlgorithm algo) {
		switch (algo) {
		case QUICK_SORT: quickSort(arr, 0, size - 1); break;
		case MERGE_SORT: mergeSort(arr, 0, size - 1); break;
		case BUBBLE_SORT: bubbleSort(arr, size); break;
		case SELECTION_SORT: selectionSort(arr, size); break;
		}
	}
};


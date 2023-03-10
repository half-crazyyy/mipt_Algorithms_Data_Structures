#ifndef MHEAP_H
#define MHEAP_H

#include <vector>

void sift_up(std::vector<int>& heap, int n_heap, int index) {
	if (index >= n_heap)
		return;
	while (index > 0) {
		int parent = (index - 1) / 2;
		if (heap[index] <= heap[parent])
			return; 
		std::swap(heap[index], heap[parent]);
		index = parent;
	}
}
inline void sift_down(std::vector<int>& heap, int n_heap, int index) {
	if (index >= n_heap)
		return;
	int L_index = 2 * index + 1;
	int R_index = 2 * index + 2;
	int max_index = index;
	if (L_index<n_heap && heap[L_index]>heap[max_index])
		max_index = L_index;
	if (R_index<n_heap && heap[R_index]>heap[max_index])
		max_index = R_index;
	if (max_index != index) {
		std::swap(heap[index], heap[max_index]);
		sift_down(heap, n_heap, max_index);
	}
}
inline void build_heap(std::vector<int>& heap) {
	for (int i = heap.size() / 2 - 1; i >= 0; --i)
		sift_down(heap, heap.size(), i);
}








#endif


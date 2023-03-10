#ifndef MHEAP_H
#define MHEAP_H

#include <vector>
#include <functional>

void sift_up(std::vector<int>& heap, int n_heap, int index, std::function<bool(int,int)> cmp = std::less<int>()){
	if (index >= n_heap)
		return;
	while (index > 0) {
		int parent = (index - 1) / 2;
		if (!cmp(heap[parent],heap[index]))
			return; 
		std::swap(heap[index], heap[parent]);
		index = parent;
	}
}
inline void sift_down(std::vector<int>& heap, int n_heap, int index, std::function<bool(int, int)> cmp = std::less<int>()) {
	if (index >= n_heap)
		return;
	int L_index = 2 * index + 1;
	int R_index = 2 * index + 2;
	int max_index = index;
	if (L_index<n_heap && cmp(heap[max_index],heap[L_index]))
		max_index = L_index;
	if (R_index<n_heap && cmp(heap[max_index],heap[R_index]))
		max_index = R_index;
	if (max_index != index) {
		std::swap(heap[index], heap[max_index]);
		sift_down(heap, n_heap, max_index,cmp);
	}
}
inline void build_heap(std::vector<int>& heap, std::function<bool(int, int)> cmp = std::less<int>()) {
	for (int i = heap.size() / 2 - 1; i >= 0; --i)
		sift_down(heap, heap.size(), i, cmp);
}
inline void heap_sort(std::vector<int>& v, std::function<bool(int, int)> cmp = std::less<int>()) {
	build_heap(v, cmp);
	auto& heap = v;
	for (int i = heap.size() - 1; i > 0; --i) {
		std::swap(heap[0], heap[i]);
		sift_down(heap, i, 0, cmp);
	}
}








#endif


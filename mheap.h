#ifndef MHEAP_H
#define MHEAP_H

#include <vector>
#include <functional>

inline void sift_upi(std::vector<int>& heap, int n_heap, int index, std::function<bool(int,int)> cmp = std::less<int>()){
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
inline void sift_downi(std::vector<int>& heap, int n_heap, int index, std::function<bool(int, int)> cmp = std::less<int>()) {
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
		sift_downi(heap, n_heap, max_index,cmp);
	}
}
inline void build_heapi(std::vector<int>& heap, std::function<bool(int, int)> cmp = std::less<int>()) {
	for (int i = heap.size() / 2 - 1; i >= 0; --i)
		sift_downi(heap, heap.size(), i, cmp);
}
inline void heap_sorti(std::vector<int>& v, std::function<bool(int, int)> cmp = std::less<int>()) {
	build_heapi(v, cmp);
	auto& heap = v;
	for (int i = heap.size() - 1; i > 0; --i) {
		std::swap(heap[0], heap[i]);
		sift_downi(heap, i, 0, cmp);
	}
}
template<class Container, class Comparator=std::less<typename Container::value_type>>
inline void sift_up(Container& heap, int n_heap, int index, Comparator cmp = Comparator()) {
	if (index >= n_heap)
		return;
	while (index > 0) {
		int parent = (index - 1) / 2;
		if (!cmp(heap[parent], heap[index]))
			return;
		std::swap(heap[index], heap[parent]);
		index = parent;
	}
}
template<class Container, class Comparator = std::less<typename Container::value_type>>
inline void sift_down(Container& heap, int n_heap, int index, Comparator cmp = Comparator()) {
	if (index >= n_heap)
		return;
	int L_index = 2 * index + 1;
	int R_index = 2 * index + 2;
	int max_index = index;
	if (L_index < n_heap && cmp(heap[max_index], heap[L_index]))
		max_index = L_index;
	if (R_index < n_heap && cmp(heap[max_index], heap[R_index]))
		max_index = R_index;
	if (max_index != index) {
		std::swap(heap[index], heap[max_index]);
		sift_down(heap, n_heap, max_index, cmp);
	}
}
template<class Container, class Comparator = std::less<typename Container::value_type>>
inline void build_heap(Container& heap, Comparator cmp = Comparator()) {
	for (int i = heap.size() / 2 - 1; i >= 0; --i)
		sift_down(heap, heap.size(), i, cmp);
}

template<class Container, class Comparator = std::less<typename Container::value_type>>
inline void heap_sort(Container& v,  Comparator cmp = Comparator()) {
	build_heap(v, cmp);
	auto& heap = v;
	for (int i = heap.size() - 1; i > 0; --i) {
		std::swap(heap[0], heap[i]);
		sift_down(heap, i, 0, cmp);
	}
}

template<class T, class Comparator = std::less<T>>
class mpriority_queue 
{
public:
	mpriority_queue() = default;
	mpriority_queue(Comparator cmp) : m_cmp(cmp) {
		
	}

	void push(const T& value) {
		m_container.push_back(value);
		sift_up(m_container, m_container.size(),m_container.size()-1, m_cmp);
	}
	const T& top() const{
		return m_container[0];
	}
	void pop() {
		m_container[0] = m_container[m_container.size() - 1];
		m_container.pop_back();
		sift_down(m_container, m_container.size(), 0, m_cmp);
	}
	bool empty() const{
		return m_container.size() == 0;
	}
private:
	mvector<T> m_container;
	Comparator m_cmp;
};


#endif


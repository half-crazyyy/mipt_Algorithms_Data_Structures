#ifndef Quick_sort_h
#define Quick_sort_h
#include <vector>

inline int pivot_central(std::vector<int> &vect, int first, int last){
    return (first+last)/2;
}

inline int pivot_random(std::vector<int> &vect, int first, int last){
    return first+rand()%(last-first+1);
}

inline int partition (std::vector<int> &vect, int first, int last, int pivot){
    if (last<=first)
        return first;
    std::swap(vect[pivot], vect[last]);
    int i = first;
    int j = last-1;
    while (i<=j){
        while (vect[i]<vect[last])
            ++i;
        while (j>=first && vect[j]>=vect[last])
            --j;
        if (i<j)
            std::swap(vect[i++], vect[j++]);
    }
    std::swap(vect[i], vect[last]);
    return i;
}

inline void quick_sort(std::vector<int> &vect, int first, int last, std::function<int(std::vector<int> &, int, int)> pivot){
    if (last<=first)
        return;
    int p = partition(vect, first, last, pivot(vect, first, last));
    quick_sort(vect, first, p-1, pivot);
    quick_sort(vect, p+1, last, pivot);
}

inline int k_stat(std::vector<int> &vect, int k, std::function<int(std::vector<int> &, int, int)> pivot){
    int first = 0;
    int last = vect.size() - 1;
    while(first<last){
        int p = partition(vect, first, last, pivot(vect, first, last));
        if (k<p)
            last=p-1;
        else if (k>p)
            first=p+1;
        else
            break;
    }
    return vect[k];
}

#endif
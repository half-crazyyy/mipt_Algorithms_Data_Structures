#ifndef Quick_sort_h
#define Quick_sort_h
#include <vector>

inline int pivot(std::vector<int> &vect, int first, int last){
    return (first+last)/2;
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

#endif
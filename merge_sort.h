//
// Created by dmitr on 24.03.2023.
//

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>

inline void mergei(const std::vector<int> &vect,
                   int begin0, int end0, int begin1, int end1,
                   std::vector<int> &buffer) {
    int i = begin0;
    int j = begin1;
    int k = begin0;

    while (i < end0 && j < end1) {
        if (vect[i] < vect[j])
            buffer[k++] = vect[i++];
        else
            buffer[k++] = vect[j++];
    }
    while (i < end0)
        buffer[k++] = vect[i++];
    while (j < end1)
        buffer[k++] = vect[j++];
}


inline void merge_sorti(std::vector<int> &vect, int begin, int end, std::vector<int> &buffer) {
    if (end - begin == 2) {
        if (vect[begin] > vect[begin + 1])
            std::swap(vect[begin], vect[begin + 1]);
    } else if (end - begin > 2) {
        int middle = (begin + end) / 2;
        // Левая часть массива
        merge_sorti(vect, begin, middle, buffer);
        // Правая часть массива
        merge_sorti(vect, middle, end, buffer);
        mergei(vect, begin, middle, middle, end, buffer);
        for (int i = begin; i < end; ++i)
            vect[i] = buffer[i];
    }
}

template<typename T>
inline void merge(const std::vector<T> &vect,
                  int begin0, int end0, int begin1, int end1,
                  std::vector<T> &buffer) {
    int i = begin0;
    int j = begin1;
    int k = begin0;

    while (i < end0 && j < end1) {
        if (vect[i] < vect[j])
            buffer[k++] = vect[i++];
        else
            buffer[k++] = vect[j++];
    }
    while (i < end0)
        buffer[k++] = vect[i++];
    while (j < end1)
        buffer[k++] = vect[j++];
}

template<typename T>
inline void merge_sort(std::vector<T> &vect, int begin, int end, std::vector<T> &buffer) {
    if (end - begin == 2) {
        if (vect[begin] > vect[begin + 1])
            std::swap(vect[begin], vect[begin + 1]);
    } else if (end - begin > 2) {
        int middle = (begin + end) / 2;
        // Левая часть массива
        merge_sort(vect, begin, middle, buffer);
        // Правая часть массива
        merge_sort(vect, middle, end, buffer);
        merge(vect, begin, middle, middle, end, buffer);
        for (int i = begin; i < end; ++i)
            vect[i] = buffer[i];
    }

}

template<typename T>
inline void merge_sort(std::vector<T> &vect) {
    std::vector<T> buffer(vect.size());
    merge_sort(vect, 0, vect.size(), buffer);
}

inline void merge_sort_up_i(std::vector<int> &vect, std::vector<int> &buffer) {
    for (int len = 1; len < vect.size(); len *= 2) { // len - length of merging vectors
        for (int i = 0, j = len; j < vect.size(); i += 2 * len, j += 2 * len) {
            int m = std::min(j + len, int(vect.size()));
            merge(vect, i, j, j, m, buffer);
            for (int k = i; k < m; ++k)
                vect[k] = buffer[k];
        }
    }
}

#endif //MIPT_ALGORITHMS_DATA_STRUCTURES_MERGE_SORT_H

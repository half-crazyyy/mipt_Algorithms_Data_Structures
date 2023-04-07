#ifndef Counting_sort_H
#define Counting_sort_H

#include <vector>
#include <functional>
#include <type_traits>

template <int N>
void counting_sort(std::vector<int>& a) {
    int c[N] = { 0 };
    for (int i = 0; i < a.size(); ++i) {
        ++c[a[i]];
    }
    std::vector<int> a1(a.size());
    for (int i = 0, p = 0; i < N; ++i)
        for (int j = 0; j < c[i]; ++j)
            a1[p++] = i;
    a.swap(a1);
}
template <int N>
void pocket_sort(std::vector<int>& a) {
    int c[N] = { 0 };
    for (int i = 0; i < a.size(); ++i) 
        ++c[a[i]];
    int p[N] = { 0 };
    std::vector<int> a1(a.size());
    for (int i = 1; i < N; ++i)
        p[i] = p[i - 1] + c[i-1];
    for (int i = 0; i < a.size(); ++i)
        a1[p[a[i]]++] = a[i];
    a.swap(a1);
}


inline void LSD(std::vector<unsigned long long>& a) {
    std::vector<unsigned long long> a1(a.size());
    for (int digit_index = 0; digit_index < sizeof(unsigned long long); ++digit_index) {
        int c[256] = { 0 };
        for (int i = 0; i < a.size(); ++i)
            ++c[(a[i] >> (digit_index * 8)) & 0xFF];
        int p[256] = { 0 };
        for (int i = 1; i < 256; ++i)
            p[i] = p[i - 1] + c[i - 1];
        for (int i = 0; i < a.size(); ++i)
            a1[p[(a[i] >> (digit_index * 8)) & 0xFF]++] = a[i];
        a.swap(a1);
    }
}
template <class T>
inline void MSD(std::vector<T>&a) {
    static_assert(std::is_unsigned<T>::value);
    std::vector<T> a1(a.size()); 
    std::function<void(int, int, int)> msd = [&](int pocket_begin, int pocket_end, int digit_index) {
        if (pocket_begin >= pocket_end - 1 || digit_index < 0)
            return;
        int c[256] = { 0 };
        for (int i = pocket_begin; i < pocket_end; ++i)
            ++c[(a[i] >> (digit_index * 8)) & 0xFF];
        int p[256] = { 0 };
        for (int i = 1; i < 256; ++i)
            p[i] = p[i - 1] + c[i - 1];
        for (int i = pocket_begin; i < pocket_end; ++i)
            a1[pocket_begin + p[(a[i] >> (digit_index * 8)) & 0xFF]++] = a[i];
        for (int i = pocket_begin; i < pocket_end; ++i)
            a[i] = a1[i];
        for (int i = 0; i < 256; ++i)
            msd(pocket_begin + p[i] - c[i], pocket_begin + p[i], digit_index - 1);
    };
    msd(0, a.size(), sizeof(T) - 1);

}
    
#endif

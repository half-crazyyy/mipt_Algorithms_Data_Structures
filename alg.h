#ifndef Algo_h
#define Algo_h

#include <vector>
#include <functional>
#include "mvector.h"


static int fact(int n) {
    return (n == 1) ? 1 : fact(n - 1) * n;
}


static int fact_loop(int n) {
    int res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}


template<class T>
inline int lin_search(const std::vector<T> &vect, T a) {
    for (int i = 0; i < vect.size(); ++i) {
        if (vect.at(i) == a) {
            return 1;
        }
    }
    return -1;
}


template<class T>
inline int bin_search(const std::vector<T> &vect, T a) {
    int i = 0;
    int j = vect.size();
    while (i < j) {
        int m = i + (j - i) / 2;
        if (a < vect[m])
            j = m;
        else if (vect[m] < a)
            i = m + 1;
        else
            return m;
    }
    return -1;
}


template<class T>
inline int bin_search_rec(const std::vector<T> &vect, T a, int i = 0, int j = -1) {
    if (j == -1) {
        j = vect.size();
    }
    if (i < j) {
        int m = i + (j - i) / 2;
        if (a < vect[m])
            return bin_search_rec(vect, a, m, i);
        else if (vect[m] < a)
            return bin_search_rec(vect, a, m + 1, j);
        return m;
    }
    return -1;
}


template<class T>
inline int bin_search_rec_lambda(const std::vector<T> &vect, T a) {
    //lambda:
    std::function<int(int, int)> rec = [&](int i, int j) {
      if (i < j) {
          int m = i + (j - i) / 2;
          if (a < vect[m])
              return rec(m, i);
          else if (vect[m] < a)
              return rec(m + 1, j);
          return m;
      }
      return -1;
    };
    return rec(0, vect.size());
}

#endif

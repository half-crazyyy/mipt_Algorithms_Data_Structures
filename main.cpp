#include"alg.h"
#include<iostream>
#include<vector>
#include<string>
#include "mdeque.h"
#include "mheap.h"

template <class T>
inline std::ostream & operator << (std::ostream & o, const std::vector<T> & mvect){
    o << '(';
    if (mvect.size() != 0){
        int i = 0;
        for (; i < mvect.size()-1; ++i)
            o << mvect[i] << ", ";
        o << mvect[i];
    }
    o << ')';
    return o;
}

template <class T>
inline std::ostream & operator << (std::ostream & o, const mvector<T> & mvect){
    o << '[';
    if (mvect.size() != 0){
        int i = 0;
        for (; i < mvect.size()-1; ++i)
            o << mvect[i] << ", ";
        o << mvect[i];
    }
    o << ']';
    return o;
}
template <class T>
inline std::ostream & operator << (std::ostream & o, const mdeque<T> & mvect){
    o << '[';
    if (mvect.size() != 0){
        int i = 0;
        for (; i < mvect.size()-1; ++i)
            o << mvect[i] << ", ";
        o << mvect[i];
    }
    o << ']';
    return o;
}


void test_factorial() {
    for (int i = 0; i < 60; i++)
        std::cout << i << " -> " << fact(i) << std::endl;

}
void test_linsearch() {
    std::vector<int> vec = { 1,-2,3,4,333,-34,0 };
    std::cout << lin_search(vec, 333) << std::endl;
    std::cout << lin_search(vec, 9999999) << std::endl;
    std::cout << lin_search(vec, -2) << std::endl;

    std::vector<std::string> stvec = {"assa","ds","sds","s s "};
    std::cout << lin_search<std::string>(stvec, "ds") << std::endl;

    std::vector<double> fv = {1.222,0.2332,322,9.23};
    std::cout << lin_search(fv, 1.222) << std::endl;
    std::cout << lin_search(fv, 9.23) << std::endl;


}
void test_binsearch() {
    std::vector<int> vec = {-10,-8,3,4,10};
    //std::cout << bin_search(vec, 4) << "  " << bin_search_req(vec, 4) <<"  "<<bin_search_req_lambda(vec,4)<< std::endl;
    for(int val:{4,10,-10,0,-11,15})
        std::cout <<val<<"   "<< bin_search(vec, val) << "  " << bin_search_rec(vec, val) <<"  "<<bin_search_rec_lambda(vec,val)<< std::endl;
}

void test_mvector(){
    mvector<int> mvect;
    mvect.push_back(-10);
    mvect.push_back(-8);
    mvect.push_back(3);
    mvect.push_back(4);
    std::cout << mvect << std::endl;
    mvect.pop_back();
    mvect.pop_back();
    std::cout << mvect << std::endl;
    mvect.push_back(8);
    std::cout << mvect << std::endl;
    mvector<std::vector<int>> mvect1;
    mvect1.push_back({1,2,3});
    mvect1.push_back({2,3});
    std::cout << mvect1 << std::endl;
    mvector<float> mvect2(3);
    mvect2[2] = 4.0f;
    std::cout << mvect2 << std::endl;
    mvector<mvector<int>> mvect3{{1,2,3},{4,5,6},{},{2}};
    std::cout << mvect3 << std::endl;
    mvect3[1] = {10,9,11};
    std::cout << mvect3 << std::endl;
    std::vector<int> vect = {100,200,300};
    mvect3[2] = vect;
    std::cout << mvect3 << std::endl;
    mvector<std::vector<mvector<int>>> mvect4{{{1,2,3},{4,5,6}},{{555,666},{777}}};
    std::cout << mvect4 << std::endl;

    for (auto & val: mvect4){
        std::cout << val << std::endl;
    }
}

void test_mdeque(){
    mdeque<int> md;
    md.reserve(8);
    std::cout << md.test_mem() << std::endl;
    md.push_back(1);
    std::cout << md.test_mem() << std::endl;
    md.push_back(2);
    std::cout << md.test_mem() << std::endl;
    md.push_back(3);
    std::cout << md.test_mem() << std::endl;
    md.push_back(4);
    std::cout << md.test_mem() << std::endl;
    md.pop_front();
    std::cout << md.test_mem() << std::endl;
    md.pop_front();
    std::cout << md.test_mem() << std::endl;
    md.push_back(5);
    std::cout << md.test_mem() << std::endl;
    md.push_back(6);
    std::cout << md.test_mem() << std::endl;
    md.push_back(7);
    std::cout << md.test_mem() << std::endl;
    md.pop_front();
    std::cout << md.test_mem() << std::endl;
    md.pop_front();
    std::cout << md.test_mem() << std::endl;
    md.pop_front();
    std::cout << md.test_mem() << std::endl;
    md.push_back(8);
    std::cout << md.test_mem() << std::endl;
    md.push_back(9);
    std::cout << md.test_mem() << std::endl;
    md.push_back(10);
    std::cout << md.test_mem() << ' ' << md <<std::endl;
    md.push_front(11);
    std::cout << md.test_mem() << ' ' << md <<std::endl;
    md.pop_back();
    std::cout << md.test_mem() << ' ' << md <<std::endl;
    md.pop_back();
    std::cout << md.test_mem() << ' ' << md <<std::endl;
    md.pop_back();
    std::cout << md.test_mem() << ' ' << md <<std::endl;

    mdeque<int> mvect;
    mvect.push_back(-10);
    mvect.push_front(-8);
    mvect.push_back(3);
    mvect.push_back(4);
    std::cout << mvect << std::endl;
    mvect.pop_back();
    mvect.pop_back();
    std::cout << mvect << std::endl;
    mvect.push_back(8);
    std::cout << mvect << std::endl;
    mdeque<std::vector<int>> mvect1;
    mvect1.push_back({1,2,3});
    mvect1.push_back({2,3});
    std::cout << mvect1 << std::endl;
    mdeque<float> mvect2(3);
    mvect2[2] = 4.0f;
    std::cout << mvect2 << std::endl;
    mdeque<mdeque<int>> mvect3{{1,2,3},{4,5,6},{},{2}};
    std::cout << mvect3 << std::endl;
    mvect3[1] = {10,9,11};
    std::cout << mvect3 << std::endl;
    std::vector<int> vect = {100,200,300};
    mvect3[2] = vect;
    std::cout << mvect3 << std::endl;
    mdeque<std::vector<mdeque<int>>> mvect4{{{1,2,3},{4,5,6}},{{555,666},{777}}};
    std::cout << mvect4 << std::endl;
    mdeque<mvector<mdeque<int>>> mvect5{{{1,2,3},{4,5,6}},{{555,666},{777}}};
    std::cout << mvect5 << std::endl;
    mdeque<mdeque<mdeque<int>>> mvect6{{{1,2,3},{4,5,6}},{{555,666},{777}}};
    std::cout << mvect6 << std::endl;
    mvect6.push_back({{555, 2048}});
    mvect6.push_back({{}});
    mvect6.push_back({{}});
    mvect6.push_front({{10}, {100}});
    std::cout <<mvect6.test_mem() << std::endl;

    std::cout << std::endl;
    for (const auto & val: mvect6){
        std::cout << val << std::endl;
    }

    std::cout << std::endl;
    for (auto & val: mvect6){
        val.push_front({-1, -2, -3});
    }
    std::cout << mvect6 << std::endl;

    std::cout << std::endl;
    for (auto & val: mvect6){
        for(auto & val1: val){
            std::cout << val1 << std::endl;
        }
    }
}
void test_heap() {
    std::vector<int> heap{ 16, 8, 8, 7, 1, 0, 1, 3, 20};
    sift_up(heap, heap.size(), heap.size() - 1);
    std::cout << heap<<std::endl;
    for (int i = heap.size() - 1; i > 0; --i) {
        std::swap(heap[0], heap[i]);
        sift_down(heap, i, 0);
        std::cout << heap << std::endl;
    }
    build_heap(heap);
    std::cout << heap << std::endl;
}

int main(){
    //test_factorial();
    //test_linsearch();
    //test_binsearch();
    //test_mvector();
    //test_mdeque();
    test_heap();
    return 0;
}

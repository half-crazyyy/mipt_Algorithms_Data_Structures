#ifndef MDeque
#define MDeque
#include "mvector.h"

template <class T>
class mdeque{
public:
    using value_type = T;
    class iterator{
    public:
        T & operator * (){
            return md[i];
        }
        const T & operator * ()const{
            return md[i];
        }
        iterator & operator ++ (){
            ++i;
            return *this;
        }
        const iterator & operator ++ () const{
            ++i;
            return *this;
        }
        bool operator ==(const iterator & it) const {
            return it.i == i;
        }
        bool operator !=(const iterator & it) const {
            return it.i != i;
        }
    private:
        friend class mdeque;
        mdeque & md;
        mutable int i = 0;
        iterator(mdeque & md, int i): md(md), i(i){}

    };

    mdeque(){}
    mdeque(const mdeque & md){
        for (int i = 0; i < md.size(); ++i)
            push_back(md[i]);
    }
    mdeque(const std::vector<T> & mvect){
        for (const T & val : mvect)
            push_back(val);
    }

    mdeque(int n){
        resize(n);
    }

    mdeque(const mvector<T> & mvect){
        for (const T & val : mvect)
            push_back(val);
    }
    mdeque(std::initializer_list<T> list){
        for (auto & val : list)
            push_back(val);
    }

    ~mdeque(){
        clear();
    }

    mdeque & operator = (const std::initializer_list<T> & list){
        clear();
         for (auto & val : list)
            push_back(val);
        return *this;
    }

    mdeque & operator = (const std::vector<T> & mvect){
        clear();
        for (const T & val : mvect)
            push_back(val);
        return *this;
    }


    mdeque & operator = (const mvector<T> & mvect){
        clear();
        for (int i = 0; i < mvect.size(); ++i)
            push_back(mvect[i]);
        return *this;
    }

    mdeque & operator = (const mdeque & mvect){
        clear();
        for (int i = 0; i < mvect.size(); ++i)
            push_back(mvect[i]);
        return *this;
    }

    void push_front(const T& val){
        reserve(m_size + 1);
        m_size ++;
        if (--m_front_index < 0)
            m_front_index = m_cap - 1;
        m_mem[m_front_index] = val;
    }
    void push_back(const T& val){
        reserve(m_size + 1);
        m_size ++;
        if (++m_back_index>= m_cap)
            m_back_index = 0;
        m_mem[m_back_index] = val;
    }
    void pop_front(){
        m_mem[m_front_index] = T();
        if(++m_front_index >= m_cap)
            m_front_index = 0;
        --m_size;
    }
    void pop_back(){
        m_mem[m_back_index] = T();
        if(--m_back_index < 0)
            m_back_index = m_cap - 1;
        --m_size;
    }
    T & front(){
        return m_mem[m_front_index];
    }

    const T & front() const{
        return m_mem[m_front_index];
    }

    T & back(){
        return m_mem[m_back_index];
    }

    const T & back() const{
        return m_mem[m_back_index];
    }

    int size() const{
        return m_size;
    }

    const T & operator [] (int i) const {
        return m_mem[(m_front_index + i)%m_cap];
    }

    T & operator [] (int i){
        return m_mem[(m_front_index + i)%m_cap];
    }

    void reserve(int size){
        if (size > m_cap){
            int cap = (m_cap == 0 ? 1 : m_cap);
            while (cap < size)
                cap *= 2;
            T * mem = new T[cap]();
            for (int i = 0; i < m_size; ++i)
                mem[i] = m_mem[(m_front_index + i)%m_cap];
            delete[] m_mem;
            m_mem = mem;
            m_cap = cap;
            m_front_index = 0;
            m_back_index = m_size - 1;
        }
    }

    void resize(int new_size){
         while (new_size < m_size)
                pop_back();
         while (new_size > m_size)
                push_back(T());
    }

    void clear(){
        delete[] m_mem;
        m_mem = nullptr;
        m_size = 0;
        m_cap = 0;
        m_front_index = 0;
        m_back_index = 0;
    }

    iterator begin(){
        return iterator(*this, 0);
    }
    const iterator begin() const {
        return iterator(*this, 0);
    }
    iterator end(){
        return iterator(*this, m_size);
    }
    const iterator end() const {
        return iterator(*this, m_size);
    }

    mvector<T> test_mem() const{
        mvector<T> mvec(m_cap);
        for(int i = 0; i < m_cap; ++i){
            mvec[i] = m_mem[i];
        }
        return mvec;
    }

private:
   // mvector<int> m_mem;  //m_cap = m_cap
    int m_size = 0;
    int m_front_index = 0;
    int m_back_index = 0;
    T * m_mem = nullptr;
    int m_cap = 0;



};





#endif
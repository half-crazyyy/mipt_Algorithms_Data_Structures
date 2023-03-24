#ifndef MVector_h
#define MVector_h
#include <initializer_list>
#include <vector>

template <class T>
class mvector{
    public:
        using value_type = T;
        mvector(){}
        mvector(const mvector & mvect){
            for (const T & val : mvect)
                push_back(val);
        }
        mvector(const std::vector<T> & mvect){
            for (const T & val : mvect)
                push_back(val);
        }
        mvector(int n){
            resize(n);
        }
        mvector(std::initializer_list<T> list){
            for (auto & val : list)
                push_back(val);
        }
        ~mvector(){
            clear();
        }
        int size() const{
            return m_size;
        }
        void push_back(const T & a){
            reserve(m_size+1);
            m_mem[m_size++] = a;
        }
        void pop_back(){
            m_mem[--m_size] = T();
        }
        const T & operator [] (int i) const{
            return m_mem[i];
        }
        T & operator [] (int i){
            return m_mem[i];
        }
        mvector & operator = (const std::initializer_list<T> & list){
            clear();
             for (auto & val : list)
                push_back(val);
            return *this;
        }

        mvector & operator = (const std::vector<T> & mvect){
            clear();
            for (const T & val : mvect)
                push_back(val);
            return *this;
        }

        
        mvector & operator = (const mvector & mvect){
            clear();
            for (int i = 0; i < mvect.size(); ++i)
                push_back(mvect[i]);
            return *this;
        }
        void resize(int size){
            while (size < m_size)
                   pop_back();
            while (size > m_size)
                   push_back(T());
        }

        void reserve(int size){
            if (size > m_cap){
                int cap = (m_cap == 0 ? 1 : m_cap);
                while (cap < size)
                    cap *= 2;
                T * mem = new T[cap]();
                for (int i = 0; i < m_size; ++i)
                    mem[i] = m_mem[i];
                delete[] m_mem;
                m_mem = mem;
                m_cap = cap;
            }
        }

        void swap(mvector& m){
            std::swap(m_mem, m.m_mem);
            std::swap(m_cap, m.m_cap);
            std::swap(m_size, m.m_size);
        }

        void clear(){
            delete[] m_mem;
            m_mem = nullptr;
            m_size = 0;
            m_cap = 0;
        }
        T * begin(){
            return m_mem;
        }
        const T * begin() const {
            return m_mem;
        }
        T * end(){
            return m_mem + m_size;
        }
        const T * end() const {
            return m_mem + m_size;
        }
        
    private:
        T * m_mem = nullptr;
        int m_size = 0;
        int m_cap = 0;

};







#endif

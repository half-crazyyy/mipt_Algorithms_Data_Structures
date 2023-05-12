#ifndef Hash_h
#define Hash_h
#include <vector>
#include <list>
#include <stdexcept>

template <typename Tkey, typename Tval>
class mhash{
public:
    void insert(Tkey key, Tval val){
        reserve(m_size + 1);
        if (insert(vect, key, val))
            ++m_size;
    }
    void remove(Tkey key){
        size_t h_key = std::hash<Tkey>()(key)%vect.size();
        for (auto it = vect[h_key].begin(); it != vect[h_key].end(); ++it){
            if (it->first == key){
                vect[h_key].erase(it);
                --m_size;
                return;
            }
        }
    }
    Tval & operator [](Tkey key){
        reserve(m_size + 1);
        size_t h_key = std::hash<Tkey>()(key)%vect.size();
        for (auto & kv : vect[h_key])
            if (kv.first == key)
                return kv.second;
        vect[h_key].push_back({key,Tval()});
        m_size++;
        return operator[](key);
    }
    int size(){
        return m_size;
    }
    void reserve(int size){
       if (size > 3*vect.size()/4){
            int cap = (vect.size() == 0 ? 8 : vect.size());
            while (cap < size)
                cap *= 2;
            std::vector<std::list<std::pair<Tkey,Tval>>> v1(cap);
            for (auto & lst : vect)
                for (auto & kv : lst)
                    insert(v1, kv.first, kv.second);
            v1.swap(vect);
       } 
    }
private:
    static bool insert(std::vector<std::list<std::pair<Tkey,Tval>>> & vect, Tkey key, Tval val){
        size_t h_key = std::hash<Tkey>()(key)%vect.size();
        for (auto kv : vect[h_key]){    
            if (kv.first == key)
                return false;
        }
        vect[h_key].push_back({key,val});
        return true;
    }

    std::vector<std::list<std::pair<Tkey,Tval>>> vect;
    int m_size = 0;
};














#endif
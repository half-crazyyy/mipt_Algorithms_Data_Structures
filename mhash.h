#ifndef Hash_h
#define Hash_h
#include <vector>
#include <list>
#include <stdexcept>

template <typename Tkey, typename Tval>
class mhash{
    //метод цепочек
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
        return vect[h_key].back().second;
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


template<class Tkey>
class muset
{
    enum state
    {
        empty=0,
        filled,
        deleted
    };
    struct record
    {
        Tkey key;
        state state = empty;
    };

    class iterator{
    public:
        const Tkey & operator * () const{
            return m_buffer[i].key;
        }
        const iterator & operator ++ () const{
            do ++i;
            while(i<m_buffer.size() && m_buffer[i].state != filled);
            return *this;
        }
        bool operator ==(const iterator & it) const {
            return it.i == i;
        }
        bool operator !=(const iterator & it) const {
            return it.i != i;
        }
    private:
        friend class muset;
        const std::vector<record> & m_buffer;
        mutable int i;
        iterator(const std::vector<record> & m_buffer, int i): m_buffer(m_buffer), i(i){
            while(i<m_buffer.size() && m_buffer[i].state != filled)
                ++i;
        }
    };

public:
    bool contains(const Tkey &key){
        if(m_size == 0)
            return false;
        int h = std::hash<Tkey>()(key) % m_buffer.size();
        for(int i = 0; i<m_buffer.size(); ++i){
            switch (m_buffer[h].state)
            {
            case empty:
                return false;
            case filled:
                if(m_buffer[h].key == key)
                    return true;
                break;
            case deleted:
                break;
            }
            h = (h + i + 1) % m_buffer.size();
        }
        return false;
    }

    void insert(const Tkey &key)
    {
        if(contains(key))
            return;
        Tkey key1 = key;
        reserve(m_size+1);
        int h = std::hash<Tkey>()(key1) % m_buffer.size();
        for(int i = 0; i<m_buffer.size(); ++i){
            switch (m_buffer[h].state)
            {
            case empty:
            case deleted:
                m_buffer[h].key = std::move(key1);
                m_buffer[h].state = filled;
                ++m_size;
                return;
            case filled:
                break;
            }
            h = (h + i + 1) % m_buffer.size();
        }
    }

    void remove(const Tkey &key)
    {
        int h = std::hash<Tkey>()(key) % m_buffer.size();
        for(int i = 0; i<m_buffer.size(); ++i){
            switch (m_buffer[h].state)
            {
            case empty:
                return;
            case filled:
                if(m_buffer[h].key == key){
                    m_buffer[h].key = Tkey();
                    m_buffer[h].state = deleted;
                    --m_size;
                    return;
                }
                break;
            case deleted:
                break;
            }
            h = (h + i + 1) % m_buffer.size();
        }
    }

    void reserve(int size){
        if (size > 3*m_buffer.size()/4){
            int cap = (m_buffer.size() == 0 ? 8 : m_buffer.size());
            while (cap < size)
                cap *= 2;
            std::vector<record> v1(cap);
            std::hash<Tkey> hash_func;
            for (record & r : m_buffer){
                int h = hash_func(r.key) % v1.size();
                for(int i = 0; i<v1.size(); ++i){
                    switch (m_buffer[h].state)
                    {
                    case empty:
                        v1[h].key = std::move(r.key);
                        v1[h].state = filled;
                        break;
                    case deleted:
                        break;
                    case filled:
                        break;
                    }
                    h = (h + i + 1) % v1.size();
                }
            }
            v1.swap(m_buffer);
       } 
    }
    const iterator begin() const {
        return iterator(m_buffer, 0);
    }
    const iterator end() const {
        return iterator(m_buffer, m_buffer.size());
    }

private:
    std::vector<record> m_buffer;
    int m_size = 0;
};

template<class Tkey, class Tval>
class mumap
{
    enum state
    {
        empty=0,
        filled,
        deleted
    };
    struct record
    {
        Tkey key;
        Tval val;
        state state = empty;
    };

    class iterator{
    public:
        const Tkey & operator * () const{
            return m_buffer[i].key;
        }
        const iterator & operator ++ () const{
            do ++i;
            while(i<m_buffer.size() && m_buffer[i].state != filled);
            return *this;
        }
        iterator & operator ++ (){
            do ++i;
            while(i<m_buffer.size() && m_buffer[i].state != filled);
            return *this;
        }
        bool operator ==(const iterator & it) const {
            return it.i == i;
        }
        bool operator !=(const iterator & it) const {
            return it.i != i;
        }
    private:
        friend class mumap;
        std::vector<record> & m_buffer;
        mutable int i;
        iterator(const std::vector<record> & m_buffer, int i): m_buffer(const_cast<std::vector<record>&>(m_buffer)), i(i){
            while(i<m_buffer.size() && m_buffer[i].state != filled)
                ++i;
        }
    };

public:
    bool contains(const Tkey &key){
        if(m_size == 0)
            return false;
        int h = std::hash<Tkey>()(key) % m_buffer.size();
        for(int i = 0; i<m_buffer.size(); ++i){
            switch (m_buffer[h].state)
            {
            case empty:
                return false;
            case filled:
                if(m_buffer[h].key == key)
                    return true;
                break;
            case deleted:
                break;
            }
            h = (h + i + 1) % m_buffer.size();
        }
        return false;
    }

    void insert(const Tkey &key, const Tval &val)
    {
        if(contains(key))
            return;
        Tkey key1 = key;
        Tval val1 = val;
        reserve(m_size+1);
        int h = std::hash<Tkey>()(key1) % m_buffer.size();
        for(int i = 0; i<m_buffer.size(); ++i){
            switch (m_buffer[h].state)
            {
            case empty:
            case deleted:
                m_buffer[h].key = std::move(key1);
                m_buffer[h].val = std::move(val1);
                m_buffer[h].state = filled;
                ++m_size;
                return;
            case filled:
                break;
            }
            h = (h + i + 1) % m_buffer.size();
        }
    }

    void remove(const Tkey &key)
    {
        int h = std::hash<Tkey>()(key) % m_buffer.size();
        for(int i = 0; i<m_buffer.size(); ++i){
            switch (m_buffer[h].state)
            {
            case empty:
                return;
            case filled:
                if(m_buffer[h].key == key){
                    m_buffer[h].key = Tkey();
                    m_buffer[h].val = Tval();
                    m_buffer[h].state = deleted;
                    --m_size;
                    return;
                }
                break;
            case deleted:
                break;
            }
            h = (h + i + 1) % m_buffer.size();
        }
    }

    void reserve(int size){
        if (size > 3*m_buffer.size()/4){
            int cap = (m_buffer.size() == 0 ? 8 : m_buffer.size());
            while (cap < size)
                cap *= 2;
            std::vector<record> v1(cap);
            std::hash<Tkey> hash_func;
            for (record & r : m_buffer){
                int h = hash_func(r.key) % v1.size();
                for(int i = 0; i<v1.size(); ++i){
                    switch (m_buffer[h].state)
                    {
                    case empty:
                        v1[h].key = std::move(r.key);
                        v1[h].val = std::move(r.val);
                        v1[h].state = filled;
                        break;
                    case deleted:
                        break;
                    case filled:
                        break;
                    }
                    h = (h + i + 1) % v1.size();
                }
            }
            v1.swap(m_buffer);
       } 
    }
    const iterator begin() const {
        return iterator(m_buffer, 0);
    }
    iterator begin(){
        return iterator(m_buffer, 0);
    }
    const iterator end() const {
        return iterator(m_buffer, m_buffer.size());
    }
    iterator end(){
        return iterator(m_buffer, m_buffer.size());
    }

    Tval& operator[] (const Tkey& key){
        if(contains(key)){
            int h = std::hash<Tkey>()(key) % m_buffer.size();
            for(int i = 0; i<m_buffer.size(); ++i){
                switch (m_buffer[h].state)
                {
                case filled:
                    if(m_buffer[h].key == key)
                        return m_buffer[h].val;
                    break;
                case deleted:
                    break;
                }
                h = (h + i + 1) % m_buffer.size();
            }
        }
        Tkey key1 = key;
        insert(key, Tval());
        return operator[](key1);
    }

private:
    std::vector<record> m_buffer;
    int m_size = 0;
};

#endif
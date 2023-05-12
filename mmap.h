#ifndef MMAP_H
#define MMAP_H
#include <vector>
#include <stdexcept>
#include <iostream>

template <class Key, class Value>
class mmap
{
private:
    struct node
    {
        Key key = 0;
        Value data = 0;
        int height = 1;
        node * left = nullptr;
        node * right = nullptr;
        node * parent = nullptr;

        int left_height(){
            return left ? left->height : 0;
        }

        int right_height(){
            return right ? right->height : 0;
        }

        int dh(){
            return right_height() - left_height();
        }

        void update(){
            height = std::max(left_height(), right_height()) + 1;
            if (left)
                left->parent = this;
            if (right)
                right->parent = this;
        }

    };
    node * m_root = nullptr;
    bool contains(const Key & key, node *n)
    {
        if (n == nullptr)
            return false;
        if (key < n->key)
            return contains(key, n->left);
        if (key > n->key)
            return contains(key, n->right);
        return true;
    }

    void insert(const Key & key, const Value & data, node *&n)
    {
        if (n == nullptr)
            n = new node {key, data};
        else if (key < n->key)
            insert(key, data, n->left);
        else if (key > n->key)
            insert(key, data, n->right);

        balance(n);
    }

    void remove_right_minimum(node *& n, Key & key, Value & data)
    {
        if (n->left == nullptr)
        {
            node * x = n;
            n = x->right;
            key = x->key;
            data = x->data;
            delete x;
            return;
        }
        remove_right_minimum(n->left, key, data);
        balance(n);
    }

    void remove(const Key & key, node *&n)
    {
        if (n == nullptr)
            return;
        else if (key < n->key)
            remove(key, n->left);
        else if (key > n->key)
            remove(key, n->right);
        else
        {
            if (n->right == nullptr)
            {
                node * x = n;
                n = x->left;
                delete x;

            }
            else if (n->left == nullptr)
            {
                node * x = n;
                n = x->right;
                delete x;
            }
            else
            {
                remove_right_minimum(n->right, n->key, n->data);
            }
        }
        balance(n);
    }

    void left_little_rotate(node *&n) {
        node *x = n->right;
        n->right = x->left;
        x->left = n;
        n->update();
        x->update();
        n = x;
    }

    void right_little_rotate(node *&n) {
        node *x = n->left;
        n->left = x->right;
        x->right = n;
        n->update();
        x->update();
        n = x;
    }

    void balance(node *&n){
        n->update();
        if (n->dh()<=-2){
            if (n->left->dh()>0)
                left_little_rotate(n->left);
            right_little_rotate(n);
        }
        else if (n->dh()>=2){
            if (n->right->dh()<0)
                right_little_rotate(n->right);
            left_little_rotate(n);
        }
    }

    void find_or_insect(node *&n,node *& r1, const Key & key){
        if (n == nullptr)
            r1 =  (n = new node {key});
        else if (key < n->key)
            find_or_insect(n->left,r1, key);
        else if (key > n->key)
            find_or_insect(n->right,r1, key);
        else
            r1 = n;
        balance(n);
    }

//    static void print(node *n, std::ostream & o){
//        if (n==nullptr)
//            return;
//        print(n->left, o);
//        o<<'{'<<n->key<<','<<n->data<<'}'<<',';
//        print(n->right , o);
//    }

    void clear(node *n){
        if (n==nullptr)
            return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

public:

    class iterator{
    public:
        friend class mmap;
        std::pair <const Key &, Value &> operator * (){
            return {n->key, n->data};
        }
        const std::pair <const Key &, const Value &> operator * () const{
            return {n->key, n->data};
        }
        iterator & operator ++ (){
            inc();
            return *this;
        }
        const iterator & operator ++ () const{
            inc();
            return *this;
        }
        bool operator ==(const iterator & it) const {
            return it.n == n;
        }
        bool operator !=(const iterator & it) const {
            return it.n != n;
        }
    private:
        mutable node * n;
        iterator( node *n): n(n) {}

        void inc() const{
            if (n->right){
                n=n->right;
                while (n->left)
                    n=n->left;
                return;
            }
            while (n->parent){
                if (n->parent->left == n){
                    n = n->parent;
                    return;
                }
                n = n->parent;
            }
            n = nullptr;
            return;
        }
    };


    mmap() = default;
    mmap(std::initializer_list <std::pair <Key, Value>> list){
        for (auto value: list)
            insert(value.first, value.second);
    }

    mmap(const mmap & m){
        for (auto value: m)
            insert(value.first, value.second);
    }

    ~mmap(){
        clear();
    }

    bool contains(const Key & key)
    {
       return contains(key, m_root);
    }
    void insert(const Key & key, const Value & data)
    {
        insert(key, data, m_root);
        m_root->parent = nullptr;
    }
    void remove(const Key & key)
    {
        remove(key, m_root);
        m_root->parent = nullptr;
    }

    Value & operator[](const Key & key){
        node * r1 = nullptr;
        find_or_insect(m_root, r1, key);
        m_root->parent = nullptr;
        return r1->data;
    }

    friend std::ostream & operator<<(std::ostream & o, mmap & m){
        std::cout<<'{';
        for (auto it : m)
            o<<'{'<<it.first<<','<<it.second<<'}'<<',';
        std::cout<<'}';
        return o;
    }

    mmap & operator=(std::initializer_list <std::pair <Key, Value>> list){
        clear();
        for (auto value: list)
            insert(value.first, value.second);
        return *this;
    }

    mmap & operator=(const mmap & m){
        clear();
        for (auto value: m)
            insert(value.first, value.second);
        return *this;
    }

    bool empty(){
        return m_root == nullptr;
    }

    void clear(){
        clear(m_root);
        m_root = nullptr;
    }

    iterator begin(){
        node * n = m_root;
        while (n->left)
            n = n->left;
        return iterator(n);
    }
    const iterator begin() const {
        node * n = m_root;
        while (n->left)
            n = n->left;
        return iterator(n);
    }
    iterator end(){
        return iterator(nullptr);
    }
    const iterator end() const {
        return iterator(nullptr);
    }
};


#endif // MMAP_H

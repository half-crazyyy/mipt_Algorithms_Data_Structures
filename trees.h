
#ifndef Trees_H
#define Trees_H
#include <vector>
#include <iostream>

class bin_search_tree
{
private:
    struct node
    {
        int key = 0;
        node * left = nullptr;
        node * right = nullptr;
    };
    node * m_root = nullptr;

    bool contains(int key, node *n)
    {
        if (n == nullptr)
            return false;
        if (key < n->key)
            return contains(key, n->left);
        if (key > n->key)
            return contains(key, n->right);
        return true;
    }

    void insert(int key, node *&n)
    {
        if (n == nullptr)
            n = new node {key};
        else if (key < n->key)
            insert(key, n->left);
        else if (key > n->key)
            insert(key, n->right);
    }

    int remove_right_minimum(node *& n)
    {
        if (n->left == nullptr)
        {
            node * x = n;
            n = x->right;
            int key = x->key;
            delete x;
            return key;
        }
        return remove_right_minimum(n->left);
    }

    void remove(int key, node *&n)
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
                n->key = remove_right_minimum(n->right);
            }
        }
    }



public:
    bool contains(int key)
    {
       return contains(key, m_root); 
    }
    void insert(int key)
    {
        insert(key, m_root);
    }
    void remove(int key)
    {
        remove(key, m_root);
    }
};

class avl_search_tree
{
private:
    struct node
    {
        int key = 0;
        int height = 1;
        node * left = nullptr;
        node * right = nullptr;

        int left_height(){
            return left ? left->height : 0;
        }

        int right_height(){
            return right ? right->height : 0;
        }

        int dh(){
            return right_height() - left_height();
        }

        void update_height(){
            height = std::max(left_height(), right_height()) + 1;
        }
    };
    node * m_root = nullptr;
    bool contains(int key, node *n)
    {
        if (n == nullptr)
            return false;
        if (key < n->key)
            return contains(key, n->left);
        if (key > n->key)
            return contains(key, n->right);
        return true;
    }

    void insert(int key, node *&n)
    {
        if (n == nullptr)
            n = new node {key};
        else if (key < n->key)
            insert(key, n->left);
        else if (key > n->key)
            insert(key, n->right);
        balance(n);
    }

    int remove_right_minimum(node *& n)
    {
        if (n->left == nullptr)
        {
            node * x = n;
            n = x->right;
            int key = x->key;
            delete x;
            return key;
        }
        int key = remove_right_minimum(n->left);
        balance(n);
        return key;
    }

    void remove(int key, node *&n)
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
                n->key = remove_right_minimum(n->right);
            }
        }
        balance(n);
    }

    void left_little_rotate(node *&n) {
        node *x = n->right;
        n->right = x->left;
        x->left = n;
        n->update_height();
        x->update_height();
        n = x;
    }

    void right_little_rotate(node *&n) {
        node *x = n->left;
        n->left = x->right;
        x->right = n;
        n->update_height();
        x->update_height();
        n = x;
    }

    void balance(node *&n){
        n->update_height();
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



public:
    bool contains(int key)
    {
       return contains(key, m_root);
    }
    void insert(int key)
    {
        insert(key, m_root);
    }
    void remove(int key)
    {
        remove(key, m_root);
    }
};

class avl_search_tree_test_balance
{
private:
    struct node
    {
        int key = 0;
        int height = 1;
        node * left = nullptr;
        node * right = nullptr;

        int left_height(){
            return left ? left->height : 0;
        }

        int right_height(){
            return right ? right->height : 0;
        }

        int dh(){
            return right_height() - left_height();
        }

        void update_height(){
            height = std::max(left_height(), right_height()) + 1;
        }
    };
    node * m_root = nullptr;

    void insert(int key, node *&n)
    {
        if (n == nullptr)
            n = new node {key};
        else if (key < n->key)
            insert(key, n->left);
        else if (key > n->key)
            insert(key, n->right);
        n->update_height();
    }

    void left_little_rotate(node *&n) {
        node *x = n->right;
        n->right = x->left;
        x->left = n;
        n->update_height();
        x->update_height();
        n = x;
    }

    void right_little_rotate(node *&n) {
        node *x = n->left;
        n->left = x->right;
        x->right = n;
        n->update_height();
        x->update_height();
        n = x;
    }

    void balance(node *&n){
        n->update_height();
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

    void print(node *n){
        if (n==nullptr)
            return;
        print(n->left);
        std::cout<<n->key<<' ';
        print(n->right);
    }

public:

    void insert(int key)
    {
        insert(key, m_root);
    }
    void balance_root(){
        balance(m_root);
    }

    void print(){
        print(m_root);

    }
};

class decart_tree
{
private:
    struct node
    {
        int key = 0;
        int priority = 0;
        node* left = nullptr;
        node* right = nullptr;
    };
    node* m_root = nullptr;

    bool contains(int key, node* n)
    {
        if (n == nullptr)
            return false;
        if (key < n->key)
            return contains(key, n->left);
        if (key > n->key)
            return contains(key, n->right);
        return true;
    }

    void split(int key, node* n, node*& left_tree, node*& right_tree)
    {
        if (n == nullptr)
        {
            left_tree = nullptr;
            right_tree = nullptr;
        }
        else if (key < n->key)
        {
            //node* split_root = n;
            //right_tree = n;
            //split(key, split_root->left, left_tree, right_tree->left);
            split(key, n->left, left_tree, n->left);  
            right_tree = n;
        }
        else if (key > n->key)
        {
            split(key, n->right, n->right, right_tree);
            left_tree = n;
        }
    }
    
    node* merge(node* left, node* right)
    {
        if (left == nullptr)
            return right;
        if (right == nullptr)
            return left;
        if (right->priority < left->priority)
        {
            left->right = merge(left->right, right);
            return left;
        }
        right->left = merge(left, right->left);
        return right;
        

    }

    void insert(int key, int priority, node*& n)
    {
        if (n == nullptr)
            n = new node{ key , priority };
        if (priority > n->priority)
        {
            node* m = new node {key, priority};
            split(key, n, m->left, m->right);
            n = m;
        }
        else if (key < n->key)
            insert(key, priority, n->left);
        else if (key > n->key)
            insert(key, priority, n->right);
    }

    int remove_right_minimum(node*& n)
    {
        if (n->left == nullptr)
        {
            node* x = n;
            n = x->right;
            int key = x->key;
            delete x;
            return key;
        }
        return remove_right_minimum(n->left);
    }

    void remove(int key, node*& n)
    {
        if (n == nullptr)
            return;
        else if (key < n->key)
            remove(key, n->left);
        else if (key > n->key)
            remove(key, n->right);
        else
        {
            node* m = n;
            n = merge(n->left, n->right);
            delete m;

        }
    }



public:
    bool contains(int key)
    {
        return contains(key, m_root);
    }
    void insert(int key, int priority)
    {
        insert(key, priority, m_root);
    }
    void remove(int key)
    {
        remove(key, m_root);
    }
};






















#endif

#ifndef Trees_H
#define Trees_H

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




























#endif
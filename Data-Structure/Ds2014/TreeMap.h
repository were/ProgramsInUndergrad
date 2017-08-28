/** @file */
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "ElementNotExist.h"
#include "iostream"
#include "ctime"
#include "cstdlib"

/**
 * TreeMap is the balanced-tree implementation of map. The iterators must
 * iterate through the map in the natural order (operator<) of the key.
 */
template<class K, class V>
class TreeMap
{
public:
    class Entry
    {
        K key;
        V value;
    public:
        Entry(K k, V v)
        {
            key = k;
            value = v;
        }

        K getKey() const
        {
            return key;
        }

        V getValue() const
        {
            return value;
        }
        V &getConstValue()
        {
            return value;
        }
        void modifyValue(V _value)
        {
            value=_value;
        }
    };

    class Iterator
    {
    public:
        /**
         * TODO Returns true if the iteration has more elements.
         */
        bool hasNext()
        {
            if(!cursor)return !base->isEmpty();
            return base->succ(cursor->elem.getKey());
        }

        /**
         * TODO Returns the next element in the iteration.
         * @throw ElementNotExist exception when hasNext() == false
         */
        const Entry &next()
        {
            if(!hasNext())throw ElementNotExist();
            if(!cursor)
            {
                for(cursor=base->root;cursor->left;cursor=cursor->left);
            }else
            {
                cursor=base->succ(cursor->elem.getKey());
            }
            return cursor->elem;
        }

        /**
         * TODO Constructor
         */
        Iterator(const TreeMap<K,V> *c=0):base(c),cursor(0)
        {
        }
    private:
        const TreeMap<K,V> *base;
        struct TreeMap<K,V>::Node *cursor;
    };

    /**
     * TODO Constructs an empty tree map.
     */
    TreeMap():amount(0),root(NULL)
    {
    }

    /**
     * TODO Destructor
     */
    ~TreeMap()
    {
        clear();
    }

    /**
     * TODO Assignment operator
     */
    TreeMap &operator=(const TreeMap &x)
    {
        if(&x!=this)
        {
            clear();
            auto it=x.iterator();
            while(it.hasNext())
            {
                auto temp=it.next();
                put(temp.getKey(),temp.getValue());
            }
        }
        return *this;
    }

    /**
     * TODO Copy-constructor
     */
    TreeMap(const TreeMap &x)
    {
        amount=0;
        root=0;
        auto it=x.iterator();
        while(it.hasNext())
        {
            auto temp=it.next();
            put(temp.getKey(),temp.getValue());
        }
    }

    /**
     * TODO Returns an iterator over the elements in this map.
     */
    Iterator iterator() const
    {
        return Iterator(this);
    }

    /**
     * TODO Removes all of the mappings from this map.
     */
    void clear()
    {
        removeall(root);
        amount=0;
        root=0;
    }

    /**
     * TODO Returns true if this map contains a mapping for the specified key.
     */
    bool containsKey(const K &key)const
    {
        auto w=root;
        while(w)
        {
            if(!(key<w->elem.getKey()) && !(w->elem.getKey()<key))
            {
                return 1;
            }
            if(key<w->elem.getKey())w=w->left;else w=w->right;
        }
        return 0;
    }

    /**
     * TODO Returns true if this map maps one or more keys to the specified value.
     */
    bool containsValue(const V &value) const
    {
        return containsValue(root,value);
    }

    /**
     * TODO Returns a const reference to the value to which the specified key is mapped.
     * If the key is not present in this map, this function should throw ElementNotExist exception.
     * @throw ElementNotExist
     */
    const V &get(const K &key) const
    {
        auto w=root;
        while(w)
        {
            if(!(key<w->elem.getKey()) && !(w->elem.getKey()<key))
            {
                return w->elem.getConstValue();
            }
            if(key<w->elem.getKey())w=w->left;else w=w->right;
        }
        throw ElementNotExist();
    }

    /**
     * TODO Returns true if this map contains no key-value mappings.
     */
    bool isEmpty() const
    {
        return (amount==0);
    }

    /**
     * TODO Associates the specified value with the specified key in this map.
     */
    void put(const K &key, const V &value)
    {
            put(root,key,value);
    }


    /**
     * TODO Removes the mapping for the specified key from this map if present.
     * If there is no mapping for the specified key, throws ElementNotExist exception.
     * @throw ElementNotExist
     */
    void remove(const K &key)
    {
        if(!containsKey(key))throw ElementNotExist();
        amount--;
        //show(root);
        remove(root,key);
    }

    /**
     * TODO Returns the number of key-value mappings in this map.
     */
    int size() const
    {
        return amount;
    }

private:
    struct Node
    {
        Entry elem;
        Node *left,*right;
        unsigned int seed;
        Node(Entry _elem,Node *_left,Node *_right):elem(_elem),left(_left),right(_right)
        {
            seed=(rand()<<31)+rand();
        }
    };

    /**
     * @param amount the size of the tree
     * @param root the root of the splay
     */
    int amount;
    Node *root;

    /**
     * TODO right rotate
     */
    void rightRotate(Node *&x)
    {
        auto y=x->left;
        x->left=y->right;
        y->right=x;
        x=y;
    }

    /**
     * TODO left rotate
     */
    void leftRotate(Node *&x)
    {
        auto y=x->right;
        x->right=y->left;
        y->left=x;
        x=y;
    }

    void put(Node *&v,const K &key,const V &value)
    {
        if(v)
        {
            if(!(v->elem.getKey()<key || key<v->elem.getKey()))
            {
                v->elem.modifyValue(value);
            }else
            {
                if(key<v->elem.getKey())
                {
                    put(v->left,key,value);
                    if(v->left->seed<v->seed)rightRotate(v);
                }else
                {
                    put(v->right,key,value);
                    if(v->right->seed<v->seed)leftRotate(v);
                }
            }
        }else
        {
            v=new Node(Entry(key,value),0,0);
            amount++;
        }
    }

    void remove(Node *&v,const K &key)
    {
        if(!(v->elem.getKey()<key || key<v->elem.getKey()))
        {
            if(!(v->left) && !(v->right))
            {
                delete v;
                v=0;
                return;
            }
            if(v->right==0)
            {
                rightRotate(v);
                remove(v->right,key);
                return;
            }
            if(v->left==0)
            {
                leftRotate(v);
                remove(v->left,key);
                return;
            }
            if(v->left->seed<v->right->seed)
            {
                rightRotate(v);
                remove(v->right,key);
            }else
            {
                leftRotate(v);
                remove(v->left,key);
            }
        }else
        {
            if(key<v->elem.getKey())remove(v->left,key);else remove(v->right,key);
        }
    }

    void removeall(Node *v)
    {
        if(!v)return;
        removeall(v->left);
        removeall(v->right);
        delete v;
    }
    /**
     * TODO Returns true if this map maps one or more keys to the specified value. (private)
     */
    bool containsValue(Node* const &v,const V &value)const
    {
        if(v==NULL)return 0;
        if(v->elem.getValue()==value)return 1;
        return containsValue(v->left,value) || containsValue(v->right,value);
    }

    Node *succ(const K &key)const
    {
        Node *w=root,*res=0;
        while(w)
        {
            if(key<w->elem.getKey())
            {
                res=w;
                w=w->left;
            }else w=w->right;
        }
        return res;
    }

    void show(Node *v)
    {
        if(!v)return;
        std::cout<<v<<" "<<v->elem.getKey()<<" "<<v->left<<" "<<v->right<<std::endl;
        show(v->left);
        show(v->right);
    }
};

#endif

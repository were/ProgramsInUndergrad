/**
 * This is a simple test of your project.
 * Passing this test does not guarantee you passing the final test,
 * as this test is extremely weak.
 * Memory status is not checked in this test. 
 */
#include "bits/stdc++.h"
#include "LinkedList.h"
#include "ArrayList.h"
#include "HashMap.h"
#include "TreeMap.h"
#include "Deque.h"
#include "PriorityQueue.h"
#include "ElementNotExist.h"
#include "IndexOutOfBound.h"
using namespace std;

const int vsize = 34;

class Info
{
private:
    string to_string(long long x) const
    {
        string s;
        while (x)
        {
            s = (char)('0' + x % 10) + s;
            x /= 10;
        }
        return s;
    }
public:
    long long id;
    string name;
    Info(long long id, string name): id(id), name(name) {}
    Info() {}
    string toString() const
    {
        return "(" + to_string(id) + ", " + name + ")";
    }
};

Info v[34] = {
Info(5120309059LL, string("SQY")),
Info(5130309008LL, string("ZYD")),
Info(5130309015LL, string("HYC")),
Info(5130309016LL, string("HYY")),
Info(5130309017LL, string("MHJ")),
Info(5130309019LL, string("W_X")),
Info(5130309021LL, string("YSQ")),
Info(5130309022LL, string("ZJR")),
Info(5130309023LL, string("ZXH")),
Info(5130309026LL, string("BJW")),
Info(5130309028LL, string("SJR")),
Info(5130309030LL, string("W F")),
Info(5130309031LL, string("WLL")),
Info(5130309032LL, string("W_C")),
Info(5130309033LL, string("W_J")),
Info(5130309045LL, string("BZH")),
Info(5130309052LL, string("LJH")),
Info(5130309056LL, string("XYF")),
Info(5130309058LL, string("C_D")),
Info(5130309059LL, string("LJJ")),
Info(5130309062LL, string("G_Y")),
Info(5130309066LL, string("CXY")),
Info(5130309067LL, string("J_Y")),
Info(5130309070LL, string("SHY")),
Info(5130309305LL, string("CZH")),
Info(5130379062LL, string("SSW")),
Info(5130379096LL, string("YJT")),
Info(5130719033LL, string("LYW")),
Info(5132029007LL, string("CJL")),
Info(5132409031LL, string("ZYY")),
Info(5132409032LL, string("GJF")),
Info(5132409033LL, string("W_T")),
Info(5132409034LL, string("ZYL")),
Info(5134139006LL, string("X_C"))};

//-----------------test LinkedList------------------------

template <class T>
void printLink(LinkedList<T> l)
{
    typename LinkedList<T>::Iterator itr = l.iterator();
    while (itr.hasNext())
    {
        T t = itr.next();
        cout << t << '\t';
    }
    cout << endl;
    cout << "End print" << endl;
}

void testLink()
{
    cout << "Test LinkedList" << endl;
    LinkedList<string> list1;
    for (int i = 0; i < vsize; ++i)
    {
       switch (i % 4)
       {
       case 0:
           list1.add(v[i].name);
           break;
       case 1:
           list1.addFirst(v[i].name);
           break;
       case 2:
           list1.addLast(v[i].name);
           break;
       case 3:
           list1.add(i / 2, v[i].name);
           break;
       }
    }
    cout << list1.isEmpty() << endl;
    printLink(list1);
    LinkedList<string> list2 = list1; 
    printLink(list2);
    LinkedList<string> list3;
    list3 = list1;
    printLink(list3);
    int cnt = 0;
    for (int i = 0; i < vsize; ++i)
    {
        cnt += list1.contains(v[i].name);
    }
    cout << cnt << endl;
    cout << list1.contains("SJTU") << endl;
    list1.set(15, "Ln");
    printLink(list1);
    cout << list1.getFirst() << '\t' << list1.getLast() << endl;
    try
    {
        cout << list1.get(100) << endl;
    }
    catch (IndexOutOfBound e)
    {
        cout << "Index out of bound" << endl;
    }
    list1.clear();
    printLink(list1);
    for (int i = vsize - 1; i >= 0; --i)
    {
        switch (i % 3)
        {
        case 0:
            list2.removeFirst();
            break;
        case 1:
            list2.removeLast();
            break;
        case 2:
            list2.removeIndex(i / 2);
            break;
        }
        if (i % 10 == 0)
        {
            printLink(list2);
        }
    }
    cout << list2.isEmpty() << endl;
    LinkedList<string>::Iterator itr = list3.iterator();
    while (itr.hasNext())
    {
        itr.next();
        itr.remove();
    }
    try
    {
        itr.remove();
    }
    catch (ElementNotExist e)
    {
        cout << "Element not exist" << endl;
    }
    cout << list3.size() << endl;
}

//-----------------test ArrayList----------------------

template <class T>
void printArray(ArrayList<T> a)
{
    typename ArrayList<T>::Iterator itr = a.iterator();
    while (itr.hasNext())
    {
        T t = itr.next();
        cout << t << '\t';
    }
    cout << endl;
    cout << "End print" << endl;
}

void testArray()
{
    cout << "Test ArrayList" << endl;
    ArrayList<string> array1;
    for (int i = 0; i < vsize; ++i)
    {
        switch (i % 2)
        {
        case 0:
            array1.add(v[i].name);
            break;
        case 1:
            array1.add(i / 2, v[i].name);
            break;
        }
    }
    cout << array1.isEmpty() << endl;
    printArray(array1);
    ArrayList<string> array2 = array1;
    printArray(array2);
    ArrayList<string> array3;
    array3 = array1;
    printArray(array3);
    int cnt = 0;
    for (int i = 0; i < vsize; ++i)
    {
        cnt += array1.contains(v[i].name);
    }
    cout << cnt << endl;
    cout << array1.contains("SJTU") << endl;
    array1.set(15, "Ln");
    printArray(array1);
    cout << array1.get(0) << '\t' << array1.get(33) << endl;
    try
    {
        cout << array1.get(100) << endl;
    }
    catch (IndexOutOfBound e)
    {
        cout << "Index out of bound" << endl;
    }
    array1.clear();
    printArray(array1);
    for (int i = vsize - 1; i >= 0; --i)
    {
        switch (i % 2)
        {
        case 0:
            array2.remove(v[i].name);
            break;
        case 1:
            array2.removeIndex(i / 2);
            break;
        }
        if (i % 10 == 0)
        {
            printArray(array2);
        }
    }
    printArray(array2);
    array2.clear();
    cout << array2.isEmpty() << endl;
    ArrayList<string>::Iterator itr = array3.iterator();
    while (itr.hasNext())
    {
        itr.next();
        itr.remove();
    }
    try
    {
        itr.remove();
    }
    catch (ElementNotExist e)
    {
        cout << "Element not exist" << endl;
    }
    cout << array3.size() << endl;
}

//----------------test HashMap-----------------------------

class Hashint
{
public:
    static int hashCode(long long n)
    {
        return n & 0x7fffffffLL;
    }
};

template <class K, class V, class H>
bool cmp(typename HashMap<K, V, H>::Entry e1,
        typename HashMap<K, V, H>::Entry e2)
{
    return H::hashCode(e1.getKey()) < H::hashCode(e2.getKey());
}

template <class K, class V, class H>
void printHash(HashMap<K, V, H> h)
{
    typename HashMap<K, V, H>::Iterator itr = h.iterator();
    vector<typename HashMap<K, V, H>::Entry> v;
    while (itr.hasNext())
    {
        v.push_back(itr.next());
    }
    sort(v.begin(), v.end(), cmp<K, V, H>);
    for (int i = 0; i < v.size(); ++i)
    {
        cout << "(" << v[i].getKey() << ", " << v[i].getValue() << ")\t";
    }
    cout << endl;
    cout << "End print" << endl;
}

void testHash()
{
    cout << "Test HashMap" << endl;
    HashMap<long long, string, Hashint> hash1;
    for (int i = 0; i < vsize; ++i)
    {
        hash1.put(v[i].id, v[i].name);
    }
    cout << hash1.size() << endl;
    cout << hash1.isEmpty() << endl;
    printHash(hash1);
    HashMap<long long, string, Hashint> hash2 = hash1;
    printHash(hash2);
    HashMap<long long, string, Hashint> hash3;
    hash3 = hash1;
    printHash(hash3);
    int cnt = 0;
    for (int i = 0; i < vsize; ++i)
    {
        cnt += hash1.containsKey(v[i].id);
        cnt += hash1.containsValue(v[i].name);
    }
    cout << cnt << endl;
    cout << hash1.containsKey(0) << endl;
    cout << hash1.containsValue("SJTU") << endl;
    hash1.put(5130719033LL, "Ln");
    printHash(hash1);
    cout << hash1.get(v[0].id) << '\t' << hash1.get(v[33].id) << endl;
    try
    {
        cout << hash1.get(0) << endl;
    }
    catch (ElementNotExist e)
    {
        cout << "Element not exist" << endl;
    }
    hash1.clear();
    printHash(hash1);
    for (int i = 0; i < vsize; ++i)
    {
        hash2.remove(v[i].id);
        if (i % 10 == 0)
        {
            printHash(hash2);
        }
    }
    cout << hash2.isEmpty() << endl;
    HashMap<long long, string, Hashint>::Iterator itr = hash3.iterator();
    while (itr.hasNext())
    {
        itr.next();
    }
    try
    {
        itr.next();
    }
    catch (ElementNotExist e)
    {
        cout << "Element not exist" << endl;
    }
    cout << hash3.size() << endl;
}

//----------------------test TreeMap--------------------------

template <class K, class V>
void printTree(TreeMap<K, V> t)
{
    typename TreeMap<K, V>::Iterator itr = t.iterator();
    while (itr.hasNext())
    {
        typename TreeMap<K, V>::Entry e = itr.next();
        cout << "(" << e.getKey() << ", " << e.getValue() << ")\t";
    }
    cout << endl;
    cout << "End print" << endl;
}

void testTree()
{
    cout << "Test TreeMap" << endl;
    TreeMap<long long, string> tree1;
    for (int i = 0; i < vsize; ++i)
    {
        tree1.put(v[i].id, v[i].name);
    }
    cout << tree1.isEmpty() << endl;
    cout << tree1.size() << endl;
    printTree(tree1);
    TreeMap<long long, string> tree2 = tree1;
    printTree(tree2);
    TreeMap<long long, string> tree3;
    tree3 = tree1;
    printTree(tree3);
    int cnt = 0;
    for (int i = 0; i < vsize; ++i)
    {
        cnt += tree1.containsKey(v[i].id);
        cnt += tree1.containsValue(v[i].name);
    }
    cout << cnt << endl;
    cout << tree1.containsKey(0) << endl;
    cout << tree1.containsValue("SJTU") << endl;
    tree1.put(5130719033LL, "Ln");
    printTree(tree1);
    cout << tree1.get(v[0].id) << '\t' << tree1.get(v[33].id) << endl;
    try
    {
        cout << tree1.get(0) << endl;
    }
    catch (ElementNotExist e)
    {
        cout << "Element not exist" << endl;
    }
    tree1.clear();
    printTree(tree1);
    for(int i = 0; i < vsize; ++i)
    {
        tree2.remove(v[i].id);
        if (i % 10 == 0)
        {
            printTree(tree2);
        }
    }
    cout << tree2.isEmpty() << endl;
    TreeMap<long long, string>::Iterator itr = tree3.iterator();
    while (itr.hasNext())
    {
        itr.next();
    }
    try
    {
        itr.next();
    }
    catch (ElementNotExist e)
    {
        cout << "Element not exist" << endl;
    }
    cout << tree3.size() << endl;
}

//-------------------test Deque---------------------------

template <class T>
void printDeque(Deque<T> q)
{
    typename Deque<T>::Iterator itr1 = q.iterator();
    while (itr1.hasNext())
    {
        cout << itr1.next() << "\t";
    }
    cout << endl;
    typename Deque<T>::Iterator itr2 = q.descendingIterator();
    while (itr2.hasNext())
    {
        cout << itr2.next() << "\t";
    }
    cout << endl;
    cout << "End print" << endl;
}

void testDeque()
{
    cout << "Test Deque" << endl;
    Deque<string> q1;
    for (int i = 0; i < vsize; ++i)
    {
        switch (i % 2)
        {
        case 0:
            q1.addFirst(v[i].name);
            break;
        case 1:
            q1.addLast(v[i].name);
            break;
        }
    }
    cout << q1.isEmpty() << endl;
    printDeque(q1);
    Deque<string> q2 = q1;
    printDeque(q2);
    Deque<string> q3;
    q3 = q1;
    printDeque(q3);
    int cnt = 0;
    for (int i = 0; i < vsize; ++i)
    {
        cnt += q1.contains(v[i].name);
    }
    cout << cnt << endl;
    cout << q1.contains("SJTU") << endl;
    q1.set(30, "Ln");
    printDeque(q1);
    cout << q1.getFirst() << "\t" << q1.getLast() << endl;
    try
    {
        cout << q1.get(100) << endl;
    }
    catch (IndexOutOfBound e)
    {
        cout << "Index out of bound" << endl;
    }
    q1.clear();
    printDeque(q1);
    for (int i = vsize - 1; i >= 0; --i)
    {
        switch (i % 2)
        {
        case 0:
            q2.removeFirst();
            break;
        case 1:
            q2.removeLast();
            break;
        }
        if (i % 10 == 0)
        {
            printDeque(q2);
        }
    }
    printDeque(q2);
    cout << q2.isEmpty() << endl;
    Deque<string> q4 = q3;
    Deque<string>::Iterator itr3 = q3.iterator();
    while (itr3.hasNext())
    {
        itr3.next();
        itr3.remove();
    }
    try
    {
        itr3.remove();
    }
    catch (ElementNotExist e)
    {
        cout << "Element not exist" << endl;
    }
    cout << q3.size() << endl;
    Deque<string>::Iterator itr4 = q4.iterator();
    while (itr4.hasNext())
    {
        itr4.next();
        itr4.remove();
    }
    try
    {
        itr4.remove();
    }
    catch (ElementNotExist e)
    {
        cout << "Element not exist" << endl;
    }
    cout << q4.size() << endl;
}

//----------------------test PriorityQueue--------------------------

bool cmp1(const Info& x, const Info& y)
{
    return x.id < y.id;
}

template <class V, class C>
void printHeap(PriorityQueue<V, C> q)
{
    typename PriorityQueue<V, C>::Iterator itr = q.iterator();
	//cout << "printing..." << endl;
    vector<V> s;
    while (itr.hasNext())
    {
        s.push_back(itr.next());
    }
	//cout << "^_^" << endl;
    sort(s.begin(), s.end(), cmp1);
    for (int i = 0; i < s.size(); ++i)
    {
        cout << s[i].toString() << '\t';
    }
    cout << endl;
    cout << "End print" << endl;
}

class Cmp
{
    public: bool operator()(const Info& a, const Info& b)
    {
        return a.id < b.id;
    }
};

void testHeap()
{
    cout << "Test PriorityQueue" << endl;
    PriorityQueue<Info, Cmp> q1;
    for (int i = 0; i < vsize; ++i)
    {
        q1.push(v[i]);
    }
    cout << q1.empty() << endl;
	//cout << "printing..." << endl;
    printHeap(q1);
    PriorityQueue<Info, Cmp> q2 = q1;
    printHeap(q2);
    PriorityQueue<Info, Cmp> q3;
    q3 = q1;
    printHeap(q3);
    ArrayList<Info> a;
    for (int i = vsize - 1; i >= 0; --i) a.add(v[i]);
    PriorityQueue<Info, Cmp> q4(a);
    while (!q1.empty())
    {
        cout << q1.front().toString() << '\t';
        q1.pop();
    }
    cout << endl;
    cout << q1.size() << endl;
    PriorityQueue<Info, Cmp>::Iterator itr = q4.iterator();
    int cnt = 0;
    while (itr.hasNext())
    {
        itr.next();
        itr.remove();
        ++cnt;
    }
    cout << cnt << endl;
    q2.clear();
    cout << q2.empty() << endl;
	//cout << "ccccccc" << endl;
}

//-----------------------------------------------------------

int main()
{
	freopen("myOut", "w", stdout);
    testLink();
    testArray();
    testHash();
    testTree();
    testDeque();
    testHeap();
    return 0;
}


#include <algorithm>
#include <cstdlib>
#include <iostream>
#include "LinkedList.h"

/** @file */
#ifndef __PRIORITYQUEUE_H
#define __PRIORITYQUEUE_H

#include "ArrayList.h"
#include "ElementNotExist.h"

using std::swap;

/**
 * This is a priority queue based on a priority priority queue. The
 * elements of the priority queue are ordered according to their 
 * natual ordering (operator<), or by a Comparator provided as the
 * second template parameter.
 * The head of this queue is the least element with respect to the
 * specified ordering (different from C++ STL).
 * The iterator does not return the elements in any particular order.
 * But it is required that the iterator will eventually return every
 * element in this queue (even if removals are performed).
 */

/*----------------------------------------------------------------------*/
/**
 * Default Comparator with respect to natural order (operator<).
 */
template <class V>
class Less {
public:
	bool operator()(const V& a, const V& b) {
		return a < b;
	}
};

/**
 * To use this priority queue, users need to either use the
 * default Comparator or provide their own Comparator of this
 * kind.
 * The Comparator should be a class with a public function
 * public: bool operator()(const V&, const V&);
 * overriding the "()" operator.
 * The following code may help you understand how to use a
 * Comparator and, especially, why we override operator().
 */


/*----------------------------------------------------------------------*/

template <class V, class C = Less<V> >
class PriorityQueue {
	V **a;
	int sz, cap;
	C cmp;

	int up(int x) {
		while(x > 1 && cmp(*a[x], *a[x / 2])) {
			swap(a[x], a[x / 2]);
			x /= 2;
		}
		return x;
	}

	int down(int x) {
		while(x * 2 <= sz) {
			int y = x * 2;
			if(y + 1 <= sz && cmp(*a[y + 1], *a[y])) {
				++y;
			}
			if(cmp(*a[y], *a[x])) {
				swap(a[y], a[x]);
				x = y;
			}
			else {
				return x;
			}
		}
		return x;
	}

	V **getMemory(int len) {
		V **ret = new V*[len];
		for(int i = 0; i < len; ++i) {
			ret[i] = NULL;
		}
		return ret;
	}

	void free() {
		if (a) {
			for(int i = 1; i <= sz; ++i) {
				delete a[i];
			}
			delete []a;
			a = NULL;
		}
	}

	void mul() {
		if(sz >= cap - 1) {
			cap = cap * 2 + 2;
			V **tmp = getMemory(cap);
			for(int i = 1; i <= sz; ++i) {
				tmp[i] = a[i];
			}
			delete []a;
			a = tmp;
		}
	}

public:
	class Iterator {
	public:
		/**
		 * TODO Returns true if the iteration has more elements.
		 */
		PriorityQueue<V, C> *x;
		int idx, nxt, pre, cnt, realSize;
		
		Iterator(PriorityQueue<V, C> *x) : x(x), idx(0), nxt(-1), pre(-1), cnt(0), realSize(x->sz){
		}
		
		bool hasNext() {
			// cout << nxt << " " << idx << " " << x->sz << endl;
			if (cnt < realSize) {
				return true;
			}
			return false;
		}

		/**
		 * TODO Returns the next element in the iteration.
		 * @throw ElementNotExist exception when hasNext() == false
		 */
		const V &next() {
			if (hasNext()) {
				++cnt;
				V *ret;
				if(nxt != -1) {
					ret = x->a[pre = nxt];
					nxt = -1;
				}
				else {
					pre = ++idx;
					ret = x->a[pre];
				}
				/*
				if(*ret == 0) {
					cout << cnt << " " << idx << " " << x->sz << " " << realSize << " " << nxt << endl;
				}
				*/
				return *ret;
			}
			throw ElementNotExist("Iteration next");
		}

		/**
		 * TODO Removes from the underlying collection the last element
		 * returned by the iterator.
		 * The behavior of an iterator is unspecified if the underlying
		 * collection is modified while the iteration is in progress in
		 * any way other than by calling this method.
		 * @throw ElementNotExist
		 */
		void remove() {
			if (pre != -1) {
				swap(x->a[pre], x->a[x->sz]);
				delete x->a[x->sz];
				if(pre == x->sz) {
					--x->sz;
					pre = -1;
					return;
				}
				if(--x->sz) {
					int tmp = x->down(x->up(pre));
					if(tmp <= idx) {
						nxt = tmp;
					}
					else {
						--idx;
					}
				}
				pre = -1;
			}
			else {
				throw ElementNotExist("Iteration remove");
			}
		}
	};

	/**
	 * TODO Constructs an empty priority queue.
	 */
	PriorityQueue() {
		cap = sz = 0;
		a = NULL;
	}

	/**
	 * TODO Destructor
	 */
	~PriorityQueue() {
		clear();
	}

	/**
	 * TODO Assignment operator
	 */
	PriorityQueue &operator=(const PriorityQueue<V, C> &x) {
		if(&x == this) {
			return *this;
		}
		clear();
		sz = x.sz;
		a = getMemory(cap = x.cap);
		cmp = x.cmp;
		for(int i = 1; i <= sz; ++i) {
			a[i] = new V(*x.a[i]);
		}
		return *this;
	}

	/**
	 * TODO Copy-constructor
	 */
	PriorityQueue(const PriorityQueue<V, C> &x) {
		sz = x.sz;
		a = getMemory(cap = x.cap);
		cmp = x.cmp;
		for(int i = 1; i <= sz; ++i) {
			a[i] = new V(*x.a[i]);
		}
	}

	/**
	 * TODO Initializer_list-constructor
	 * Constructs a priority queue over the elements in this Array List.
	 * Requires to finish in O(n) time.
	 */
	PriorityQueue(const ArrayList<V> &x) {
		for(cap = 0; cap < x.size(); cap = (cap * 2) + 2);
		a = getMemory(cap);
		sz = x.size();
		for(int i = 1; i <= sz; ++i) {
			a[i] = new V(x.get(i - 1));
		}
		for(int i = sz / 2; i >= 1; --i) {
			down(i);
		}
	}

	/**
	 * TODO Returns an iterator over the elements in this priority queue.
	 */
	Iterator iterator() {
		return Iterator(this);
	}

	/**
	 * TODO Removes all of the elements from this priority queue.
	 */
	void clear() {
		free();
		sz = cap = 0;
	}

	/**
	 * TODO Returns a const reference to the front of the priority queue.
	 * If there are no elements, this function should throw ElementNotExist exception.
	 * @throw ElementNotExist
	 */
	const V &front() const {
		if (sz) {
			return *a[1];
		}
		throw ElementNotExist("front");
	}

	/**
	 * TODO Returns true if this PriorityQueue contains no elements.
	 */
	bool empty() const {
		return sz == 0;
	}

	/**
	 * TODO Add an element to the priority queue.
	 */
	void push(const V &value) {
		mul();
		if(value == 0) {
			cout << "push..." << endl;
		}
		a[++sz] = new V(value);
		up(sz);
	}

	/**
	 * TODO Removes the top element of this priority queue if present.
	 * If there is no element, throws ElementNotExist exception.
	 * @throw ElementNotExist
	 */
	void pop() {
		if (sz) {
			swap(a[1], a[sz]);
			delete a[sz];
			--sz;
			down(1);
		}
		else {
			throw ElementNotExist("pop");
		}
	}

	/**
	 * TODO Returns the number of key-value mappings in this map.
	 */
	int size() const {
		return sz;
	}
};

#endif

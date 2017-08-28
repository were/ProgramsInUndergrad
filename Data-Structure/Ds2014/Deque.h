/** @file */
#ifndef __DEQUE_H
#define __DEQUE_H

#include "ElementNotExist.h"
#include "IndexOutOfBound.h"

/**
 * An deque is a linear collection that supports element insertion and removal at both ends.
 * The name deque is short for "double ended queue" and is usually pronounced "deck".
 * Remember: all functions but "contains" and "clear" should be finished in O(1) time.
 *
 * You need to implement both iterators in proper sequential order and ones in reverse sequential order. 
 */
template <class T>
class Deque {
	T **a;
	int cap, l, r, sz;
	void free() {
		if(a) {
			delete []a;
		}
	}
	T **getMemory(int x) {
		T **ret = new T*[x];
		for (int i = 0; i < x; ++i) {
			ret[i] = 0;
		}
		return ret;
	}
	void mul() {
		if (sz + 2 >= cap) {
			T **tmp = getMemory(cap * 2 + 1);
			for (int i = (l + 1) % cap, j = 0; i != r; i = (i + 1) % cap, ++j) {
				tmp[j] = a[i];
			}
			cap = cap * 2 + 1;
			l = cap - 1;
			r = sz;
			free();
			a = tmp;
		}
	}
public:
	class Iterator {
		Deque<T> *x;
		bool rev, pre;
		int idx;
	public:
		Iterator(Deque<T> *x, bool rev) : x(x), rev(rev) {
			pre = false;
			idx = 0;
		}
		/**
		 * TODO Returns true if the iteration has more elements.
		 */
		
		bool hasNext() {
			return idx < x->sz;
		}

		/**
		 * TODO Returns the next element in the iteration.
		 * @throw ElementNotExist exception when hasNext() == false
		 */
		const T &next() {
			if (hasNext()) {
				pre = true;
				if (rev) {
					return *x->a[(x->r - (++idx) + x->cap) % x->cap];
				}
				else {
					return *x->a[(x->l + (++idx)) % x->cap];
				}
			}
			throw ElementNotExist("next");
		}

		/**
		 * TODO Removes from the underlying collection the last element
		 * returned by the iterator
		 * The behavior of an iterator is unspecified if the underlying
		 * collection is modified while the iteration is in progress in
		 * any way other than by calling this method.
		 * @throw ElementNotExist
		 */
		void remove() {
			if (!pre) {
				throw ElementNotExist("remove");
			}
			pre = false;
			if (rev) {
				delete x->a[(x->r - idx + x->cap) % x->cap];
				for (int i = idx; i < x->sz; ++i) {
					x->a[(x->r - i + x->cap) % x->cap] = x->a[(x->r - (i + 1) + x->cap) % x->cap];
					x->a[(x->r - (i + 1) + x->cap) % x->cap] = 0;
				}
				x->l = (x->l + 1) % x->cap;
			}
			else {
				delete x->a[(x->l + idx) % x->cap];
				for (int i = idx; i < x->sz; ++i) {
					x->a[(x->l + i) % x->cap] = x->a[(x->l + i + 1) % x->cap];
					x->a[(x->l + i + 1) % x->cap] = 0;
				}
				x->r = (x->r - 1 + x->cap) % x->cap;
			}
			--idx;
			--x->sz;
		}
	};

	/**
	 * TODO Constructs an empty deque.
	 */
	Deque() {
		l = 0;
		r = 1;
		sz = 0;
		a = getMemory(cap = 4);
	}

	/**
	 * TODO Destructor
	 */
	~Deque() {
		clear();
		free();
	}

	/**
	 * TODO Assignment operator
	 */
	Deque& operator=(const Deque& x) {
		if(&x == this) {
			return *this;
		}
		clear();
		l = x.l;
		r = x.r;
		sz = x.sz;
		a = getMemory(cap = x.cap);
		for (int i = (x.l + 1) % cap; i != x.r; i = (i + 1) % cap) {
			a[i] = new T(*x.a[i]);
		}
		return *this;
	}

	/**
	 * TODO Copy-constructor
	 */
	Deque(const Deque& x) {
		l = x.l;
		r = x.r;
		sz = x.sz;
		a = getMemory(cap = x.cap);
		for (int i = (x.l + 1) % cap; i != x.r; i = (i + 1) % cap) {
			a[i] = new T(*x.a[i]);
		}
	}
	
	/**
	 * TODO Inserts the specified element at the front of this deque. 
	 */
	void addFirst(const T& e) {
		mul();
		a[l] = new T(e);
		l = (l - 1 + cap) % cap;
		++sz;
	}

	/**
	 * TODO Inserts the specified element at the end of this deque.
	 */
	void addLast(const T& e) {
		mul();
		a[r] = new T(e);
		(++r) %= cap;
		++sz;
	}

	/**
	 * TODO Returns true if this deque contains the specified element.
	 */
	bool contains(const T& e) const {
		for (int i = (l + 1) % cap; i != r; i = (i + 1) % cap) {
			if (*a[i] == e) {
				return true;
			}
		}
		return false;
	}

	/**
	 * TODO Removes all of the elements from this deque.
	 */
	void clear() {
		for (int i = (l + 1) % cap; i != r; i = (i + 1) % cap) {
			delete a[i];
		}
		free();
		l = 0;
		r = 1;
		sz = 0;
		a = new T*[cap = 4];
	}

	 /**
	  * TODO Returns true if this deque contains no elements.
	  */
	bool isEmpty() const {
		return sz == 0;
	}

	/**
	 * TODO Retrieves, but does not remove, the first element of this deque.
	 * @throw ElementNotExist
	 */
	const T& getFirst() {
		if (sz) {
			 return *a[(l + 1) % cap];
		}
		throw ElementNotExist("getFirst");
	}

	 /**
	  * TODO Retrieves, but does not remove, the last element of this deque.
	  * @throw ElementNotExist
	  */
	 const T& getLast() {
		 if (sz) {
			 return *a[(r - 1 + cap) % cap];
		 }
		 throw ElementNotExist("getLast");
	 }

	 /**
	  * TODO Removes the first element of this deque.
	  * @throw ElementNotExist
	  */
	void removeFirst() {
		if (sz) {
			(++l) %= cap;
			--sz;
			delete a[l];
		}
		else {
			throw ElementNotExist("removeFirst");
		}
	}

	/**
	 * TODO Removes the last element of this deque.
	 * @throw ElementNotExist
	 */
	void removeLast() {
		if (sz) {
			r = (r - 1 + cap) % cap;
			--sz;
			delete a[r];
		}
		else {
			throw ElementNotExist("removeLast");
		}
	}

	/**
	 * TODO Returns a const reference to the element at the specified position in this deque.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	const T& get(int index) const {
		if (index >= 0 && index < sz) {
			index = (index + l + 1) % cap;
			return *a[index];
		}
		throw IndexOutOfBound("get");
	}
	
	/**
	 * TODO Replaces the element at the specified position in this deque with the specified element.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	void set(int index, const T& e) {
		if (index >= 0 && index < sz) {
			index = (index + l + 1) % cap;
			*a[index] = e;
		}
		else {
			throw IndexOutOfBound("set");
		}
	}

	/**
	 * TODO Returns the number of elements in this deque.
	 */
	 int size() const {
		 return sz;
	 }

	 /**
	  * TODO Returns an iterator over the elements in this deque in proper sequence.
	  */
	 Iterator iterator() {
		 return Iterator(this, false);
	 }

	 /**
	  * TODO Returns an iterator over the elements in this deque in reverse sequential order.
	  */
	 Iterator descendingIterator() {
		 return Iterator(this, true);
	 }
};

#endif

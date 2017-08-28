/** @file */
#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

/**
 * The ArrayList is just like vector in C++.
 * You should know that "capacity" here doesn't mean how many elements are now in this list, where it means
 * the length of the array of your internal implemention
 *
 * The iterator iterates in the order of the elements being loaded into this list
 */
template <class T>
class ArrayList {
	T **a;
	int cap, sz;

	void freeMemory() {
		if(!a) {
			return;
		}
		for (int i = 0; i < sz; ++i) {
			delete a[i];
		}
		delete []a;
		a = 0;
	}
	
	T** newMemory(int len) {
		T **ret = new T*[len];
		for (int i = 0; i < len; ++i) {
			ret[i] = NULL;
		}
		return ret;
	}
	
	void mul() {
		if(sz + 1 >= cap) {
			T **tmp = newMemory(cap = cap * 2 + 1);
			for(int i = 0; i < cap / 2; ++i) {
				tmp[i] = a[i];
			}
			delete []a;
			a = tmp;
		}
	}

public:
	/**
	 * TODO Removes the element at the specified position in this list.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	void removeIndex(int index) {
		if (index >= 0 && index < sz) {
			delete a[index];
			for (int i = index + 1; i < sz; ++i) {
				a[i - 1] = a[i];
				a[i] = NULL;
			}
			--sz;
		}
		else {
			throw IndexOutOfBound("removeIndex");
		}
	}

	class Iterator {
		bool pre;
		int idx;
		ArrayList<T> &x;
	public:
		Iterator(ArrayList<T> &x) : pre(false), idx(0), x(x) {} 
		/**
		 * TODO Returns true if the iteration has more elements.
		 */
		bool hasNext() {
			return idx < x.size();
		}

		/**
		 * TODO Returns the next element in the iteration.
		 * @throw ElementNotExist exception when hasNext() == false
		 */
		const T &next() {
			if (hasNext()) {
				pre = true;
				return *(x.a[idx++]);
			}
			throw ElementNotExist("Iteration next");
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
			if (pre) {
				pre = false;
				x.removeIndex(--idx);
			}
			else {
				throw ElementNotExist("Iteration remove");
			}
		}
	};

	/**
	 * TODO Constructs an empty array list.
	 */
	ArrayList() {
		cap = 0;
		sz = 0;
		a = NULL;
	}

	/**
	 * TODO Destructor
	 */
	~ArrayList() {
		clear();
	}

	/**
	 * TODO Assignment operator
	 */
	ArrayList& operator=(const ArrayList<T> &x) {
		if(&x == this) {
			return *this;
		}
		clear();
		a = newMemory(cap = x.cap);
		sz = x.sz;
		for (int i = 0; i < x.sz; ++i) {
			a[i] = new T(*x.a[i]);
		}
		return *this;
	}

	/**
	 * TODO Copy-constructor
	 */
	ArrayList(const ArrayList& x) {
		a = newMemory(cap = x.cap);
		sz = x.sz;
		for (int i = 0; i < sz; ++i) {
			a[i] = new T(*x.a[i]);
		}
	}

	/**
	 * TODO Appends the specified element to the end of this list.
	 * Always returns true.
	 */
	bool add(const T& e) {
		mul();
		a[sz++] = new T(e);
		return true;
	}

	/**
	 * TODO Inserts the specified element to the specified position in this list.
	 * The range of index parameter is [0, size], where index=0 means inserting to the head,
	 * and index=size means appending to the end.
	 * @throw IndexOutOfBound
	 */
	void add(int index, const T& element) {
		if (index > sz) {
			throw IndexOutOfBound("add");
		}
		mul();
		++sz;
		for (int i = sz; i > index; --i) {
			a[i] = a[i - 1];
		}
		a[index] = new T(element);
	}

	/**
	 * TODO Removes all of the elements from this list.
	 */
	void clear() {
		freeMemory();
		sz = cap = 0;
	}

	/**
	 * TODO Returns true if this list contains the specified element.
	 */
	bool contains(const T& e) const {
		for (int i = 0; i < sz; ++i) {
			if (*a[i] == e) {
				return true;
			}
		}
		return false;
	}

	/**
	 * TODO Returns a const reference to the element at the specified position in this list.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	const T& get(int index) const {
		if (index >= 0 && index < sz) {
			return *a[index];
		}
		else {
			throw IndexOutOfBound("get");
		}
	}

	/**
	 * TODO Returns true if this list contains no elements.
	 */
	bool isEmpty() const {
		return !sz;
	}

	/**
	 * TODO Removes the first occurrence of the specified element from this list, if it is present.
	 * Returns true if it was present in the list, otherwise false.
	 */
	bool remove(const T &e) {
		for (int i = 0; i < sz; ++i) {
			if (*a[i] == e) {
				removeIndex(i);
				return true;
			}
		}
		return false;
	}

	/**
	 * TODO Replaces the element at the specified position in this list with the specified element.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	void set(int index, const T &element) {
		if (index >= 0 && index < sz) {
			delete a[index];
			a[index] = new T(element);
		}
		else {
			throw IndexOutOfBound("set");
		}
	}

	/**
	 * TODO Returns the number of elements in this list.
	 */
	int size() const {
		return sz;
	}

	/**
	 * TODO Returns an iterator over the elements in this list.
	 */
	Iterator iterator() {
		return Iterator(*this);
	}
};

#endif

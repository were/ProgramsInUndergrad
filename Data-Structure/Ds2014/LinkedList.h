/** @file */
#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include <iostream>
using namespace std;
#include "IndexOutOfBound.h"
#include "ElementNotExist.h"

/**
 * A linked list.
 *
 * The iterator iterates in the order of the elements being loaded into this list.
 */
template <class T> class LinkedList {

	int sz;

	struct Node {
		T *ky;
		Node *pre, *nxt;
		Node(T *ky, Node *pre, Node *nxt) : ky(ky), pre(pre), nxt(nxt) {}
	};

	Node *null;

public:
	class Iterator {
		Node *cur;
		bool pre;
		LinkedList<T> &x;
	public:
		Iterator(LinkedList<T> &forit) : cur(forit.null), pre(false), x(forit) {}
		/**
		 * TODO Returns true if the iteration has more elements.
		 */
		bool hasNext() {
			return cur->nxt != x.null;
		}

		/**
		 * TODO Returns the next element in the iteration.
		 * @throw ElementNotExist exception when hasNext() == false
		 */
		const T &next() {
			if (hasNext()) {
				pre = true;
				cur = cur->nxt;
				return *cur->ky;
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
			if(pre) {
				pre = false;
				--x.sz;
				cur->pre->nxt = cur->nxt;
				cur->nxt->pre = cur->pre;
				if(cur->ky) {
					delete cur->ky;
				}
				Node *tmp = cur->pre;
				delete cur;
				cur = tmp;
			}
			else {
				throw ElementNotExist("Iteration remove");
			}
		}
	};

	/**
	 * TODO Removes all of the elements from this list.
	 */
	void clear() {
		for(Node *cur = null->nxt, *nxt; cur != null; cur = nxt) {
			nxt = cur->nxt;
			delete cur->ky;
			delete cur;
		}
		null->nxt = null->pre = null;
		sz = 0;
	}

	/**
	 * TODO Returns an iterator over the elements in this list.
	 */
	Iterator iterator() {
		return Iterator(*this);
	}

	/**
	 * TODO Constructs an empty linked list
	 */
	LinkedList() {
		null = new Node(NULL, NULL, NULL);
		null->nxt = null->pre = null;
		sz = 0;
	}

	/**
	 * TODO Copy constructor
	 */
	LinkedList(const LinkedList<T> &c) {
		null = new Node(NULL, NULL, NULL);
		null->nxt = null->pre = null;
		sz = 0;
		for(Node *cur = c.null->nxt; cur != c.null; cur = cur->nxt) {
			addLast(*cur->ky);
		}
	}

	/**
	 * TODO Assignment operator
	 */
	LinkedList<T>& operator=(const LinkedList<T> &c) {
		if(&c == this) {
			return *this;
		}
		clear();
		for(Node *cur = c.null->nxt; cur != c.null; cur = cur->nxt) {
			addLast(*cur->ky);
		}
		return *this;
	}

	/**
	 * TODO Desturctor
	 */
	~LinkedList() {
		clear();
		delete null;
	}

	/**
	 * TODO Appends the specified element to the end of this list.
	 * Always returns true.
	 */
	bool add(const T& e) {
		Node *tmp = new Node(new T(e), NULL, NULL);
		null->pre->nxt = tmp;
		tmp->pre = null->pre;
		null->pre = tmp;
		tmp->nxt = null;
		++sz;
		return true;
	}

	/**
	 * TODO Inserts the specified element to the beginning of this list.
	 */
	void addFirst(const T& elem) {
		Node *tmp = new Node(new T(elem), NULL, NULL);
		tmp->nxt = null->nxt;
		tmp->nxt->pre = tmp;
		null->nxt = tmp;
		tmp->pre = null;
		++sz;
	}

	/**
	 * TODO Insert the specified element to the end of this list.
	 * Equivalent to add.
	 */
	void addLast(const T &elem) {
		add(elem);
	}

	/**
	 * TODO Inserts the specified element to the specified position in this list.
	 * The range of index parameter is [0, size], where index=0 means inserting to the head,
	 * and index=size means appending to the end.
	 * @throw IndexOutOfBound
	 */
	void add(int index, const T& element) {
		if (index >= 0 && index <= sz) {
			if (index == 0) {
				addFirst(element);
				return;
			}
			if (index == sz) {
				addLast(element);
				return;
			}
			Node *cur = null;
			while(index--) {
				cur = cur->nxt;
			}
			Node *tmp = new Node(new T(element), cur->pre, cur);
			tmp->nxt = cur->nxt;
			cur->nxt->pre = tmp;
			cur->nxt = tmp;
			tmp->pre = cur;
			++sz;
		}
		else {
			throw IndexOutOfBound("addIndex");
		}
	}

	/**
	 * TODO Returns true if this list contains the specified element.
	 */
	bool contains(const T& e) const {
		for (Node *cur = null->nxt; cur != null; cur = cur->nxt) {
			if (*cur->ky == e) {
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
			Node *ret = null->nxt;
			while (index) {
				ret = ret->nxt;
				--index;
			}
			return *ret->ky;
		}
		else {
			throw IndexOutOfBound("get");
		}
	}

	/**
	 * TODO Returns a const reference to the first element.
	 * @throw ElementNotExist
	 */
	const T& getFirst() const {
		if (!sz) {
			throw ElementNotExist("getFirst");
		}
		else {
			return *null->nxt->ky;
		}
	}

	/**
	 * TODO Returns a const reference to the last element.
	 * @throw ElementNotExist
	 */
	const T& getLast() const {
		if (!sz) {
			throw ElementNotExist("getLast");
		}
		else {
			return *null->pre->ky;
		}
	}

	/**
	 * TODO Returns true if this list contains no elements.
	 */
	bool isEmpty() const {
		return sz == 0;
	}

	/**
	 * TODO Removes the element at the specified position in this list.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	void removeIndex(int index) {
		if (index >= 0 && index < sz) {
			if(index == 0){
				removeFirst();
				return;
			}
			if(index == sz - 1){
				removeLast();
				return;
			}
			Node *cur = null->nxt;
			while (index) {
				cur = cur->nxt;
				--index;
			}
			cur->nxt->pre = cur->pre;
			cur->pre->nxt = cur->nxt;
			delete cur->ky;
			delete cur;
			--sz;
		}
		else {
			throw IndexOutOfBound("removeIndex");
		}
	}

	/**
	 * TODO Removes the first occurrence of the specified element from this list, if it is present.
	 * Returns true if it was present in the list, otherwise false.
	 */
	bool remove(const T &e) {
		int i = 0;
		for (Node *cur = null->nxt; cur != null; cur = cur->nxt, ++i) {
			if ((*cur->ky) == e) {
				removeIndex(i);
				return true;
			}
		}
		return false;
	}

	/**
	 * TODO Removes the first element from this list.
	 * @throw ElementNotExist
	 */
	void removeFirst() {
		if(sz) {
			Node *cur = null->nxt;
			cur->pre->nxt = cur->nxt;
			cur->nxt->pre = cur->pre;
			delete cur->ky;
			delete cur;
			--sz;
		}
		else {
			throw ElementNotExist("removeFirst");
		}
	}

	/**
	 * TODO Removes the last element from this list.
	 * @throw ElementNotExist
	 */
	void removeLast() {
		if(sz) { 
			Node *cur = null->pre;
			cur->pre->nxt = cur->nxt;
			cur->nxt->pre = cur->pre;
			delete cur->ky;
			delete cur;
			--sz;
		}
		else {
			throw ElementNotExist("removeFirst");
		}
	}

	/**
	 * TODO Replaces the element at the specified position in this list with the specified element.
	 * The index is zero-based, with range [0, size).
	 * @throw IndexOutOfBound
	 */
	void set(int index, const T &element) {
		if(index >= 0 && index < sz) {
			Node *cur = null->nxt;
			while (index--) {
				cur = cur->nxt;
			}
			delete cur->ky;
			cur->ky = new T(element);
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

	void show() {
		for(Node *cur = null->nxt; cur != null; cur = cur->nxt) {
			cout << *cur->ky << '\t';
		}
		cout << endl;
	}
};

#endif

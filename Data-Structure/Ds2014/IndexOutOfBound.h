/** @file IndexOutOfBound.h
 * Thrown when an index is out of range
 * For example, list.get(10); while list.size() == 5 raises this exception.
 */

#include <string>

#ifndef __INDEXOUTOFBOUND_H
#define __INDEXOUTOFBOUND_H

class IndexOutOfBound {
public:
    IndexOutOfBound() {}
    IndexOutOfBound(std::string msg) : msg(msg) {}
    std::string getMessage() const { return msg; }
private:
    std::string msg;
};
#endif

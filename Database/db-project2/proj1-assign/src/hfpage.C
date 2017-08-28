#include <iostream>
#include <stdlib.h>
#include <memory.h>

#include "hfpage.h"
#include "heapfile.h"
#include "buf.h"
#include "db.h"

#define USED (data + usedPtr)

// **********************************************************
// page class constructor

void HFPage::init(PageId pageNo)
{
	slotCnt = 0;
	slot[0] = (slot_t) {-1, -1};
	this->nextPage = this->prevPage = -1;
	this->curPage = pageNo;
	this->freeSpace = MAX_SPACE - DPFIXED + sizeof(slot_t);
	this->usedPtr = MAX_SPACE - DPFIXED;
	memset(this->data, 0, sizeof this->data);
}

// **********************************************************
// dump page utlity
void HFPage::dumpPage()
{
    int i;

    cout << "dumpPage, this: " << this << endl;
    cout << "curPage= " << curPage << ", nextPage=" << nextPage << endl;
    cout << "usedPtr=" << usedPtr << ",  freeSpace=" << freeSpace
         << ", slotCnt=" << slotCnt << endl;
   
    for (i=0; i < slotCnt; i++) {
        cout << "slot["<< i <<"].offset=" << slot[i].offset
             << ", slot["<< i << "].length=" << slot[i].length << endl;
    }
}

// **********************************************************
PageId HFPage::getPrevPage()
{
    return this->prevPage;
}

// **********************************************************
void HFPage::setPrevPage(PageId pageNo)
{

	this->prevPage = pageNo;
}

// **********************************************************
void HFPage::setNextPage(PageId pageNo)
{
	this->nextPage = pageNo;
}

// **********************************************************
PageId HFPage::getNextPage()
{
    return this->nextPage;
}

// **********************************************************
// Add a new record to the page. Returns OK if everything went OK
// otherwise, returns DONE if sufficient space does not exist
// RID of the new record is returned via rid parameter.
Status HFPage::insertRecord(char* recPtr, int recLen, RID& rid)
{
	if (recLen > available_space()) {
		return DONE;
	}
	int empty_slot = -1;
	for (int i = 0; i < slotCnt; ++i) {
		if (slot[i].offset == -1) {
			empty_slot = i;
			break;
		}
	}
	if (empty_slot == -1) {
		empty_slot = slotCnt++;
		freeSpace -= sizeof (slot_t);
	}
	slot[empty_slot] = (slot_t){usedPtr -= recLen, (short) recLen};
	memcpy(USED, recPtr, recLen);
	freeSpace -= recLen;
	rid = (RID) {this->curPage, empty_slot};
    return OK;
}

// **********************************************************
// Delete a record from a page. Returns OK if everything went okay.
// Compacts remaining records but leaves a hole in the slot array.
// Use memmove() rather than memcpy() as space may overlap.
Status HFPage::deleteRecord(const RID& rid)
{
	if (rid.slotNo < 0 || rid.slotNo > slotCnt || 
			rid.pageNo != curPage || slot[rid.slotNo].offset == -1) {
		return FAIL;
	}
	int delta = slot[rid.slotNo].length;
	int from = slot[rid.slotNo].offset;
	int total = 0;
	for (int i = 0; i < slotCnt; ++i) {
		if (slot[i].offset == -1) {
			continue;
		}
		if (slot[i].offset < from) {
			slot[i].offset += delta;
			total += slot[i].length;
		}
	}
	slot[rid.slotNo] = (slot_t) {-1, -1};
	//cout << delta << ", " << total << endl;
	memmove(USED + delta, USED, total);
	usedPtr += delta;
	freeSpace += delta;
	while (slotCnt > 0 && slot[slotCnt - 1].length == -1) {
		--slotCnt;
		freeSpace += sizeof (slot_t);
	}
    return OK;
}

// **********************************************************
// returns RID of first record on page
Status HFPage::firstRecord(RID& firstRid)
{
	int res = -1;
	for (int i = 0; i < slotCnt; ++i) {
		if (slot[i].offset == -1 || slot[i].length == -1) {
			continue;
		}
		if (res == -1 || slot[i].offset > slot[res].offset) {
			res = i;
		}
	}
	if (~res) {
		firstRid = (RID) {curPage, res};
		return OK;
	}
	return DONE;
}

// **********************************************************
// returns RID of next record on the page
// returns DONE if no more records exist on the page; otherwise OK
Status HFPage::nextRecord (RID curRid, RID& nextRid)
{
	if (curRid.slotNo < 0 || curRid.slotNo > slotCnt || 
			curRid.pageNo != curPage || slot[curRid.slotNo].offset == -1) {
		return FAIL;
	}
	for (int i = 0; i < slotCnt; ++i) {
		if (slot[i].offset + slot[i].length == slot[curRid.slotNo].offset) {
			nextRid = (RID) {this->curPage, i};
			return OK;
		}
	}
	return DONE;
}

// **********************************************************
// returns length and copies out record with RID rid
Status HFPage::getRecord(RID rid, char* recPtr, int& recLen)
{
	if (rid.slotNo < 0 || rid.slotNo > slotCnt || 
			rid.pageNo != curPage || slot[rid.slotNo].offset == -1) {
		return FAIL;
	}
	memcpy(recPtr, data + slot[rid.slotNo].offset, slot[rid.slotNo].length);
	recLen = slot[rid.slotNo].length;
    return OK;
}

// **********************************************************
// returns length and pointer to record with RID rid.  The difference
// between this and getRecord is that getRecord copies out the record
// into recPtr, while this function returns a pointer to the record
// in recPtr.
Status HFPage::returnRecord(RID rid, char*& recPtr, int& recLen)
{
	if (rid.slotNo < 0 || rid.slotNo > slotCnt || 
			rid.pageNo != curPage || slot[rid.slotNo].offset == -1) {
		return FAIL;
	}
	recPtr = data + slot[rid.slotNo].offset;
	recLen = slot[rid.slotNo].length;
    return OK;
}

// **********************************************************
// Returns the amount of available space on the heap file page
int HFPage::available_space(void)
{
	for (int i = 0; i < slotCnt; ++i) {
		if (slot[i].offset == -1) {
			return freeSpace;
		}
	}
    return freeSpace - sizeof(slot_t);
}

// **********************************************************
// Returns 1 if the HFPage is empty, and 0 otherwise.
// It scans the slot directory looking for a non-empty slot.
bool HFPage::empty(void)
{
	if (slotCnt == 0) {
		return true;
	}
	for (int i = 0; i < slotCnt; ++i) {
		if (slot[i].offset != -1) {
			return false;
		}
	}
    return true;
}


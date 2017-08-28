/*****************************************************************************/
/*************** Implementation of the Buffer Manager Layer ******************/
/*****************************************************************************/


#include "buf.h"

// Define buffer manager error messages here
//enum bufErrCodes  {...};

// Define error message here
static const char* bufErrMsgs[] = { 
// error message strings go here
};

// Create a static "error_string_table" object and register the error messages
// with minibase system 
static error_string_table bufTable(BUFMGR,bufErrMsgs);

int BufMgr::findFromHash(int pageId) {
//cerr << "Descriptor Listener: " << descriptor.size() << endl;
	int key = hashFunc(pageId);
	list<pair<int, int> > &entry = hash_table[key];
	for (auto i = entry.begin(); i != entry.end(); ++i) {
		if (i->first == pageId) {
			return i->second;
		}
	}
//cerr << "Descriptor Listener: " << descriptor.size() << endl;
	return -1;
}

bool BufMgr::putIntoHash(int pageId, int frame) {
//cerr << "Descriptor Listener: " << descriptor.size() << endl;
	if (~findFromHash(pageId)) {
		return false;
	}
	int key = hashFunc(pageId);
	list<pair<int, int> > &entry = hash_table[key];
	entry.push_back(make_pair(pageId, frame));
//cerr << "Descriptor Listener: " << descriptor.size() << endl;
	return true;
}

bool BufMgr::eraseFromHash(int pageId) {
//cerr << "Descriptor Listener: " << descriptor.size() << endl;
	if (!~findFromHash(pageId)) {
		return false;
	}
	int key = hashFunc(pageId);
	list<pair<int, int> > &entry = hash_table[key];
	for (auto i = entry.begin(); i != entry.end(); ++i) {
		if (i->first == pageId) {
			entry.erase(i);
			break;
		}
	}
//cerr << "Descriptor Listener: " << descriptor.size() << endl;
	return true;
}

BufMgr::BufMgr (int numbuf, Replacer *replacer) {
	this->bufPool = new Page[numbuf];
	for (int i = 0; i < numbuf; ++i)
		descriptor.push_back(Descriptor());
	//cerr << "Size " << this->descriptor.size() << endl;
	for (int i = 0; i < numbuf; ++i) {
		this->free.push_back(i);
	}
}

Status BufMgr::pinPage(PageId PageId_in_a_DB, Page*& page, int emptyPage) {
	//cerr << "Try to pin " << PageId_in_a_DB << endl;
	int frame = this->findFromHash(PageId_in_a_DB);
	if (frame != -1) {
		if (this->descriptor[frame].pinCnt++ == 0) {
			auto &candInfo = descriptor[frame].candInfo;
			if(candInfo.first != NULL) {
				candInfo.first->erase(candInfo.second);
				candInfo.first = NULL;
				candInfo.second = list<int>::iterator();
			}
		}
		page = bufPool + frame;
		return OK;
	}
	//cerr << "Not found!" << endl;
	if (!free.empty()) {
		//cerr << "Free!" << endl;
		frame = *free.begin();
		free.erase(free.begin());
	} else if (!hate.empty()) {
		list<int>::iterator iter = hate.end(); --iter;
		frame = *iter;
		hate.erase(iter);
		eraseFromHash(descriptor[frame].pageNo);
	} else if (!love.empty()) {
		frame = *love.begin();
		love.erase(love.begin());
		eraseFromHash(descriptor[frame].pageNo);
	} else {
		//No page to replace...
		return FAIL;
	}
	if (descriptor[frame].dirtyBit && 
			MINIBASE_DB->write_page(descriptor[frame].pageNo, bufPool + frame) != OK) {
		return FAIL;
	}
	if (MINIBASE_DB->read_page(PageId_in_a_DB, bufPool + frame) != OK) {
		return FAIL;
	}
	page = bufPool + frame;
	//cerr << "Kickout & written!" << endl;
	this->putIntoHash(PageId_in_a_DB, frame);
	//cerr << "Put?!" << endl;
	descriptor[frame] = Descriptor(PageId_in_a_DB, 1, false);
	//cerr << "Before done " << descriptor.size() << endl;
	//cerr << "Done..." << endl;
	return OK;
}//end pinPage


Status BufMgr::newPage(PageId& firstPageId, Page*& firstpage, int howmany) {
	//cerr << "Try to new " << firstPageId << endl;
  // put your code here
	if (MINIBASE_DB->allocate_page(firstPageId, howmany) != OK) {
		return FAIL;
	}
	return pinPage(firstPageId, firstpage);
}

Status BufMgr::flushPage(PageId pageid) {
	//cerr << "Try to flush " << pageid << endl;
	int frame = findFromHash(pageid);
	if (~frame) {
		if (MINIBASE_DB->write_page(pageid, bufPool + frame) != OK) {
			return FAIL;
		}
		descriptor[frame].dirtyBit = false;
		return OK;
	} else {
		return FAIL;
	}
}
    
	  
//*************************************************************
//** This is the implementation of ~BufMgr
//************************************************************
BufMgr::~BufMgr() {
	flushAllPages();
	delete[] this->bufPool;
}


//*************************************************************
//** This is the implementation of unpinPage
//************************************************************

Status BufMgr::unpinPage(PageId page_num, int dirty = FALSE, int isHate = FALSE) {
	//cerr << "?! Try to unpin " << page_num << endl;
	//cerr << "Size of des: " << descriptor.size() << endl;
	int frame = findFromHash(page_num);
	//cerr << "Unpin frame[" << frame << "]" << endl;
	if (frame == -1) {
		//cerr << "Not Found?! " << page_num << endl;
		return FAIL;
	}
	//cerr << "Size of des: " << descriptor.size() << endl;
	//cerr << descriptor[frame].pinCnt << " on it!" << endl;
	if (descriptor[frame].pinCnt <= 0) {
		//cerr << "No pin on?! " << page_num << endl;
		return FAIL;
	}
	descriptor[frame].dirtyBit = dirty;
	if (--descriptor[frame].pinCnt == 0) {
		list<int>::iterator iter;
		if (isHate) {
			hate.push_back(frame);
			iter = hate.end(); --iter;
			descriptor[frame].candInfo = make_pair(&hate, iter);
		} else {
			love.push_back(frame);
			iter = love.end(); --iter;
			descriptor[frame].candInfo = make_pair(&love, iter);
		}
	}
	return OK;
}

//*************************************************************
//** This is the implementation of freePage
//************************************************************

Status BufMgr::freePage(PageId globalPageId){
	//cerr << "?! Try to free " << globalPageId << endl;
	int frame = findFromHash(globalPageId);
	if (~frame && descriptor[frame].pinCnt > 0) {
		return FAIL;
	}
	if (~frame) {
		auto &candInfo = descriptor[frame].candInfo;
		if (candInfo.first) {
			candInfo.first->erase(candInfo.second);
		}
		descriptor[frame] = Descriptor();
		free.push_back(frame);
	}
	MINIBASE_DB->deallocate_page(globalPageId);
	return OK;
}

Status BufMgr::flushAllPages(){
	//cerr << "?! Try to flushAllPages" << endl;
	int i = 0;
	for (auto &cur: descriptor) {
		if (cur.dirtyBit) {
			if (MINIBASE_DB->write_page(cur.pageNo, bufPool + i) != OK) {
				return FAIL;
			}
			cur.dirtyBit = false;
		}
		++i;
	}
	return OK;
}

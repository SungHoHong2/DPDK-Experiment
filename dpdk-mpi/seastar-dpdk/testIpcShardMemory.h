/*
 * testIpcShardMemory.h
 *
 *  Created on: Nov 29, 2016
 *      Author: Infobank, MyungRae Kim[Harry]
 */

#ifndef TESTIPCSHARDMEMORY_H_
#define TESTIPCSHARDMEMORY_H_



#define TEXT_SIZE 1024  // total size is 2048 over that is ignored
#define KEY_ID 2016

struct shared_use_st {
    char host[6];
    int written_by_you;
    char data[TEXT_SIZE];
};



#endif /* TESTIPCSHARDMEMORY_H_ */

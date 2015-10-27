#ifndef _DATA_COLLECTION_H_
#define _DATA_COLLECTION_H_


#define JOINING                 0x01
#define REPORT                  0x03
#define CONFIRM                 0x05



int DataCollectionInit();

int DataCollectionUnInitialize();

int DataCollection(char buf[], int len);

#endif

//
// Created by g on 2020/9/26.
//

#ifndef MALOC_DYNAMICSTORE_H
#define MALOC_DYNAMICSTORE_H
#include<stdlib.h>

typedef void* StoreType;
typedef unsigned int UnUseDataLen;
typedef UnUseDataLen DataMaxLen;
typedef struct {
    StoreType* p; // 指向一个数据
    int where; // 偏离最头的那个指针多少个位置
}Point;


typedef enum {
    Faill,
    Sucess

}AddDataStatus;

typedef  struct {
    StoreType* dataSource; // 数据源指针
    Point dataStart; // 游走指针 指向有效数据第一位
    Point dataEnd;  // 游走指针 指向有效数据最后一位
    UnUseDataLen unUseDataLen; // 没有用到的数据 还有几位
    DataMaxLen dataMaxLen; // 这个堆开的内存是多少个数据

}DynamicBuffData;



void init(DynamicBuffData* data); // 刚定义BuffData时一定要调用这个函数

AddDataStatus addData(DynamicBuffData* data, StoreType d);
//void moveDataToHead(DynamicBuffData* data);
AddDataStatus getStoreData(DynamicBuffData* data, StoreType* d);
const int defaultLen = 200;


#endif //MALOC_DYNAMICSTORE_H

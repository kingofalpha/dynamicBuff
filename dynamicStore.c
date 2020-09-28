//
// Created by g on 2020/9/26.
//

#include "dynamicStore.h"


#include <stdio.h>




void init(DynamicBuffData* data){

    data->dataSource = (StoreType *)(malloc(defaultLen* sizeof(StoreType)) );

    data->dataMaxLen = defaultLen;
    data->unUseDataLen = 0;

    data->dataStart.p = NULL;
    data->dataStart.where = -1;

    data->dataEnd.p = NULL;
    data->dataEnd.where = -1;


}

AddDataStatus addData(DynamicBuffData* data, StoreType d){

    if(NULL == data->dataStart.p && NULL == data->dataEnd.p || 0 == data->unUseDataLen){
        data->dataStart.p = data->dataSource;
        data->dataEnd.p = data->dataSource;
        *(data->dataEnd.p) = d;

        ++data->unUseDataLen;
        ++data->dataEnd.where;
        ++data->dataStart.where;

        return Sucess;
    }

    if(data->unUseDataLen < data->dataMaxLen && data->dataEnd.where < data->dataMaxLen -1){
        ++data->dataEnd.p;
        *data->dataEnd.p = d;
        ++data->dataEnd.where;
        data->unUseDataLen++;
        return Sucess;
    }

    if(data->unUseDataLen < data->dataMaxLen && data->dataEnd.where == data->dataMaxLen - 1){
        moveDataToHead(data);
        return addData(data,d);

    }

    if(data->unUseDataLen  == data->dataMaxLen){
        StoreType* temp = data->dataSource;
        DataMaxLen nowLen = data->unUseDataLen;
        int i;
        data->dataSource = (StoreType *)malloc((data->dataMaxLen + defaultLen)* sizeof(StoreType));
        if(NULL == data->dataSource){
            data->dataSource = temp;
            return Faill;
        }
        data->dataMaxLen = defaultLen + data->dataMaxLen;
        data->unUseDataLen = 0;

        data->dataStart.p = NULL;
        data->dataStart.where = -1;

        data->dataEnd.p = NULL;
        data->dataEnd.where = -1;
        for(i = 0 ; i < nowLen;i++ ){
            addData(data,temp[i]);
        }
        free(temp);
        return addData(data,d);

    }

    return Faill;
}

void moveDataToHead(DynamicBuffData* data){
    StoreType *temp , *realEnd,*realStart;
    temp = data->dataSource;
    realStart = data->dataStart.p;
    realEnd = data->dataEnd.p;
    realEnd++;
    while (realStart != realEnd){
        *temp = *realStart;
        ++temp;
        ++realStart;
    }

    data->dataStart.p = data->dataSource;
    data->dataStart.where = 0;
    --temp;
    data->dataEnd.p = temp;
    data->dataEnd.where = data->unUseDataLen -1;

}


AddDataStatus getStoreData(DynamicBuffData* data, StoreType* d){

    if(data->unUseDataLen > 0){
      *d = data->dataStart.p;
      ++data->dataStart.p;
      ++data->dataStart.where;
      -- data->unUseDataLen;
        return Sucess;
    }
    if(0 == data->unUseDataLen ){
        free(data->dataSource);
        init(data);
        return Faill;
    }
}
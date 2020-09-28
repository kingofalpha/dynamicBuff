#include <iostream>
#include <list>
#include <vector>
#include <cassert>
#include<random>
using namespace std;
extern "C" {
#include "dynamicStore.h"
}

AddDataStatus putData(DynamicBuffData* data,StoreType a){
    return addData(data,a);
}

AddDataStatus popData(DynamicBuffData* data,StoreType* a){
    return getStoreData(data,a);
}

int main() {

    DynamicBuffData data;
    init(&data);
    vector<StoreType> vectors;
    std::default_random_engine random;
    const int putSize = 200;
    const int getSize = 30;

    std::uniform_int_distribution<short> us(0,200);
    for(int i = 0 ; i < putSize;i++){
        vectors.push_back(us(random));
        //cout<<(int)vectors.back()<<endl;

    }
    for(int i = 0 ; i < vectors.size();i++){
        putData(&data,vectors[i]);
        assert((i + 1 )== data.unUseDataLen);
        assert(data.dataStart.where == 0);
        assert(data.dataEnd.where == i);
        assert(data.dataStart.p != NULL);
        assert(data.dataEnd.p != NULL);

    }

    assert(data.dataEnd.where < data.dataMaxLen);
    for(int i = 0 ; i < vectors.size();i++){
        assert(vectors[i]==data.dataSource[i]);
        assert(vectors.size() == data.unUseDataLen);
    }

    assert(vectors.size()==data.unUseDataLen);
   // std::cout << data.dataMaxLen << std::endl;
    //std::cout << data.unUseDataLen << std::endl;

    for(int i = 0 ; i < getSize;i++){
        StoreType  s;
        if(Sucess== popData(&data, &s)){

        } else{
            assert(data.unUseDataLen == 0);
            assert(data.dataStart.where == -1);
            assert(data.dataEnd.where == -1);
        }

    }
    assert(data.dataEnd.where < data.dataMaxLen);
    assert(data.unUseDataLen == putSize -getSize);
    assert(data.dataEnd.where == putSize -1 );
    assert(data.dataStart.where == getSize );


    putData(&data,3);

    assert(data.dataStart.where == 0);
    assert(data.dataMaxLen == putSize);
    assert(data.unUseDataLen == putSize -getSize + 1); // 因为又调用了一次 putData(&data,3);所以要加1
    assert(data.dataEnd.where == data.unUseDataLen -1  );
    assert(data.dataEnd.where < data.dataMaxLen); // data.dataEnd.where 永远要小于 data.dataMaxLen



    //std::cout << data.dataMaxLen << std::endl;
    //std::cout << data.unUseDataLen << std::endl;

    StoreType s;
    while (Sucess == getStoreData(&data,&s));
    assert(data.unUseDataLen == 0);
    assert(data.dataStart.where == -1);
    assert(data.dataStart.p == NULL);
    assert(data.dataEnd.where == -1);
    assert(data.dataEnd.p == NULL);
    assert(data.dataMaxLen == putSize);

    vectors.clear();
    for(int i = 0 ; i < putSize + 2;i++){
        vectors.push_back(i);
        putData(&data,i);
    }

    for(int i = 0 ; i < vectors.size();i++){
        assert(vectors[i] == data.dataSource[i]);
    }

    assert(data.unUseDataLen == putSize + 2);
    assert(data.dataMaxLen == putSize*2);
    assert(data.dataStart.where == 0);
    assert(data.dataEnd.where == data.unUseDataLen -1);

    while (Sucess == getStoreData(&data,&s));
    assert(data.unUseDataLen == 0);
    assert(data.dataStart.where == -1);
    assert(data.dataStart.p == NULL);
    assert(data.dataEnd.where == -1);
    assert(data.dataEnd.p == NULL);
    assert(data.dataMaxLen == putSize);

    return 0;
}

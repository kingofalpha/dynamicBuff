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

void test1(){
    DynamicBuffData data;
    init(&data);
    vector<StoreType> vectors;
    std::default_random_engine random;
    const int putSize = 200;
    const int getSize = 30;
    void* pp = malloc(2);
    std::uniform_int_distribution<short> us(0,200);
    for(int i = 0 ; i < putSize;i++){
        vectors.push_back(pp);
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


    putData(&data,pp);

    assert(data.dataStart.where == 0);
    assert(data.dataMaxLen == putSize);
    assert(data.unUseDataLen == putSize -getSize + 1); // 因为又调用了一次 putData(&data,3);所以要加1
    assert(data.dataEnd.where == data.unUseDataLen -1  );
    assert(data.dataEnd.where < data.dataMaxLen); // data.dataEnd.where 永远要小于 data.dataMaxLen



    std::cout << data.dataMaxLen << std::endl;
    std::cout << data.unUseDataLen << std::endl;

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
        vectors.push_back(pp);
        putData(&data,pp);
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
}


typedef struct{
    void* cmd;
    int type;
}BuffCmd;
void test2(){
    DynamicBuffData cmdDatas; // 用来缓存 cmd datas
    init(&cmdDatas);
    for(int i = 0 ; i < 100; i++){
        int *p = (int*)malloc(sizeof(int));
        *p = i;
        BuffCmd * cmd = (BuffCmd*)malloc(sizeof(BuffCmd));
        cmd->cmd = p;
        cmd->type = i;
        int *k = (int*)cmd->cmd;
        //cout<< *k<<endl;
        //cout<<cmd<<endl;
        addData(&cmdDatas,cmd);

    }
    //cout<<cmdDatas.unUseDataLen<<endl;
    StoreType s;

    BuffCmd* temp;
    while (Sucess == getStoreData(&cmdDatas,&s)) {

        temp = (BuffCmd*)s;
        int *k = (int*)temp->cmd;
        cout<<*(int*)temp->cmd<<"   "<<temp->type<<endl;
    }


}


int main() {

test2();

    return 0;
}

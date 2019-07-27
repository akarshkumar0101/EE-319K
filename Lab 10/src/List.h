//
//  List.h
//  Lab 10
//
//  Created by Akarsh Kumar on 5/2/19.
//  Copyright © 2019 Akarsh Kumar. All rights reserved.
//

#ifndef List_h
#define List_h

template <class T, int MAXN>
class List {
private:
    T array[MAXN];
    int numItems;
    
    
public:
    List(){
        numItems = 0;
    }
    void add(const T& item){
        if(numItems<MAXN){
            array[numItems] = item;
            numItems++;
        }
    }
    void remove(int index) {
        if(index>=0 && index<numItems){
            for(int i=index+1;i<numItems;i++){
                array[i-1]= array[i];
            }
            numItems--;
        }
    }
    T& get(int index){
        return array[index];
    }
    
    int getIndex(const T& item){
        for(int i=0; i <numItems;i++){
            if(array[i]==item){
                return i;
            }
        }
        return -1;
    }
    bool contains(const T& item){
        return getIndex(item)!=-1;
    }
    int length(){
        return numItems;
    }
    
};



#endif /* List_h */

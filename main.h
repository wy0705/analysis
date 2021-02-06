//
// Created by wy on 2021/2/5.
//

#ifndef ANALYSIS_MAIN_H
#define ANALYSIS_MAIN_H

#endif //ANALYSIS_MAIN_H
#include "iostream"
#include "cstring"
#include <sstream>
#define MASTER 1
#define END 16
using namespace std;
class ToRedis{
public:
    //增
    char* insert(char* key,string value);

    char* update(string key,string value);

    char* deleter(char* key);

    //string select(string key,string value);

private:
    string tos(int num){
        stringstream ss;
        string str;
        ss<<num;
        ss>>str;
        return str;
    }
};
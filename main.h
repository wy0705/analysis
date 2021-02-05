//
// Created by wy on 2021/2/5.
//

#ifndef ANALYSIS_MAIN_H
#define ANALYSIS_MAIN_H

#endif //ANALYSIS_MAIN_H
#include "iostream"
#include "cstring"
#define MASTER 1
#define END 16
using namespace std;
class ToRedis{
public:
    //增
    string insert(string key,string value);

    string update(string key,string value);

    string deleter(string key,string value);

    string select(string key,string value);
//查
//增表
//删表
};
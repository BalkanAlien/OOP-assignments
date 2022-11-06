#ifndef ANGLER_H_INCLUDED
#define ANGLER_H_INCLUDED
#include "contest.h"
#include <iostream>
#pragma once
struct Angler
{
    std::string name;
    std::string contest;
    bool atLeastTwo=false;
    int count=0;
};

class AnglerEnor
{
private:
    ContestEnor _tt;
    Angler _cur;
    bool _end;
public:
    AnglerEnor(const std::string &fileName) : _tt(fileName) { }
    void first() { _tt.first(); _tt.next(); }
    void next();
    Angler current() const { return _cur; }
    bool end() const { return _end; }
};

#endif // ANGLER_H_INCLUDED

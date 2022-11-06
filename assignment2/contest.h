#ifndef CONTEST_H_INCLUDED
#define CONTEST_H_INCLUDED
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#pragma once
struct Contest
{
    std::string angler;
    std::string id;
    bool caughtCarp=false;
    int count=0;
};

class ContestEnor
{
private:
    std::ifstream _f;
    Contest _cur;
    bool _end;
public:
    enum FileError { MissingInputFile };
    ContestEnor(const std::string &fileName);
    void first() { next(); }
    void next();
    Contest current() const{ return _cur; }
    bool end() const { return _end; }
};
#endif // CONTEST_H_INCLUDED

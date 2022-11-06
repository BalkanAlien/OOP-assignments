#include "contest.h"
#include <iostream>

ContestEnor::ContestEnor(const std::string &fileName)
{
    _f.open(fileName);
    if (_f.fail())
        throw FileError::MissingInputFile;
}

void ContestEnor::next()
{
    std::string line;
    getline(_f, line, '\n');
    if (!(_end=_f.fail()))
    {
        std::istringstream is(line);
        is >> _cur.angler >> _cur.id;
        std::string fish;
        int size;
        bool flag = false;
        for (is>>fish>>size; !is.fail(); is>>fish>>size)
        {
            if(fish=="carp")
                flag=true;
                _cur.count++;
        }
        _cur.caughtCarp = flag;
    }
}



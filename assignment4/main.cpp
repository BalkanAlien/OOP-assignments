#include <iostream>
#include <fstream>
#include "../oop/library/summation.hpp"
#include "../oop/library/seqinfileenumerator.hpp"
#include "../oop/library/stringstreamenumerator.hpp"
#include "../oop/library/linsearch.hpp"

/* Print the competitions and anglers where carps were caught.  --Linear Search
Is there a contest where at least 2 anglers caught a carp? --Counting */

struct Hunt
{
    std::string fish_name;
    int fish_size;

    friend std::istream &operator>>(std::istream &is, Hunt &m)
    {
        is >> m.fish_name >> m.fish_size;
        return is;
    }
};

class MySearch : public LinSearch<Hunt>
{
    bool cond(const Hunt &e) const override { return e.fish_name == "carp"; }
};

struct Line
{
    std::string angler_name;
    std::string contest_ID;
    bool isThereCarp;
    friend std::istream &operator>>(std::istream &is, Line &m);
};

std::istream &operator>>(std::istream &is, Line &m)
{
    std::string str;
    getline(is, str, '\n');
    std::stringstream ss(str);
    ss >> m.angler_name >> m.contest_ID;
    MySearch pr;
    StringStreamEnumerator<Hunt> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    m.isThereCarp= pr.found();
    return is;
}

struct Contest
{
    std::string contest_name;
    int carp_lines = 0;
    bool atLeastTwoCarp;

    Contest() : atLeastTwoCarp(true), carp_lines(0), contest_name("") {}
    Contest(const std::string &name, int lines, bool least) : contest_name(name), carp_lines(lines), atLeastTwoCarp(least) {}
};

class caughtCarp : public Summation<Line, Contest>
{
private:
    std::string _name;

public:
    caughtCarp(const std::string &anglerName) : _name(anglerName) {}

protected:
    Contest func(const Line &e) const override
    {
        if (e.isThereCarp)
            std::cout << e.contest_ID << " " << e.angler_name << "\n";
        return Contest(e.contest_ID, e.isThereCarp ? 1 : 0, e.isThereCarp);
    }
    Contest neutral() const override { return Contest(); }
    Contest add(const Contest &a, const Contest &b) const override
    {
        return Contest(b.contest_name, a.carp_lines + b.carp_lines, a.carp_lines + b.carp_lines >= 2);
    }
    bool whileCond(const Line &e) const override { return e.contest_ID == _name; }
    void first() override {}
};

class ContestEnum : public Enumerator<Contest>
{
private:
    SeqInFileEnumerator<Line> *_f;
    Contest _Contest;
    bool _empty;
    bool _end;

public:
    ContestEnum(const std::string &fname) { _f = new SeqInFileEnumerator<Line>(fname); }
    ~ContestEnum() { delete _f; }
    void first() override
    {
        _f->first();
        next();
        if (!end())
            _empty = false;
    }
    void next() override;
    Contest current() const override { return _Contest; }
    bool end() const override { return _end; }
    bool getEmpty() const { return _empty; }
};

void ContestEnum::next()
{
    if (_end = _f->end())
        return;
    _Contest.contest_name = _f->current().contest_ID;
    _Contest.atLeastTwoCarp = false;
    _Contest.carp_lines = 0;
    caughtCarp pr(_Contest.contest_name);
    pr.addEnumerator(_f);
    pr.run();
    _Contest = pr.result();
}

class Out : public LinSearch<Contest>
{
    bool cond(const Contest &e) const override { return e.atLeastTwoCarp; }
};

int main()
{
    try
    {
        ContestEnum stenor("input.txt");
        Out pr;
        pr.addEnumerator(&stenor);
        pr.run();
        if (stenor.getEmpty())
            std::cout << "The file is empty.\n";
        else
        {
            (pr.elem().atLeastTwoCarp)
                ? std::cout << "We have found a contest where at least 2 anglers caught a carp\n"
                : std::cout << "We did not find a contest where at least 2 anglers caught a carp\n";
        }
    }
    catch (SeqInFileEnumerator<Line>::Exceptions exc)
    {
        std::cout << "File not found.\n";
    }
    return 0;
}

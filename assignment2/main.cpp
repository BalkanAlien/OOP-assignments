#include <iostream>
#include "contest.h"
#include "angler.h"
using namespace std;

//First task
//Activity: Printing competitions and anglers where carps were caught.
bool first_search(const string &fileName)
{
    int cnt=0;
    ContestEnor t(fileName);
    for(t.first(); !t.end(); t.next())
    {
        if(t.current().caughtCarp)
        {
            cnt++;
            cout<<t.current().id<<" "<<t.current().angler<<endl;
        }
    }
    return cnt>0;
}

//Second task
//Activity: Checking if there exists a competition where at least two anglers have caught a carp.
bool second_search(const string &fileName)
{
    AnglerEnor t(fileName);
    bool isThere = false;
    for (t.first(); !isThere && !t.end(); t.next())
    {
        isThere=t.current().atLeastTwo;
    }
    return isThere;
}
#define NORMAL_MODE
#ifdef NORMAL_MODE2

int main()
{
    string fileName;
    cout<<"Enter the name of the input file please: "; cin>>fileName;

    //First task
    cout<<"First task\n\n";
    try
    {
        if(!first_search(fileName)){
            cout<<"No anglers caught carps on any competition."<<endl;
        }
    }
    catch(ContestEnor::FileError err)
    {
        cout<<"Can't find input file "<<fileName<<"!"<<endl;
    }
    //Second task
    cout<<"Second task\n\n";
    try
    {
        if(second_search(fileName))
            cout<<"There exists at least one competition where at least two anglers have caught a carp."<<endl;
        else
            cout<<"There doesn't exist a competition where at least two anglers have caught a carp."<<endl;
    }
    catch(ContestEnor::FileError err)
    {
        cout<<"Can't find input file "<<fileName<<"!"<<endl;
    }
}


#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
TEST_CASE("1st task, empty file", "t0.txt")
{
    ContestEnor t("t0.txt");
    t.first();
    CHECK_FALSE(t.current().caughtCarp);
}
TEST_CASE("1st task, first angler caught carp", "t1.txt")
{
    ContestEnor t("t1.txt");
    t.first();
    CHECK(t.current().caughtCarp);
}
TEST_CASE("1st task, first 2 anglers caught carp", "t1.txt")
{
    ContestEnor t("t1.txt");
    t.first();
    CHECK(t.current().caughtCarp);
    t.next();
    CHECK(t.current().caughtCarp);
}
TEST_CASE("1st task, last angler caught carp", "t2.txt")
{
    ContestEnor t("t2.txt");
    t.first();
    while (!t.end()){
        t.next();}
    CHECK(t.current().caughtCarp);
}
TEST_CASE("1st task, no one meets the requirements", "t3.txt")
{
    ContestEnor t("t3.txt");
    t.first();
    while (!t.end())
    {
        CHECK_FALSE(t.current().caughtCarp);
        t.next();
    }
}
TEST_CASE("2nd task, empty file", "t0.txt")
{
    CHECK_FALSE(second_search("t0.txt"));
}
TEST_CASE("2nd task, first one meets the requirements", "t1.txt")
{
    CHECK_FALSE(second_search("t1.txt"));
}
TEST_CASE("2nd task, second one meets the requirements", "t4.txt")
{
    CHECK(second_search("t4.txt"));
}
TEST_CASE("2nd task, middle one meets the requirements", "t4.txt")
{
    CHECK(second_search("t4.txt"));
}
TEST_CASE("2nd task, last one meets the requirements", "t5.txt")
{
    CHECK(second_search("t5.txt"));
}
TEST_CASE("2nd task, no one meets the requirements", "t3.txt")
{
    CHECK_FALSE(second_search("t3.txt"));
}

#endif
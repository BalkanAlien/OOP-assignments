#ifndef ATHMOSPHERE_H_INCLUDED
#define ATHMOSPHERE_H_INCLUDED
#pragma once


//class of the abstract atmospheric variables (Singleton design pattern)
class AthmosphericVariable
{
public:
    virtual bool isThunderstorm() const { return false; }
    virtual bool isSunshine() const { return false; }
    virtual bool isOther() const { return false; }
    virtual ~AthmosphericVariable() { }
};

//class of Thunderstorm
class Thunderstorm : public AthmosphericVariable
{
public:
    static Thunderstorm* instance();
    bool isThunderstorm() const override { return true; }
    void static destroy()
    {
        if(nullptr != _instance)
        {
            delete _instance;
            _instance = nullptr;
        }
    }
protected:
    Thunderstorm(){}
private:
    static Thunderstorm* _instance;
};

//class of Sunshine
class Sunshine : public AthmosphericVariable
{
public:
    static Sunshine* instance();
    bool isSunshine() const override { return true; }
    void static destroy()
    {
        if(nullptr != _instance)
        {
            delete _instance;
            _instance = nullptr;
        }
    }
protected:
    Sunshine() { }
private:
    static Sunshine* _instance;
};

//class of Other Effects
class OtherEffects : public AthmosphericVariable
{
public:
    static OtherEffects* instance();
    bool isOther() const override { return true; }
    void static destroy()
    {
        if(nullptr != _instance)
        {
            delete _instance;
            _instance = nullptr;
        }
    }
protected:
    OtherEffects() { }
private:
    static OtherEffects* _instance;
};
#endif // ATHMOSPHERE_H_INCLUDED

#include "athmosphere.h"
#include "gas.h"
using namespace std;

//implementation of class Thunderstorm
Thunderstorm* Thunderstorm::_instance = nullptr;
Thunderstorm* Thunderstorm::instance()
{
    if(_instance == nullptr)
    {
        _instance = new Thunderstorm();
    }
    return _instance;
}
Sunshine* Sunshine::_instance = nullptr;
Sunshine* Sunshine::instance()
{
    if(_instance == nullptr)
    {
        _instance = new Sunshine();
    }
    return _instance;
}
OtherEffects* OtherEffects::_instance = nullptr;
OtherEffects* OtherEffects::instance()
{
    if(_instance == nullptr)
    {
        _instance = new OtherEffects();
    }
    return _instance;
}
Gas* Ozone::transformsTo(const AthmosphericVariable *var)
{
    if(var->isOther())
    {
        Gas* g = new Oxygen('X', 0.05*_thickness);
        _thickness-=0.05*_thickness;
        return g;
    }
    return nullptr;
}
Gas* CarbonDioxide::transformsTo(const AthmosphericVariable *var)
{
    if(var->isSunshine())
    {
        Gas* g = new Oxygen('X', 0.05*_thickness);
        _thickness-=0.05*_thickness;
        return g;
    }
    return nullptr;
}
Gas* Oxygen::transformsTo(const AthmosphericVariable *var)
{
    if(var->isThunderstorm())
    {
        Gas* g = new Ozone('Z', 0.5*_thickness);
        _thickness-=0.5*_thickness;
        return g;
    }
    else if(var->isSunshine())
    {
        Gas* g = new Ozone('Z', 0.05*_thickness);
        _thickness-=0.05*_thickness;
        return g;
    }
    else if(var->isOther())
    {
        Gas* g = new CarbonDioxide('C', 0.1*_thickness);
        _thickness-=0.1*_thickness;
        return g;
    }
    return nullptr;
}


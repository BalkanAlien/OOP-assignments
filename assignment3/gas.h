#ifndef GAS_H_INCLUDED
#define GAS_H_INCLUDED
#include "athmosphere.h"
#include <fstream>
//class of the abstract gases
class Gas
{
protected:
    char _type;
    double _thickness;
    Gas(char t, double e) : _type(t), _thickness(e) {}
public:
    virtual Gas* transformsTo(const AthmosphericVariable* var) = 0;
    void ascend(double e) { _thickness += e; }
    bool isThin() { return _thickness < 0.5; }
    char getType() { return _type; }
    double getThickness() { return _thickness; }
    virtual ~Gas() { }
};

//class of Ozones
class Ozone : public Gas
{
public:
    Ozone(char t, double e) : Gas(t,e) {}
    Gas* transformsTo(const AthmosphericVariable* var) override;
};

//class of Oxygens
class Oxygen : public Gas
{
public:
    Oxygen(char t, double e) : Gas(t, e) {}
    Gas* transformsTo(const AthmosphericVariable* var) override;
};

//class of Carbon Dioxides
class CarbonDioxide : public Gas
{
public:
    CarbonDioxide(char t, double e) : Gas(t, e) {}
    Gas* transformsTo(const AthmosphericVariable* var) override;
};
#endif // GAS_H_INCLUDED

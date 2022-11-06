//Title: simulation of gases
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "athmosphere.h"
#include "gas.h"
using namespace std;


void vectors(const string &fileName, vector<Gas*>&gases, vector<AthmosphericVariable*>&variables, int &layersCount)
{
    fstream file;
    file.open(fileName);
    int n;
    file >> n;
    gases.resize(n);
    string line; char c; double t;
    for (int i = 0; i < n; ++i)
    {
        file >> c >> t;
        if (c == 'X') gases[layersCount++] = new Oxygen(c,t);
        else if (c == 'Z') gases[layersCount++] = new Ozone(c,t);
        else if (c == 'C') gases[layersCount++] = new CarbonDioxide(c,t);
    }
    file >> line;
    variables.resize(line.length());
    for (int i = 0; i < line.length(); ++i)
    {
        if (line[i] == 'T')
            variables[i] = Thunderstorm::instance();
        else if (line[i] == 'S')
            variables[i] = Sunshine::instance();
        else if (line[i] == 'O')
            variables[i] = OtherEffects::instance();
    }
    file.close();
}

bool IsUpperLayerIdentical(vector<Gas*>&gases, Gas *g, int current_Layer)
{
    for (int i = current_Layer + 1; i < gases.size(); ++i)
    {
        if(g->getType() == gases[i]->getType())
        {
            gases[i]->ascend(g->getThickness());
            return true;
        }
    }
    return false;
}

void simulation(vector<Gas*>&gases, vector<AthmosphericVariable*>&variables, int &layersCount)
{
    int initialNumberOfLayers = layersCount;
    int current_layer = 0, current_variable = 0;
    while(layersCount >= 3 && layersCount != 3*initialNumberOfLayers)
    {
        if(gases[current_layer]->isThin())
        {
            gases.erase(gases.begin()+current_layer);
            layersCount--;
        }
        else
        {
            Gas *g = gases[current_layer]->transformsTo(variables[current_variable]);
            cout<<gases[current_layer]->getType()<<" "<<gases[current_layer]->getThickness()<<endl;
            if (g != nullptr)
            {
                if (IsUpperLayerIdentical(gases, g, current_layer)) { }
                    //if the upper layer is identical, it ascends
                else if(!IsUpperLayerIdentical(gases, g, current_layer) && g->isThin()) { }
                    //the layer perishes
                else if(!(IsUpperLayerIdentical(gases, g, current_layer)) && !(g->isThin()))
                {
                    gases.push_back(g);
                    layersCount++;
                    //we add the new layer on the top of the athmosphere
                }
            }
        }
        current_layer++;
        if(current_layer == gases.size()) // we begin the simulation again
        {
            current_layer = 0;
            current_variable++;
        }
        if(current_variable == variables.size())
        {
            current_variable = 0;
        }

    }
}

void destroy(vector<Gas*>&gases, vector<AthmosphericVariable*>&variables)
{
    for (int i = 0; i < gases.size(); ++i)
    {
        delete gases[i];
    }
    gases.clear();
    Thunderstorm::destroy();
    Sunshine::destroy();
    OtherEffects::destroy();
    variables.clear();
}

#ifdef NORMAL_MODE
int main()
{
    int layersCount=0;
    string fileName;
    vector<Gas*>gases;
    vector<AthmosphericVariable*>variables;
    cout<<"Enter the name of the file: ";
    cin>>fileName;
    vectors(fileName, gases, variables, layersCount);
    simulation(gases, variables, layersCount);
    destroy(gases, variables);

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include"catch.hpp"
TEST_CASE("sample input", "input1.txt")
{
    vector<Gas*>gases;
    vector<AthmosphericVariable*>variables;
    int layersCount=0;
    vectors("input1.txt", gases, variables, layersCount);
    simulation(gases,variables,layersCount);
    CHECK(gases.size()==2);
    destroy(gases,variables);
}
TEST_CASE("1 layer", "input2.txt")
{
    vector<Gas*>gases;
    vector<AthmosphericVariable*>variables;
    int layersCount=0;
    vectors("input2.txt", gases, variables, layersCount);
    simulation(gases,variables,layersCount);
    CHECK(gases.size()==1);
    destroy(gases,variables);
}
TEST_CASE("2 layers", "input3.txt")
{
    vector<Gas*>gases;
    vector<AthmosphericVariable*>variables;
    int layersCount=0;
    vectors("input3.txt", gases, variables, layersCount);
    simulation(gases,variables,layersCount);
    CHECK(gases.size()==2);
    destroy(gases,variables);
}
TEST_CASE("3 layers", "input4.txt")
{
    vector<Gas*>gases;
    vector<AthmosphericVariable*>variables;
    int layersCount=0;
    vectors("input4.txt", gases, variables, layersCount);
    simulation(gases,variables,layersCount);
    CHECK(gases.size()==2);
    destroy(gases,variables);
}
TEST_CASE("empty file", "empty.txt")
{
    vector<Gas*>gases;
    vector<AthmosphericVariable*>variables;
    int layersCount = 0;
    vectors("empty.txt", gases, variables, layersCount);
    simulation(gases,variables,layersCount);
    CHECK(gases.size()==0);
    destroy(gases,variables);
}
#endif

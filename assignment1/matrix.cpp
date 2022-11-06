#include "matrix.h"
#include <iostream>
#include <vector>
using namespace std;

Matrix::Matrix(){ //default constructor
mainDiag.clear();
minorDiag.clear();
}


Matrix::Matrix(const vector<int> &v){ //constructing the matrix by inputting all diagonal elements
    if(v.size() <= 0) throw Matrix::INVALID;
    else if (v.size() % 2 == 0){ //if matrix is even-sized
        for (unsigned int i=0; i<v.size()/2; i++){
            if(i%2==0)
                mainDiag.push_back(v[i]);
            else
                minorDiag.push_back(v[i]);
    }
        for (unsigned int i=v.size()/2; i<v.size(); i++){
            if(i%2==0)
                minorDiag.push_back(v[i]);
            else
                mainDiag.push_back(v[i]);
    }
    }
    else if(v.size() % 2 != 0){ //if matrix is odd-sized
        for (unsigned int i=0; i<v.size(); i++){
            if(i%2==0){
                mainDiag.push_back(v[i]);
            }
            else
            {
                minorDiag.push_back(v[i]);
            }

        }
    }

}

int Matrix::mainLeng() const
{
    return int (mainDiag.size());
}


int Matrix::minorLeng () const
{
    return int(minorDiag.size());
}


Matrix& Matrix::operator=(const Matrix& a)
{
    mainDiag = a.mainDiag;
    minorDiag = a.minorDiag;
    return *this;
}



Matrix::Matrix(const vector<int> &maind, const vector<int> &minord){
    mainDiag = maind;
    minorDiag = minord;
}

int Matrix::operator()(int i, int j) const { //getter
    if (i<0 || i>int (mainDiag.size()) || j<0 || j>int (mainDiag.size())) throw Matrix::OVERINDEXED;
    if(i==j)
    {
       return mainDiag[i];

    }
    if(mainLeng() % 2 ==0)
    {
        if (i+j+1 ==int (minorDiag.size()))
            return minorDiag[i];
    }
    else {
    if(i+j == int (minorDiag.size()))
        {
        if (mainLeng() % 2 !=0)
            {
            if (i > (minorLeng()/2))
                {
                    return minorDiag[i-1];
                }
            else
                return minorDiag[i];
            }
        }
    }
    return 0;
}

int& Matrix::operator()(int i, int j)  { //setter
    if (i<0 || i>int (mainDiag.size()) || j<0 || j>int (mainDiag.size())) throw Matrix::OVERINDEXED;

    if(i==j)
    {
       return mainDiag[i];
    }
    if(mainLeng() % 2 ==0)
    {
        if (i+j+1 ==int (minorDiag.size()))
            return minorDiag[i];
    }
    else {
    if(i+j == int (minorDiag.size()))
        {
        if (mainLeng() % 2 !=0)
            {
            if (i > (minorLeng()/2))
                {
                    return minorDiag[i-1];
                }
            else
                return minorDiag[i];
            }
        }
    }
    throw NULLPART;
}

Matrix operator+ (const Matrix& a, const Matrix& b){
    if((a.mainLeng() != b.mainLeng()) || (a.minorLeng() != b.minorLeng())) throw Matrix::DIFFERENT;
    Matrix c;
    c.mainDiag.resize(a.mainDiag.size());
    c.minorDiag.resize(a.minorDiag.size());
    for(int i=0; i<a.mainLeng(); i++){
        c.mainDiag[i] = a.mainDiag[i] + b.mainDiag[i];
    }
    for(int i=0; i<a.minorLeng(); i++){
        c.minorDiag[i] = a.minorDiag[i] + b.minorDiag[i];
    }
    return c;
}

Matrix operator* (const Matrix& a, const Matrix& b){
    if((a.mainLeng() != b.mainLeng()) || (a.minorLeng() != b.minorLeng())) throw Matrix::DIFFERENT;
    Matrix c;
    c.mainDiag.resize(a.mainDiag.size());
    c.minorDiag.resize(a.minorDiag.size());
    for (int i=0; i<a.mainLeng(); i++){
        c.mainDiag[i] = a.mainDiag[i] * b.mainDiag[i];
    }
    for (int i=0; i<a.minorLeng(); i++){
        c.minorDiag[i] = a.minorDiag[i] * b.minorDiag[i];
    }
    return c;
}

ostream& operator<<(ostream& os, const Matrix& a){
    int s = a.mainLeng();
    if (s%2==0) { //if the Matrix is even sized(2x2,4x4,...)
    for (int i=0; i<s; i++){
        for (int j=0; j<s; j++){
            if (i==j)
                os<<a.mainDiag[i]<<" ";
            else if(j+i+1==s)
                os<<a.minorDiag[i]<<" ";
            else
                os<<"0 ";
        }
        os<<"\n";
    }
    }
    else{ //if the Matrix is odd sized (3x3, 5x5,...) we have stored the overlapping element in the main diagonal
        for (int i=0; i<s; i++)
        {
          for (int j=0; j<s; j++)
          {
            if (i==j)
            {
                os<<a.mainDiag[i]<<" ";
            }
            else if(j+i==s-1)
            {
                if (i<s/2)
                {
                    os<<a.minorDiag[i]<<" ";
                }
                else if (i>s/2)
                {
                    os<<a.minorDiag[i-1]<<" ";
                }
            }
            else
            {
                os<<"0 ";
            }
          }
          os<<std::endl;
       }
    }
        return os;

}
istream& operator>>(istream& is, Matrix& a){
    int s;
    is >> s;
    std::vector<int> allDiag;
    if (s%2!=0) //odd-sized matrix
    {
       for (int i=0; i<2*s-1; i++)
       {
          int b;
          is >> b;
          allDiag.push_back(b);
       }
    }
    else //even sized matrix
    {
       for (int i=0; i<2*s; i++)
       {
          int b;
          is >> b;
          allDiag.push_back(b);
       }
    }
    Matrix b(allDiag);
    a = b;
    return is;
}

void Matrix::print(){
    if (mainDiag.size() < 1) throw Matrix::INVALID;
    else
        cout<<*this;

}

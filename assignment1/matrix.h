#include<iostream>
#include<vector>

//Class of both diagonals of a matrix
//Methods: getting the entry at index (i,j), adding, multiplying, printing
//Representation: elements of both diagonals of the matrix
class Matrix{
public:
    enum Exceptions{OVERINDEXED,NULLPART,DIFFERENT,INVALID};

    Matrix();//default constructor
    Matrix(const std::vector<int> &v);//constructor with input vector of diagonal elements
    Matrix(const std::vector<int> &maind, const std::vector<int> &minord);

    int operator()(int i, int j) const;
    int& operator()(int i, int j);
    Matrix& operator=(const Matrix& a);

    friend Matrix operator+ (const Matrix& a, const Matrix& b);
    friend Matrix operator* (const Matrix& a, const Matrix& b);

    friend std::ostream& operator<< (std::ostream& os, const Matrix& a);
    friend std::istream& operator>> (std::istream& is, Matrix& a);
    int mainLeng ()const;
    int minorLeng () const;
    void print();

private:
    std::vector<int> mainDiag;
    std::vector<int> minorDiag;
};

#include <iostream>
#include "matrix.h"
using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE
//class of menu for Matrix

class Menu{
public:
    void run();
private:
    Matrix a;
    Matrix b;
    void menuWrite();
    void getIndex() const;
    void adding();
    void multiplying();
    void inserting();
    void printing();
};

int main()
{
    Menu m;
    m.run();
}

void Menu::run(){
    int n=0;
    do{
        menuWrite();
        cout << endl << ">>>>" ;
        cin >> n;
        switch(n){
    case 0:
        cout<<"Goodbye!"<<endl;
        break;
    case 1:
        inserting();
        break;
    case 2:
        getIndex();
        break;
    case 3:
        adding();
        break;
    case 4:
        multiplying();
    case 5:
        printing();
        break;
    default: cout<<"Please enter a number between 0-5"<<endl;
        break;
        }
    }while(n!=0);
}

void Menu::menuWrite()
{
    cout << "0. - Quit"<<endl;
    cout << "1. - Enter Your Matrix"<<endl;
    cout << "2. - Get an Element from the matrix"<<endl;
    cout << "3. - Enter a new matrix and add it to your original matrix" <<endl;
    cout << "4. - Enter a new matrix and multiply it to your original matrix"<<endl;
    cout << "5. - Print the matrix."<<endl;
    cout << '\n'<<endl;
    cout << "Enter Your Choice : ";
}

void Menu::getIndex() const
{
    int i, j;
    cout<<"Give the index of the row:"<<endl;
    cin>>i;
    cout<<"Give the index of the column:"<<endl;
    cin>>j;
    try{
        cout<<"a["<<i<<","<<j<<"]="<<a(i,j)<<endl;
    }
    catch(Matrix::Exceptions ex){
        if(ex == Matrix::OVERINDEXED)
            cout << "Overindexing!" << endl;
        else
            cout << "Unhandled exception!" << endl;
    }
}
void Menu::inserting()
{
    try
    {
        cout << "Give the size and the items of the matrix: ";
        cin >> a;
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::INVALID)
            cout << "Invalid size!" << endl;
        else
            cout << "Unhandled exception!" << endl;
    }
}

void Menu::printing()
{
    try
    {
        a.print();
    }
    catch(const Matrix::Exceptions ex)
    {
        if(ex==Matrix::INVALID)
            cerr<<"The matrix is empty."<<endl;
        else
            cout<<"Unhandled exception."<<endl;
    }
}
void Menu::adding()
{
    try
    {
        cout<<"Enter the size of the new matrix followed by its diagonals: "<<endl;
        cin>>b;
        cout << "Sum of the matrices: " << endl;
        cout << a + b << endl;
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::INVALID)
            cout << "Invalid size!" << endl;
        if(ex == Matrix::DIFFERENT)
            cout << "Different sizes!" << endl;
    }
}

void Menu::multiplying()
{
    try
    {
        cout<<"Enter the size of the new matrix followed by its diagonals:"<<endl;
        cin>>b;
        cout << "Product of the matrices: " << endl;
        cout << a * b << endl;
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::INVALID)
            cout << "Invalid size!" << endl;
        if(ex == Matrix::DIFFERENT)
            cout << "Different sizes!" << endl;
    }
}

#else


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("create", "inp.txt"){
    const string fileName = "inp.txt";
    ifstream in(fileName.c_str());
    if(in.fail()){
        cout<<"File name error!"<<endl;
        exit(0);
    }
    Matrix c;
    in>>c;//5
    CHECK(c(0,0)==1);
    CHECK(c(0,2)==2);
    CHECK(c(1,1)==3);
    CHECK(c(2,0)==4);
    CHECK(c(2,2)==5);

    Matrix b;
    in>>b;//4
    CHECK(b(0,0)==1);
    CHECK(b(0,1)==2);
    CHECK(b(1,0)==3);
    CHECK(b(1,1)==4);

    Matrix a;
    in>>a; //1
    CHECK(a(0,0)==1);

    Matrix biig;
    in>>biig; //1
    CHECK(biig(0,0)==1);
    CHECK(biig(0,4)==2);
    CHECK(biig(1,1)==3);
    CHECK(biig(1,3)==4);
    CHECK(biig(2,2)==5);
    CHECK(biig(3,1)==6);
    CHECK(biig(3,3)==7);
    CHECK(biig(4,0)==8);
    CHECK(biig(4,4)==9);

    Matrix even;
    in >> even;
    CHECK(even(0,0)==1);
    CHECK(even(0,3)==2);
    CHECK(even(1,1)==3);
    CHECK(even(1,2)==4);
    CHECK(even(2,1)==5);
    CHECK(even(2,2)==6);
    CHECK(even(3,0)==7);
    CHECK(even(3,3)==8);

    Matrix odd;
    in >>odd;
    CHECK(odd(0,0)==1);
    CHECK(odd(0,5)==2);
    CHECK(odd(1,1)==3);
    CHECK(odd(1,4)==4);
    CHECK(odd(2,2)==5);
    CHECK(odd(2,3)==6);
    CHECK(odd(3,2)==7);
    CHECK(odd(3,3)==8);
    CHECK(odd(4,1)==9);
    CHECK(odd(4,4)==10);
    CHECK(odd(5,0)==11);
    CHECK(odd(5,5)==12);
}

TEST_CASE("getting and changing an element of the matrix", ""){
    Matrix a( {1,1,1} );
    CHECK(a(0,0) == 1);
    a(0,0) = 0;
    CHECK(a(0,0) == 0);
}


TEST_CASE("add", "inp2.txt"){
const string fileName = "inp2.txt";
ifstream in(fileName.c_str());
if(in.fail()){
    cout<<"File name error!"<<endl;
    exit(1);
}
Matrix a;
in>>a;
Matrix b;
in>>b;
Matrix c;
c=a+b; //check every nonzero item
CHECK(c(0,0)==7);
CHECK(c(0,2)==9);
CHECK(c(1,1)==11);
CHECK(c(2,0)==13);
CHECK(c(2,2)==15);
Matrix d;
d=b+a; //check every nonzero item
CHECK(d(0,0)==7);
CHECK(d(0,2)==9);
CHECK(d(1,1)==11);
CHECK(d(2,0)==13);
CHECK(d(2,2)==15);
}



TEST_CASE("multiply", "inp2.txt"){
const string fileName = "inp2.txt";
ifstream in(fileName.c_str());
if(in.fail()){
    cout<<"File name error!"<<endl;
    exit(1);
}
Matrix a;
in>>a;
Matrix b;
in>>b;
Matrix c;
c = a*b;
CHECK(c(0,0)==6);
CHECK(c(0,2)==14);
CHECK(c(1,1)==24);
CHECK(c(2,0)==36);
CHECK(c(2,2)==50);
Matrix d;
d=b*a; //check every nonzero item
CHECK(d(0,0)==6);
CHECK(d(0,2)==14);
CHECK(d(1,1)==24);
CHECK(d(2,0)==36);
CHECK(d(2,2)==50);


}

TEST_CASE("exceptions", ""){
Matrix a;
if (a.mainLeng()==3){

    try
    {
        a(3,3) = 4;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::OVERINDEXED);
    }

    try
    {
        a(-1,4) = 4;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::OVERINDEXED);
    }
}
    Matrix b;
    Matrix c;

    if (c.mainLeng()==3 && b.mainLeng()==2){

    try
    {
        c = a + b;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::DIFFERENT);
    }

    try
    {
        c = a * b;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::DIFFERENT);
    }


    try
    {
        a(1,0) = 4;
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::NULLPART);
    }

    try
    {
        int  k = a(1,0);
    }
    catch(Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::NULLPART);
    }
    }
}

#endif

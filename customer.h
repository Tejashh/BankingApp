/*customer.h*/

//
// Customer class for banking program in modern C++.
//
// << Tejash Contractor >>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 01
//

#pragma once

#include <iostream>
#include <string>

using namespace std;

//Customer class
class Customer
{
    
public:
    string Name;
    int ID;
    double Balance;
    
    //constructor:
    Customer(string name, int iD, double balance)
    : Name(name), ID(iD), Balance(balance)
    {
        
    }
    
};  //end of customor class


//transaction class
class Transaction
{

public:
    int Identity;
    double Amount;
    
    //constructor:
    Transaction(int identity, double amount)
    : Identity(identity), Amount(amount)
    {

    }
};//end of transaction class

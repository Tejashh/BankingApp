/*main.cpp*/

//
// Banking program in modern C++.
//
// <<Tejash Contractor>>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 01
//


// In Build Libraries includes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// Including customers.h file
#include "customer.h"

using namespace std;

//Beggining of the main method
int main()
{
    //initializing strings to open file
    string  customerFilename, transactionsFilename;
    
    //cin to input the file name for customer file
    cin >> customerFilename;
    
    //print the file name for customer file
    cout << customerFilename << endl;
    
    //cin to input the file name for transactions file
    cin >> transactionsFilename;
    
    //cout the file name for transactions file
    cout << transactionsFilename << endl;
    
    //use of ifstream inbulid function to open close file
    ifstream  custFile(customerFilename);
    ifstream  txFile(transactionsFilename);
    
    string line, name, iD, balance, ln;
    
    cout << std::fixed;
    cout << std::setprecision(2);   //Decimal in 2 palces
    
    // Invalid file name
    if (!custFile.good())
    {
        cout << "**ERROR: cannot open customers file: '" << customerFilename << "'" << endl;
        return -1;
    }
    if (!txFile.good())
    {
        cout << "**ERROR: cannot open transactions file: '" << transactionsFilename << "'" << endl;
        return -1;
    }
    
    
    //create Customer vector
    vector<Customer> customers;
    
    //Parse the name, ID, and balance and push it into customers vector
    while(getline(custFile,line))
    {
        stringstream ss(line);
        
        getline(ss,name,',');
        getline(ss,iD,',');
        getline(ss,balance);
        
        Customer C(name, stoi(iD), stod(balance));
        
        customers.push_back(C);
    }
    
    
    //sort the vector by its name of the customers
    sort(customers.begin(),
         customers.end(),
         [](Customer c1, Customer c2)
         {
             
             if(c1.Name < c2.Name)
                return true;
            else
                return false;
         }
    );
    
    //Starting the output
    cout << ">> Customers before:" << endl;
    
    // Printing out the customers vector
    for(Customer& c: customers)
    {
        cout << " " << c.Name << " (" << c.ID << "): $" << c.Balance << endl;
    }
    
    //Create transactions vector
    vector<Transaction> transactions;
    
    string identity, amount;
    
    //Pasrse the identity and amount of transcations class
    // and push it on the transactions vector
    while(getline(txFile,ln))
    {
        stringstream ss(ln);
        
        getline(ss,identity,',');
        getline(ss,amount);
        
        Transaction T(stoi(identity), stod(amount));
        
        transactions.push_back(T);
    }
    
    //Start processing the trasactions
    cout << ">> Processing..." << endl;
    
    for(int i = 0; i < transactions.size() ; i++)
    {
        bool equal = false, equal1 = false;
        int flag = 0;
        
        int temp = transactions[i].Identity;    //set temp as an transactions identity
        
        for(int j = 0; j < customers.size(); j++)
        {
            if(temp == customers[j].ID)         // if transactions id matches with customers id
            {
                
                if(customers[j].Balance + transactions[i].Amount >= 0)   //if its not declined
                {
                    customers[j].Balance = customers[j].Balance + transactions[i].Amount; //update:
                    equal1 = true;
                }
                else if(customers[j].Balance + transactions[i].Amount < 0) //if Declined:
                {
                    flag = 1;   //change flag from 0  to 1.
                }
                
                equal = true;
            }
        }
        if(equal1 == false && equal == true && flag == 1)    //rejecting the id
            cout << " **Rejected Tx: " << transactions[i].Identity << "," << transactions[i].Amount << endl;
        if(equal == false)  //invalid id
            cout << " **Invalid Tx: " << transactions[i].Identity << "," << transactions[i].Amount << endl;
    }
    
    cout << ">> Customers after:" << endl;
    
    //Sort the customers vector with balance value decending order
    sort(customers.begin(),
         customers.end(),
         [](Customer c1, Customer c2)
         {
             
             if(c1.Balance > c2.Balance)
                 return true;
             else if(c1.Balance == c2.Balance)  // if balance is same
             {
                 if(c1.Name < c2.Name)  //sort it using name
                     return true;
                 else
                     return false;
             }
             else
             {
                 return false;
             }
         }
    );
    
    for(Customer& c: customers) //print the final customers info
    {
        cout << " " << c.Name << " (" << c.ID << "): $" << c.Balance << endl;
    }
    return 0;
}//end of the main method

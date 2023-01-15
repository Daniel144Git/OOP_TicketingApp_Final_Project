#pragma once
#include <iostream>
#include <string>

#pragma warning(disable:4996)
using namespace std;

class iSerializabil {
public:
    virtual void serializare(ofstream& f) = 0;
    virtual void deserializare(ifstream& f) = 0;
}; 

#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <list>


// include your other headers here
#include "AbstractWrapper.h"
#include "./../../spa/src/Parser.h"

class TestWrapper : public AbstractWrapper {
private:
    PKB pkb;
    Parser parser;

public:
    // default constructor
    TestWrapper();

    // destructor
    ~TestWrapper();

    // method for parsing the SIMPLE source
    virtual void parse(std::string filename);

    // method for evaluating a query
    virtual void evaluate(std::string query, std::list<std::string>& results);
};

#endif

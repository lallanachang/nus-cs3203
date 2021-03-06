#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <PKB.h>
#include <QueryUtility.h>
#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>
#include <pql_dto/Pattern.h>
#include <ConverterUtil.h>

class AssignEvaluator
{
public:
    static unordered_map<string, vector<string>> evaluate(pql_dto::Pattern &pattern,
            pql_dto::Entity &first_param, pql_dto::Entity &second_param, PKB &PKB);
};

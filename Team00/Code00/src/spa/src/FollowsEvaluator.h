#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <QueryUtility.h>
#include <pql_dto/Entity.h>
#include <pql_dto/Relationships.h>

class FollowsEvaluator
{
public:
    static unordered_map<string, vector<string>> evaluate_non_trivial(pql_dto::Entity first_param,
            pql_dto::Entity second_param);
    static bool evaluate_trivial(pql_dto::Entity first_param,
            pql_dto::Entity second_param);
};


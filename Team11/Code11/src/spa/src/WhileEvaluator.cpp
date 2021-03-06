#include "WhileEvaluator.h"

unordered_map<string, vector<string>> WhileEvaluator::evaluate(pql_dto::Pattern &pattern,
        pql_dto::Entity &first_param, pql_dto::Entity &second_param, PKB &PKB)
{
    unordered_map<string, vector<string>> result;
    pql_dto::Entity pattern_entity = pattern.get_pattern_entity();
    string pattern_name = pattern_entity.get_entity_name();
    string first_name = first_param.get_entity_name();

    if (first_param.get_entity_type() == EntityType::ANY)
    { // pattern w(_, _)
        unordered_map<int, vector<string>> int_str_map = PKB.get_all_whilestmt_and_control_var();
        vector<int> int_vec;
        int_vec.reserve(int_str_map.size());
        for (const auto& iter : int_str_map)
        {
            int_vec.push_back(iter.first);
        }
        result = QueryUtility::mapping(pattern_name, int_vec);
    }
    else if (QueryUtility::is_var_name(first_param))
    { // pattern w("x", _)
        vector<int> int_vec = PKB.get_while_with_control_var(first_name);
        result = QueryUtility::mapping(pattern_name, int_vec);
    }
    else
    { // pattern w(v, _)
        unordered_map<int, vector<string>> int_str_map = PKB.get_all_whilestmt_and_control_var();
        result = QueryUtility::mapping(pattern_entity, first_param, int_str_map, PKB);
    }
    return result;
}

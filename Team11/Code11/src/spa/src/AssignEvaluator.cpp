#include "AssignEvaluator.h"

unordered_map<string, vector<string>> AssignEvaluator::evaluate(pql_dto::Pattern &pattern,
        pql_dto::Entity &first_param, pql_dto::Entity &second_param, PKB &PKB)
{
    unordered_map<string, vector<string>> result;
    string pattern_name = pattern.get_pattern_entity().get_entity_name();
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (second_param.get_entity_type() == EntityType::ANY)
    {
        if (first_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. pattern a(_, _)
            vector<int> int_vec = PKB.get_all_assigns();
            result = QueryUtility::mapping(pattern_name, int_vec);
        }
        else if (QueryUtility::is_var_name(first_param))
        {
            // e.g. pattern a("y", _)
            vector<int> int_vec = PKB.get_all_assigns();
            result = QueryUtility::mapping(pattern_name, first_name, int_vec, PKB);
        }
        else
        {
            // e.g. pattern a(v, _)
            vector<int> int_vec = PKB.get_all_assigns();
            result = QueryUtility::mapping(pattern_name, first_param, int_vec, PKB);
        }
    }
    else if (second_param.get_entity_type() == EntityType::PATTEXPR)
    {
        if (first_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. pattern a(_, _"x"_)
            vector<int> int_vec = PKB.get_all_assign_pattern_contains(ConverterUtil::convert_infix_prefix(second_name));
            result = QueryUtility::mapping(pattern_name, int_vec);
        }
        else if (QueryUtility::is_var_name(first_param))
        {
            // e.g. pattern a("y", _"x"_)
            vector<int> int_vec = PKB.get_assign_pattern_contains(first_name, ConverterUtil::convert_infix_prefix(second_name));
            result = QueryUtility::mapping(pattern_name, int_vec);
        }
        else
        {
            // e.g. pattern a(v, _"x"_)
            vector<int> int_vec = PKB.get_all_assign_pattern_contains(ConverterUtil::convert_infix_prefix(second_name));
            result = QueryUtility::mapping(pattern_name, first_param, int_vec, PKB);
        }
    }
    else
    {
        if (first_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. pattern a(_, "x")
            vector<int> int_vec = PKB.get_all_assign_pattern_matches(ConverterUtil::convert_infix_prefix(second_name));
            result = QueryUtility::mapping(pattern_name, int_vec);
        }
        else if (QueryUtility::is_var_name(first_param))
        {
            // e.g. pattern a("y", "x")
            vector<int> int_vec = PKB.get_assign_pattern_matches(first_name, ConverterUtil::convert_infix_prefix(second_name));
            result = QueryUtility::mapping(pattern_name, int_vec);
        }
        else
        {
            // e.g. pattern a(v, "x")
            vector<int> int_vec = PKB.get_all_assign_pattern_matches(ConverterUtil::convert_infix_prefix(second_name));
            result = QueryUtility::mapping(pattern_name, first_param, int_vec, PKB);
        }
    }
    return result;
}

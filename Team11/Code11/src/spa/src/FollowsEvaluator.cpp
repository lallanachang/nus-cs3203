#include "FollowsEvaluator.h"

unordered_map<string, vector<string>> FollowsEvaluator::evaluate_non_trivial(pql_dto::Entity &first_param,
                                   pql_dto::Entity &second_param, PKB &PKB)
{
    unordered_map<string, vector<string>> result;
    unordered_map<string, vector<string>> empty_map;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.is_entity_declared())
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Follows(s, _)
            vector<int> int_vec = PKB.get_all_followed();
            result = QueryUtility::mapping(first_param, int_vec, PKB);
        }
        else if (QueryUtility::is_statement_num(second_param))
        {
            // e.g. Follows(s, 2)
            int first_stmt_num = PKB.get_followed_by(stoi(second_name));
            if (first_stmt_num > 0)
            {
                result = QueryUtility::mapping(first_param, first_stmt_num, PKB);
            }
            else
            {
                return empty_map;
            }
        }
        else if (first_param.equals(second_param))
        {
            // e.g. Follows(s, s)
            return empty_map;
        }
        else
        {
            // e.g. Follows(s1, s2)
            unordered_map<int, vector<int>> int_map = PKB.get_all_follows_relationship();
            result = QueryUtility::mapping(first_param, second_param, int_map, PKB);
        }
    }

    if (second_param.is_entity_declared())
    {
        if (first_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Follows(_, s)
            vector<int> int_vec = PKB.get_all_follows();
            result = QueryUtility::mapping(second_param, int_vec, PKB);
        }
        else if (QueryUtility::is_statement_num(first_param))
        {
            // e.g. Follows(1, s)
            int second_stmt_num = PKB.get_follows(stoi(first_name));
            if (second_stmt_num > 0)
            {
                result = QueryUtility::mapping(second_param, second_stmt_num, PKB);
            }
            else
            {
                return empty_map;
            }
        }
    }
    return result;
}

bool FollowsEvaluator::evaluate_trivial(pql_dto::Entity &first_param,
                                        pql_dto::Entity &second_param, PKB &PKB)
{
    bool result = false;
    string first_name = first_param.get_entity_name();
    string second_name = second_param.get_entity_name();

    if (first_param.get_entity_type() == EntityType::ANY)
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Follows(_, _)
            result = PKB.does_follows_exist();
        }
        else if (QueryUtility::is_statement_num(second_param))
        {
            // e.g. Follows(_, 2)
            result = PKB.get_followed_by(stoi(second_name)) > 0;
        }
    }

    if (QueryUtility::is_statement_num(first_param))
    {
        if (second_param.get_entity_type() == EntityType::ANY)
        {
            // e.g. Follows(1, _)
            result = PKB.get_follows(stoi(first_name)) > 0;
        }
        else if (QueryUtility::is_statement_num(second_param))
        {
            // e.g. Follows(1, 2)
            result = PKB.is_follows(stoi(first_name), stoi(second_name));
        }
    }
    return result;
}

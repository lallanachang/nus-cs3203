#include "TypeBank.h"

bool TypeBank::insert_type(int stmt, EntityType type)
{
    // check if valid type
    switch (type)
    {
    case EntityType::ASSIGN :
    case EntityType::CALL :
    case EntityType::IF :
    case EntityType::PRINT :
    case EntityType::READ :
    case EntityType::WHILE :
        break;
    default:
        return false;
    }

    if (bank.find(stmt) != bank.end())
    {
        std::vector<EntityType> &bank_value = bank.at(stmt);
        // check if value exists already
        for (EntityType val : bank_value)
        {
            if (type == val)
            {
                return false;
            }
        }
        bank_value.push_back(type);
    }
    else
    {
        std::vector<EntityType> value_list;
        value_list.push_back(type);
        bank.insert({stmt, value_list});
    }

    if (reverse_bank.find(type) != reverse_bank.end())
    {
        std::vector<int> &reverse_bank_value = reverse_bank.at(type);
        // check if value exists already
        for (int key : reverse_bank_value)
        {
            if (stmt == key)
            {
                return true;
            }
        }
        reverse_bank_value.push_back(stmt);
    }
    else
    {
        std::vector<int> key_list;
        key_list.push_back(stmt);
        reverse_bank.insert({type, key_list});
    }
    return true;
}

EntityType TypeBank::get_statement_type(int stmt)
{
    if (bank.find(stmt) != bank.end())
    {
        return bank[stmt][0];
    }
    return EntityType::INVALID;
}

std::vector<int> TypeBank::get_all_of_type(EntityType type)
{
    if (reverse_bank.find(type) != reverse_bank.end())
    {
        return reverse_bank[type];
    }

    return std::vector<int>();
}

std::unordered_map<int, std::vector<EntityType>> TypeBank::copy()
{
    return bank;
}


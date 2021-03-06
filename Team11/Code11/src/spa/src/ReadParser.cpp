#include "ReadParser.h"

std::regex read_statement_pattern("^[\\s]*read[\\s]+([a-zA-Z][a-zA-Z0-9]*[\\s]*);$");

ReadParser::ReadParser(PKB &pkb, Statement statement, std::string parent_prog_line)
{
    if (!is_read_stmt_valid(statement.get_statement()))
    {
        throw error_messages::invalid_read_statement;
    }

    if (statement.get_statement_type() != EntityType::READ)
    {
        throw error_messages::invalid_read_type;
    }

    std::string read_var = StringUtil::trim(get_var(statement.get_statement()), " \n\t\r\f\v");

    //Insert var
    pkb.insert_variable(read_var);

    //Insert modifies
    pkb.insert_modifies(statement.get_prog_line(), read_var);
    pkb.insert_modifies(statement.get_procedure(), read_var);
    if (std::regex_match(parent_prog_line, std::regex("^[a-zA-Z][a-zA-Z0-9]+$")))
    {
        pkb.insert_modifies(parent_prog_line, read_var);
    }

    //Insert parents
    if (std::regex_match(parent_prog_line, std::regex("^[0-9]+$")))
    {
        pkb.insert_parent(stoi(parent_prog_line), statement.get_prog_line());
    }

    //Insert type
    pkb.insert_type(statement.get_prog_line(), statement.get_statement_type());
}

bool ReadParser::is_read_stmt_valid(std::string statement)
{
    return std::regex_match(statement, read_statement_pattern);
}

std::string ReadParser::get_var(std::string statement)
{
    smatch match;
    if (std::regex_search(statement, match, read_statement_pattern))
    {
        return match.str(1);
    }
    return "";
}

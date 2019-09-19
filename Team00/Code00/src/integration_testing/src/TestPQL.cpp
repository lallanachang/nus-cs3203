#include "catch.hpp"
#include "./../../spa/src/QueryEvaluator.h"
#include "PKBStub.cpp"

using namespace std;


TEST_CASE("No such that or pattern clauses") {
    PKBStub PKB;
    SECTION("variable")
    {
        string pql_query = "variable v; Select v";
        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
        unordered_set<string> expected_result {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
        REQUIRE(my_result == expected_result);
    }

    SECTION("assign")
    {
        string pql_query = "assign a; Select a";
        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
        unordered_set<string> expected_result {"1", "10", "11", "12", "15", "16", "17", "20", "21", "22", "23"};
        REQUIRE(my_result == expected_result);
    }
}

//TEST_CASE("One such that clause: Follows and Follows*")
//{
//    SECTION("Follows(a, _)")
//    {
//        string pql_query_1 = "assign a; Select a such that Follows(a, _)";
//        string pql_query_2 = "assign a; variable v; Select v such that Follows(a, _)";
//        unordered_set<string> my_result_1 = QueryEvaluator::get_result(pql_query_1);
//        unordered_set<string> my_result_2 = QueryEvaluator::get_result(pql_query_2);
//        unordered_set<string> expected_result_1 {"1", "10", "11", "12", "15", "16", "17", "21"};
//        unordered_set<string> expected_result_2 {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
//        REQUIRE(my_result_1 == expected_result_1);
//        REQUIRE(my_result_2 == expected_result_2);
//    }
//
//    SECTION("Follows(s, 12)")
//    {
//        string pql_query_1 = "stmt s; Select s such that Follows(s, 12)";
//        string pql_query_2 = "stmt s; variable v; Select v such that Follows(s, 12)";
//        string pql_query_3 = "stmt s; Select s such that Follows(s, 15)";
//        unordered_set<string> my_result_1 = QueryEvaluator::get_result(pql_query_1);
//        unordered_set<string> my_result_2 = QueryEvaluator::get_result(pql_query_2);
//        unordered_set<string> my_result_3 = QueryEvaluator::get_result(pql_query_3);
//        unordered_set<string> expected_result_1 {"11"};
//        unordered_set<string> expected_result_2 {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
//        unordered_set<string> expected_result_3 {};
//        REQUIRE(my_result_1 == expected_result_1);
//        REQUIRE(my_result_2 == expected_result_2);
//        REQUIRE(my_result_3 == expected_result_3);
//    }
//
//    SECTION("Follows(s, s)")
//    {
//        string pql_query = "stmt s; Select s such that Follows(s, s)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//        unordered_set<string> expected_result {};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Follows(s, cl)")
//    {
//        string pql_query_1 = "call cl; stmt s; Select s such that Follows(s, cl)";
//        string pql_query_2 = "call cl; stmt s; variable v; Select v such that Follows(cl, w)";
//        unordered_set<string> my_result_1 = QueryEvaluator::get_result(pql_query_1);
//        unordered_set<string> my_result_2 = QueryEvaluator::get_result(pql_query_2);
//        unordered_set<string> expected_result_1 {"12", "17"};
//        unordered_set<string> expected_result_2 {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
//        REQUIRE(my_result_1 == expected_result_1);
//        REQUIRE(my_result_2 == expected_result_2);
//    }
//
//    SECTION("Follows(_, _)")
//    {
//        string pql_query = "call cl; Select cl such that Follows(_, _)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//        unordered_set<string> expected_result {"2", "3", "13", "18"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Follows(_, 2)")
//    {
//        string pql_query = "call cl; Select cl such that Follows(_, 2)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//        unordered_set<string> expected_result {"2", "3", "13", "18"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Follows*(s, 12)")
//    {
//        string pql_query = "stmt s; Select s such that Follows*(s, 12)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//        unordered_set<string> expected_result {"10", "11"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Follows*(s, cl)")
//    {
//        string pql_query = "call cl; stmt s; Select s such that Follows*(s, cl)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//        unordered_set<string> expected_result {"10", "11", "12", "15", "16", "17"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Follows*(_, _)")
//    {
//        string pql_query = "call cl; Select cl such that Follows*(_, _)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//        unordered_set<string> expected_result {"2", "3", "13", "18"};
//        REQUIRE(my_result == expected_result);
//    }
//
//    SECTION("Follows*(_, 12)")
//    {
//        string pql_query = "stmt s; Select s such that Follows*(_, 12)";
//        unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//        unordered_set<string> expected_result {"10", "11"};
//        REQUIRE(my_result == expected_result);
//    }
//}
//
//TEST_CASE("One such that clause: Parent and Parent*")
//{
//    SECTION("Parent(s, _)")
//    {
//        string pql_query_1 = "stmt s; Select s such that Parent(s, _)";
//        string pql_query_2 = "stmt s; variable v; Select v such that Parent(s, _)";
//        unordered_set<string> my_result_1 = QueryEvaluator::get_result(pql_query_1);
//        unordered_set<string> my_result_2 = QueryEvaluator::get_result(pql_query_2);
//        unordered_set<string> expected_result_1 {"14", "19"};
//        unordered_set<string> expected_result_2 {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
//        REQUIRE(my_result_1 == expected_result_1);
//        REQUIRE(my_result_2 == expected_result_2);
//    }
//
//    SECTION("Parent(s, 15)")
//    {
//        string pql_query_1 = "stmt s; Select s such that Follows(s, 15)";
//        string pql_query_2 = "stmt s; variable v; Select v such that Follows(s, 15)";
//        unordered_set<string> my_result_1 = QueryEvaluator::get_result(pql_query_1);
//        unordered_set<string> my_result_2 = QueryEvaluator::get_result(pql_query_2);
//        unordered_set<string> expected_result_1 {"14"};
//        unordered_set<string> expected_result_2 {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
//        unordered_set<string> expected_result_3 {};
//        REQUIRE(my_result_1 == expected_result_1);
//        REQUIRE(my_result_2 == expected_result_2);
//    }
//
//SECTION("Follows(s, s)")
//{
//string pql_query = "stmt s; Select s such that Follows(s, s)";
//unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//unordered_set<string> expected_result {};
//REQUIRE(my_result == expected_result);
//}
//
//SECTION("Follows(s, cl)")
//{
//string pql_query_1 = "call cl; stmt s; Select s such that Follows(s, cl)";
//string pql_query_2 = "call cl; stmt s; variable v; Select v such that Follows(cl, w)";
//unordered_set<string> my_result_1 = QueryEvaluator::get_result(pql_query_1);
//unordered_set<string> my_result_2 = QueryEvaluator::get_result(pql_query_2);
//unordered_set<string> expected_result_1 {"12", "17"};
//unordered_set<string> expected_result_2 {"flag", "count", "cenX", "cenY", "x", "y", "normSq"};
//REQUIRE(my_result_1 == expected_result_1);
//REQUIRE(my_result_2 == expected_result_2);
//}
//
//SECTION("Follows(_, _)")
//{
//string pql_query = "call cl; Select cl such that Follows(_, _)";
//unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//unordered_set<string> expected_result {"2", "3", "13", "18"};
//REQUIRE(my_result == expected_result);
//}
//
//SECTION("Follows(_, 2)")
//{
//string pql_query = "call cl; Select cl such that Follows(_, 2)";
//unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//unordered_set<string> expected_result {"2", "3", "13", "18"};
//REQUIRE(my_result == expected_result);
//}
//
//SECTION("Follows*(s, 12)")
//{
//string pql_query = "stmt s; Select s such that Follows*(s, 12)";
//unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//unordered_set<string> expected_result {"10", "11"};
//REQUIRE(my_result == expected_result);
//}
//
//SECTION("Follows*(s, cl)")
//{
//string pql_query = "call cl; stmt s; Select s such that Follows*(s, cl)";
//unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//unordered_set<string> expected_result {"10", "11", "12", "15", "16", "17"};
//REQUIRE(my_result == expected_result);
//}
//
//SECTION("Follows*(_, _)")
//{
//string pql_query = "call cl; Select cl such that Follows*(_, _)";
//unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//unordered_set<string> expected_result {"2", "3", "13", "18"};
//REQUIRE(my_result == expected_result);
//}
//
//SECTION("Follows*(_, 12)")
//{
//string pql_query = "stmt s; Select s such that Follows*(_, 12)";
//unordered_set<string> my_result = QueryEvaluator::get_result(pql_query);
//unordered_set<string> expected_result {"10", "11"};
//REQUIRE(my_result == expected_result);
//}
//}
//

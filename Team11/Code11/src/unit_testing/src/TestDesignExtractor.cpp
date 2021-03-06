#include "catch.hpp"
#include "DesignExtractor.h"
#include "FollowsBank.h"
#include "FollowsStarBank.h"
#include "CallsBank.h"
#include "CallsStarBank.h"

TEST_CASE("DesignExtractor::extract_follows_star()")
{
    SECTION("extract empty FollowsBank")
    {
        FollowsBank follows_bank;
        FollowsStarBank follows_star_bank;
        REQUIRE_FALSE(follows_bank.does_follows_exists());
        DesignExtractor::extract_follows_star(follows_bank, follows_star_bank);
        REQUIRE_FALSE(follows_star_bank.does_follows_star_exist());
    }

    SECTION("extract 1 stmt FollowsBank")
    {
        FollowsBank follows_bank;
        FollowsStarBank follows_star_bank;
        follows_bank.insert_follows(1, 2);
        REQUIRE(follows_bank.does_follows_exists());
        DesignExtractor::extract_follows_star(follows_bank, follows_star_bank);
        REQUIRE(follows_star_bank.does_follows_star_exist());
        REQUIRE(follows_star_bank.get_all_follows_star().size() == 1);
        REQUIRE(follows_star_bank.get_all_followed_star().size() == 1);
    }

    SECTION("extract >1 stmt FollowsBank")
    {
        FollowsBank follows_bank;
        FollowsStarBank follows_star_bank;
        follows_bank.insert_follows(1, 2);
        follows_bank.insert_follows(2, 3);
        REQUIRE(follows_bank.does_follows_exists());
        DesignExtractor::extract_follows_star(follows_bank, follows_star_bank);
        REQUIRE(follows_star_bank.does_follows_star_exist());
        REQUIRE(follows_star_bank.get_all_follows_star().size() == 2);
        REQUIRE(follows_star_bank.get_all_followed_star().size() == 2);
        std::vector<int> result = follows_star_bank.get_follows_star(1);
        std::vector<int> expected({2, 3});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(result == expected);
    }
}

TEST_CASE("DesignExtractor::extract_parent_star()")
{
    SECTION("extract empty FollowsBank")
    {
        ParentBank parent_bank;
        ParentStarBank parent_star_bank;
        UsesBank uses_bank;
        ModifiesBank modifies_bank;
        REQUIRE_FALSE(parent_bank.does_parent_exist());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank, uses_bank, modifies_bank);
        REQUIRE_FALSE(parent_star_bank.does_parent_star_exist());
        REQUIRE(uses_bank.does_uses_exist());
        REQUIRE(modifies_bank.does_modifies_exist());
    }

    SECTION("extract 1 stmt FollowsBank")
    {
        ParentBank parent_bank;
        ParentStarBank parent_star_bank;
        UsesBank uses_bank;
        ModifiesBank modifies_bank;
        uses_bank.insert_uses(2, "v");
        modifies_bank.insert_modifies(2, "v");
        parent_bank.insert_parent(1, 2);
        REQUIRE(parent_bank.does_parent_exist());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank, uses_bank, modifies_bank);
        REQUIRE(parent_star_bank.does_parent_star_exist());
        REQUIRE(parent_star_bank.get_all_parent_star().size() == 1);
        REQUIRE(parent_star_bank.get_all_children_star().size() == 1);
        REQUIRE(uses_bank.get_used_by_statement(1).size() == 1);
        REQUIRE(modifies_bank.get_modified_by_statement(1).size() == 1);
    }

    SECTION("extract >1 stmt ParentBank 3-level depth")
    {
        ParentBank parent_bank;
        ParentStarBank parent_star_bank;
        UsesBank uses_bank;
        ModifiesBank modifies_bank;
        parent_bank.insert_parent(1, 2);
        parent_bank.insert_parent(2, 3);
        uses_bank.insert_uses(3, "v");
        modifies_bank.insert_modifies(3, "v");
        REQUIRE(parent_bank.does_parent_exist());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank, uses_bank, modifies_bank);
        REQUIRE(parent_star_bank.does_parent_star_exist());
        REQUIRE(parent_star_bank.get_all_parent_star().size() == 2);
        REQUIRE(parent_star_bank.get_all_children_star().size() == 2);
        std::vector<int> result_parent = parent_star_bank.get_parent_star(3);
        std::vector<int> expected_parent({2, 1});
        std::sort(result_parent.begin(), result_parent.end());
        std::sort(expected_parent.begin(), expected_parent.end());
        REQUIRE(result_parent == expected_parent);
        REQUIRE(uses_bank.get_used_by_statement(1).size() == 1);
        REQUIRE(modifies_bank.get_modified_by_statement(1).size() == 1);

        std::vector<int> result_child = parent_star_bank.get_children_star(1);
        std::vector<int> expected_child({2, 3});
        std::sort(result_child.begin(), result_child.end());
        std::sort(expected_child.begin(), expected_child.end());
        REQUIRE(result_child == expected_child);
    }

    SECTION("extract >1 stmt ParentBank 4-level depth")
    {
        ParentBank parent_bank;
        ParentStarBank parent_star_bank;
        UsesBank uses_bank;
        ModifiesBank modifies_bank;
        parent_bank.insert_parent(1, 2);
        parent_bank.insert_parent(1, 5);
        parent_bank.insert_parent(2, 3);
        parent_bank.insert_parent(3, 4);
        parent_bank.insert_parent(5, 6);
        uses_bank.insert_uses(5, "t");
        modifies_bank.insert_modifies(5, "v");
        uses_bank.insert_uses(6, "v");
        modifies_bank.insert_modifies(6, "v");
        REQUIRE(parent_bank.does_parent_exist());
        DesignExtractor::extract_parent_star(parent_bank, parent_star_bank, uses_bank, modifies_bank);
        REQUIRE(parent_star_bank.does_parent_star_exist());
        REQUIRE(parent_star_bank.get_all_parent_star().size() == 4);
        REQUIRE(parent_star_bank.get_all_children_star().size() == 5);
        std::vector<int> result = parent_star_bank.get_parent_star(6);
        std::vector<int> expected({1, 5});
        std::sort(result.begin(), result.end());
        std::sort(expected.begin(), expected.end());
        REQUIRE(uses_bank.get_used_by_statement(1).size() == 2);
        REQUIRE(modifies_bank.get_modified_by_statement(1).size() == 1);
        REQUIRE(result == expected);

        std::vector<int> result_child = parent_star_bank.get_children_star(1);
        std::vector<int> expected_child({2, 3, 4, 5, 6});
        std::sort(result_child.begin(), result_child.end());
        std::sort(expected_child.begin(), expected_child.end());
        REQUIRE(result_child == expected_child);
    }
}

TEST_CASE("DesignExtractor::extract_calls_star()")
{
    CallsBank calls_bank;
    CallsStarBank calls_star_bank;
    UsesBank uses_bank;
    ModifiesBank modifies_bank;
    ParentStarBank parent_star_bank;
    
    SECTION("empty")
    {
        REQUIRE(DesignExtractor::extract_calls_star(calls_bank, calls_star_bank, uses_bank, modifies_bank, parent_star_bank));
        REQUIRE_FALSE(calls_star_bank.does_calls_star_exist());
    }

    SECTION("no cyclic")
    {
        calls_bank.insert_calls(1, "a", "b");
        calls_bank.insert_calls(2, "b", "c");
        calls_bank.insert_calls(3, "b", "e");        
        calls_bank.insert_calls(4, "e", "f");        
        calls_bank.insert_calls(5, "f", "d");        
        calls_bank.insert_calls(6, "c", "d");
        calls_bank.insert_calls(7, "a1", "b1");
        uses_bank.insert_uses("a", "near");
        uses_bank.insert_uses("b", "middle");
        uses_bank.insert_uses("d", "far");
        modifies_bank.insert_modifies("b", "nowhere");
        modifies_bank.insert_modifies("f", "somewhere");
        REQUIRE(DesignExtractor::extract_calls_star(calls_bank, calls_star_bank, uses_bank, modifies_bank, parent_star_bank));
        
        std::vector<std::string> result_1 = calls_star_bank.get_procedures_called_by_star("a");
        std::vector<std::string> expected_1({"b", "c", "d", "e", "f"});
        std::sort(result_1.begin(), result_1.end());
        std::sort(expected_1.begin(), expected_1.end());
        REQUIRE(result_1.size() == 5);
        REQUIRE(result_1 == expected_1);

        std::vector<std::string> result_2 = calls_star_bank.get_procedures_called_by_star("c");
        std::vector<std::string> expected_2({"d"});
        std::sort(result_2.begin(), result_2.end());
        std::sort(expected_2.begin(), expected_2.end());
        REQUIRE(result_2.size() == 1);
        REQUIRE(result_2 == expected_2);

        std::vector<std::string> result_3 = calls_star_bank.get_procedures_called_by_star("e");
        std::vector<std::string> expected_3({"f", "d"});
        std::sort(result_3.begin(), result_3.end());
        std::sort(expected_3.begin(), expected_3.end());
        REQUIRE(result_3.size() == 2);
        REQUIRE(result_3 == expected_3);

        std::vector<std::string> result_4 = calls_star_bank.get_procedures_called_by_star("a1");
        std::vector<std::string> expected_4({"b1"});
        std::sort(result_4.begin(), result_4.end());
        std::sort(expected_4.begin(), expected_4.end());
        REQUIRE(result_4.size() == 1);
        REQUIRE(result_4 == expected_4);

        std::vector<std::string> result_5 = uses_bank.get_used_by_procedure("a");
        std::vector<std::string> expected_5({"near", "middle", "far"});
        std::sort(result_5.begin(), result_5.end());
        std::sort(expected_5.begin(), expected_5.end());
        REQUIRE(result_5.size() == 3);
        REQUIRE(result_5 == expected_5);

        std::vector<std::string> result_6 = uses_bank.get_used_by_procedure("e");
        std::vector<std::string> expected_6({"far"});
        std::sort(result_6.begin(), result_6.end());
        std::sort(expected_6.begin(), expected_6.end());
        REQUIRE(result_6.size() == 1);
        REQUIRE(result_6 == expected_6);

        std::vector<std::string> result_7 = modifies_bank.get_modified_by_procedure("a");
        std::vector<std::string> expected_7({"nowhere", "somewhere"});
        std::sort(result_7.begin(), result_7.end());
        std::sort(expected_7.begin(), expected_7.end());
        REQUIRE(result_7.size() == 2);
        REQUIRE(result_7 == expected_7);

        std::vector<std::string> result_8 = modifies_bank.get_modified_by_procedure("e");
        std::vector<std::string> expected_8({"somewhere"});
        std::sort(result_8.begin(), result_8.end());
        std::sort(expected_8.begin(), expected_8.end());
        REQUIRE(result_8.size() == 1);
        REQUIRE(result_8 == expected_8);

        REQUIRE(modifies_bank.get_modified_by_procedure("d").empty());
        REQUIRE(modifies_bank.get_modified_by_procedure("c").empty());
        REQUIRE(modifies_bank.get_modified_by_statement(6).empty());

        std::vector<std::string> result_9 = modifies_bank.get_modified_by_statement(1);
        std::vector<std::string> expected_9({"nowhere", "somewhere"});
        std::sort(result_9.begin(), result_9.end());
        std::sort(expected_9.begin(), expected_9.end());
        REQUIRE(result_9.size() == 2);
        REQUIRE(result_9 == expected_9);

        std::vector<std::string> result_10 = modifies_bank.get_modified_by_statement(3);
        std::vector<std::string> expected_10({"somewhere"});
        std::sort(result_10.begin(), result_10.end());
        std::sort(expected_10.begin(), expected_10.end());
        REQUIRE(result_10.size() == 1);
        REQUIRE(result_10 == expected_10);

        std::vector<std::string> result_11 = uses_bank.get_used_by_statement(1);
        std::vector<std::string> expected_11({"middle", "far"});
        std::sort(result_11.begin(), result_11.end());
        std::sort(expected_11.begin(), expected_11.end());
        REQUIRE(result_11.size() == 2);
        REQUIRE(result_11 == expected_11);

        std::vector<std::string> result_12 = uses_bank.get_used_by_statement(2);
        std::vector<std::string> expected_12({"far"});
        std::sort(result_12.begin(), result_12.end());
        std::sort(expected_12.begin(), expected_12.end());
        REQUIRE(result_12.size() == 1);
        REQUIRE(result_12 == expected_12);
    
        std::vector<std::string> result_13 = uses_bank.get_used_by_statement(3);
        std::vector<std::string> expected_13({"far"});
        std::sort(result_13.begin(), result_13.end());
        std::sort(expected_13.begin(), expected_13.end());
        REQUIRE(result_13.size() == 1);
        REQUIRE(result_13 == expected_13);
    }

    SECTION("check while/if nesting")
    {
        calls_bank.insert_calls(2, "a", "b");
        calls_bank.insert_calls(3, "b", "c");
        uses_bank.insert_uses("c", "used");
        modifies_bank.insert_modifies("b", "modified");
        parent_star_bank.insert_parent_star(1, 2);
        DesignExtractor::extract_calls_star(calls_bank, calls_star_bank, uses_bank, modifies_bank, parent_star_bank);
        
        std::vector<std::string> result_1 = uses_bank.get_used_by_statement(1);
        std::vector<std::string> expected_1({"used"});
        REQUIRE(result_1.size() == 1);
        REQUIRE(result_1 == expected_1);

        std::vector<std::string> result_2 = modifies_bank.get_modified_by_statement(1);
        std::vector<std::string> expected_2({"modified"});
        REQUIRE(result_2.size() == 1);
        REQUIRE(result_2 == expected_2);
    }

    SECTION("cyclic")
    {
        SECTION("direct loopback")
        {
            calls_bank.insert_calls(1, "a", "b");
            calls_bank.insert_calls(2, "b", "a");
            REQUIRE_FALSE(DesignExtractor::extract_calls_star(calls_bank, calls_star_bank, uses_bank, modifies_bank, parent_star_bank));
        }

        SECTION("chained loopback")
        {
            calls_bank.insert_calls(1, "b", "a");
            calls_bank.insert_calls(2, "a", "c");
            calls_bank.insert_calls(3, "c", "e");
            calls_bank.insert_calls(4, "e", "b");
            REQUIRE_FALSE(DesignExtractor::extract_calls_star(calls_bank, calls_star_bank, uses_bank, modifies_bank, parent_star_bank));
        }
    }
}

TEST_CASE("DesignExtractor::extract_next_bip")
{
    SECTION("SIMPLE SANITY CHECK")
    {
        PKB pkb;

        pkb.insert_procedure("B", 4, {5});
        pkb.insert_next(1, 2);
        pkb.insert_next(2, 3);
        pkb.insert_type(2, EntityType::CALL);
        pkb.insert_calls(2, "A", "B");
        pkb.insert_next(4, 5);
        pkb.extract_design();

        REQUIRE(pkb.is_next_bip(2,4));
        REQUIRE(pkb.is_next_bip(5,3));
    }
}
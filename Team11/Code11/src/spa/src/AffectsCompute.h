#ifndef AUTOTESTER_AFFECTSCOMPUTE_H
#define AUTOTESTER_AFFECTSCOMPUTE_H

#include <vector>
#include <unordered_map>
#include "PKB.h"

class AffectsCompute {
public:
    std::vector<int> get_all_assigns_affect(PKB& pkb);   //e.g. Affects(a, _)
    std::vector<int> get_assigns_affect(int stmt, PKB& pkb);  //e.g. Affects(a, 2)
    std::unordered_map<int, std::vector<int>> get_all_affects_relationship(PKB& pkb);   //e.g. Affects(a1, a2), a1 can equal to a2
    std::vector<int> get_all_assigns_affected(PKB& pkb);   //e.g. Affects(_, a)
    std::vector<int> get_assigns_affected_by(int stmt, PKB& pkb);   //e.g. Affects(1, a)
    bool does_affects_exist(int last_stmt_num, PKB& pkb);
    bool is_affects(int stmt1, int stmt2, PKB& pkb);

private:
    bool can_exist_affects(int stmt1, int stmt2, PKB& pkb);
    bool modified_by_others(int stmt1, int inter_stmt, PKB& pkb);
    bool DFS_checking_is_affects(int stmt1, int stmt2, PKB& pkb);
    bool affects_other_stmts(int stmt, PKB& pkb);
    bool DFS_checking_assign_affects(int stmt, PKB& pkb);
};


#endif //AUTOTESTER_AFFECTSCOMPUTE_H

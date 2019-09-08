using namespace std;

#include "Relationships.h"

namespace pql_dto
{
    class UsesRelationship : public Relationships
    {
    public:
        UsesRelationship(string first_param, string second_param, bool is_star)
        {
            set_relationship(USES);
            set_first_param(first_param);
            set_second_param(second_param);
            set_relationship_star(is_star);
        }

    private:
        void Relationships::set_first_param(string param)
        {
            
        }

        void Relationships::set_second_param(string param)
        {

        }
    };
}

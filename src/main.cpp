#include <iostream>
#include "epsilon_nfa.hpp"
using namespace std;

int main()
{
    vector<State> all_state;
    State state_1(1, {}, {}, {2}, true, true);
    State state_2(2, {2,3}, {}, {}, false, false);
    State state_3(3, {}, {4}, {}, false, false);
    State state_4(4, {}, {5}, {1}, false, false);
    State state_5(5, {4}, {}, {}, false, false);
    all_state = {state_1, state_2, state_3, state_4,state_5};

    epsilon_NFA nfa(all_state);
    nfa.print_epsilon_nfa_table();
    getchar();
    nfa.calculate_s_prime_0();

    return 0;
}
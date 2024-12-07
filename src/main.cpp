#include <iostream>
#include "epsilon_nfa.hpp"
#include "dfa.hpp"
#include "nfa.hpp"
#include <cstdlib> // system()

using namespace std;

int main()
{
    vector<State> all_state;
    State state_1(1, {}, {}, {2}, true, true);
    State state_2(2, {2, 3}, {}, {}, false, false);
    State state_3(3, {}, {4}, {}, false, false);
    State state_4(4, {}, {5}, {1}, false, false);
    State state_5(5, {4}, {}, {}, false, false);

    State state_6(1, {1}, {}, {2, 4}, true, true);
    State state_7(2, {3}, {5}, {}, false, false);
    State state_8(3, {}, {2}, {}, false, false);
    State state_9(4, {5}, {4}, {}, false, false);
    State state_10(5, {}, {}, {}, false, false);

    vector<State> nfa1_states = {state_1, state_2, state_3, state_4, state_5};
    vector<State> nfa2_states = {state_6, state_7, state_8, state_9, state_10};

    epsilon_NFA e_nfa(nfa1_states);
    epsilon_NFA nfa2(nfa2_states);
    // e_nfa.print_epsilon_nfa_table();
    e_nfa.calculate_s_prime_0();
    e_nfa.calculate_s_prime_1();
    cout << "-----------" << endl;
    NFA nfa(e_nfa);
    system("clear");
    nfa.print_map();
    // nfa2.print_epsilon_nfa_table();
    // nfa2.calculate_s_prime_0();
    // nfa2.calculate_s_prime_1();

    return 0;
}
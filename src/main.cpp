#include <iostream>
#include "epsilon_nfa.hpp"
#include "dfa.hpp"
#include <cstdlib> // system()

using namespace std;
void calculate_NFA(epsilon_NFA *e_nfa)
{
    system("clear");
    e_nfa->calculate_s_prime_0();
    e_nfa->calculate_s_prime_1();
    e_nfa->print_epsilon_nfa_table();
}
void calculate_and_print_DFA(DFA dfa)
{
    cout << endl;
    cout << "DFA" << endl;
    dfa.print_map();
}
int main()
{
    vector<State> all_state;
    // State Name, O transtion, 1 transition, Epsilon Transition, is_start, is_final
    // !!! STATE NAME 0 olamaz.
    State state_1(1, {}, {}, {2}, true, true);
    State state_2(2, {2, 3}, {}, {}, false, false);
    State state_3(3, {}, {4}, {}, false, false);
    State state_4(4, {}, {5}, {1}, false, false);
    State state_5(5, {4}, {}, {}, false, false);

    State state_6(1, {1}, {}, {2, 4}, true, false);
    State state_7(2, {3}, {5}, {}, false, false);
    State state_8(3, {}, {2}, {}, false, false);
    State state_9(4, {5}, {4}, {}, false, false);
    State state_10(5, {}, {}, {}, false, true);

    State state_a(1, {1}, {}, {2}, true, false);
    State state_b(2, {3}, {}, {4}, false, false);
    State state_c(3, {}, {2}, {}, false, false);
    State state_d(4, {4}, {}, {}, false, true);

    State state_s(1, {3}, {}, {4}, true, false);
    State state_p(2, {1, 4}, {2}, {}, false, false);
    State state_q(3, {3}, {}, {4}, false, true);
    State state_r(4, {}, {3}, {2}, false, false);

    State state_k(1, {}, {2}, {2}, true, true);
    State state_l(2, {2, 3}, {3}, {}, false, false);
    State state_m(3, {1}, {}, {}, false, false);

    vector<State> e_nfa1_states = {state_1, state_2, state_3, state_4, state_5};
    vector<State> e_nfa2_states = {state_6, state_7, state_8, state_9, state_10};
    vector<State> e_nfa3_states = {state_a, state_b, state_c, state_d};
    vector<State> e_nfa4_states = {state_s, state_p, state_q, state_r};
    vector<State> e_nfa5_states = {state_k, state_l, state_m};

    epsilon_NFA e_nfa(e_nfa1_states);
    epsilon_NFA e_nfa2(e_nfa2_states);
    epsilon_NFA e_nfa3(e_nfa3_states);
    epsilon_NFA e_nfa4(e_nfa4_states);
    epsilon_NFA e_nfa5(e_nfa5_states);

    calculate_NFA(&e_nfa);
    DFA dfa(e_nfa);
    calculate_and_print_DFA(dfa);
    getchar();

    calculate_NFA(&e_nfa2);
    DFA dfa2(e_nfa2);
    calculate_and_print_DFA(dfa2);
    getchar();

    calculate_NFA(&e_nfa3);
    DFA dfa3(e_nfa3);
    calculate_and_print_DFA(dfa3);
    getchar();

    calculate_NFA(&e_nfa4);
    DFA dfa4(e_nfa4);
    calculate_and_print_DFA(dfa4);
    getchar();

    calculate_NFA(&e_nfa5);
    DFA dfa5(e_nfa5);
    calculate_and_print_DFA(dfa5);
    return 0;
}
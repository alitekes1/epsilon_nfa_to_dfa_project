#include <iostream>
#include <stdlib.h>
#include "epsilon_nfa.hpp"

using namespace std;

int main()
{
    vector<State> all_state;
    State state_0(0, {-1}, {1}, {2}, true, false);
    State state_1(1, {-1}, {0}, {-1}, false, false);
    State state_2(2, {3}, {4}, {-1}, false, true);
    State state_3(3, {2}, {-1}, {-1}, false, false);
    State state_4(4, {2}, {-1}, {-1}, false, false);
    all_state = {state_0, state_1, state_2, state_3, state_4};

    epsilon_NFA nfa(all_state);
    nfa.calculate_s_prime_0();
}

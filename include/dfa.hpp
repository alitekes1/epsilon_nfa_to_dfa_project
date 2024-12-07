#ifndef DFA_HPP
#define DFA_HPP
#include "epsilon_nfa.hpp"
#include <utility>
#include <algorithm>
#include <cmath>
class DFA
{
private:
public:
    DFA(epsilon_NFA nfa);
    void function();
    State start_state;
    vector<State> all_states;
    vector<State> final_states;
    epsilon_NFA epsilon_nfa_map;

    int states_to_state(vector<State> s);
    vector<State> get_s_prime_0(vector<State> s);
    vector<State> get_s_prime_1(vector<State> s);
};

DFA::DFA(epsilon_NFA nfa)
{
    this->start_state = nfa.start_state;
    this->final_states = nfa.final_states;
    this->epsilon_nfa_map = nfa;

    all_states.push_back(start_state);
    function();
}
vector<State> DFA::get_s_prime_0(vector<State> s_list)
{
    vector<State> prime_list;
    for (int i = 0; i < s_list.size(); i++)
    {
        auto temp = epsilon_nfa_map.s_prime_0[s_list[i]];
        prime_list.insert(prime_list.end(), temp.begin(), temp.end());
    }
    return prime_list;
}

vector<State> DFA::get_s_prime_1(vector<State> s_list)
{
    vector<State> prime_list;
    for (int i = 0; i < s_list.size(); i++)
    {
        auto temp = epsilon_nfa_map.s_prime_1[s_list[i]];
        prime_list.insert(prime_list.end(), temp.begin(), temp.end());
    }
    return prime_list;
}

void DFA::function()
{
}
int DFA::states_to_state(vector<State> s)
{
    string state_name = "";
    for (int i = 0; i < s.size(); i++)
    {
        state_name += to_string(s.at(i).get_state_name());
    }
    return atoi(state_name.c_str());
}
#endif
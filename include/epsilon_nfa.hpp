#ifndef EPSILON_NFA
#define EPSILON_NFA
#include <vector>
#include "state.hpp"
#include <utility>

class epsilon_NFA
{
private:
    vector<State> all_states;
    pair<State, vector<int>> s_prime_0;
    pair<State, vector<int>> s_prime_1;

public:
    epsilon_NFA(vector<State> all_states);
    void calculate_s_prime_0();
    void calculate_s_prime_1();
    ~epsilon_NFA();s
};

epsilon_NFA::epsilon_NFA(vector<State> all_states)
{
    this->all_states = all_states;
}

epsilon_NFA::~epsilon_NFA()
{
}
void epsilon_NFA::calculate_s_prime_0()
{
}
void epsilon_NFA::calculate_s_prime_1()
{
}
#endif
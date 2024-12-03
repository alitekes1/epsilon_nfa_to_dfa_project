#ifndef DFA_HPP
#define DFA_HPP
#include "epsilon_nfa.hpp"

class DFA
{
private:
    /* data */
public:
    DFA(map<State, vector<State>> nfa);
    vector<State> final_states;
    State start_state;
    ~DFA();
};

DFA::DFA(map<State, vector<State>> nfa)
{
    for (const auto &pair : nfa)
    {
        // Anahtar (State) yazdırma
        cout << "State:" << pair.first << ":";

        // Değer (vector<State>) yazdırma
        for (const State &state : pair.second)
        {
            std::cout << state << " ";
        }
        cout << "\n";
    }
}

DFA::~DFA()
{
}

#endif
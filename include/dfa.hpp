#ifndef DFA__HPP
#define DFA__HPP
#include "epsilon_nfa.hpp"
#include <set>

class DFA
{
private:
    epsilon_NFA e_nfa;
    void calculate_DFA();
    bool is_exist_in_map(int stn);
    State state_name_to_state(int state_name);
    vector<State> const get_ones_transtion_state(State s);
    vector<State> const get_zeros_transtion_state(State s);

public:
    State start_state;
    vector<State> all_states;
    vector<State> final_states;
    map<State, pair<State, State>> all;

    DFA(epsilon_NFA e_nfa);

    void print_map();
    void print_nfa_table();
    bool check_is_final(int st_name);
    int states_to_state(vector<State> s);
    State calculate_s_prime_0(vector<State> s);
    State calculate_s_prime_1(vector<State> s);
    vector<State> get_reachable_states(State n);
    vector<State> get_s_prime_0_of_state(State s);
    vector<State> get_s_prime_1_of_state(State s);
};
void DFA::print_map()
{
    for (const auto &pair : all)
    {
        if (check_is_final(pair.first.get_state_name()))
        {
            pair.first.set_final();
        }
    }
    for (const auto &[key, value] : all)
    {
        cout << "State: " << key << " -> ("
             << "0: " << value.first << "| " << "1: " << value.second << "| "
             << ((key.get_is_start()) ? "Start" : "Non-Start") << ", "
             << ((key.get_is_final()) ? "Final" : "Non-Final") << ")\n";
    }
}
DFA::DFA(epsilon_NFA e_nfa)
{
    this->e_nfa = e_nfa;
    this->final_states = e_nfa.final_states;
    this->start_state = e_nfa.start_state;
    all_states.push_back(start_state);

    calculate_DFA();
}
vector<State> DFA::get_s_prime_0_of_state(State s)
{
    return e_nfa.s_prime_0[s];
}
vector<State> DFA::get_s_prime_1_of_state(State s)
{
    return e_nfa.s_prime_1[s];
}
vector<int> getDigits(int number)
{
    vector<int> digits;
    while (number > 0)
    {
        digits.push_back(number % 10); // Son rakamı al
        number /= 10;                  // Sayıyı küçült
    }

    return digits;
}
vector<State> DFA::get_reachable_states(State s)
{
    vector<State> list;
    vector<int> number_list = getDigits(s.get_state_name());
    for (int i = 0; i < number_list.size(); i++)
    {
        if (!is_exist_in_vector(list, number_list.at(i)))
        {
            list.push_back(state_name_to_state(number_list.at(i)));
        }
    }
    return list;
}
bool DFA::is_exist_in_map(int state_name)
{
    for (const auto &entry : all)
    {
        if (entry.first.get_state_name() == state_name)
        {
            return true;
        }
    }
    return false;
}
bool DFA::check_is_final(int st_name)
{
    string temp = to_string(st_name);
    for (int i = 0; i < temp.size(); i++)
    {
        if (is_exist_in_vector(final_states, temp[i] - '0'))
        {
            return true;
        }
    }
    return false;
}
void DFA::calculate_DFA()
{
    auto temp = all_states;
    while (!temp.empty())
    {
        State cur_state = temp.front();
        State new_state_0 = calculate_s_prime_0(get_reachable_states(cur_state));
        if (!is_exist_in_map(new_state_0.get_state_name()) && new_state_0.get_state_name() != 0)
        {
            temp.push_back(new_state_0);
            all_states.push_back(new_state_0);
        }

        State new_state_1 = calculate_s_prime_1(get_reachable_states(cur_state));
        if (!is_exist_in_map(new_state_1.get_state_name()) && new_state_1.get_state_name() != 0)
        {
            temp.push_back(new_state_1);
            all_states.push_back(new_state_1);
        }
        all[cur_state] = make_pair(new_state_0, new_state_1);
        temp.erase(temp.begin());
    }

    State dead_state(0, {0}, {0}, 0, 0);
    all[dead_state] = make_pair(dead_state, dead_state);
}

State DFA::calculate_s_prime_0(vector<State> s_list)
{
    vector<State> prime_list;
    for (int i = 0; i < s_list.size(); i++)
    {
        vector<State> temp = get_s_prime_0_of_state(s_list[i]);
        prime_list.insert(prime_list.end(), temp.begin(), temp.end());
    }
    int st_name = 0;
    if (prime_list.size() != 0)
    {
        st_name = states_to_state(prime_list);
    }
    State new_state(st_name);
    return new_state;
}

State DFA::calculate_s_prime_1(vector<State> s_list)
{
    vector<State> prime_list;
    for (int i = 0; i < s_list.size(); i++)
    {
        auto temp = get_s_prime_1_of_state(s_list[i]);
        prime_list.insert(prime_list.end(), temp.begin(), temp.end());
    }
    int st_name = 0;
    if (prime_list.size() != 0)
    {
        st_name = states_to_state(prime_list);
    }
    State new_state(st_name);
    return new_state;
}

int DFA::states_to_state(vector<State> s_0)
{
    set<int> unique_states;
    for (int i = 0; i < s_0.size(); i++)
    {
        unique_states.insert(s_0.at(i).get_state_name());
    }
    string st_name = "";
    for (int state : unique_states)
    {
        st_name += to_string(state);
    }

    int state_name_0 = atoi(st_name.c_str());

    return state_name_0;
}
State DFA::state_name_to_state(int state_name)
{
    for (const auto &pair : e_nfa.s_prime_0)
    {
        const State &key = pair.first;
        if (key.get_state_name() == state_name)
        {
            return key;
        }
    }
    throw runtime_error("State not found for the given state_name: " + to_string(state_name));
}

#endif
#ifndef EPSILON_NFA__HPP
#define EPSILON_NFA__HPP
#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include "state.hpp"

class epsilon_NFA
{
private:
    vector<State> all_states;
    State state_name_to_state(int state_name);
    vector<State> get_ones_transtion_states(State s);
    vector<State> get_zeros_transtion_states(State s);
    vector<State> get_epsilon_transtion_states(State s);
    set<State> get_s_prime(vector<State> list, bool is_get_zeros);

public:
    State start_state;
    set<State> final_states;
    map<State, set<State>> s_prime_0;
    map<State, set<State>> s_prime_1;

    epsilon_NFA();
    epsilon_NFA(vector<State> all_states);
    ~epsilon_NFA();

    void calculate_s_prime_0();
    void calculate_s_prime_1();
    void print_epsilon_nfa_table();
    void print_map(map<State, set<State>> mp);
};
void print_vector(vector<State> v);

epsilon_NFA::epsilon_NFA() {}

epsilon_NFA::epsilon_NFA(vector<State> all_states)
{
    this->all_states = all_states;
    for (int i = 0; i < all_states.size(); i++)
    {
        State current_state = all_states.at(i);
        if (current_state.get_is_final())
        {
            final_states.insert(current_state);
        }
        if (current_state.get_is_start())
        {
            this->start_state = current_state;
        }
    }
}
void epsilon_NFA::print_epsilon_nfa_table()
{
    int colWidth = 7;
    cout << setw(colWidth) << setw(colWidth) << "S TABLE" << endl;
    const int rows = all_states.size();
    const int cols = 5;

    string colNames[cols] = {"S(q,0)", "S(q,1)", "S(q,ε)", "S*(q,0)", "S*(q,1)"};

    cout << "+----------+----------+----------+----------+----------+" << endl;
    cout << "|";
    cout << setw(colWidth) << " ";
    for (int j = 0; j < cols; ++j)
    {
        cout << "|" << setw(colWidth) << colNames[j];
    }
    cout << "|" << endl;
    cout << "+----------+----------+----------+----------+----------+" << endl;

    for (int i = 0; i < rows; ++i)
    {
        State temp = all_states.at(i);
        cout << "|" << setw(colWidth) << temp.get_state_name() << "|" << setw(colWidth);

        for (int value : temp.get_transition_zero())
        {
            cout << value << ",";
        }
        cout << "|" << setw(colWidth);
        for (int value : temp.get_transition_one())
        {
            cout << value << ",";
        }
        cout << "|" << setw(colWidth);
        for (int value : temp.get_transition_epsilon())
        {
            cout << value << ",";
        }
        cout << "|" << setw(colWidth);
        for (const auto &pair : s_prime_0)
        {
            if (pair.first == temp)
            {
                for (State s : pair.second)
                {
                    cout << s.get_state_name() << ",";
                }
            }
        }
        cout << "|" << setw(colWidth);
        for (const auto &pair : s_prime_1)
        {
            if (pair.first == temp)
            {
                for (State s : pair.second)
                {
                    cout << s.get_state_name() << ",";
                }
            }
        }
        cout << "|" << endl
             << "+----------+----------+----------+----------+----------+" << endl;
    }
    getchar();
}

bool is_exist_in_vector(set<State> &vec, int currrent_state_name)
{
    for (auto &value : vec)
    {
        if (value.get_state_name() == currrent_state_name)
        {
            return true;
        }
    }
    return false;
}
void epsilon_NFA::calculate_s_prime_1()
{
    for (int i = 0; i < all_states.size(); i++) // tüm statelere bakıyoruz.
    {
        State current_state = all_states.at(i);

        vector<State> epsilon_transitions_of_current_state = get_epsilon_transtion_states(current_state);
        s_prime_1[current_state] = get_s_prime(epsilon_transitions_of_current_state, false);
    }
    cout << "S PRIME 1" << endl;
    print_map(s_prime_1);
    cout << endl
         << endl
         << endl
         << endl;
}
void epsilon_NFA::calculate_s_prime_0()
{
    for (int i = 0; i < all_states.size(); i++) // tüm statelere bakıyoruz.
    {
        State current_state = all_states.at(i);

        vector<State> epsilon_transitions_of_current_state = get_epsilon_transtion_states(current_state);
        s_prime_0[current_state] = get_s_prime(epsilon_transitions_of_current_state, true);
    }
    cout << "S PRIME 0" << endl;
    print_map(s_prime_0);
    cout << endl
         << endl
         << endl
         << endl;
}
set<State> epsilon_NFA::get_s_prime(vector<State> epsilon_list, bool is_get_zeros)
{
    // ilk a lara bakıp sonra epsilonlara bakmalıyız.
    set<State> prime_list;
    set<State> prime_list2;
    prime_list2.insert(epsilon_list.begin(), epsilon_list.end());

    for (State state : prime_list2)
    {
        if (state.is_there_any_transition_epsilon())
        {
            vector<State> episode1 = get_epsilon_transtion_states(state);
            for (State value : episode1)
            {
                prime_list2.insert(value);
            }

            for (State value1 : prime_list2)
            {
                if (value1.is_there_any_transition_epsilon())
                {
                    vector<State> episode2 = get_epsilon_transtion_states(value1);
                    for (State value2 : episode2)
                    {
                        prime_list2.insert(value2);
                    }
                }
            }
        }
    }
    for (State value : prime_list2)
    {
        vector<State> list;
        if (is_get_zeros)
        {
            list = get_zeros_transtion_states(value);
            for (State value : list)
            {
                prime_list.insert(value);
            }
        }
        else
        {
            list = get_ones_transtion_states(value);
            for (State value : list)
            {
                prime_list.insert(value);
            }
        }
    }
    /*
     */
    for (State state : prime_list)
    {
        if (state.is_there_any_transition_epsilon())
        {
            vector<State> episode1 = get_epsilon_transtion_states(state);
            for (State value : episode1)
            {
                prime_list.insert(value);
            }

            for (State value1 : prime_list)
            {
                if (value1.is_there_any_transition_epsilon())
                {
                    vector<State> episode2 = get_epsilon_transtion_states(value1);
                    for (State value2 : episode2)
                    {
                        prime_list.insert(value2);
                    }
                }
            }
        }
    }
    return prime_list;
}

vector<State> epsilon_NFA::get_zeros_transtion_states(State s) // sıkıntı burada
{
    vector<State> list;
    for (int i = 0; i < s.get_transition_zero().size(); i++)
    {
        list.push_back(state_name_to_state(s.get_transition_zero().at(i)));
    }
    return list;
}
vector<State> epsilon_NFA::get_ones_transtion_states(State s) // sıkıntı burada
{
    vector<State> list;
    for (int i = 0; i < s.get_transition_one().size(); i++)
    {
        list.push_back(state_name_to_state(s.get_transition_one().at(i)));
    }
    return list;
}
State epsilon_NFA::state_name_to_state(int state_name)
{
    for (int i = 0; i < all_states.size(); i++)
    {
        State temp = all_states.at(i);
        if (temp.get_state_name() == state_name)
        {
            return temp;
        }
    }
    throw std::runtime_error("State not found for the given state_name: " + std::to_string(state_name));
}

void epsilon_NFA::print_map(map<State, set<State>> map)
{
    for (const auto &pair : map)
    {
        std::cout << "State:" << pair.first << ":";
        for (const auto &state : pair.second)
        {
            std::cout << state << " ";
        }
        std::cout << "\n";
    }
}
void print_vector(vector<State> v)
{
    for (const auto &state : v)
    {
        std::cout << state << endl;
    }
}
epsilon_NFA::~epsilon_NFA()
{
}

vector<State> epsilon_NFA::get_epsilon_transtion_states(State s)
{
    vector<State> list;
    list.push_back(s);
    for (int i = 0; i < s.get_transition_epsilon().size(); i++)
    {
        list.push_back(state_name_to_state(s.get_transition_epsilon().at(i)));
    }
    return list;
}

#endif
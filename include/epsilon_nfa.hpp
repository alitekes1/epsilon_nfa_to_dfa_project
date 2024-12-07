#ifndef EPSILON_NFA__HPP
#define EPSILON_NFA__HPP
#include <iostream>
#include <vector>
#include <iomanip> // setw fonksiyonu için gerekli
#include <map>
#include "state.hpp"

class epsilon_NFA
{
private:
    vector<State> all_states;
    State state_name_to_state(int state_name);
    vector<State> const get_ones_transtion_states(State s);
    vector<State> const get_zeros_transtion_states(State s);
    vector<State> const get_epsilon_transtion_states(State s);
    vector<State> get_s_prime(vector<State> list, bool is_get_zeros);

public:
    State start_state;
    vector<State> final_states;
    map<State, vector<State>> s_prime_0;
    map<State, vector<State>> s_prime_1;

    epsilon_NFA();
    epsilon_NFA(vector<State> all_states);
    void calculate_s_prime_0();
    void calculate_s_prime_1();
    void print_epsilon_nfa_table();
    void print_map(map<State, vector<State>> mp);
    ~epsilon_NFA();
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
            final_states.push_back(current_state);
        }
        if (current_state.get_is_start())
        {
            this->start_state = current_state;
        }
    }
}
void epsilon_NFA::print_epsilon_nfa_table()
{
    const int rows = all_states.size();
    const int cols = 5;

    string colNames[cols] = {"S(q,0)", "S(q,1)", "S(q,ε)", "S*(q,0)", "S*(q,1)"};

    int colWidth = 10;
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

        for (int i = 0; i < temp.get_transition_zero().size(); i++)
        {
            cout << temp.get_transition_zero().at(i) << ",";
        }
        cout << "|" << setw(colWidth);
        for (int i = 0; i < temp.get_transition_one().size(); i++)
        {
            cout << temp.get_transition_one().at(i) << ",";
        }
        cout << "|" << setw(colWidth);
        for (int i = 0; i < temp.get_transition_epsilon().size(); i++)
        {
            cout << temp.get_transition_epsilon().at(i) << ",";
        }

        // cout << "|" << setw(colWidth);
        // for (int i = 0; i < temp.get_transition_one().size(); i++)
        // {
        //     cout << temp.get_transition_one().at(i) << ",";
        // }
        cout << "|" << setw(colWidth);
        cout << "|" << endl
             << "+----------+----------+----------+----------+----------+" << endl;
    }
}

bool is_exist_in_vector(std::vector<State> &vec, int currrent_state_name)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec.at(i).get_state_name() == currrent_state_name)
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
        epsilon_transitions_of_current_state.push_back(current_state); // kendine de boşlukla gidebiliyor.
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
        epsilon_transitions_of_current_state.push_back(current_state); // kendine de boşlukla gidebiliyor.
        s_prime_0[current_state] = get_s_prime(epsilon_transitions_of_current_state, true);
    }
    cout << "S PRIME 0" << endl;
    print_map(s_prime_0);
    cout << endl
         << endl
         << endl
         << endl;
}
vector<State> epsilon_NFA::get_s_prime(vector<State> epsilon_list, bool is_get_zeros)
{
    vector<State> list2;
    for (int i = 0; i < epsilon_list.size(); i++)
    {
        State current_state = epsilon_list.at(i);
        if (current_state.get_transition_zero().size() > 0 && is_get_zeros)
        {
            vector<State> temp = get_zeros_transtion_states(current_state);
            list2.insert(list2.end(), temp.begin(), temp.end());
        }
        else if (current_state.get_transition_one().size() > 0 && !is_get_zeros)
        {
            vector<State> temp = get_ones_transtion_states(current_state);
            list2.insert(list2.end(), temp.begin(), temp.end());
        }
        for (int j = 0; j < current_state.get_transition_epsilon().size(); j++)
        {
            vector<State> temp2 = get_epsilon_transtion_states(current_state); // burada sorgula.
            for (int k = 0; k < temp2.size(); k++)
            {
                if (!is_exist_in_vector(list2, temp2.at(k).get_state_name()))
                {
                    epsilon_list.push_back(temp2.at(k));
                }
            }
        }
    }
    for (int j = 0; j < list2.size(); j++)
    {
        if (list2.at(j).get_transition_epsilon().size() > 0)
        {
            vector<State> temp2 = get_epsilon_transtion_states(list2.at(j));

            for (int k = 0; k < temp2.size(); k++)
            {
                if (!is_exist_in_vector(list2, temp2.at(k).get_state_name()))
                {
                    list2.push_back(temp2.at(k));
                }
            }
        }
    }
    return list2;
}

vector<State> const epsilon_NFA::get_zeros_transtion_states(State s) // sıkıntı burada
{
    vector<State> list;
    for (int i = 0; i < s.get_transition_zero().size(); i++)
    {
        list.push_back(state_name_to_state(s.get_transition_zero().at(i)));
    }
    return list;
}
vector<State> const epsilon_NFA::get_ones_transtion_states(State s) // sıkıntı burada
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

void epsilon_NFA::print_map(map<State, vector<State>> map)
{
    for (const auto &pair : map)
    {
        // Anahtar (State) yazdırma
        std::cout << "State:" << pair.first << ":";

        // Değer (vector<State>) yazdırma
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

vector<State> const epsilon_NFA::get_epsilon_transtion_states(State s)
{
    vector<State> list;
    for (int i = 0; i < s.get_transition_epsilon().size(); i++)
    {
        list.push_back(state_name_to_state(s.get_transition_epsilon().at(i)));
    }
    return list;
}

#endif
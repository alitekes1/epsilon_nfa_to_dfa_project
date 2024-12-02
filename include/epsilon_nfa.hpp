#ifndef EPSILON_NFA
#define EPSILON_NFA
#include <vector>
#include "state.hpp"
#include <iomanip> // setw fonksiyonu için gerekli
#include <map>

void print_map(map<State, vector<State>> mp);
class epsilon_NFA
{
private:
    vector<State> all_states;
    vector<State> final_state;
    State start_state;
    map<State, vector<State>> s_prime_0;
    map<State, vector<State>> s_prime_1;

public:
    epsilon_NFA(vector<State> all_states);
    ~epsilon_NFA();
    void calculate_s_prime_0();
    void calculate_s_prime_1();
    void print_epsilon_nfa_table();
    void s_prime_values(vector<State> v);
    State state_name_to_state(int state_name);
    vector<State> control_epsilon_zero(vector<State> list);
    vector<State> get_epsilon_transtion_states(State s);
    vector<State> get_zeros_transtion_states(State s);
};
void print_vector(vector<State> v);
epsilon_NFA::epsilon_NFA(vector<State> all_states)
{
    this->all_states = all_states;
    for (int i = 0; i < all_states.size(); i++)
    {
        State current_state = all_states.at(i);
        if (current_state.get_is_final())
        {
            final_state.push_back(current_state);
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
        // for (auto it = s_prime_0.begin(); it != s_prime_0.end(); ++it)
        // {
        //     cout << it->first << endl;
        //     for (int num : it->second)
        //     {
        //         std::cout << num << " ";
        //     }
        //     std::cout << std::endl;
        // }
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
// ilk önce boşluk ile o durumdan gidebildiklerimi bul. kendine de gidebiliyor.
// bulduğun durumların tüm 0 geçişlerini ekle.
// eklediğin yerlerin epsilon geçişlerini de ekle. eklediğin yerlerin boşluk geçişi bitene kadar ekle.
void epsilon_NFA::calculate_s_prime_0()
{
    for (int i = 0; i < all_states.size(); i++) // tüm statelere bakıyoruz.
    {
        State current_state = all_states.at(i);

        vector<State> epsilon_transitions_of_current_state = get_epsilon_transtion_states(current_state);
        epsilon_transitions_of_current_state.push_back(current_state); // kendine de boşlukla gidebiliyor.
        s_prime_0[current_state] = control_epsilon_zero(epsilon_transitions_of_current_state);
    }
    print_map(s_prime_0);
}

vector<State> epsilon_NFA::control_epsilon_zero(vector<State> epsilon_list)
{
    vector<State> list2;
    for (int i = 0; i < epsilon_list.size(); i++)
    {
        if (epsilon_list.at(i).get_transition_zero().size() > 0)
        {
            vector<State> temp = get_zeros_transtion_states(epsilon_list.at(i));
            list2.insert(list2.end(), temp.begin(), temp.end());
        }
    }
    for (int j = 0; j < list2.size(); j++)
    {
        if (list2.at(j).get_transition_epsilon().size() > 0)
        {
            vector<State> temp_2 = get_epsilon_transtion_states(list2.at(j));
            list2.insert(list2.end(), temp_2.begin(), temp_2.end());
        }
    }
    return list2;
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

void epsilon_NFA::calculate_s_prime_1()
{
}
void print_map(map<State, vector<State>> s_prime_0)
{
    for (const auto &pair : s_prime_0)
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
    cout << endl;
}
epsilon_NFA::~epsilon_NFA()
{
}

vector<State> epsilon_NFA::get_epsilon_transtion_states(State s)
{
    vector<State> list;
    for (int i = 0; i < s.get_transition_epsilon().size(); i++)
    {
        list.push_back(state_name_to_state(s.get_transition_epsilon().at(i)));
    }
    return list;
}

#endif
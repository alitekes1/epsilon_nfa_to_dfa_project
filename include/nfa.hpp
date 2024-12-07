#ifndef NFA__HPP
#define NFA__HPP
#include "epsilon_nfa.hpp"
#include <set>

class NFA
{
private:
    epsilon_NFA e_nfa;
    State state_name_to_state(int state_name);
    vector<State> const get_ones_transtion_state(State s);
    vector<State> const get_zeros_transtion_state(State s);

public:
    State start_state;
    vector<State> final_states;
    vector<State> all_states;
    map<State, pair<State, State>> all;

    NFA(epsilon_NFA e_nfa);
    State calculate_s_prime_0(vector<State> s);
    State calculate_s_prime_1(vector<State> s);
    void print_nfa_table();
    void function();
    vector<State> get_s_prime_0_of_state(State s);
    vector<State> get_s_prime_1_of_state(State s);
    vector<State> calisma(State n);
    int states_to_state(vector<State> s);
    void print_map();
    bool is_exist_in_map(int stn);
};
void NFA::print_map()
{
    for (const auto &[key, value] : all)
    {
        std::cout << "Key: " << key << " -> Value: ("
                  << value.first << ", " << value.second << ")\n";
    }
    getchar();
}
NFA::NFA(epsilon_NFA e_nfa)
{
    this->e_nfa = e_nfa;
    this->start_state = e_nfa.start_state;
    all_states.push_back(start_state);

    function();
}
vector<State> NFA::get_s_prime_0_of_state(State s)
{
    return e_nfa.s_prime_0[s];
}
vector<State> NFA::get_s_prime_1_of_state(State s)
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
vector<State> NFA::calisma(State s)
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
bool NFA::is_exist_in_map(int state_name)
{
    // Map üzerinde state_name'e sahip bir State nesnesinin varlığını kontrol et
    for (const auto &entry : all)
    {
        if (entry.first.get_state_name() == state_name)
        {
            return true; // Anahtar bulunursa true döner
        }
    }
    return false; // Anahtar bulunmazsa false döner
}
void NFA::function()
{
    while (!all_states.empty())
    {
        State cur_state = all_states.front();
        cout << "current state:" << cur_state << endl;
        State new_state_0 = calculate_s_prime_0(calisma(cur_state)); // 2 ve 3 ü ayıracak bişeyler lazım.
        if (!is_exist_in_map(new_state_0.get_state_name()) && new_state_0.get_state_name() != 0)
        {
            all_states.push_back(new_state_0);
        }

        State new_state_1 = calculate_s_prime_1(calisma(cur_state));
        if (!is_exist_in_map(new_state_1.get_state_name()) && new_state_1.get_state_name() != 0)
        {
            all_states.push_back(new_state_1);
        }
        all[cur_state] = make_pair(new_state_0, new_state_1);
        print_map();
        cout << "----------" << endl;
        all_states.erase(all_states.begin());
        cout << "all_states:" << endl;
        print_vector(all_states);
        cout << "----------" << endl;
    }
    State dead_state(0, {0}, {0}, 0, 1);
    all[dead_state] = make_pair(dead_state, dead_state);
}

State NFA::calculate_s_prime_0(vector<State> s_list)
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

State NFA::calculate_s_prime_1(vector<State> s_list)
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
int NFA::states_to_state(std::vector<State> s_0)
{
    std::set<int> unique_states; // Tekrar edenleri otomatik olarak kaldıracak
    for (int i = 0; i < s_0.size(); i++)
    {
        unique_states.insert(s_0.at(i).get_state_name()); // Set'e ekler, tekrarları engeller
    }
    std::string state_name_zero = "";
    for (int state : unique_states)
    {
        state_name_zero += std::to_string(state); // Her state'i string olarak birleştir
    }

    int state_name_0 = std::atoi(state_name_zero.c_str());

    return state_name_0;
}
State NFA::state_name_to_state(int state_name)
{
    for (const auto &pair : e_nfa.s_prime_0)
    {
        const State &key = pair.first; // map'in anahtarı
        if (key.get_state_name() == state_name)
        {
            return key; // Eşleşen anahtarı döndür
        }
    }
    throw runtime_error("State not found for the given state_name: " + to_string(state_name));
}

#endif NFA__HPP
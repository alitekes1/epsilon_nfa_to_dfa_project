#ifndef STATE_HPP
#define STATE_HPP
#include <vector>
#include <string>
using namespace std;

class State
{
private:
    int state_name;
    vector<int> transition_one;
    vector<int> transition_zero;
    vector<int> transition_epsilon;
    bool is_final;
    bool is_start;

public:
    State() = default;
    State(int, vector<int>, vector<int>, vector<int>, bool, bool);
    ~State();
    vector<int> get_transition_one();
    vector<int> get_transition_zero();
    vector<int> get_transition_epsilon();
    bool get_is_final();
    bool get_is_start();
    int get_state_name();
    bool is_there_any_transition_epsilon();
    void print_int_vector();
    // map fonksiyonları için gerekli

    bool operator<(const State &other) const
    {
        return state_name < other.state_name;
    }
    bool operator==(const State &other) const
    {
        return state_name == other.state_name;
    }
    friend std::ostream &operator<<(std::ostream &os, const State &state)
    {
        os << "SN" << state.state_name << " ";
        return os;
    }
};

State::State(int state_name, vector<int> transition_zero, vector<int> transition_one, vector<int> transition_epsilon, bool is_start = false, bool is_final = false)
{
    this->state_name = state_name;
    this->transition_one = transition_one;
    this->transition_zero = transition_zero;
    this->transition_epsilon = transition_epsilon;
    this->is_final = is_final;
    this->is_start = is_start;
}
State::~State()
{
}
vector<int> State::get_transition_one()
{
    return this->transition_one;
}
vector<int> State::get_transition_zero()
{
    return this->transition_zero;
}
vector<int> State::get_transition_epsilon()
{
    return this->transition_epsilon;
}
bool State::get_is_final()
{
    return this->is_final;
}
bool State::get_is_start()
{
    return this->is_start;
}
int State::get_state_name()
{
    return this->state_name;
}
bool State::is_there_any_transition_epsilon()
{
    return transition_epsilon.size() > 0;
}
void State::print_int_vector()
{
    for (int i = 0; i < transition_zero.size(); i++)
    {
        cout << transition_zero.at(i) << endl;
    }
}
#endif
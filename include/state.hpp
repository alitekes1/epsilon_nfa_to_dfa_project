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
#endif
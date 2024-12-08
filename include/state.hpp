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
    bool is_start;
    mutable bool is_final;

public:
    State() = default;
    State(int state_name);
    State(int state_name, vector<int> zero_transtions, vector<int> one_transitions, bool = false, bool = false);
    State(int state_name, vector<int> zero_transtions, vector<int> one_transitions, vector<int> epsilon_transitions, bool = false, bool = false);

    ~State();

    void set_final() const;
    void print_int_vector();
    bool get_is_start() const;
    bool get_is_final() const;
    int get_state_name() const;
    vector<int> get_transition_one();
    vector<int> get_transition_zero();
    vector<int> get_transition_epsilon();
    bool is_there_any_transition_epsilon();

    void set_transition_one(vector<int> s)
    {
        this->transition_one = s;
    }
    void set_transition_zero(vector<int> s)
    {
        this->transition_zero = s;
    }
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
        os << "S" << state.state_name << " ";
        return os;
    }
};

State::State(int state_name, vector<int> transition_zero, vector<int> transition_one, vector<int> transition_epsilon, bool is_start, bool is_final)
{
    this->state_name = state_name;
    this->transition_one = transition_one;
    this->transition_zero = transition_zero;
    this->transition_epsilon = transition_epsilon;
    this->is_final = is_final;
    this->is_start = is_start;
}
State::State(int state_name, vector<int> transition_zero, vector<int> transition_one, bool is_start, bool is_final)
{
    this->state_name = state_name;
    this->transition_one = transition_one;
    this->transition_zero = transition_zero;
    this->is_final = is_final;
    this->is_start = is_start;
}
State::State(int state_name)
{
    this->state_name = state_name;
    this->is_final = false;
    this->is_start = false;
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
bool State::get_is_final() const
{
    return this->is_final;
}
bool State::get_is_start() const
{
    return this->is_start;
}
int State::get_state_name() const
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
void State::set_final() const
{
    this->is_final = 1;
}
#endif
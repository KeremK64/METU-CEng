#ifndef NFA_HPP
#define NFA_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <set>
#include "components.hpp"

class NFA
{
private:
    std::set<std::string> all_states;
    Alphabet alphabet;
    TransitionTable transitions;
    std::string starting_state;
    std::set<std::string> final_states;
    bool has_state(const std::string& state) const;
    bool is_final_state(const std::string& state) const;

public:
    NFA() = default;
    NFA(const NFA& other) = default;
    NFA& operator=(const NFA& other) = default;

    // you do not have to worry about reading inputs
    // all test cases will be compatible with the below
    NFA(const std::string filename) 
    {
        std::string line;
        std::ifstream config_file(filename);
        if (!config_file.is_open()){
            std::cout << "cannot open the file (wrong file path?)" << std::endl;
            return;
        }
        std::getline(config_file, line); // read the symbols
        this->alphabet.init_from_line(line);

        std::getline(config_file, line); // read all states
        std::vector<std::string> states = parse_line(line, ' ');
        for (const std::string& state: states)
            this->all_states.insert(state);

        std::getline(config_file, line); // read the starting state
        this->starting_state = line;

        std::getline(config_file, line); // read the final states
        states = parse_line(line, ' ');
        for (const std::string& state: states)
            this->final_states.insert(state);

        this->transitions.init_from_stream(config_file);

        config_file.close();
    }
    bool is_DFA() const;
    void update_state_name(const std::string& old_name, const std::string& new_name);
    bool process(std::string input);

    NFA operator!() const;
    NFA operator+(const NFA& other) const;
    friend std::ostream& operator<<(std::ostream& os, NFA& nfa){
        bool first = true;
        os << nfa.alphabet << std::endl;
        // all states
        for (auto it=nfa.all_states.begin(); it != nfa.all_states.end(); it++){
            if (first) {
                os << *it;
                first = false;
            }
            else
                os << " " << *it;
        }
        os << std::endl;
        os << nfa.starting_state << std::endl;
        // final states
        first = true;
        for (auto it=nfa.final_states.begin(); it != nfa.final_states.end(); it++){
            if (first) {
                os << *it;
                first = false;
            }
            else
                os << " " << *it;
        }
        os << std::endl;
        os << nfa.transitions;
        return os;
    }
};

#endif // NFA_HPP
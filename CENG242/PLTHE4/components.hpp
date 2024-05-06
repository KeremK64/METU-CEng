#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include "utils.hpp"


class Alphabet
{
private:
    std::set<char> symbols;

public:
    void init_from_line(std::string line){
        std::vector<std::string> parseds = parse_line(line, ' ');
        for (std::string symbol : parseds)
            this->symbols.insert(symbol[0]);
    }
    bool is_valid(const std::string& input) const;
    const std::set<char> get_symbols() const;

    Alphabet& operator+=(const Alphabet& other);
    friend std::ostream& operator<<(std::ostream& os, Alphabet& a);
};


class Rule
{
private:
    std::string initial_state;
    char symbol;
    std::string final_state;

public:
    Rule() = delete;
    Rule(const Rule&) = default;
    Rule(const std::string& init_s, char symbol, const std::string& final_s);

    const std::string get_final_state() const;
    bool applies_to(const std::string& init_state, char symbol) const;
    void update_state_name(const std::string& old_name, const std::string& new_name);
    friend std::ostream& operator<<(std::ostream& os, const Rule& r);
};


class TransitionTable
{
private:
    std::vector<Rule> rules;

public:
    void init_from_stream(std::ifstream& config_file){
        std::string line;
        std::vector<std::string> parsed;
        while(std::getline(config_file, line)){
            parsed = parse_line(line, ' ');
            add_rule(parsed[0], parsed[1][0], parsed[2]);
        }
    }
    void add_rule(const std::string& initial_state, char symbol, const std::string& final_state);
    void update_state_name(const std::string& old_name, const std::string& new_name);
    const std::set<std::string> operator()(const std::string& curr_state, char symbol) const;
    TransitionTable& operator+=(const TransitionTable& other);
    friend std::ostream& operator<<(std::ostream& os, TransitionTable& t);
};


class ComputationBranch{
private:
    std::vector<std::pair<std::string,std::string>> config_history;

public:
    ComputationBranch() {};
    ComputationBranch(const ComputationBranch& other) = default;
    ComputationBranch(std::string state, std::string input) {
        // use make_pair(x,y) to create a variable of type pair<std::string,std::string>
        config_history.push_back(std::make_pair(state, input));
    }
    ComputationBranch& operator=(const ComputationBranch& other) = default;
    ComputationBranch(ComputationBranch&& other) = default; // be careful when using move
    ComputationBranch& operator=(ComputationBranch&& other) = default;

    void push_config(const std::string& state, const std::string& input);
    const std::pair<std::string,std::string> get_last_config() const;
    friend std::ostream& operator<<(std::ostream& os, const ComputationBranch& c);
};

#endif // COMPONENTS_HPP
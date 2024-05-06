#include "components.hpp"

/* operator<< overloads */
std::ostream& operator<<(std::ostream& os, Alphabet& a){
    const std::set<char>& symbols = a.get_symbols();
    for (char letter : symbols) {
        if(letter == *symbols.rbegin()){
            os << letter;
        }
        else{
            os << letter << " ";
        }
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, const Rule& r){
    os << r.initial_state << " " << r.symbol << " " << r.final_state;
    return os;
}
std::ostream& operator<<(std::ostream& os, TransitionTable& t){
    for(Rule rule: t.rules){
        os << rule << "\n";
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, const ComputationBranch& c){
    auto last_pair_it = std::prev(c.config_history.end());
    for (auto it = c.config_history.begin(); it != c.config_history.end(); ++it) { //pointer arithmetic
        const std::pair<std::string, std::string>& pair = *it;

        if(pair.first == ""){
            os << "(" << "e" << ", " << pair.second << ")";
        }
        else if(pair.second == ""){
            os << "(" << pair.first << ", " << "e" << ")";
        }
        else{
            os << "(" << pair.first << ", " << pair.second << ")";
        }

        if (it != last_pair_it) { //shouldn't print :- if i'm at the end
            os << " :- ";
        }
    }
    return os;
}


/* Alphabet */
bool Alphabet::is_valid(const std::string& input) const{

    for(char letter : input){
        if(symbols.find(letter) == symbols.end()){
            return false;
        }
    }
    return true;
}

const std::set<char> Alphabet::get_symbols() const { 
    std::set<char> a;

    for(char symbol : symbols){
        a.insert(symbol);
    }
    return a; 
}

Alphabet& Alphabet::operator+=(const Alphabet& other){
    for(char letter : other.symbols){
        this->symbols.insert(letter);
    }
    return *this;
}


/* Rule */
Rule::Rule(const std::string& init_s, char symbol, const std::string& final_s): initial_state(init_s), symbol(symbol), final_state(final_s){
    
}

const std::string Rule::get_final_state() const {
    return final_state;
}

void Rule::update_state_name(const std::string& old_name, const std::string& new_name){
    if (initial_state == old_name) {
        initial_state = new_name;
    }
    if (final_state == old_name) {
        final_state = new_name;
    }
}

bool Rule::applies_to(const std::string& c, char s) const{
    if(c == this->initial_state && s == this->symbol){
        return true;
    }
    return false;
}


/* TransitionTable */
void TransitionTable::add_rule(const std::string& initial_state, char symbol, const std::string& final_state){
    Rule kerem = Rule(initial_state, symbol, final_state);
    this->rules.push_back(kerem);
}

void TransitionTable::update_state_name(const std::string& old_name, const std::string& new_name){
    for(Rule &rule : rules){
        rule.update_state_name(old_name, new_name);
    }
}

const std::set<std::string> TransitionTable::operator()(const std::string& curr_state, char symbol) const{
    std::set<std::string> next_states;

    for(const Rule &rule : rules){
        if(rule.applies_to(curr_state, symbol)){
            next_states.insert(rule.get_final_state());
        }
    }
    return next_states;
}

TransitionTable& TransitionTable::operator+=(const TransitionTable& other){
    for(const Rule &rule : other.rules){
        this->rules.push_back(rule);
    }
    return *this;
}


/* ComputationBranch */
void ComputationBranch::push_config(const std::string& state, const std::string& input) {
    std::pair<std::string, std::string> pair;
    if (input == "") {
        pair = std::make_pair(state, "e");
    } else {
        pair = std::make_pair(state, input);
    }
    this->config_history.push_back(pair);
}

const std::pair<std::string, std::string> ComputationBranch::get_last_config() const {
    if (!this->config_history.empty()) {
        return this->config_history.back();
    } else {
    
    }
}
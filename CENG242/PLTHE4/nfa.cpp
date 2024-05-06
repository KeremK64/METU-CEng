#include "nfa.hpp"

// private:
bool NFA::has_state(const std::string& state) const{
    for(auto sta : this->all_states){
        if(sta == state){
            return true;
        }
    }
    return false;
}

bool NFA::is_final_state(const std::string& state) const{
    for(auto finals : this->final_states){
        if(finals == state){
            return true;
        }
    }
    return false;
}

// public:
bool NFA::is_DFA() const{

    for(std::string state : this->all_states){
        for(char ch : this->alphabet.get_symbols()){
            if(transitions(state, 'e').size() > 0){
                return false;
            }
            
            if(transitions(state, ch).size() == 1){
                continue;
            }
            else{
                return false;
            }
            
            
        }
    }
    return true;
}

void NFA::update_state_name(const std::string& old_name, const std::string& new_name){
    
    auto all_states_it = all_states.find(old_name);
    if (all_states_it != all_states.end()) {
        all_states.erase(all_states_it);
        all_states.insert(new_name);
    }

    auto final_states_it = final_states.find(old_name);
    if (final_states_it != final_states.end()) {
        final_states.erase(final_states_it);
        final_states.insert(new_name);
    }

    if (starting_state == old_name) {
        starting_state = new_name;
    }

    transitions.update_state_name(old_name, new_name);
}

bool NFA::process(std::string input){
    if (!alphabet.is_valid(input)) {
        std::cout << "Invalid string\n";
        return false;
    }

    std::queue<ComputationBranch> Q;
    ComputationBranch branch("s", input);
    Q.push(ComputationBranch(starting_state, input));
    ComputationBranch last;
 
    while (!Q.empty()) {
        branch = Q.front();
        Q.pop();
        if(branch.get_last_config().second == "e"){
            if (is_final_state(branch.get_last_config().first)) {
                std::cout << branch << std::endl;
                std::cout << "Accept\n";
                return true;
            }
        }
        

        std::string current_state = branch.get_last_config().first;
        std::string input_symbol = branch.get_last_config().second;
        
        // empty handling
        for (const auto& transition : transitions(current_state, 'e')) {
            ComputationBranch new_branch(branch);
            new_branch.push_config(transition, input_symbol); 
            Q.push(new_branch);
        }


        for (const auto& transition : transitions(current_state, input_symbol[0])) {
            ComputationBranch new_branch(branch);
            std::string remaining_input = input_symbol.substr(1);
            new_branch.push_config(transition, remaining_input); 
            Q.push(new_branch);
        }
        last = branch;
    }
    std::cout << last << "\n";
    std::cout << "Reject\n";
    return false;
}
    
NFA NFA::operator!() const{
    if (!is_DFA()) {
        std::cout << "Not a DFA\n";
        return *this;
    }

    NFA complement_NFA(*this); 

    // K-F
    std::set<std::string> complement_final_states;
    for (const auto& state : all_states) {
        if (final_states.find(state) == final_states.end()) {
            complement_final_states.insert(state);
        }
    }
    complement_NFA.final_states = complement_final_states;

    return complement_NFA;
}

NFA NFA::operator+(const NFA& other) const{
    NFA result = NFA(*this);
    NFA notResult = other;

    result.alphabet += other.alphabet;


    result.all_states = this->all_states;
    for (const std::string& state : other.all_states) {
        std::string newState = state;
        while (result.all_states.find(newState) != result.all_states.end()) {
            newState = "q" + newState;
        }
        result.all_states.insert(newState);
        notResult.all_states.erase(state);
        notResult.all_states.insert(newState);
        notResult.update_state_name(state, newState);
        if (other.final_states.find(state) != other.final_states.end()) {
            notResult.final_states.erase(state);
            notResult.final_states.insert(newState);
        }
        
    }





    result.starting_state = "s";
    while (result.all_states.find(result.starting_state) != result.all_states.end()) {
        result.starting_state = "s" + result.starting_state;
    }
    result.all_states.insert(result.starting_state);



    result.final_states = this->final_states;
    for (const std::string& state : notResult.final_states) {
        std::string newState = state;
        result.final_states.insert(newState);
    }



    result.transitions += notResult.transitions;
    TransitionTable TT = TransitionTable();
    TT.add_rule(result.starting_state , 'e', this->starting_state);
    TT.add_rule(result.starting_state, 'e', notResult.starting_state);
    result.transitions += TT;


    return result;
}
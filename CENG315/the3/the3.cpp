
#include <iostream>
using namespace std;
#include <string>
#include <climits>


int pickMax(int a, int b, bool &option){
    if(a > b){
        option = true;
        return a;
    }
    else{
        option = false;
        return b;
    }
}
int recursive_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment, int call_count){

    if(call_count == 1000000){
        possible_alignment = "STACK LIMIT REACHED";
        return INT_MIN;
    }


    if (sequence_A.empty()) {
        return -gap * sequence_B.length();
    }
    if (sequence_B.empty()) {
        return -gap * sequence_A.length();
    }

    int match_score = (sequence_A.front() == sequence_B.front()) ? match : -mismatch;
    int option1 = recursive_alignment(sequence_A.substr(1), sequence_B.substr(1), gap, mismatch, match, possible_alignment, call_count + 1) + match_score;
    int option2 = recursive_alignment(sequence_A.substr(1), sequence_B, gap, mismatch, match, possible_alignment, call_count + 1) - gap;
    int option3 = recursive_alignment(sequence_A, sequence_B.substr(1), gap, mismatch, match, possible_alignment, call_count + 1) - gap;

    bool optionPick = false;
    int x = pickMax(option1, option2, optionPick);
    bool temp = optionPick;
    int highest_alignment_score = pickMax(x, option3, optionPick);

    if (!optionPick) {
        possible_alignment = "_" + possible_alignment;
    }
    else{
        if(temp){
            possible_alignment = sequence_A.front() == sequence_B.front() ? sequence_A.front() + possible_alignment : "!";
        }
        else{
            possible_alignment = "." + possible_alignment;
        }
    }

    return highest_alignment_score;
}



int dp_table_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment){
    int highest_alignment_score;


    return highest_alignment_score;
}

int main(){

    string A = "THY";
    string B = "BETH";
    int gap = 1;
    int mismatch = 2;
    int match = 4;
    string possible_allignment = "";
    int call_count = 0;

    int score = recursive_alignment(A, B, gap, mismatch, match, possible_allignment, call_count);

    cout << score << " " << call_count << " " << possible_allignment << endl;

    return 0;
}

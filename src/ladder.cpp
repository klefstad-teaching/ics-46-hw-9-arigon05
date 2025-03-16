#include "ladder.h"

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int len1 = str1.size()
    int len2 = str2.size();

    if (abs(len1 - len2) > d) {
        return false; 
    }

    int differences_count = 0
    int i = 0, j = 0;

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            differences_count++;
            if (differences_count > d){
                return false;
            }

            if (len1 > len2) i++;  //deletion in str 1
            else if (len1 < len2) j++; //insertion in str 1
            else { i++; j++; }   //replacement  
        }
        else {
            i++;
            j++;
        } //continues on if the characters match
    }

    if (i < len1 || j < len2) {
        differences++;
    }

    return differences_count == d;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1); //if they are seperated by one distance(neighbors)
}

void error(string word1, string word2, string msg){
    std::cout << "ERROR in " << word1 << " and " << word 2 << " " << msg << std::endl;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and end words must be different.");
        return {};
    }

    queue<vector<string>> ladder_queue;
    set<string> visited;

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        return new_ladder;
                    }

                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return{} // empty ladder

}

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }

    file.close();
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()) {
        error(" ", " ", "No ladder found.");
        return;
    }
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
    }
    cout << endl;
}

void verify_word_ladder(){
    
    set<string> word_list;
    load_words(word_list, "../src/words.txt");

    string begin_word, end_word;
    cout << "Enter start word: ";
    cin >> begin_word;
    cout << "Enter end word: ";
    cin >> end_word;
    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);

    if (ladder.empty()) {
        cout << "No valid word ladder found.\n";
        return;
    }

    print_word_ladder(ladder);

    for (size_t i = 1; i < ladder.size(); ++i) {
        if (word_list.find(ladder[i]) == word_list.end()) {
            cout << "Invalid word ladder: '" << ladder[i] << "' is not a dictionary word.\n";
            return;
        }
    }

    for (size_t i = 1; i < ladder.size(); ++i) {
        if (!is_adjacent(ladder[i - 1], ladder[i])) {
            cout << "Invalid word ladder: '" << ladder[i - 1] << "' → '" << ladder[i] << "' is not a valid step.\n";
            return;
        }
    }

     cout << "Word ladder verified successfully!\n";
}
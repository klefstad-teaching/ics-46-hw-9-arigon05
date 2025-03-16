#include "ladder.h"

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int len1 = str1.size()
    int len2 = str2.size();

    if (abs(len1 - len2) > d) {
        return false; 
    }

    int diff_count = 0
    int i = 0, j = 0;

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            diff_count++;
            if (diff_count > d){
                return false;
            }

            if (len1 > len2) i++;      
            else if (len1 < len2) j++; 
            else { i++; j++; }         
        }
        else {
            i++;
            j++;
        }
    }

    return diff_count <= d;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1); //if they are seperated by one distance(neighbors)
}

void error(string word1, string word2, string msg){
    std::cout << "ERROR in " << word1 << " and " << word 2 << " " << msg << std::endl;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word) {
        error("Start and end words must be different.");
        return {};
    }
    if (word_list.find(end_word) == word_list.end()) {
        error("Error: End word is not in the dictionary.");
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

void load_words(set<string> & word_list, const string& file_name);
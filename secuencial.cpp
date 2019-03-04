#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <ctype.h> //toupper y tolower
#include <stdio.h>

using namespace std;

int main() {
    string line;
    vector<vector<string> > lines;
    multimap<string, string> dictionary; 
    ifstream file("all-the-news/articles1.csv");
    if (file) {
        while (getline(file, line)) {
            size_t n = lines.size();
            lines.resize(n + 1);
            istringstream ss(line);
            string field, push_field("");
            bool no_quotes = true;
            while (getline(ss, field, ',')) {
                if (static_cast<size_t>(count(field.begin(), field.end(), '"')) % 2 != 0) {
                    no_quotes = !no_quotes;
                }
                push_field += field + (no_quotes ? "" : ",");
                if (no_quotes) {
                    lines[n].push_back(push_field);
                    push_field.clear();
                }
            }
        }
    }
    string word;
    cout << "Ingrese una palabra: ";
    cin >> word;
    string wordUpper = word;
    string wordLower = word;
    int j = 0;
    for(int i = 0; i < word.length(); i++) {
        wordUpper[i] = toupper(word[i]);
        wordLower[j] = tolower(word[j]);
        j++;
    }
    for (auto line : lines) {
        int length = line.size();
        if(length > 4) {
            replace(line[length-1].begin(), line[length-1].end(), ',', ' ');
            replace(line[length-1].begin(), line[length-1].end(), '.', ' ');
            replace(line[length-1].begin(), line[length-1].end(), ';', ' ');
            replace(line[length-1].begin(), line[length-1].end(), ':', ' ');
            replace(line[length-1].begin(), line[length-1].end(), '?', ' ');
            replace(line[length-1].begin(), line[length-1].end(), '!', ' ');
            replace(line[length-1].begin(), line[length-1].end(), '"', ' ');
            stringstream ss(line[length-1]);
            string token;
            int count = 0;
            while (getline(ss, token, ' ')) {
                if(token.compare(wordLower) == 0 || token.compare(wordUpper) == 0){
                    count++;
                }
            }
            if (count > 0) {
                dictionary.insert(pair<string, string>(to_string(count) + "\t" + line[1], line[2])); // adding to a multimap
            }
        }
    }
    // printing multimap dictionary
    multimap<string, string>::iterator itr;
    for (itr = dictionary.begin(); itr != dictionary.end(); ++itr) { 
        cout << itr->first << '\t' << itr->second << '\n'; 
    }
    return 0;
}

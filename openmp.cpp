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
#include <omp.h>

using namespace std;

vector<vector<string>> readFiles(string fileP){
    string line;
    vector<vector<string>> lines;
    ifstream file(fileP);
    if (file)
    {
        while (getline(file, line))
        {
            size_t n = lines.size();
            lines.resize(n + 1);
            istringstream ss(line);
            string field, push_field("");
            bool no_quotes = true;
            while (getline(ss, field, ','))
            {
                if (static_cast<size_t>(count(field.begin(), field.end(), '"')) % 2 != 0)
                {
                    no_quotes = !no_quotes;
                }
                push_field += field + (no_quotes ? "" : ",");
                if (no_quotes)
                {
                    lines[n].push_back(push_field);
                    push_field.clear();
                }
            }
        }
    }
    return lines;
}

string toLower(string wordP)
{
    string word = wordP;
    for (int i = 0; i < wordP.length(); i++)
    {
        word[i] = tolower(wordP[i]);
    }
    return word;
}

int main(int argc, char const *argv[])
{
    multimap<int, string, greater<int>> dictionary;
    string word = argv[1];
    word = toLower(word);
    vector<string> files = {"all-the-news/articles1.csv", "all-the-news/articles2.csv", "all-the-news/articles3.csv"};
    int totalCount = 0;

    #pragma omp parallel
    {
        # pragma omp for
        for (int i = 0; i < 3; ++i)
        {
            vector<vector<string>> lines = readFiles(files[i]);
            for (auto line : lines)
            {
                int length = line.size();
                if (length > 4)
                {
                    string aux = "’“";
                    replace(line[length - 1].begin(), line[length - 1].end(), ',', ' ');
                    replace(line[length - 1].begin(), line[length - 1].end(), '.', ' ');
                    replace(line[length - 1].begin(), line[length - 1].end(), ';', ' ');
                    replace(line[length - 1].begin(), line[length - 1].end(), ':', ' ');
                    replace(line[length - 1].begin(), line[length - 1].end(), '?', ' ');
                    replace(line[length - 1].begin(), line[length - 1].end(), '!', ' ');
                    replace(line[length - 1].begin(), line[length - 1].end(), '"', ' ');
                    replace(line[length - 1].begin(), line[length - 1].end(), aux[0], ' ');
                    replace(line[length - 1].begin(), line[length - 1].end(), aux[1], ' ');
                    stringstream ss(line[length - 1]);
                    string token;
                    int count = 0;
                    while (getline(ss, token, ' '))
                    {
                        if (toLower(token).compare(word) == 0)
                        {
                            count++;
                            totalCount++;
                        }
                    }
                    if (count > 0)
                    {
                        dictionary.insert(pair<int, string>(count, line[1] + "\t" + line[2])); // adding to a multimap
                    }
                }
            }
        }
    }
    // printing multimap dictionary
    multimap<int, string>::iterator itr;
    int i = 0;
    for (itr = dictionary.begin(); itr != dictionary.end(); ++itr) {
        cout << itr->first << '\t' << itr->second << endl;
        if(i == 9) break;
        i++;
    }
    cout << word + " is " << totalCount << " times in all the news." << endl;
    return 0;
}

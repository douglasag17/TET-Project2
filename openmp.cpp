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
#include <time.h>

using namespace std;

string toLower(string wordP)
{
    string word = wordP;
    for (int i = 0; i < wordP.length(); i++)
    {
        word[i] = tolower(wordP[i]);
    }
    return word;
}

bool sortinrev(const pair<int,string> &a, const pair<int,string> &b){
    return (a.first > b.first);
}

int main(){
    clock_t start = clock();
    multimap<string, vector<pair<int,string>>> dictionary;
    multimap<string, vector<pair<int,string>>>::iterator it;
    vector<string> files = {"Particles1.csv", "Particles2.csv", "Particles3.csv"};
    for (int i = 0; i < files.size(); ++i){
        ifstream file(files[i]);
        string pos;
        string id;
        string title;
        string content;
        if (file){
            #pragma omp parallel
	    {
	    //while (getline(file, pos, '\t')){
	    while (!file.eof()) {   
                # pragma omp critical 
	        {
                getline(file, id, '\t');
                getline(file, title, '\t');
                getline(file, content);
		            stringstream ss(content);
                string token;
                while (getline(ss, token, ' '))
                {
                    vector<pair<int,string>> article;
                    it = dictionary.find(token);
                    if(it == dictionary.end()){
                        article.push_back(make_pair(1, id + "," + title));
                        dictionary.insert(make_pair(token, article));
                    }else{
                        if(it->second.back().second.compare(id + "," + title) == 0){
                            it->second.back().first += 1;
                        }else{
                            it->second.resize(it->second.size()+1);
                            it->second.at(it->second.size()-1) = make_pair(1, id + "," + title);
                        }
                    }
                }
		            }
            }
	          }
	      }
    }
    cout << "Time: " << (double)(clock() - start)/(CLOCKS_PER_SEC) << endl;
    multimap<string, vector<pair<int,string>>>::iterator itAux;
    string word;
    do{
        int i, total = 0;
        cout << "Enter the word (/ to quit): ";
        cin >> word;
        word = toLower(word);
        itAux = dictionary.find(word);
        if(itAux != dictionary.end()){
            sort(itAux->second.begin(), itAux->second.end(), sortinrev);
	      for (i = 0; i < itAux->second.size(); ++i){
                if(i < 10){
                    cout << itAux->second[i].first << " "<< itAux->second[i].second << endl;
                }
                total += itAux->second[i].first;
            }
            cout << word << " is " << total << " times in all the news." << endl;
        }else{
            cout << word <<" not found." << endl;
        }
    }while(word != "/");
    return 0;
}

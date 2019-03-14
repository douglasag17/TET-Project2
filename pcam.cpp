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
#include <string.h>
#include "mpi.h"
#include <omp.h>
#define N 110

using namespace std;

string toLower(string wordP) {
  string word = wordP;
  for (int i = 0; i < wordP.length(); i++) {
    word[i] = tolower(wordP[i]);
  }
  return word;
  }

  bool sortinrev(const pair<int,string> &a, const pair<int,string> &b){
    return (a.first > b.first);
  }

  int main (int argc, char *argv[]) {
    MPI_Init (&argc, &argv); // Initialize MPI environment
    int rank, size, namelen;
    char name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status info;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank); // ID of current process
    MPI_Get_processor_name (name, &namelen); // Hostname of node                                                                     
    MPI_Comm_size (MPI_COMM_WORLD, &size); // Number of processes

    char valueRec[N];
    char vectorKeyRec[N];
    char vectorValRec[N];
    char totalRec[10];

    if (rank == 0) {
      multimap<string, vector<pair<int,string>>> dictionary;
      multimap<string, vector<pair<int,string>>>::iterator it;
      vector<string> files = {"Particles1.csv"};
      for (int i = 0; i < files.size(); ++i){
        ifstream file(files[i]);
        string pos;
        string id;
        string title;
        string content;
        if (file){
	  while (getline(file, pos, '\t')){
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
		    it->second.push_back(make_pair(1, id + "," + title));
		  }
		}
	      }
	  }
        }
      }
      multimap<string, vector<pair<int,string>>>::iterator itAux;
      string word;
      //do{
        vector<pair<int,string>> vectorFinal;
	int i, total = 0;
        cout << "Enter the word (/ to quit): ";
        cin >> word;
        word = toLower(word);
        const char *wordSend = word.c_str();
        MPI_Send(wordSend, strlen(wordSend), MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Send(wordSend, strlen(wordSend), MPI_CHAR, 2, 0, MPI_COMM_WORLD);   
        itAux = dictionary.find(word);
        if(itAux != dictionary.end()){
	  sort(itAux->second.begin(), itAux->second.end(), sortinrev);
	  for (i = 0; i < itAux->second.size(); ++i){
	    if(i < 10){
	      //cout << itAux->second[i].first << " " << itAux->second[i].second << endl;
	      vectorFinal.push_back(make_pair(itAux->second[i].first, itAux->second[i].second));
	    }
	    total += itAux->second[i].first;
	  }
	  for(int i = 0; i < 2; ++i){
	    MPI_Recv(&totalRec, 10, MPI_CHAR, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &info);
	    int totalRecAux = atoi(totalRec);
	    total += totalRecAux;
	  }
	  cout << word << " is " << total << " times in all the news." << endl;
	  for (int i = 0; i < 20; i++) {
	    MPI_Recv(&vectorKeyRec, N, MPI_CHAR, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &info);
	    MPI_Recv(&vectorValRec, N, MPI_CHAR, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &info);
	    vectorFinal.push_back(make_pair(atoi(vectorKeyRec), vectorValRec));
	  }
        }else{
	  cout << word << " not found." << endl;
        }
	sort(vectorFinal.begin(), vectorFinal.end(), sortinrev);
	for(int i = 0; i < 10; ++i){
	  cout << vectorFinal[i].first << " " << vectorFinal[i].second << endl;
	}
	//}while(word != "/");
    }    
    if (rank == 1) {
      multimap<string, vector<pair<int,string>>> dictionary;
      multimap<string, vector<pair<int,string>>>::iterator it;
      vector<string> files = {"Particles2.csv"};
      for (int i = 0; i < files.size(); ++i){
        ifstream file(files[i]);
        string pos;
        string id;
        string title;
        string content;
        if (file){
	  while (getline(file, pos, '\t')){
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
		    it->second.push_back(make_pair(1, id + "," + title));
		  }
		}
	      }
	  }
        }
      }
      multimap<string, vector<pair<int,string>>>::iterator itAux;
      string word;
      int i, total = 0;
      MPI_Recv(&valueRec, N, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &info);
      word = valueRec;
      itAux = dictionary.find(word);
      if(itAux != dictionary.end()){
        sort(itAux->second.begin(), itAux->second.end(), sortinrev);
        for (i = 0; i < itAux->second.size(); ++i){
	  if(i < 10){
	    // cout << itAux->second[i].first << " "<< itAux->second[i].second << endl;
	    string key = to_string(itAux->second[i].first);
	    const char *keySend = key.c_str();
	    string value = itAux->second[i].second;
	    const char *valueSend = value.c_str();
	    MPI_Send(keySend, strlen(keySend), MPI_CHAR, 0, 1, MPI_COMM_WORLD);
	    MPI_Send(valueSend, strlen(valueSend), MPI_CHAR, 0, 1, MPI_COMM_WORLD);
	  }
	  total += itAux->second[i].first;
        }
	string totalStr = to_string(total);
	const char *totalSend = totalStr.c_str();
	MPI_Send(totalSend, strlen(totalSend), MPI_CHAR, 0, 3, MPI_COMM_WORLD);
        //cout << word << " is " << total << " times in all the news." << endl;
      }else{
        //cout << word <<" not found." << endl;
      }
    }

    if (rank == 2) {
      multimap<string, vector<pair<int,string>>> dictionary;
      multimap<string, vector<pair<int,string>>>::iterator it;
      vector<string> files = {"Particles3.csv"};
      for (int i = 0; i < files.size(); ++i){
        ifstream file(files[i]);
        string pos;
        string id;
        string title;
        string content;
        if (file){
          while (getline(file, pos, '\t')){
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
                    it->second.push_back(make_pair(1, id + "," + title));
                  }
                }
              }
          }
        }
      }
      multimap<string, vector<pair<int,string>>>::iterator itAux;
      string word;
      int i, total = 0;
      MPI_Recv(&valueRec, N, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &info);
      word = valueRec;
      itAux = dictionary.find(word);
      if(itAux != dictionary.end()){
        sort(itAux->second.begin(), itAux->second.end(), sortinrev);
        for (i = 0; i < itAux->second.size(); ++i){
          if(i < 10){
            // cout << itAux->second[i].first << " "<< itAux->second[i].second << endl;
            string key = to_string(itAux->second[i].first);
            const char *keySend = key.c_str();
            string value = itAux->second[i].second;
            const char *valueSend = value.c_str();
            MPI_Send(keySend, strlen(keySend), MPI_CHAR, 0, 1, MPI_COMM_WORLD);
            MPI_Send(valueSend, strlen(valueSend), MPI_CHAR, 0, 1, MPI_COMM_WORLD);
          }
          total += itAux->second[i].first;
        }
	string totalStr = to_string(total);
        const char *totalSend = totalStr.c_str();
        MPI_Send(totalSend, strlen(totalSend), MPI_CHAR, 0, 3, MPI_COMM_WORLD);
        //cout << word << " is " << total << " times in all the news." << endl;                                                                                                      
      }else{
        //cout << word <<" not found." << endl;                                                                                                                                      
      }
    }

    MPI_Finalize();
}

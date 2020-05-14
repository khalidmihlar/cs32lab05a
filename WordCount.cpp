// WordCount.cpp

#include "WordCount.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int answer=0;
	for (size_t i=0; i<CAPACITY; i++){
		for (pair<string,int> p : table[i]){
			answer+=p.second;
		}
	}
	return answer;
}

int WordCount::getNumUniqueWords() const {
	int answer=0;
	for (size_t i=0; i<CAPACITY; i++){
		answer+=table[i].size();
	}
	return answer;
}

int WordCount::getWordCount(std::string word) const {
	string fun = makeValidWord(word);
	int key = hash(fun);
	for (size_t i=0; i<table[key].size(); i++){
		if (fun == table[key][i].first){
			return table[key][i].second;
		}
	}
	return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	string fun = makeValidWord(word);
	if (fun==""){
		return 0;
	}
	int key = hash(fun);
	for (size_t i=0; i<table[key].size(); i++){
		if (fun == table[key][i].first){
			table[key][i].second+=1;
			return table[key][i].second;
		}
	}
	table[key].push_back(pair<string,int>(fun, 1));
	return 1;
}

int WordCount::decrWordCount(std::string word) {
	string fun = makeValidWord(word);
	int key = hash(fun);
	for (size_t i=0; i<table[key].size(); i++){
		if (fun == table[key][i].first){
			table[key][i].second-=1;
			if (table[key][i].second==0){
				table[key].erase(table[key].begin() + i);
				return 0;
			}
			return table[key][i].second;
		}
	}
	return -1;
}

bool WordCount::isWordChar(char c) {
	if ((c<='z' && c>='a') || (c<='Z' && c>='A')){
		return true;
	}
	return false;
}

std::string WordCount::makeValidWord(std::string word) {
	string bruh;
	for (size_t i=0; i<word.length(); i++){
		if (isWordChar(word[i])){
			if (word[i]<='Z' && word[i]>='A'){
				bruh+=tolower(word[i]);
			}
			else{
				bruh+=word[i];
			}
		}
		else{
				if ((word[i] == '\'' || word[i]== '-') && isWordChar(word[i-1]) && isWordChar(word[i+1])){
					bruh+=word[i];
				}
			}
		}
	}
	return bruh;
}


void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	vector<pair<string,int>> temp;
	for (size_t i=0; i<CAPACITY; i++){
		for (size_t j=0; j<table[i].size(); j++){
			temp.push_back(table[i][j]);
		}
	}
	bool sort = false;
	vector<pair<string,int>> other;
	while (sort==false){
		sort = true;
		for (size_t i=0; i<temp.size()-1; i++){
			if (temp[i].first < temp[i+1].first){
				other.push_back(temp[i]);
				temp[i] = temp[i+1];
				temp[i+1] = other[0];
				other.pop_back();
				sort = false;
			}
		}
	}
	for (size_t i=0; i<temp.size(); i++){
		out<<temp[i].first<<","<<temp[i].second<<endl;
	}
	return;
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	vector<pair<string,int>> temp;
	for (size_t i=0; i<CAPACITY; i++){
		for (size_t j=0; j<table[i].size(); j++){
			temp.push_back(table[i][j]);
		}
	}
	bool sort = false;
	vector<pair<string,int>> other;
	while (sort==false){
		sort = true;
		for (size_t i=0; i<temp.size()-1; i++){
			if (temp[i].second > temp[i+1].second){
				other.push_back(temp[i]);
				temp[i] = temp[i+1];
				temp[i+1] = other[0];
				other.pop_back();
				sort = false;
			}
			else if (temp[i].second == temp[i+1].second){
				if (temp[i].first > temp[i+1].first){
					other.push_back(temp[i]);
					temp[i] = temp[i+1];
					temp[i+1] = other[0];
					other.pop_back();
					sort = false;
				}
			}
		}
	}
	for (size_t i=0; i<temp.size(); i++){
		out<<temp[i].first<<","<<temp[i].second<<endl;
	}
	return;
}

void WordCount::addAllWords(std::string text) {
	string bruh;
	for (size_t i=0; i<text.size(); i++){
		if ((text[i] == ' ' || text[i] == '\n' || text[i] == '\t') && bruh!=""){
			incrWordCount(bruh);
			bruh="";
		}
		else{
			bruh+=text[i];
		}
	}
	if (bruh!=""){
		incrWordCount(bruh);
	}
	return;
}

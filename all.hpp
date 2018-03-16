#include <iostream>
#include "sqlite3.h"
#include <vector>
#include <string>
struct Word{
	int id;
	std::string eng;
	std::string ru;
	std::string audio;
	std::string image;
};
std::vector<Word> getWord();

inline Word getBlockWord(){
	Word word={-1,"#","#","#","#"};
	return word;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "all.hpp"
using namespace std;

const int ROW_TABLE=40;
const int COL_TABLE=40;

enum __status__{freely,alone,block,wordHere};
enum _pos_{vertical,horizontal,zero};

class Cell{
public:
	explicit Cell(char value,__status__ status=freely,_pos_ pos=zero,char print='@',Word word={-1,"0","0","0","0"}):
			status_(status),
			value_(value),
			pos_(pos),
			print_(print),
			word_(word){}
	Cell():
			status_(freely),
			value_('0'),
			pos_(zero),
			print_('@'){}
	__status__ Status()const{return status_;}
	void setPrint(char x){print_=x;}
	char Print() const{return print_;}
	void setStatus(__status__ x){status_=x;}
	char Value() const{return value_;};
	void setValue(char x){value_=x;}
	_pos_ Pos()const{return pos_;}
	void setPos(_pos_ x){pos_=x;}
	friend ostream &operator<<(ostream&, const Cell&);
	void setRow(int x){row_=x;}
	void setCol(int x){col_=x;}
	int Row()const{return row_;}
	int Col()const{return col_;}
	Word getWord()const{return word_;}
private:
	int row_;
	int col_;
	char value_;
	char print_;
	__status__ status_;
	_pos_ pos_;
	Word word_;
};
ostream & operator<<(ostream &x,Cell const &cell){
	x<<cell.Value();
	return x;
}

Cell SetCell(char str,__status__ status,_pos_ pos,char print,Word word){
	Cell cell(str, status,pos,print,word);
	return cell;
}


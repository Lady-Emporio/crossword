#include "Cell.hpp"
// #include "all.hpp"
#include <ctime>	//time
#include <cstdlib>	//rand srand
#include <iomanip> //std::setw(3)
//SetCell(char str,__status__ status,_pos_ pos,char print)
Cell table[ROW_TABLE][COL_TABLE];
void PrintTable(int flag=0){
	for(int row=0;row!=ROW_TABLE;++row){
		for(int col=0;col!=COL_TABLE;++col){
			if(flag==1){
				char i=table[row][col].Value();
				if(i=='0'){ i=' ';}
				cout<<i<<" ";
			}
			else if(flag==2){
				char i=table[row][col].Value();
				if(i=='0' || i=='#'){ i=' ';}
				cout<<i<<" ";
			}
			else if(flag==3){
				char i=table[row][col].Print();
				cout<<i<<" ";
			}
			else if(flag==4){
				char i=table[row][col].Print();
				if(i=='*'){
					string i=to_string(table[row][col].getWord().id);
					cout<<std::setfill ('x')<<std::setw(3)<<i;
				}else{cout<<std::setfill (i)<<std::setw(3)<<i;}
			}
			else{cout<<table[row][col]<<" ";}
			
		}
		cout<<endl;
	}
}
//Проверка, поменяется ли эта позиция в таблицу (квадратная)
//Если за границу выходит, вернет истину.
bool NOTInTable(int x){
	if(x>=ROW_TABLE){return true;}//всего 40х40, он не может быть больше или равен 40.
	else if(x<0){return true;}
	else 		{return false;}
}
//Проверка на то, могу ли я запихнуть слово в таблицу.
//Позиция [row][col] первого элемента строки и саму строку.
//pos -проверка по вертикали или диагонали. То, как мы размещаем слово
bool CanISetWord(int row,int col,string word,_pos_ pos,int collaps=-1){
	if(NOTInTable(row)){return false;}
	if(NOTInTable(col)){return false;}
	if (pos==vertical){//horizontal vertical
		for(int i=-1;i!=word.size()+1;++i){
			if(NOTInTable(row+i)){return false;}
			Cell cell=table[row+i][col];
			if ((cell.Status()==block || cell.Status()==wordHere)&& i!=collaps){return false;}
		};
		return true;
	}else if(pos==horizontal){
		for(int i=-1;i!=word.size()+1;++i){
			if(NOTInTable(col+i)){return false;}
			Cell cell=table[row][col+i];
			if ((cell.Status()==block || cell.Status()==wordHere) && i!=collaps){return false;}
		};
		return true;
	}
}

void SetInTable(int row,int col,string word,_pos_ pos,Word ClassWord){
	if(pos==vertical){
		for(int i=0;i!=word.size();i++){
			if(i==0){table[row+i][col]=SetCell(word[i],wordHere,pos,'*',ClassWord);continue;}
			table[row+i][col]=SetCell(word[i],wordHere,pos,' ',ClassWord);
		}
	}
	else if(pos==horizontal){
		for(int i=0;i!=word.size();i++){
			if(i==0){table[row][col+i]=SetCell(word[i],wordHere,pos,'*',ClassWord); continue;}
			table[row][col+i]=SetCell(word[i],wordHere,pos,' ',ClassWord);
		}
	}
}

void SetBlock(int row, int col,string word,_pos_ pos){
	if(pos==horizontal){
		//Перед словом по вертикали
		if(NOTInTable(row)){return;}
		if(NOTInTable(col-1)){return;}
		table[row][col-1]=SetCell('#',block,zero,'#',getBlockWord());
		//за словом по вертикали
		if(NOTInTable(col+word.size())){return;}
		table[row][col+word.size()]=SetCell('#',block,zero,'#',getBlockWord());
	}else if(pos==vertical){
		//над словом
		if(NOTInTable(row-1)){return;}
		if(NOTInTable(col)){return;}
		table[row-1][col]=SetCell('#',block,zero,'#',getBlockWord());
		//под словом
		if(NOTInTable(row+word.size())){return;}
		table[row+word.size()][col]=SetCell('#',block,zero,'#',getBlockWord());
	}
}	

//Если ячейка граничит с 2+ буквами, ставлю в нее блок.
void IfNeedBlock(){
	for(int row=0;row!=ROW_TABLE;++row){
		for(int col=0;col!=COL_TABLE;++col){
			Cell *cell=&table[row][col];
			if(cell->Status()!=wordHere && cell->Status()!=block){
				int sum=0;
				if(!NOTInTable(col+1)){if(table[row][col+1].Status()==wordHere){sum+=1;}}
				if(!NOTInTable(col-1)){if(table[row][col-1].Status()==wordHere){sum+=1;}}
				if(!NOTInTable((row+1))){if(table[row+1][col].Status()==wordHere){sum+=1;}}
				if(!NOTInTable(row-1)){if(table[row-1][col].Status()==wordHere){sum+=1;}}
				if(sum>1){
					*cell=SetCell('#',block,zero,'#',getBlockWord());
				}
			}
		}
	}
}
//Беру слово и ищу куда его можно поместить. Если есть совпадающая буква, то смотрю, какая позиция у слова
//и проверяю, поместиться ли слово в противоположную позицию (ищу первый индекс.)
bool FindIndex(int *row,int *col,string word,_pos_ *pos,int *indexCollaps=0){
	for(int i_row=0;i_row!=ROW_TABLE;++i_row){
		for(int i_col=0;i_col!=COL_TABLE;++i_col){
			for(int i=0;i!=word.size();++i){
				if(table[i_row][i_col].Value()==word[i]){
					if(table[i_row][i_col].Pos()==horizontal){
						//ищу zero индекс по вертикали, так как слово по горизонтали
						int r,c;
						r=i_row-i;
						c=i_col;
						if(CanISetWord(r,c,word,vertical,i)){
							*row=r;
							*col=c;
							*pos=vertical;
// 							*indexCollaps=i;
// 							SetInTable(r,c,word,vertical);
							return true;
						}
					}
					else if(table[i_row][i_col].Pos()==vertical){
						//ищу zero индекс по горизонтали, так как слово по вертикали.
						int r,c;	
						r=i_row;
						c=i_col-i;
						if(CanISetWord(r,c,word,horizontal,i)){
							*row=r;
							*col=c;
							*pos=horizontal;
// 							*indexCollaps=i;
// 							SetInTable(r,c,word,vertical);
							return true;
						}
					}
				}
			};	
		};
	};
	return false;
}

int main(){
    vector<Word> ListWord=getWord();
	{//Region vector<string> ListWord
	if (ListWord.size()<=15){
		cout<<"Small size: "<<ListWord.size()<<endl;
		return 1;
	}
	sort(ListWord.begin(),ListWord.end(),[](Word x1,Word x2) {return (x1.eng<x2.eng);}); //убираю дубли
	auto last=unique(ListWord.begin(),ListWord.end(),[](Word x1,Word x2) {return (x1.eng==x2.eng);});
	ListWord.erase(last, ListWord.end());
	//сортирую по возрастанию размера строки
	sort(ListWord.begin(),ListWord.end(),[](Word x1,Word x2) {return (x1.eng.size()<x2.eng.size());});
	}//EndRegion vector<string> ListWord
	int xy[3]={-1,-1,-1};
	{//Десять последних самых больших слов рандомно сортируем.
	std::srand ( (int)time(0));
	random_shuffle ( ListWord.end()-11, ListWord.end(),[](int i) {return std::rand()%i;});
	}//Конец сортировки больших слов.
	/*Region вставляем первое слово по середине*/{
	Word fword=ListWord.back();
	string FirstWord=fword.eng;
	ListWord.pop_back();
	if(CanISetWord(ROW_TABLE/2,(COL_TABLE/2)-(FirstWord.size()/2),FirstWord,horizontal)){
		SetInTable(ROW_TABLE/2,(COL_TABLE/2)-(FirstWord.size()/2),FirstWord,horizontal,fword);
		SetBlock(ROW_TABLE/2, (COL_TABLE/2)-(FirstWord.size()/2),FirstWord,horizontal);
	}else{
		cout<<"Не хватило места для первого же слова."<<endl;
	}
	}//EndRegion закончили вставляь первое слово по середине.

	int row=-1,col=-1,indexCollaps=-1;_pos_ pos=zero;

	for(int i=ListWord.size()-1;/*i!=ListWord.size()-5*/ i!=0;--i){
		string word=ListWord[i].eng;
		if(FindIndex(&row,&col,word,&pos)){
			SetInTable(row,col,word,pos,ListWord[i]);
			SetBlock(row,col,word,pos);
			IfNeedBlock();
		}
	};
	//PrintTable();	//c нулями таблица
	// PrintTable(1);//с # таблица
	PrintTable(2);
	cout<<"\n\n\n";
	PrintTable(3);
	cout<<"\n\n\n";
	PrintTable(4);
	
	return 0;
}
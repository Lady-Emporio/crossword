#include "all.hpp"
using namespace std;
vector<Word> getWord(){
vector<Word> List_word;
sqlite3 *db;
sqlite3_stmt * pStmt;
if (sqlite3_open("./lingualeo.txt", &db)){
	cout<<"Error MyERROR: \n"<< sqlite3_errmsg(db)<<endl;
	sqlite3_close(db);
    return List_word;}
   
if (sqlite3_prepare(db, "SELECT * FROM 'MainTable';", -1, &pStmt, NULL)){
	cout<<"Error MyERROR: \n"<< sqlite3_errmsg(db)<<endl;
	sqlite3_finalize(pStmt);
	sqlite3_close(db);
    return List_word;}
   

while((sqlite3_step(pStmt)) == SQLITE_ROW){
    int coln = sqlite3_data_count(pStmt);
//     for(int j=0; j<coln; j++) {
//        cout<<sqlite3_column_text(pStmt, j)<<endl;
//     }
//     List_word.push_back(sqlite3_column_text(pStmt, 2));
    Word next;
    string id=reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 0));
    next.id=stoi(id);
    next.eng=reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 1));
    next.ru=reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 2));
    next.audio=reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 3));
    next.image=reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 4));
	List_word.push_back(next);
};
return List_word;
}
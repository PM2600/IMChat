// sqlite3Study.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "sqlite3.h"
#include "Sqlite.h"
#include <tchar.h>
#include <iostream>

const char* createtable = "CREATE TABLE Edy(ID INT PRIMARY KEY NOT NULL, NAME TEXT NOT NULL);";
const char* insert1 = "INSERT INTO Edy(ID, NAME) VALUES(1, \"hello\");";
const char* insert2 = "INSERT INTO Edy(ID, NAME) VALUES(2, \"world\");";
const char* query = "SELECT * FROM Edy;";
const char* droptable = "DROP TABLE Edy;";


int main()
{
    Sqlite sqlite(_T("test.db"));
    std::string msg;
    int ret = sqlite.Exec(createtable, msg);
    if (ret != 0) {
        std::cout << msg << std::endl;
        return -1;
    }

    ret = sqlite.Exec(insert1, msg);
    if (ret != 0) {
        std::cout << msg << std::endl;
        return -1;
    }

    ret = sqlite.Exec(insert2, msg);
    if (ret != 0) {
        std::cout << msg << std::endl;
        return -1;
    }
    std::vector<std::vector<std::string>> results;
    std::vector<std::string> cloumns;
    ret = sqlite.Query(query, results, cloumns, msg);
    if (ret != 0) {
        std::cout << msg << std::endl;
        return -1;
    }
    for (size_t i = 0; i < results.size(); i++) {
        for (size_t j = 0; j < results[i].size(); j++) {
            std::cout << cloumns[j] << " = " << results[i][j] << std::endl;
        }
    }
    ret = sqlite.Exec(droptable, msg);
    if (ret != 0) {
        std::cout << msg << std::endl;
        return -1;
    }
}


#ifndef PROJ4CLION_CSVREADER_H
#define PROJ4CLION_CSVREADER_H
#include <string>
#include <istream>
#include <string>
#include <vector>
#include <queue>
#include <csv.h>
#include <iostream>

class CCSVReader{
protected:
    std::istream &Input;
    struct csv_parser Parser;
    std::queue< std::vector <std::string> > BufferRows;
    std::vector<std::string> RowBuffer;
    static void CallBackFeild(void *str, size_t len, void *data);
    static void CallBackRow(int ch, void *data);
    bool reachedEnd;


public:
    CCSVReader(std::istream &in);
    ~CCSVReader();

    bool End() const;
    bool ReadRow(std::vector< std::string > &row);
};

#endif
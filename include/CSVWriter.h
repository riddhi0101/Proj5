#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <ostream>
#include <string>
#include <vector>


class CCSVWriter{
protected:
    std::ostream &Output;
    std::string Join(const std::string &str, const std::vector< std::string > &vect);


public:
    CCSVWriter(std::ostream &ou);
    ~CCSVWriter();
    bool WriteRow(const std::vector< std::string > &row);
};

#endif
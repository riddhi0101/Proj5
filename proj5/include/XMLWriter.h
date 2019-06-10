#ifndef XMLWRITER_H
#define XMLWRITER_H

#include "XMLEntity.h"
#include <stack>
#include <istream>
// anything in the character data or values in the attributes convert them to the escaped form- do it in the order of &,<, ",',>
// dont need to use libexpat
// just go have to through the attribute in order where provided in the entity
// input stream will look very sim to the output- except when you have a complete element it will get parsed as both the start and end element


class CXMLWriter{
    private:
        std::ostream &Output;
        std::stack <std::string> flushstack;

    public:
        CXMLWriter(std::ostream &os);
        ~CXMLWriter();
        
        bool Flush();
        bool WriteEntity(const SXMLEntity &entity);
};

#endif
                                      
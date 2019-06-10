#ifndef XMLREADER_H
#define XMLREADER_H

#include "XMLEntity.h"
#include <istream>
#include <expat.h>
#include <queue>

class CXMLReader{
    protected:
        std::istream &Input;
        XML_Char Character;
        XML_Parser Parser;
        std::queue< SXMLEntity > BufferedEntities;
        //std::vector< TAttributes > RowBuffer;

        static void StartElementcallback (void *data, const XML_Char *name, const XML_Char **attributes);
        static void EndElementcallback (void *data, const XML_Char *name);
        static void CharhandlerCallback (void *data, const XML_Char *s, int len);

public:
        CXMLReader(std::istream &is);
        ~CXMLReader();
        
        bool End();
        bool ReadEntity(SXMLEntity &entity, bool skipcdata = false);
};

#endif

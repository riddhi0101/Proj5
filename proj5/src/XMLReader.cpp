#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <expat.h>
#include "XMLReader.h"
#include "XMLEntity.h"

//constructor
CXMLReader::CXMLReader(std::istream &is) : Input(is){
    Parser = XML_ParserCreate(NULL);
    XML_SetUserData(Parser, this);
    XML_SetElementHandler(Parser, StartElementcallback, EndElementcallback);
    XML_SetCharacterDataHandler(Parser, CharhandlerCallback);
}
//destructor
CXMLReader::~CXMLReader(){
    XML_ParserFree(Parser);
}

//startcallback
void CXMLReader::StartElementcallback(void *data, const XML_Char *name, const XML_Char **attributes){
    CXMLReader *Ptr = static_cast<CXMLReader *>(data);
    SXMLEntity entity;
    entity.DType=SXMLEntity::EType::StartElement;
    entity.DNameData=std::string(name);
    for (int i=0; attributes[i]!= NULL; i+=2){
        entity.DAttributes.push_back(std::make_pair(std::string(attributes[i]),std::string(attributes[i+1])));
    }
    Ptr->BufferedEntities.push(entity);
    /*CCSVReader *Ptr = static_cast<CCSVReader*>(data);
    std::string *sPtr = static_cast<std::string*>(str);
    std::string stdStr = *sPtr;
    Ptr->RowBuffer.push_back(stdStr);*/
    //attributes: alist of string, string is eg. "student ID=916522643"
    //logic from TA office hour
    //entity.Dtype=startelement
    //name for entity is eg. course
    //forloop(attributes[Index],index+2){pushback attributes into the entity}
    //push back the whole entity into the queue
}

//endcallback
void CXMLReader::EndElementcallback(void *data, const XML_Char* name){
    CXMLReader *Ptr = static_cast<CXMLReader *>(data);
    SXMLEntity entity;
    entity.DType=SXMLEntity::EType::EndElement;
    entity.DNameData = std::string(name);

    Ptr->BufferedEntities.push(entity);
}

//contentcallback
void CXMLReader::CharhandlerCallback(void *data, const XML_Char *s, int len){//for contents
    CXMLReader *Ptr = static_cast<CXMLReader*>(data);
    SXMLEntity entity;
    entity.DType = SXMLEntity::EType::CharData;
    entity.DNameData = std::string(s,len);
    Ptr->BufferedEntities.push(entity);
    //entity
    //s:char ptr that points to the content
    //DNamedata=
    //for loop
    //pushback the whole entity into queue
}

//readentity
bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata){
    bool read;
    //from professor nitta

    while (!Input.eof() and BufferedEntities.empty()){
        char filebuffer [256];
        Input.read(filebuffer, 256);
        XML_Parse(Parser, filebuffer, Input.gcount(), Input.eof());
    }
    if (skipcdata==true){
        while (!BufferedEntities.empty() and BufferedEntities.front().DType == SXMLEntity::EType::CharData){
            BufferedEntities.pop();
        }
    }
    if (!BufferedEntities.empty()){
        entity = BufferedEntities.front();
        read=true;
    }
    else{
        read=false;
    }

    if (BufferedEntities.empty()){
        return false;
    }
    else{
        entity.DAttributes = BufferedEntities.front().DAttributes;
        entity.DType = BufferedEntities.front().DType;
        entity.DNameData = BufferedEntities.front().DNameData;
        BufferedEntities.pop();
        return true;
    }

    return read;
}

//end
bool CXMLReader::End(){
    bool ended = false;
    if (Input.eof() and BufferedEntities.empty()){
        ended = true;
    }
    else{
        ended = false;
    }
    return ended;
}
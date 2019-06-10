//
// Created by Dev Patel on 2019-05-22.
//

#include "XMLWriter.h"
#include "XMLEntity.h"
#include "CSVWriter.h"
#include "CSVReader.h"
#include "StringUtils.h"
#include <expat.h>

CXMLWriter::CXMLWriter(std::ostream &os) : Output(os) {

}


CXMLWriter::~CXMLWriter() {

}
bool CXMLWriter::Flush() {
    while (!flushstack.empty()){
        std::string name = flushstack.top();
        flushstack.pop();
        Output<< "</" + name + ">"<<std::endl;
    }


}

bool CXMLWriter::WriteEntity(const SXMLEntity &entity) {
    std::vector < std::pair< std::string, std::string > > outputform;
    outputform = entity.DAttributes;

    if (entity.DType == SXMLEntity::EType::StartElement){
        flushstack.push(entity.DNameData);
        /*for (int i =0; i<entity.DAttributes.length(); i++ ){
            outputform.push_back(entity.DAttributes[1])
        }*/
        for (int i =0; i<outputform.size(); i++ ){
            std::get<0>(outputform[i]) = StringUtils::Replace(std::get<0>(outputform[i]), "&", "&amp");
            std::get<1>(outputform[i]) = StringUtils::Replace(std::get<1>(outputform[i]), "&", "&amp");
            std::get<0>(outputform[i]) = StringUtils::Replace(std::get<0>(outputform[i]), "\"", "&quot");
            std::get<0>(outputform[i]) = StringUtils::Replace(std::get<0>(outputform[i]), "'", "&apos");
            std::get<0>(outputform[i]) = StringUtils::Replace(std::get<0>(outputform[i]), "<", "&lt");
            std::get<0>(outputform[i]) = StringUtils::Replace(std::get<0>(outputform[i]), ">", "&gt");
            std::get<1>(outputform[i]) = StringUtils::Replace(std::get<1>(outputform[i]), "\"", "&quot");
            std::get<1>(outputform[i]) = StringUtils::Replace(std::get<1>(outputform[i]), "'", "&apos");
            std::get<1>(outputform[i]) = StringUtils::Replace(std::get<1>(outputform[i]), "<", "&lt");
            std::get<1>(outputform[i]) = StringUtils::Replace(std::get<1>(outputform[i]), ">", "&gt");
        }
        Output<< "<" + entity.DNameData;
        for (auto ch: outputform){
            Output <<" " + std::get<0>(ch) + "=" + "\"" + std::get<1>(ch) + "\"";
        }
        Output<<">"<<std::endl;

    }
    else if (entity.DType == SXMLEntity::EType::CompleteElement ){
        for (int i =0; i<outputform.size(); i++ ){
            std::get<0>(outputform[i]) = StringUtils::Replace(std::get<0>(outputform[i]), "&", "&amp");
            std::get<1>(outputform[i]) = StringUtils::Replace(std::get<1>(outputform[i]), "&", "&amp");
            std::get<0>(outputform[i]) = StringUtils::Replace(std::get<0>(outputform[i]), "\"", "&quot");
            std::get<0>(outputform[i]) = StringUtils::Replace(std::get<0>(outputform[i]), "'", "&apos");
            std::get<0>(outputform[i]) = StringUtils::Replace(std::get<0>(outputform[i]), "<", "&lt");
            std::get<0>(outputform[i]) = StringUtils::Replace(std::get<0>(outputform[i]), ">", "&gt");
            std::get<1>(outputform[i]) = StringUtils::Replace(std::get<1>(outputform[i]), "\"", "&quot");
            std::get<1>(outputform[i]) = StringUtils::Replace(std::get<1>(outputform[i]), "'", "&apos");
            std::get<1>(outputform[i]) = StringUtils::Replace(std::get<1>(outputform[i]), "<", "&lt");
            std::get<1>(outputform[i]) = StringUtils::Replace(std::get<1>(outputform[i]), ">", "&gt");

        }
        Output<< "<" + entity.DNameData;
        for (auto ch: outputform){
            Output << " " + std::get<0>(ch) + "=" + "\"" + std::get<1>(ch) + "\"";//extraspace okay?
        }
        Output<<"/>"<<std::endl;

    }
    else if(entity.DType == SXMLEntity::EType::CharData){
        Output << "\"" + entity.DNameData + "\"" << std::endl;

    }
    else{
        if (!flushstack.empty()){
            flushstack.pop();
        }
        Output<< "</" + entity.DNameData + ">"<<std::endl;
    }

}
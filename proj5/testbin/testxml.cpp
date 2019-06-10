#include <gtest/gtest.h>
#include "CSVReader.h"
#include "XMLReader.h"
#include "XMLEntity.h"
#include "CSVWriter.h"
#include "XMLWriter.h"

TEST(XMLReader, StartElementTest){
std::stringstream input("<COURSE SUBJ=\"abc\" CRSE=\"x\" SEC=\"1\">");
std::ifstream fin("filename.xml");
CXMLReader Reader(input);
SXMLEntity Readrow;
Reader.ReadEntity(Readrow);

if (Reader.DAttribute.size() == 2){
    EXPECT_EQ(std::get<0>(Readrow.DAttributes[0]), "SUBJ");
    EXPECT_EQ(std::get<1>(Readrow.DAttributes[0]), "abc");
    EXPECT_EQ(std::get<0>(Readrow.DAttributes[1]), "CRSE");
    EXPECT_EQ(std::get<1>(Readrow.DAttributes[1]), "x");
    EXPECT_EQ(std::get<0>(Readrow.DAttributes[2]), "SEC");
    EXPECT_EQ(std::get<1>(Readrow.DAttributes[2]), "1");
}

    //EXPECT_EQ(Readrow.DNameData, "COURSE");
//how to check dtype

}

TEST(XMLReader, CompleteElementTest){
    std::stringstream("<STUDENT NAME=\"Alan\" VALUE=\"12\" COLOR=\"blue\" DATE=\"Sep. 25, 2009\" >");
    CXMLReader Reader;
    SXMLEntity Readrow;
    Reader.ReadEntity(Readrow);
    if (Reader.DAttribute.size() == 4){
        EXPECT_EQ(std::get<0>(Readrow.DAttributes[0]), "NAME");
        EXPECT_EQ(std::get<1>(Readrow.DAttributes[0]), "Alan");
        EXPECT_EQ(std::get<0>(Readrow.DAttributes[1]), "VALUE");
        EXPECT_EQ(std::get<1>(Readrow.DAttributes[1]), "12");
        EXPECT_EQ(std::get<0>(Readrow.DAttributes[2]), "COLOR");
        EXPECT_EQ(std::get<1>(Readrow.DAttributes[2]), "blue");
        EXPECT_EQ(std::get<0>(Readrow.DAttributes[3]), "DATE");
        EXPECT_EQ(std::get<1>(Readrow.DAttributes[3]), "Sep. 25, 2009");
    }
    EXPECT_EQ(Readrow.DNameData, "STUDENT");
// check dtype
    //SXMLEntity endrow;
    //Reader.ReadEntity(endrow);
    //EXCEPT_EQ(endrow.DNameData, "STUDENT");




}



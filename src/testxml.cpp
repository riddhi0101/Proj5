#include <gtest/gtest.h>
#include "CSVReader.h"
#include "XMLReader.h"
#include "XMLEntity.h"
#include "CSVWriter.h"
#include "XMLWriter.h"
#include <fstream>
#include <iostream>

TEST(XMLReader, StartElementTest){
    std::stringstream input("<COURSE SUBJ=\"abc\" CRSE=\"x\" SEC=\"1\">");
    CXMLReader Reader(input);
    SXMLEntity Readrow;
    Reader.ReadEntity(Readrow);
    if (Readrow.DAttributes.size() == 3){
        std::cout<<"in test"<<std::endl;
        EXPECT_EQ(std::get<0>(Readrow.DAttributes[0]), "SUBJ");
        EXPECT_EQ(std::get<1>(Readrow.DAttributes[0]), "abc");
        EXPECT_EQ(std::get<0>(Readrow.DAttributes[1]), "CRSE");
        EXPECT_EQ(std::get<1>(Readrow.DAttributes[1]), "x");
        EXPECT_EQ(std::get<0>(Readrow.DAttributes[2]), "SEC");
        EXPECT_EQ(std::get<1>(Readrow.DAttributes[2]), "1");
    }
    EXPECT_EQ(Readrow.DNameData, "COURSE");
    EXPECT_EQ(Readrow.DType, SXMLEntity::EType::StartElement);
    EXPECT_FALSE(Reader.ReadEntity(Readrow));
//how to check dtype

}

TEST(XMLReader, CompleteElementTest){
    std::stringstream input("<STUDENT NAME=\"Alan\" VALUE=\"12\" COLOR=\"blue\" DATE=\"Sep. 25, 2009\" >");
    CXMLReader Reader(input);
    SXMLEntity Readrow;
    EXPECT_TRUE(Reader.ReadEntity(Readrow));
    if (Readrow.DAttributes.size() == 4){
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
    EXPECT_EQ(Readrow.DType, SXMLEntity::EType::StartElement);
// check dtype
    //SXMLEntity endrow;
    //Reader.ReadEntity(endrow);
    //EXCEPT_EQ(endrow.DNameData, "STUDENT");

}

TEST(XMLReader, MultipleEntities){
    std::stringstream Readfile("<COURSE SUBJ=\"ABC\" CRSE=\"114\" SEC=\"2\">"
                                   "<STUDENT SEAT=\"1\" SID=\"900667130\" SURNAME=\"Stein\" PREFNAME=\"Ava\" LEVEL=\"UG\" UNITS=\"2\" CLASS=\"FR\" MAJOR=\"DEF2\" GRADE=\"I\" STATUS=\"RE\" EMAIL=\"ava.s.stein@fakeu.edu\"/>"
                               "</COURSE>");
    CXMLReader Reader(Readfile);
    SXMLEntity Entity;
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.DNameData, "COURSE");
    EXPECT_EQ(std::get<0>(Entity.DAttributes[0]), "SUBJ");
    EXPECT_EQ(std::get<1>(Entity.DAttributes[0]), "ABC");
    EXPECT_EQ(std::get<0>(Entity.DAttributes[1]), "CRSE");
    EXPECT_EQ(std::get<1>(Entity.DAttributes[1]), "114");
    EXPECT_EQ(std::get<0>(Entity.DAttributes[2]), "SEC");
    EXPECT_EQ(std::get<1>(Entity.DAttributes[2]), "2");
    SXMLEntity Entity1;
    EXPECT_TRUE(Reader.ReadEntity(Entity1));
    EXPECT_EQ(Entity1.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity1.DNameData, "STUDENT");
    EXPECT_EQ(std::get<0>(Entity1.DAttributes[0]), "SEAT");
    EXPECT_EQ(std::get<1>(Entity1.DAttributes[0]), "1");
    EXPECT_EQ(std::get<0>(Entity1.DAttributes[1]), "SID");
    EXPECT_EQ(std::get<1>(Entity1.DAttributes[1]), "900667130");
    EXPECT_EQ(std::get<0>(Entity1.DAttributes[2]), "SURNAME");
    EXPECT_EQ(std::get<1>(Entity1.DAttributes[2]), "Stein");
    EXPECT_EQ(std::get<0>(Entity1.DAttributes[3]), "PREFNAME");
    EXPECT_EQ(std::get<1>(Entity1.DAttributes[3]), "Ava");
}

TEST(XMLReader, EndElementTest){
    std::stringstream input("<COURSE NAME=\"dev\">"
                            "</COURSE>");
    CXMLReader Reader(input);
    SXMLEntity Readrow;
    EXPECT_TRUE(Reader.ReadEntity(Readrow,true));
    EXPECT_EQ(Readrow.DNameData, "COURSE");
    EXPECT_EQ(Readrow.DType, SXMLEntity::EType::StartElement);
    SXMLEntity reade;
    EXPECT_TRUE(Reader.ReadEntity(reade,true));
    EXPECT_EQ(reade.DType, SXMLEntity::EType::EndElement);


}
TEST(XMLReader, Chardata){
    std::stringstream input("<COURSE NAME=\"dev\">"
                            "some stuff\n"
                            "<COURSE NAME=\"dev\">");
    CXMLReader Reader(input);
    SXMLEntity Readrow;
    Reader.ReadEntity(Readrow);
    EXPECT_TRUE(Reader.ReadEntity(Readrow));
    EXPECT_EQ(Readrow.DType, SXMLEntity::EType::CharData);
    EXPECT_EQ(Readrow.DNameData, "some stuff");
}

/*

TEST(XMLWriter, CompleteElement){
    SXMLEntity Writerow;
    Writerow.DType = SXMLEntity::EType::CompleteElement;
    Writerow.DAttributes.push_back(std::make_pair("CLASS","ECS34"));
    Writerow.DAttributes.push_back(std::make_pair("LEVEL","UG"));
    Writerow.DNameData = "COURSE";
    std::stringstream output;
    CXMLWriter Writer(output);
    EXPECT_TRUE(Writer.WriteEntity(Writerow));
    EXPECT_EQ(output.str(), "<COURSE CLASS=\"ECS34\" LEVEL=\"UG\"/>\n");

}

TEST(XMLWriter, StartElement){
    SXMLEntity Writerow;
    Writerow.DType = SXMLEntity::EType::StartElement;
    Writerow.DAttributes.push_back(std::make_pair("CLASS","ECS34"));
    Writerow.DAttributes.push_back(std::make_pair("LEVEL","UG"));
    Writerow.DNameData = "COURSE";
    std::stringstream output;
    CXMLWriter Writer(output);
    EXPECT_TRUE(Writer.WriteEntity(Writerow));
    EXPECT_EQ(output.str(), "<COURSE CLASS=\"ECS34\" LEVEL=\"UG\">\n");

}
TEST(XMLWriter, EndElement){
    SXMLEntity Writerow;
    Writerow.DType = SXMLEntity::EType::EndElement;
    Writerow.DNameData = "COURSE";
    std::stringstream output;
    CXMLWriter Writer(output);
    EXPECT_TRUE(Writer.WriteEntity(Writerow));
    EXPECT_EQ(output.str(), "</COURSE>\n");


}

TEST(XMLWriter, Flushing){
    SXMLEntity Writerow;
    Writerow.DType = SXMLEntity::EType::StartElement;
    Writerow.DAttributes.push_back(std::make_pair("CLASS","ECS34"));
    Writerow.DAttributes.push_back(std::make_pair("LEVEL","UG"));
    Writerow.DNameData = "COURSE";
    std::stringstream output;
    CXMLWriter Writer(output);
    EXPECT_TRUE(Writer.WriteEntity(Writerow));
    Writer.Flush();
    EXPECT_EQ(output.str(), "<COURSE CLASS=\"ECS34\" LEVEL=\"UG\">\n"
                            "</COURSE>\n");

}
TEST(XMLReader, Replace_check){
    SXMLEntity Writerow;
    Writerow.DType = SXMLEntity::EType::StartElement;
    Writerow.DAttributes.push_back(std::make_pair("CL<A&SS","E>\"CS34"));
    Writerow.DAttributes.push_back(std::make_pair("LE&<VEL","U>G"));
    Writerow.DNameData = "COURSE";
    std::stringstream output;
    CXMLWriter Writer(output);
    EXPECT_TRUE(Writer.WriteEntity(Writerow));
    EXPECT_EQ(output.str(), "<COURSE CL&ltA&ampSS=\"E&gt&quotCS34\" LE&amp&ltVEL=\"U&gtG\">\n");
}

TEST(XMLReader, Filereader){
    std::ofstream Readfile1("ABC_114_2.xml");
    Readfile1<< "<course SUBJ=\"ABC\" CRSE=\"114\" SEC=\"2\">"
                   "<student SEAT=\"1\" SID=\"900667130\" SURNAME=\"Stein\" PREFNAME=\"Ava\" LEVEL=\"UG\" UNITS=\"2\"/>"
               "</course>"<<std::endl;
    std::ifstream Readfile("ABC_114_2.xml");
    CXMLReader Reader(Readfile);
    SXMLEntity Entity;
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.DNameData, "course");
    EXPECT_EQ(std::get<0>(Entity.DAttributes[0]), "SUBJ");
    EXPECT_EQ(std::get<1>(Entity.DAttributes[0]), "ABC");
    EXPECT_EQ(std::get<0>(Entity.DAttributes[1]), "CRSE");
    EXPECT_EQ(std::get<1>(Entity.DAttributes[1]), "114");
    EXPECT_EQ(std::get<0>(Entity.DAttributes[2]), "SEC");
    EXPECT_EQ(std::get<1>(Entity.DAttributes[2]), "2");
    SXMLEntity Entity1;
    EXPECT_TRUE(Reader.ReadEntity(Entity1));
    EXPECT_EQ(Entity1.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity1.DNameData, "student");
    EXPECT_EQ(std::get<0>(Entity1.DAttributes[0]), "SEAT");
    EXPECT_EQ(std::get<1>(Entity1.DAttributes[0]), "1");
    EXPECT_EQ(std::get<0>(Entity1.DAttributes[1]), "SID");
    EXPECT_EQ(std::get<1>(Entity1.DAttributes[1]), "900667130");
    EXPECT_EQ(std::get<0>(Entity1.DAttributes[2]), "SURNAME");
    EXPECT_EQ(std::get<1>(Entity1.DAttributes[2]), "Stein");
    EXPECT_EQ(std::get<0>(Entity1.DAttributes[3]), "PREFNAME");
    EXPECT_EQ(std::get<1>(Entity1.DAttributes[3]), "Ava");

}
 */







#include <gtest/gtest.h>
#include "CSVReader.h"
#include "XMLReader.h"
#include "XMLEntity.h"
#include "CSVWriter.h"
#include "XMLWriter.h"
#include <fstream>
#include <iostream>


TEST(CSVReader, BasicTest){
    std::stringstream Input(" 1,2 ,  3         ,4,5\x0d\x0a");
    CCSVReader Reader(Input);
    std::vector <std::string> Row;

    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(),5);

    EXPECT_EQ(Row[0], "1");
    EXPECT_EQ(Row[1], "2");
    EXPECT_EQ(Row[2], "3");
    EXPECT_EQ(Row[3], "4");
    EXPECT_EQ(Row[4], "5");

    //EXPECT_FALSE(Reader.ReadRow(Row));

}

TEST(CSVReader, EmptyTest){
    std::stringstream Input(",,,,,\x0a");
    CCSVReader Reader(Input);
    std::vector <std::string> Row;
    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(),6);

    EXPECT_EQ(Row[0], "");
    EXPECT_EQ(Row[1], "");
    EXPECT_EQ(Row[2], "");
    EXPECT_EQ(Row[3], "");
    EXPECT_EQ(Row[4], "");

    //EXPECT_FALSE(Reader.ReadRow(Row));
}
TEST(CSVReader, QuoteTest){
    std::stringstream Input("\",\",\",\",\"\"\n");
    CCSVReader Reader(Input);
    std::vector <std::string> Row;
    std::cout << "hello1"<<std::endl;
    EXPECT_TRUE(Reader.ReadRow(Row));
    std::cout << "hello2"<<std::endl;
    EXPECT_EQ(Row.size(),3);
    std::cout << "hello3"<<std::endl;
    if (Row.size() >= 3){
        std::cout << "hello"<<std::endl;
        EXPECT_EQ(Row[0], ",");
        EXPECT_EQ(Row[1], ",");
        EXPECT_EQ(Row[2], "");

    }
    //EXPECT_FALSE(Reader.ReadRow(Row));
}
TEST(CSVReader, WordsTest){
    std::stringstream Input( "I call our world Flatland,\x0a"
                             "not because we call it so,\x0a"
                             "but to make its nature clearer\x0a"
                             "to you, my happy readers\x0a"
                             "who are privileged to live in Space.");
    CCSVReader Reader(Input);
    std::vector <std::string> Row;

    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(),2);
    if (Row.size() >= 1){
        EXPECT_EQ(Row[0], "I call our world Flatland");
    }
    EXPECT_TRUE(Reader.ReadRow(Row));
    if (Row.size() >= 1){
        EXPECT_EQ(Row[0], "not because we call it so");
    }
    EXPECT_TRUE(Reader.ReadRow(Row));
    if (Row.size() >= 1){
        EXPECT_EQ(Row[0], "but to make its nature clearer");
    }
    EXPECT_TRUE(Reader.ReadRow(Row));
    if (Row.size() >= 1){
        EXPECT_EQ(Row[0], "to you");
        EXPECT_EQ(Row[1], "my happy readers");
    }
    EXPECT_TRUE(Reader.ReadRow(Row));
    if (Row.size() >= 1){
        EXPECT_EQ(Row[0], "who are privileged to live in Space.");
    }

    //EXPECT_FALSE(Reader.ReadRow(Row));
}

TEST(CSVWriter, Writer_BasicTest){
    std::stringstream Output;
    CCSVWriter Writer(Output);
    std::vector< std::string > Row{"1","2","3","4","5"};

    EXPECT_TRUE(Writer.WriteRow(Row));
    EXPECT_EQ(Output.str(),"\"1\",\"2\",\"3\",\"4\",\"5\"\n");
}

TEST(CSVWriter, Writer_EmptyTest){
    std::stringstream Output;
    CCSVWriter Writer(Output);
    std::vector< std::string > Row{"","","","",""};

    EXPECT_TRUE(Writer.WriteRow(Row));
    EXPECT_EQ(Output.str(),"\"\",\"\",\"\",\"\",\"\"\n");
}
TEST(CSVWriter, Writer_QuoteTest){
    std::stringstream Output;
    CCSVWriter Writer(Output);
    std::vector< std::string > Row{"\"","\"","\"","\"","\""};

    EXPECT_TRUE(Writer.WriteRow(Row));
    EXPECT_EQ(Output.str(),"\"\"\"\",\"\"\"\",\"\"\"\",\"\"\"\",\"\"\"\"\n");
}

TEST(CSVWriter, Writer_WordTest){
    std::stringstream Output;
    CCSVWriter Writer(Output);
    std::vector< std::string > Row{"I call our world Flatland","not because we call it so","but to make its nature clearer","to you, my happy readers","who are privileged to live in Space."};

    EXPECT_TRUE(Writer.WriteRow(Row));
    EXPECT_EQ(Output.str(),"\"I call our world Flatland\",\"not because we call it so\",\"but to make its nature clearer\",\"to you, my happy readers\",\"who are privileged to live in Space.\"\n");
}

TEST(CSVReader, Filereader_CSV){
    std::ofstream Readfile1("ABC_114_2.csv");
    Readfile1<< "\"SEAT\",\"SID\",\"SURNAME\",\"PREFNAME\",\"LEVEL\",\"UNITS\",\"CLASS\",\"MAJOR\",\"GRADE\",\"STATUS\",\"EMAIL\"\n"
                "\"1\",\"900667130\",\"Stein\",\"Ava\",\"UG\",\"2\",\"FR\",\"DEF2\",\"I\",\"RE\",\"ava.s.stein@fakeu.edu\"\n"<<std::endl;
    std::ifstream Readfile("ABC_114_2.csv");
    CCSVReader Reader(Readfile);
    std::vector<std::string> Row;
    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(),11);
    EXPECT_EQ(Row[0], "SEAT");
    EXPECT_EQ(Row[1], "SID");
    EXPECT_EQ(Row[2], "SURNAME");
    EXPECT_EQ(Row[3], "PREFNAME");
    EXPECT_EQ(Row[4], "LEVEL");
    EXPECT_EQ(Row[5], "UNITS");
    EXPECT_EQ(Row[6], "CLASS");
    EXPECT_EQ(Row[7], "MAJOR");
    EXPECT_EQ(Row[8], "GRADE");
    EXPECT_EQ(Row[9], "STATUS");
    EXPECT_EQ(Row[10], "EMAIL");

    std::vector<std::string> row;
    EXPECT_TRUE(Reader.ReadRow(row));
    EXPECT_EQ(row.size(),11);
    EXPECT_EQ(row[0], "1");
    EXPECT_EQ(row[1], "900667130");
    EXPECT_EQ(row[2], "Stein");
    EXPECT_EQ(row[3], "Ava");
    EXPECT_EQ(row[4], "UG");
    EXPECT_EQ(row[5], "2");
    EXPECT_EQ(row[6], "FR");
    EXPECT_EQ(row[7], "DEF2");
    EXPECT_EQ(row[8], "I");
    EXPECT_EQ(row[9], "RE");
    EXPECT_EQ(row[10], "ava.s.stein@fakeu.edu");

}

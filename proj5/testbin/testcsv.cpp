#include <gtest/gtest.h>
#include "CSVReader.h"
#include "XMLReader.h"
#include "XMLEntity.h"
#include "CSVWriter.h"
#include "XMLWriter.h"
TEST(CSVReader, BasicTest){
    std::stringstream Input(" 1,2 ,  3         ,4,5\x0d\x0a");
    CCSVReader Reader(Input);
    std::vector <std::string> Row;

    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(),5);
    if (Row.size() >= 5){
        EXPECT_EQ(Row[0], "1");
        EXPECT_EQ(Row[1], "2");
        EXPECT_EQ(Row[2], "3");
        EXPECT_EQ(Row[3], "4");
        EXPECT_EQ(Row[4], "5");
    }
    //EXPECT_FALSE(Reader.ReadRow(Row));

}

TEST(CSVReader, EmptyTest){
    std::stringstream Input(",,,,,\x0a");
    CCSVReader Reader(Input);
    std::vector <std::string> Row;
    EXPECT_TRUE(Reader.ReadRow(Row));
    EXPECT_EQ(Row.size(),6);
    if (Row.size() >= 6){
        EXPECT_EQ(Row[0], "");
        EXPECT_EQ(Row[1], "");
        EXPECT_EQ(Row[2], "");
        EXPECT_EQ(Row[3], "");
        EXPECT_EQ(Row[4], "");
    }
    //EXPECT_FALSE(Reader.ReadRow(Row));
}
TEST(CSVReader, QuoteTest){
    std::stringstream Input("\",\",\",\",\"\"\n");
    CCSVReader Reader(Input);
    std::vector <std::string> Row;
    std::cout << "hello1"<<std::endl;
    EXPECT_TRUE(Reader.ReadRow(Row));
    std::cout << "hello2"<<std::endl;
    EXPECT_EQ(Row.size(),5);
    std::cout << "hello3"<<std::endl;
    if (Row.size() >= 5){
        std::cout << "hello"<<std::endl;
        EXPECT_EQ(Row[0], "\"\"");
        EXPECT_EQ(Row[1], "\"\"");
        EXPECT_EQ(Row[2], "\"\"");
        EXPECT_EQ(Row[3], "\"\"");
        EXPECT_EQ(Row[4], "\"\"");
    }
    //EXPECT_FALSE(Reader.ReadRow(Row));
}
TEST(CSVReader, WordsTest){
    std::stringstream Input( "I call our world Flatland,\x0a"
                             "not because we call it so,\x0a"
                             "but to make its nature clearer\x0a"
                             "to you, my happy readers,\x0a"
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



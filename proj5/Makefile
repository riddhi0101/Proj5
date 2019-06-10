CXX = g++
  
CURDIR =$(shell pwd)
LIBDIR = ./lib
OBJDIR = ./obj
BINDIR = ./bin
INCLUDEDIR = ./include
SRCDIR = ./src
LIBCSVDIR = libcsv-3.0.3
LIBCSV_NAME = libcsv.a
TESTBIN = ./testbin
INCLUDE = -I $(INCLUDEDIR) -I /opt/local/include
CXXFLAGS = -std=c++14 $(INCLUDE)

TESTLDFLAGS = -L /opt/local/lib -lgtest_main -lgtest -lpthread -lexpat

CSV_READER_OBJ = $(OBJDIR)/CSVReader.o
CSV_WRITER_OBJ = $(OBJDIR)/CSVWriter.o
XML_WRITER_OBJ = $(OBJDIR)/XMLWriter.o
XML_ENTITY_OBJ = $(OBJDIR)/XMLEntity.o
XML_READER_OBJ = $(OBJDIR)/XMLReader.o
CSV_TEST_OBJ = $(OBJDIR)/testcsv.o
XML_TEST_OBJ = $(OBJDIR)/testxml.o
MAP_TEST_OBJ = $(OBJDIR)/testrouter.o
MAPROUTE_OBJ = $(OBJDIR)/MapRouter.o
STRING_UTILS_OBJ = $(OBJDIR)/StringUtils.o
MAIN_OBJ = $(OBJDIR)/main.o

FINDROUTE_OBJS = $(CSV_READER_OBJ) $(MAPROUTE_OBJ) $(XML_READER_OBJ) $(STRING_UTILS_OBJ)

CSV_TEST_NAME = testcsv
XML_TEST_NAME = testxml
MAP_TEST_NAME = testrouter


all: $(LIBDIR)/$(LIBCSV_NAME) directories runmaprouter bin.findroute


runtest: $(TESTBIN)/$(CSV_TEST_NAME)
	$(TESTBIN)/$(CSV_TEST_NAME)

runtestxml: $(TESTBIN)/$(XML_TEST_NAME)
	$(TESTBIN)/$(XML_TEST_NAME)

runmaprouter: $(TESTBIN)/$(MAP_TEST_NAME)
	$(TESTBIN)/$(MAP_TEST_NAME)

bin.findroute: bin/findroute
	bin/findroute

bin/findroute: $(MAIN_OBJ) $(MAPROUTE_OBJ) $(STRING_UTILS_OBJ) $(CSV_READER_OBJ) $(XML_READER_OBJ) $(LIBDIR)/$(LIBCSV_NAME) 
	$(CXX) -std=c++14 $(MAIN_OBJ) $(MAPROUTE_OBJ) $(STRING_UTILS_OBJ) $(CSV_READER_OBJ) $(XML_READER_OBJ) $(LIBDIR)/$(LIBCSV_NAME) $(CXXFLAGS) $(TESTLDFLAGS) -lexpat -o bin/findroute



$(MAIN_OBJ): $(SRCDIR)/main.cpp $(INCLUDEDIR)/MapRouter.h $(INCLUDEDIR)/CSVReader.h $(INCLUDEDIR)/StringUtils.h $(INCLUDEDIR)/XMLReader.h $(LIBDIR)/$(LIBCSV_NAME) 
	$(CXX) $(SRCDIR)/main.cpp -c $(CXXFLAGS) -o $(MAIN_OBJ)


$(STRING_UTILS_OBJ): $(SRCDIR)/StringUtils.cpp $(INCLUDEDIR)/StringUtils.h
	$(CXX) $(SRCDIR)/StringUtils.cpp -c $(CXXFLAGS) -o $(STRING_UTILS_OBJ)

$(CSV_READER_OBJ): $(SRCDIR)/CSVReader.cpp $(INCLUDEDIR)/CSVReader.h $(INCLUDEDIR)/StringUtils.h $(SRCDIR)/StringUtils.cpp  $(LIBDIR)/$(LIBCSV_NAME)
	$(CXX) $(SRCDIR)/CSVReader.cpp -c $(CXXFLAGS) -o $(CSV_READER_OBJ)

$(CSV_WRITER_OBJ): $(SRCDIR)/CSVWriter.cpp $(INCLUDEDIR)/CSVWriter.h $(INCLUDEDIR)/StringUtils.h $(SRCDIR)/StringUtils.cpp  $(LIBDIR)/$(LIBCSV_NAME)
	$(CXX) $(SRCDIR)/CSVWriter.cpp -c $(CXXFLAGS) -o $(CSV_WRITER_OBJ)

$(XML_READER_OBJ): $(SRCDIR)/XMLReader.cpp $(INCLUDEDIR)/XMLReader.h $(INCLUDEDIR)/XMLEntity.h $(INCLUDEDIR)/StringUtils.h $(SRCDIR)/StringUtils.cpp 
	$(CXX) $(SRCDIR)/XMLReader.cpp -c $(CXXFLAGS) -o $(XML_READER_OBJ)

$(XML_WRITER_OBJ): $(SRCDIR)/XMLWriter.cpp $(INCLUDEDIR)/XMLWriter.h $(INCLUDEDIR)/XMLEntity.h $(INCLUDEDIR)/StringUtils.h $(SRCDIR)/StringUtils.cpp
	$(CXX) $(SRCDIR)/XMLWriter.cpp -c $(CXXFLAGS) -o $(XML_WRITER_OBJ)

$(CSV_TEST_OBJ): $(SRCDIR)/testcsv.cpp $(INCLUDEDIR)/CSVReader.h $(INCLUDEDIR)/CSVWriter.h $(INCLUDEDIR)/StringUtils.h
	$(CXX) $(SRCDIR)/testcsv.cpp -c $(CXXFLAGS) -o $(CSV_TEST_OBJ)

$(XML_TEST_OBJ): $(SRCDIR)/testxml.cpp $(INCLUDEDIR)/XMLReader.h $(INCLUDEDIR)/XMLWriter.h $(INCLUDEDIR)/XMLEntity.h $(INCLUDEDIR)/StringUtils.h
	$(CXX) $(SRCDIR)/testxml.cpp -c $(CXXFLAGS) -o $(XML_TEST_OBJ)


$(TESTBIN)/$(CSV_TEST_NAME): $(CSV_READER_OBJ) $(STRING_UTILS_OBJ) $(CSV_WRITER_OBJ) $(CSV_TEST_OBJ) $(LIBDIR)/$(LIBCSV_NAME)
	$(CXX) $(CSV_READER_OBJ) $(CSV_WRITER_OBJ) $(STRING_UTILS_OBJ) $(CSV_TEST_OBJ) $(LIBDIR)/$(LIBCSV_NAME) $(CXXFLAGS) $(TESTLDFLAGS) -o $(TESTBIN)/$(CSV_TEST_NAME)

$(TESTBIN)/$(XML_TEST_NAME): $(XML_READER_OBJ) $(STRING_UTILS_OBJ) $(XML_WRITER_OBJ) $(XML_TEST_OBJ) $(LIBDIR)/$(LIBCSV_NAME)
	$(CXX) $(XML_READER_OBJ) $(XML_WRITER_OBJ) $(STRING_UTILS_OBJ) $(XML_TEST_OBJ) $(LIBDIR)/$(LIBCSV_NAME) $(CXXFLAGS) $(TESTLDFLAGS) -o $(TESTBIN)/$(XML_TEST_NAME)


$(MAPROUTE_OBJ): $(SRCDIR)/MapRouter.cpp $(INCLUDEDIR)/MapRouter.h $(SRCDIR)/CSVReader.cpp $(SRCDIR)/StringUtils.cpp $(SRCDIR)/CSVWriter.cpp $(SRCDIR)/XMLReader.cpp $(SRCDIR)/XMLWriter.cpp $(LIBDIR)/$(LIBCSV_NAME) 
	$(CXX) $(SRCDIR)/MapRouter.cpp -c $(CXXFLAGS) -o $(MAPROUTE_OBJ)


$(MAP_TEST_OBJ): $(SRCDIR)/testrouter.cpp $(INCLUDEDIR)/MapRouter.h $(INCLUDEDIR)/CSVReader.h $(INCLUDEDIR)/StringUtils.h $(INCLUDEDIR)/CSVWriter.h $(INCLUDEDIR)/XMLReader.h $(INCLUDEDIR)/XMLWriter.h $(LIBDIR)/$(LIBCSV_NAME) 
	$(CXX) $(SRCDIR)/testrouter.cpp -c $(CXXFLAGS) -o $(MAP_TEST_OBJ)


$(TESTBIN)/$(MAP_TEST_NAME): $(MAPROUTE_OBJ) $(MAP_TEST_OBJ) $(CSV_READER_OBJ) $(CSV_WRITER_OBJ) $(XML_READER_OBJ) $(STRING_UTILS_OBJ) $(XML_WRITER_OBJ) $(LIBDIR)/$(LIBCSV_NAME)
	$(CXX) $(MAPROUTE_OBJ) $(MAP_TEST_OBJ) $(CSV_READER_OBJ) $(CSV_WRITER_OBJ) $(XML_READER_OBJ) $(STRING_UTILS_OBJ) $(XML_WRITER_OBJ) $(LIBDIR)/$(LIBCSV_NAME) $(CXXFLAGS) $(TESTLDFLAGS) -o $(TESTBIN)/$(MAP_TEST_NAME)



$(LIBCSVDIR)/Makefile:
	cd $(LIBCSVDIR); ./configure --prefix=$(CURDIR); cd ..

$(LIBCSVDIR)/libcsv.la: $(LIBCSVDIR)/Makefile
	cd $(LIBCSVDIR); make; cd ..

$(LIBDIR)/$(LIBCSV_NAME): $(LIBCSVDIR)/libcsv.la
	cd $(LIBCSVDIR); make install; cd ..

directories: $(BINDIR) $(TESTBIN) $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(TESTBIN):
	mkdir -p $(TESTBIN)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f lib/*
	rm -f include/csv.h
	cd $(LIBCSVDIR);  make clean; cd ..
	rm -f $(LIBCSVDIR)/Makefile

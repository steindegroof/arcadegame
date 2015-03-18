#--- the location of the test includes; YOU MIGHT NEED TO MODIFY THESE
INCL =		gtest-1.7.0/include
#--- the location of the test libraries; YOU MIGHT NEED TO MODIFY THESE
TLIBPATH =	-Lgtest-1.7.0/lib
TLIBS =		-lgtest -lgtest_main

GTEST_DIR = gtest-1.7.0
# All Google Test headers.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h



CXXFLAGS =	-g -Wall -fmessage-length=0 -fomit-frame-pointer -pipe -std=c++11 -I$(INCL) 
CPPFLAGS += -MD -MP 
CPPFLAGS += -isystem $(GTEST_DIR)/include

OBJS =		parsers/AbstractParser.o parsers/FieldParser.o parsers/MovesParser.o tinyxml/tinyxml.o tinyxml/tinystr.o tinyxml/tinyxmlerror.o tinyxml/tinyxmlparser.o arcade.o
TESTOBJS = 	arcadetests.o
SRCS =		arcademain.cpp #arcadetests.cpp
TARGET =	arcademain arcadetests

#--- primary target
.PHONY : all
all : $(TARGET)


# Builds gtest.a and gtest_main.a. 
 
# Usually you shouldn't tweak such internal variables, indicated by a 
# trailing _. 
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS) 
 
# For simplicity and to avoid depending on Google Test's 
# implementation details, the dependencies specified below are 
# conservative and not optimized.  This is fine as Google Test 
# compiles fast and for ordinary users its source rarely changes. 
gtest-all.o : $(GTEST_SRCS_) 
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc 
 
gtest_main.o : $(GTEST_SRCS_) 
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc 
 
gtest.a : gtest-all.o 
	$(AR) $(ARFLAGS) $@ $^ 
 
gtest_main.a : gtest-all.o gtest_main.o 
	$(AR) $(ARFLAGS) $@ $^ 



#--- compiler targets
arcademain : $(OBJS) arcademain.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
#-lpthread
arcadetests : $(OBJS) $(TESTOBJS) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ -lpthread

arcadetests.o : arcadetests.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c arcadetests.cpp

%.o : %.cpp %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<



#--- non-file targets
.PHONY : clean
clean :
	rm -f *.o $(TARGET)
	rm -f testOutput/file*.txt testOutput/happyDayOut.txt  testOutput/noWinnerOut.txt
	rm -f tinyxml/*.o parser/*.o

.PHONY : cleantests
cleantests :
	rm -f testOutput/file*.txt testOutput/happyDayOut.txt

.PHONY : depend
depend :
	g++ -MM -I $(INCL) $(SRCS)

.PHONY : echo
echo :
	@echo CXXFLAGS = $(CXXFLAGS)
	@echo CXX = $(CXX)
	@echo LDFLAGS = $(LDFLAGS)
	@echo INCL = $(INCL)
	@echo TLIBPATH = $(TLIBPATH)
	@echo TLIBS = $(TLIBS)


.PHONY : sourcestar
sourcestar :
	tar -cvf TicTacToe.tar *.h *.cpp Makefile testOutput
	
.PHONY : sourceszip
sourceszip :
	zip -q -r TicTacToe.zip *.h *.cpp Makefile testOutput
#--zip quietly and recursively


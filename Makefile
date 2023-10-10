CXX = g++

#CXXFLAGS = -std=c++11 -Wall

SOURCES = Controller.cpp MarketOrder.cpp LimitOrder.cpp MarketFactory.cpp Order.cpp Trader.cpp LimitFactory.cpp OrderBook.cpp OrderFactory.cpp Stock.cpp main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = try

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)


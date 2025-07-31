TARGET=send-arp
CXXFLAGS=-g -Wall

all: $(TARGET)

$(TARGET) : pcap-test.c
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@ -lpcap

clean:
	rm -f $(TARGET)
	rm -f *.o

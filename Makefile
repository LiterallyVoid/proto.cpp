OBJS = proto.o main.o

CXXFLAGS = `pkg-config --cflags glfw3 glu` -O3 -g -Wall -Wextra -Iinclude
LDFLAGS = `pkg-config --static --libs glfw3 glu` -O3 -g -lGLEW

currentproject: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

clean:
	-rm currentproject *.o
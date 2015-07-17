CC = g++
CFLAGS = -O2 -Wall
TARGET = a.out

SRCS = main.cpp img_io.cpp img_filter.cpp img_ui.cpp img_hist.cpp img_tree.cpp
OBJS = main.o img_io.o img_filter.o img_ui.o img_hist.o img_tree.o
HDRS = img_std.h

$(TARGET) : $(OBJS) $(HDRS)
	$(CC) $(CFLAGS) -o a.out $(OBJS)

main.o : img_io.h img_ui.h img_filter.h img_std.h main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

img_ui.o : img_std.h img_ui.h img_ui.cpp
	$(CC) $(CFLAGS) -c img_ui.cpp

img_io.o : img_std.h img_io.h img_io.cpp
	$(CC) $(CFLAGS) -c img_io.cpp

img_filter.o : img_std.h img_filter.h img_filter.cpp
	$(CC) $(CFLAGS) -c img_filter.cpp

img_hist.o : img_std.h img_hist.h img_hist.cpp
	$(CC) $(CFLAGS) -c img_hist.cpp

img_tree.o : img_std.h img_tree.h img_tree.cpp
	$(CC) $(CFLAGS) -c img_tree.cpp

clean :
	rm -rf $(OBJS) $(TARGET)

Compilador = g++
FLAGS = -ansi
LIBS = -lm

TARGET = pseudoos

SRC_DIR = .
INC_DIR = headers

ifeq ($(OS),Windows_NT)
    EXECUTABLE_EXTENSION = .exe
    RM = del /q
else
    EXECUTABLE_EXTENSION =
    RM = rm -f
endif

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(SRC_DIR)/%.o, $(SRCS))
FLAGS += -I$(INC_DIR)


$(TARGET): $(OBJS)
	$(Compilador) $(FLAGS) $(OBJS) -o $(TARGET) $(LIBS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(Compilador) $(FLAGS) -c $< -o $@ $(LIBS)

clean:
	$(RM) $(OBJS) $(TARGET)$(EXECUTABLE_EXTENSION)
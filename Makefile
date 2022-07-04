BUILD_DIR := ./build

# EXE_SRCS := onion_test.cpp proxy.cpp det_encrypt.cpp det_decrypt.cpp ope_encrypt.cpp ope_decrypt.cpp compile_text.cpp
EXE_SRCS := $(wildcard *.cpp)
TARGETS = $(EXE_SRCS:.cpp=)
TARGETS_PATH := $(BUILD_DIR)/bin
# EXE := $(EXE_SRCS:%.cpp=$(BUILD_DIR)/bin/%)

# if cpp, use the following
# EXE_SRCS := program.cpp
# EXE := $(EXE_SRCS:%.cpp=$(BUILD_DIR)/bin/%)

# name of lib
LIB := libmylib.so 

LIB_SRCS := $(wildcard src/*.c src/*.cpp)
LIB_OBJS := $(LIB_SRCS:%=$(BUILD_DIR)/%.o)
LIB_DEPS := $(LIB_OBJS:.o=.d)

INC_DIRS := $(shell find ./src -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) -I/usr/local/include
CPPFLAGS := $(INC_FLAGS) -MMD -MP

LDFLAGS := -L$(BUILD_DIR) -L/usr/local/lib
CXXFLAGS := -std=c++11 -g -lcryptopp -lpthread -lpqxx -lpq -lsqlparser -lpg_query

all: $(TARGETS)

$(TARGETS): % : %.cpp $(BUILD_DIR)/$(LIB) $(LIB_OBJS)
	@echo $(TARGETS_PATH)
	mkdir -p $(dir $(TARGETS_PATH)/$@)
	$(CXX)  $^ -o $(TARGETS_PATH)/$@ $(CXXFLAGS)  $(INC_FLAGS) $(LDFLAGS)

# $(EXE): $(BUILD_DIR)/$(LIB) $(LIB_OBJS) $(EXE_SRCS)
# 	mkdir -p $(dir $@)
# 	@echo $(EXE)
# 	$(CXX)  $^ -o $(EXE) $(CXXFLAGS)  $(INC_FLAGS) $(LDFLAGS)

$(BUILD_DIR)/$(LIB): $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) -shared -fPIC -o $@ $^

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) -fPIC $(CPPFLAGS) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) -fPIC $(CPPFLAGS) $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@



clean:
	rm -r $(BUILD_DIR)

-include $(LIB_DEPS)




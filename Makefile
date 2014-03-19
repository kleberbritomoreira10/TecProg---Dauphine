# Folders containing files
INCLUDES := include
SOURCES := src
RESOURCES := res
BUILD := build

# Target program name to directory name
TARGET := $(notdir $(CURDIR))

# Automatically build a list of object files
CPPFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))

# Object files
export OFILES := $(addprefix $(BUILD)/,$(CPPFILES:.cpp=.o))
# 
CPPFILES := $(addprefix $(SOURCES)/,$(CPPFILES))

# Compiler (CXX for C++)
export LD := $(CXX)

# Build a list of include paths
export INCLUDE := $(foreach dir,$(INCLUDES), -I$(CURDIR)/$(dir)) -I$(CURDIR)/$(BUILD)

# Compiler flags
CPPFLAGS=-g -W -Wall -pedantic -ansi
# Linking flags
LIBS := -lSDL2 -lSDL2_image
LDFLAGS = $(LIBS)

$(BUILD)/%.o:$(SOURCES)/%.cpp
	@mkdir -p $(BUILD)
	@echo Building $^ ...
	@$(LD) $(CPPFLAGS) -c $^ -o $@ $(INCLUDE)

main:$(OFILES)
	@mkdir -p $(BUILD)
	@echo Linking necessary libraries...
	@$(LD) $(OFILES) $(CPPFLAGS) $(LDFLAGS) -o $(TARGET)
	@echo Built executable "$(TARGET)"

# Cleanup
clean:
	@echo Cleaning...
	@rm -rf $(BUILD)
	@rm -f $(TARGET)
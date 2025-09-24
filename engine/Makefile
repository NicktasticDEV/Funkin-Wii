ENGINE_NAME := finengine
BUILD_DIR := build

SRC_DIRS := source \
			source/engine \
			source/system

INCLUDE_DIRS := include \
				include/finengine \
				source

ROMFS := # engine has no assets embedded directly

# Include shared settings
include ../mk/common.mk

VPATH := $(addprefix $(CURDIR)/,$(SRC_DIRS))
CPPFILES := $(foreach d,$(SRC_DIRS),$(notdir $(wildcard $(d)/*.cpp)))
OFILES := $(addprefix $(BUILD_DIR)/,$(CPPFILES:.cpp=.o)) $(ROMFS_TARGET)

INCLUDE += $(foreach d,$(INCLUDE_DIRS), -iquote $(CURDIR)/$(d))
LIBPATHS := -L$(LIBOGC_LIB) $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

# Archive path
ENGINE_LIB := $(BUILD_DIR)/lib$(ENGINE_NAME).a

# Default target
all: $(ENGINE_LIB)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@echo CXX $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(ENGINE_LIB): $(OFILES)
	@echo AR $@
	@$(AR) rcs $@ $^

clean:
	@echo Cleaning engine...
	@rm -rf $(BUILD_DIR)

.PHONY: all clean

TARGET := funkin
BUILD_DIR := build

SRC_DIRS := source \
			source/states
			
INCLUDE_DIRS := include

ROMFS := ../assets

ENGINE_LIB := ../engine/build/libfinengine.a

include ../mk/common.mk

VPATH := $(addprefix $(CURDIR)/,$(SRC_DIRS)) $(ROMFS)
CPPFILES := $(foreach d,$(SRC_DIRS),$(notdir $(wildcard $(d)/*.cpp)))
OFILES_SRC := $(CPPFILES:.cpp=.o)
OFILES := $(addprefix $(BUILD_DIR)/,$(OFILES_SRC)) $(ROMFS_TARGET)

INCLUDE += $(foreach d,$(INCLUDE_DIRS), -iquote $(CURDIR)/$(d)) -I$(CURDIR)/../engine/include
LIBS := $(ENGINE_LIB) $(LIBS_BASE)
LIBPATHS := -L$(LIBOGC_LIB) $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

all: $(BUILD_DIR)/$(TARGET).dol

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@echo CXX $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(addprefix $(BUILD_DIR)/,$(OFILES_SRC)) $(ENGINE_LIB) $(ROMFS_TARGET)
	@echo LD $@
	@$(CXX) $(LDFLAGS) -o $@ $^ $(LIBPATHS) $(LIBS)

$(BUILD_DIR)/$(TARGET).dol: $(BUILD_DIR)/$(TARGET).elf
	@echo DOL $@
	@elf2dol $< $@

clean:
	@echo Cleaning game...
	@rm -rf $(BUILD_DIR) app.romfs.o

.PHONY: all clean

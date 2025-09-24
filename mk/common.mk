ifndef COMMON_MK_INCLUDED
COMMON_MK_INCLUDED := 1

#---------------------------------------------------------------------------------
# Devkit validation and base rules
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif

include $(DEVKITPPC)/wii_rules

#---------------------------------------------------------------------------------
# Shared flags
#---------------------------------------------------------------------------------
PORTABLE_CFLAGS := -g -O2 -Wall
PLATFORM_CFLAGS := -DFINENGINE_OS_WII
CFLAGS += $(PORTABLE_CFLAGS) $(PLATFORM_CFLAGS) $(MACHDEP) $(INCLUDE)
CXXFLAGS += $(CFLAGS)
LDFLAGS += -g $(MACHDEP)

#---------------------------------------------------------------------------------
# Base library list (without engine/game specifics)
#---------------------------------------------------------------------------------
LIBS_BASE := -lgrrlib -lpngu `$(PREFIX)pkg-config freetype2 libpng libjpeg --libs` -lfat \
             -lwiiuse -ltinyxml2 -lasnd -lvorbisidec -logg -lbte -logc -lm

# Library/include dirs (add only once). Projects may append more.
LIBDIRS += $(PORTLIBS) $(LIBOGC_LIB)
INCLUDE += $(foreach dir,$(LIBDIRS),-I$(dir)/include) -I$(LIBOGC_INC)

#---------------------------------------------------------------------------------
# romfs (only once) - consumers should set ROMFS before including if they want assets
#---------------------------------------------------------------------------------
include $(DEVKITPRO)/portlibs/wii/share/romfs-ogc.mk
CFLAGS   += $(ROMFS_CFLAGS)
CXXFLAGS += $(ROMFS_CFLAGS)
LIBS_BASE += $(ROMFS_LIBS)

#---------------------------------------------------------------------------------
# Generic binary embedding rules
#---------------------------------------------------------------------------------
%.png.o : %.png
	@echo $(notdir $<)
	$(bin2o)

%.ogg.o %_ogg.h : %.ogg
	@echo $(notdir $<)
	$(bin2o)

%.ttf.o %_ttf.h : %.ttf
	@echo $(notdir $<)
	$(bin2o)

%.jpg.o %_jpg.h : %.jpg
	@echo $(notdir $<)
	$(bin2o)

endif # COMMON_MK_INCLUDED

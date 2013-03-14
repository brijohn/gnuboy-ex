.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITSH4)),)
$(error "Please set DEVKITSH4 in your environment. export DEVKITSH4=<path to sdk>")
endif

include $(DEVKITSH4)/exword_rules


TARGET		:= gnuby
SOURCEDIR 	:= src
HTMLDIR		:= html
MODNAME		:= gnuboy
APPTITLE	:= Gnuboy EX 1.0.5-2
APPID		:= GNUBY
APPMOD		:= $(TARGET).d01

BUILDS		:=	ja cn

EXCLUDE		:=	$(SOURCEDIR)/loader.c $(SOURCEDIR)/main.c $(SOURCEDIR)/newsound.c $(SOURCEDIR)/inflate.c
CFILES		:=	$(filter-out $(EXCLUDE),$(wildcard $(SOURCEDIR)/*.c)) $(wildcard $(SOURCEDIR)/sys/*.c) $(wildcard $(SOURCEDIR)/libc/*.c)
SFILES		:=	$(wildcard $(SOURCEDIR)/*.s) $(wildcard $(SOURCEDIR)/sys/*.s) $(wildcard $(SOURCEDIR)/libc/*.s)
HTMLINFILES	:= 	$(foreach dir,$(BUILDS),$(wildcard $(HTMLDIR)/$(dir)/*.in))

OBJECTS		:= 	$(CFILES:.c=.o) $(SFILES:.s=.o)
HTML		:=	$(HTMLINFILES:.htm.in=.htm)

CC_OPTS := -DGNUBOY_DISABLE_SAVESTATES -DGNUBOY_USE_BINARY_RTC_FILES -DALT_DIRSEP
LDFLAGS := -nostdlib -L$(DEVKITPRO)/libdataplus/lib -ldataplus -lgraphics -lsh4a
CFLAGS :=  -fno-builtin -I$(DEVKITPRO)/libdataplus/include -I$(SOURCEDIR) -I$(SOURCEDIR)/libc/include -O3 $(CC_OPTS)

.PHONY: clean app


app: $(TARGET).d01 $(HTML)
	@for build in $(BUILDS) ; do \
		echo building $$build version in build/$$build/$(APPID)...; \
		mkdir -p $(CURDIR)/build/$$build/$(APPID) ; \
		cp $(TARGET).d01 $(CURDIR)/build/$$build/$(APPID) ; \
		cp html/$$build/*.htm $(CURDIR)/build/$$build/$(APPID) ; \
		touch $(CURDIR)/build/$$build/$(APPID)/fileinfo.cji ; \
	done

$(TARGET).d01: $(TARGET).elf

$(TARGET).elf: $(OBJECTS)

clean:
	@echo clean ...
	@rm -fr build $(HTML) $(OBJECTS) $(TARGET).elf $(TARGET).d01 *.map


%.htm: %.htm.in
	@echo building html $@...
	@sed -e 's/@APPTITLE/$(APPTITLE)/g' \
	    -e 's/@APPID/$(APPID)/g'       \
	    -e 's/@APPMOD/$(APPMOD)/g' $< > $@

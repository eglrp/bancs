#============================================================================
# $Author: disp
# $Date: 2013/05/15
#============================================================================
# Comments:
#    all    -> create all targets
#    clean  -> remove all object files (for a total recompile)
#============================================================================

TAR1     = ${MK_DIR_LIB}/${MK_PFX_LIB}util${MK_EXT_SLIB}
OBJ1     = string${MK_EXT_OBJ}\
					utilmisc${MK_EXT_OBJ}\
					iniconfig${MK_EXT_OBJ}\
					log${MK_EXT_OBJ}\
					datetime${MK_EXT_OBJ}\
					datetimespan${MK_EXT_OBJ}\
					amountformat${MK_EXT_OBJ}\

TARGETS = $(TAR1)
OBJECTS = $(OBJ1)

#
# Options
#
# .KEEP_STATE:

#
# Rules
#
.SUFFIXES: .cpp .obj .o
.cpp.obj:
	$(MK_CMD_CPP) $(MK_FLG_CPP) -o $@ -c $<
.cpp.o:
	$(MK_CMD_CPP) $(MK_FLG_CPP) -o $@ -c $<

#
# Targets
#
all: $(TARGETS)

$(TAR1): $(OBJ1)
	$(MK_CMD_SLIB) $(MK_FLG_SLIB)$@ $?

clean: dirty
	rm -f $(OBJECTS) core

dirty:
	rm -f $(TARGETS)

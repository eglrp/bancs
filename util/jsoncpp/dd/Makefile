#============================================================================
# $Author: disp
# $Date: 2013/07/17
#============================================================================
# Comments:
#    all    -> create all targets
#    clean  -> remove all object files (for a total recompile)
#============================================================================

TAR1	= ddtest${MK_EXT_BIN}
OBJ1	= ddtest${MK_EXT_OBJ}\
            json_value${MK_EXT_OBJ}\
            json_reader${MK_EXT_OBJ}\
            json_writer${MK_EXT_OBJ}


		
TARGETS = $(TAR1)
OBJECTS = $(OBJ1)

#
# Rules
#
.SUFFIXES: .cpp .obj .o
.cpp.obj:
	$(MK_CMD_CPP) -DTIMEOUT=10  $(MK_FLG_CPP)  $(MK_FLG_DB) -D_THREAD_SAFE $(DBINCPATH)  -o $@ -c $<
.cpp.o:
	$(MK_CMD_CPP) -DTIMEOUT=10  $(MK_FLG_CPP)  $(MK_FLG_DB) -D_THREAD_SAFE $(DBINCPATH)  -o $@ -c $<

#
# Targets
#

all: $(TARGETS)
	
$(TAR1): $(OBJ1) 
	$(MK_CMD_BIN) $(MK_FLG_BIN) $(MK_FLG_OUT)$@ $(MK_LIB_PATH) $(OBJ1) 

clean: dirty
	rm -f $(OBJECTS) core

dirty:
	rm -f $(TARGETS)

#============================================================================
# $Author: disp
# $Date: 2013/07/17
#============================================================================
# Comments:
#    all    -> create all targets
#    clean  -> remove all object files (for a total recompile)
#============================================================================

TAR1	= ${MK_DIR_BIN}/tcpmain${MK_EXT_BIN}
OBJ1	= appbase${MK_EXT_OBJ}\
		mintcpio${MK_EXT_OBJ}\
		mymutex${MK_EXT_OBJ}\
		mqmanage${MK_EXT_OBJ}\
		task${MK_EXT_OBJ}\
		tcpmain${MK_EXT_OBJ}

TAR2	= ${MK_DIR_BIN}/v${MK_EXT_BIN}
OBJ2	= v${MK_EXT_OBJ}\
		mqmanage${MK_EXT_OBJ}
		
TARGETS = $(TAR1) $(TAR2)
OBJECTS = $(OBJ1) $(OBJ2)

#
# Rules
#
.SUFFIXES: .cpp .obj .o
.cpp.obj:
	$(MK_CMD_CPP) -DTIMEOUT=10  $(MK_FLG_CPP)  $(MK_FLG_DB) $(DBINCPATH)  -o $@ -c $<
.cpp.o:
	$(MK_CMD_CPP) -DTIMEOUT=10  $(MK_FLG_CPP)  $(MK_FLG_DB) $(DBINCPATH)  -o $@ -c $<

#
# Targets
#

all: $(TARGETS)
	
$(TAR1): $(OBJ1) 
	$(MK_CMD_BIN) $(MK_FLG_BIN) $(MK_FLG_OUT)$@ $(MK_LIB_PATH) $(OBJ1) $(MK_LNK_SHM)  $(MK_LNK_DBSQL) -lsyscfg
	
$(TAR2): $(OBJ2) 
	$(MK_CMD_BIN) $(MK_FLG_BIN) $(MK_FLG_OUT)$@ $(MK_LIB_PATH) $(OBJ2) $(MK_LNK_SHM)  $(MK_LNK_DBSQL) -lsyscfg	 
		
clean: dirty
	rm -f $(OBJECTS) core

dirty:
	rm -f $(TARGETS)

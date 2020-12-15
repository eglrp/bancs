#============================================================================
# $Author: disp
# $Date: 2013/06/07
#============================================================================
# Comments:
#    all    -> create all targets
#    clean  -> remove all object files (for a total recompile)
#============================================================================

TAR1 = ${MK_DIR_LIB}/${MK_PFX_LIB}sysutil$(MK_EXT_DLIB)
OBJ1 = queue${MK_EXT_OBJ}\
			dictqueue${MK_EXT_OBJ}\
			mutexlock${MK_EXT_OBJ}\
			arealock${MK_EXT_OBJ}\
			shmbase${MK_EXT_OBJ}\
			shmaccess${MK_EXT_OBJ}\
			simplelog${MK_EXT_OBJ}\
			log${MK_EXT_OBJ}
						
TARGETS     = $(TAR1)
OBJECTS		= $(OBJ1)

#
# Rules
#
.SUFFIXES: .cpp .obj .o
.cpp.obj:
	$(MK_CMD_CPP) -DBUILD_DICT_DLL $(MK_FLG_DYN) $(MK_FLG_CPP) -o $@ -c $<
.cpp.o:
	$(MK_CMD_CPP) -DBUILD_DICT_DLL $(MK_FLG_DYN) $(MK_FLG_CPP) -o $@ -c $<

#
#	TARGETS
#
all: $(TARGETS)

$(TAR1):	$(OBJ1)
	$(MK_CMD_DLIB) $(MK_FLG_DLIB) $(MK_FLG_OUT)$(TAR1) $(MK_LIB_PATH) $(OBJ1) $(MK_LNK_PKG) $(MK_LNK_NODB)

clean: dirty
	rm -f $(OBJECTS) core

dirty:
	rm -f $(TARGETS)

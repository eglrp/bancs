
echo
echo "-------------------------------------------------------------"
echo "                 Welcome to the PD environment               "
echo "-------------------------------------------------------------"
echo

export NCBS_CUSTOMER=ncbs
export NCBS_SYSTYPE=pd
export NCBS_APPL=r
export NCBS_DB_TYPE=DB2
export MACHTYPE=AIX
#
# Setup correct path
#

export PATH="$PATH:/$NCBS_CUSTOMER/$NCBS_SYSTYPE/$NCBS_APPL"
export PATH="$PATH:/$NCBS_CUSTOMER/$NCBS_SYSTYPE/$NCBS_APPL/bin"
export PATH="$PATH:/$NCBS_CUSTOMER/$NCBS_SYSTYPE/$NCBS_APPL/lib"
export PATH="$PATH:/$NCBS_CUSTOMER/$NCBS_SYSTYPE/$NCBS_APPL/sh"

export NCBS_HOME="/$NCBS_CUSTOMER/$NCBS_SYSTYPE/$NCBS_APPL"
export NCBS_LIB="$NCBS_HOME/lib"
export NCBS_BIN="$NCBS_HOME/bin"
export NCBS_INC="$NCBS_HOME/include"
export PLATS_INC="$NCBS_HOME/src/platsys/lib"

#
# Development shortcuts
#
export exe=$NCBS_HOME/bin
export bin=$NCBS_HOME/bin
export sh=$NCBS_HOME/sh
export spool=$NCBS_HOME/spool

export inc=$NCBS_HOME/include
export src=$NCBS_HOME/src
export plats=$src/platsys


export NCBS_CONFIG=$NCBS_HOME/etc
export config=$NCBS_CONFIG
export cfgsrc=$NCBS_CONFIG
export data=$NCBS_HOME/data

#export now=¡¤date +%m%d.09/10/97M¡¤


#
# Make Environment
#
export MK_DIR_ROOT=/$NCBS_CUSTOMER/$NCBS_SYSTYPE/$NCBS_APPL
export MK_DIR_LIB=$MK_DIR_ROOT/lib
export MK_DIR_BIN=$MK_DIR_ROOT/bin
export MK_DIR_SBIN=$MK_DIR_ROOT/sbin

#
# Run environment
#
export SYSTYPE=$HOST_DQPTYPE
export NCBS_DQPTYPE=p
export NCBS_SYSNUM=1


#
# Database specific
#
echo "Database : $NCBS_DB_TYPE"

export DB2PATH=/opt/IBM/db2/V9.7
export DB_HOME=$DB2PATH
export DB_VER="9.7"
export DBLIBPATH=$DB_HOME/lib64
export DBINCPATH="-I$DB2PATH/include"
export DBLIB="-ldb2"
export bnd=$NCBS_HOME/bnd
# Make DB2 Command Line look similar like Oracle SQLPlus
export DB2OPTIONS='+a +c +ec -o -p -t'

export PATH="$DB_HOME/bin:$PATH"
export SQLGEN="$DB_HOME/bin/db2 prep"
export SQLGEN_OPT="BINDFILE NOLINEMACRO TARGET CPLUSPLUS BLOCKING ALL OUTPUT "
export MK_EXT_DB=".sqc"

#export DBNAME=Q012BAND  maitao disabled for test
#export DBNAME=DBNCBQD
export MK_DBIO=Db2

if [ ! -d $bnd ]; then
    mkdir $bnd
fi

if [ -f $DB2PATH/db2profile ]; then
    . $DB2PATH/db2profile
fi

# Connect to DB2
echo "Connecting to DB2 Instance: [$DBNAME]"
#db2 connect to $DBNAME

#echo "Change current schema to 'FNSONLQD'"
#db2 select current schema from sysibm.dual
#db2 set current schema ='FNSONLQD'
#db2 select current schema from sysibm.dual

echo "Configuring Database Environment for $NCBS_DB_TYPE"

if [ $dbenv ]; then
  . $dbenv
fi

#db2 select TRAN_CODE,STATUS,NIGHT_ENABLE_FLAG from FNSONLQD.ed1p order by TRAN_CODE fetch first 20 rows only


echo "Configuring Compiler Environment for $MACHTYPE :"

case $MACHTYPE in

AIX)

    export OBJECT_MODE=64
    export AR=ar
    export CC="/usr/vacpp/bin/xlc"
    export CPP="/usr/vacpp/bin/xlC"
    export MK_INC_DIR="-I$inc -I$src -I$src/platsys -I$src/platsys/lib -I$src/platapp"
    export MK_FLG_OUT="-o "

    version=`$CC -qversion | cut -d" " -f6 | cut -d. -f1 | cut -c 2-3`
    if [ $version -lt 7 ]; then
        CC_VERSION="-DOLD_IBM_C"
    fi

    export MK_PFX_LIB=lib
    export MK_EXT_OBJ=.o
    export MK_EXT_SLIB=.a
    export MK_EXT_DLIB=.so
    export MK_EXT_BIN=

    export MK_CMD_CPP=$CPP
    export MK_CMD_C=$CC
    export MK_CMD_DLIB=$CPP
    export MK_CMD_SLIB=$AR
    export MK_CMD_BIN=$CPP

    export MK_FLG_DLIB="-G -Wl,-bbigtoc -bh:5"
    export MK_FLG_SLIB="rsv "
    export MK_FLG_CPP="-g $CC_VERSION -DOS_AIX -DBULK_ROWS=500 -qthreaded -DPARALLEL_QUERY_CPU=4"
    export MK_FLG_CPP="$MK_FLG_CPP $MK_INC_DIR"
    export MK_FLG_BIN="-brtl -bexpall -bh:5"
    export MK_FLG_SVC="-brtl -bh:5"
    export MK_FLG_C="-g $CC_VERSION -DOS_AIX -D_MSGQSUPPORT -DNO_TIMEOUT=60 -qthreaded -qsuppress=1506-342 -qcpluscmt -Aa"
    export MK_FLG_C="$MK_FLG_C $MK_INC_DIR"
    export MK_FLG_DYN=" "
    export MK_FLG_DB="-DUSE_DBSEQ"

    export MK_LNK_STAT="-L$MK_DIR_LIB -ldbsql++ -ldbio -ldb++ -lutil  -L$DBLIBPATH $DBLIB"
    export MK_LNK_STATDBIO="-L$MK_DIR_LIB -ldbio -lsysutil  -ldb++ -L$DBLIBPATH $DBLIB"
    export MK_LNK_STATNEWDBIO="-L$MK_DIR_LIB -lnewdbio -lsysutil  -ldb++ -L$DBLIBPATH $DBLIB"
    export MK_LNK_ACQ="-L$MK_DIR_LIB "
    export MK_LNK_DYN="-L$MK_DIR_LIB "
    export MK_LNK_DBIO="-L$MK_DIR_LIB "
    export MK_LNK_DLL=
    export MK_LNK_NODB=
    export MK_LNK_COM=

#  	DYNAMIC_LDFLAGS="-bdynamic -brtl"
#		STATIC_LDFLAGS="-bstatic"
    export MK_LNK_DICT="-L$MK_DIR_LIB -lBeai3Dict"
    export MK_LNK_PKG="-L$MK_DIR_LIB  -lBeai3Dict -ldict -lutil"
    export MK_LNK_SHM="-L$MK_DIR_LIB  -lBeai3Dict -ldict -lutil -lpkg  -lsysutil"
    export MK_LNK_DBSQL="-L$MK_DIR_LIB -ldbio -ldb++ -lutil -L$DBLIBPATH $DBLIB"

    export DLL=
    export ETC="/etc"
    export LIBPATH="$NCBS_LIB"
    ;;

esac


echo "    C++ Compiler   is " $MK_CMD_CPP
echo "    C   Compiler   is " $MK_CMD_C
echo "    Dynamic Linker is " $MK_CMD_DLIB
echo "    Archive Linker is " $MK_CMD_SLIB
echo "    Binary Linker  is " $MK_CMD_BIN
echo " "
echo "Environment : "
echo "    NCBS_HOME : " $NCBS_HOME
echo "    NCBS_LIB  : " $NCBS_LIB
echo "    NCBS_INC  : " $NCBS_INC
echo "    PLATS_INC : " $PLATS_INC
echo " "


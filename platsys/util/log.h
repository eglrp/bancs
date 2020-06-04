

#ifndef __UTIL__LOG__H__
#define __UTIL__LOG__H__


//==============================================================================
// Includes
//==============================================================================

#include <stdio.h>


//==============================================================================
// Macros
//==============================================================================

#define LOG_ERROR     0
#define LOG_WARNING   1
#define LOG_SYSTEM    2
#define LOG_TXN       3
#define LOG_INFO      4
#define LOG_DEBUG     5
#define LOG_DUMP_ASC  6
#define LOG_DUMP_HEX  7

#define LOG_TXN_TYPE  isRequest() ? "RQ" : "RS"
#define LOG_DATE      "%Y%m%d"

//==============================================================================
// Log Class
//==============================================================================

/***************************************************************************//**
 * \brief
 * Concrete class used for logging system wide errors
 ******************************************************************************/
class FLog
{
// Static init
public:
    static void init(const char*           , const char*,
                     const char* = __DATE__, const char* = __TIME__);
    static void exit(void);

// Static
public:
    static void error  (const char*, ...);
    static void warning(const char*, ...);
    static void system (const char*, ...);
    static void txn    (const char*, ...);
    static void info   (const char*, ...);
    static void debug  (const char*, ...);
    static void dump   (const char*, void*, int);
    static void dumpAsc(const char*, void*, int);
    static void dumpHex(const char*, void*, int);
    static void direct (const char*);
    static int  isLevel(int);

    static void reload (void);

private:
    static void msg  (const char*, char);
    static void open (void);
    static void close(void);
    static void check(void);

    static void dumpLevel  (void);
    static int  parseLevel (const char*);
    static void changeLevel(int);

// Data
private:
    static int     enabled;
    static int     debugInfo;
    static int     maxFiles;
    static int     numFile;
    static FILE *  theFile;
    static int     maxFileSize;

    static int     level;        // process level, modifiable
    static int     defaultLevel; // default level, from TPAC_TRACE_LEVEL env (read/only)

};

#endif // __UTIL__LOG__H__


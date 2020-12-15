
//==============================================================================
// Includes
//==============================================================================

#include "log.h"
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>




/***************************************************************************//**
 * \class FLog
 * Concrete implementation of a class that encapsulates the logging i
 ******************************************************************************/

#define LOG_CONFIG_DIR "debug/"

//==============================================================================
// Structs
//==============================================================================

struct logtype_t
{
    char  symbol;
    int   val;
    char  desc[10+1];
};


//==============================================================================
// Static Data
//==============================================================================

int     FLog::enabled  = 0;
int     FLog::maxFiles = 5;
int     FLog::numFile  = 0;
FILE*   FLog::theFile  = NULL;


int     FLog::maxFileSize  = (1024 * 1024);
int     FLog::level        = 0;  
int     FLog::defaultLevel = 0x0Fl; // Default level: Error,Warning,System,Txn


//==============================================================================
// Constants
//==============================================================================

const int MAXBUFFERLEN = 8192;

const logtype_t g_Options[] = 
{
    { 'E', 1 << LOG_ERROR   , "ERROR"      }, 
    { 'W', 1 << LOG_WARNING , "WARNING"    },
    { 'S', 1 << LOG_SYSTEM  , "SYSTEM"     },
    { 'T', 1 << LOG_TXN     , "TXN"        },
    { 'I', 1 << LOG_INFO    , "INFO"       },
    { 'D', 1 << LOG_DEBUG   , "DEBUG"      },
    { 'A', 1 << LOG_DUMP_ASC, "ASCII_DUMP" },
    { 'H', 1 << LOG_DUMP_HEX, "HEX_DUMP"   }
};

const int g_OptionsSize = sizeof(g_Options) / sizeof(logtype_t);
 
static inline int isSet(int val, int flag)
{
    return (val & flag) ? 1 : 0;
}

static int set(int val, int flag, int on)
{
    int result = val;
    if (on)
        result |= flag;
    else
        result &= (~flag);

    return result;
}

//==============================================================================
// Log Class
//==============================================================================

/***************************************************************************//**
 * Initialise various logs
 * @param[in]  pname name of program
 * @param[in]  desc  description of program
 * @param[in]  dt    date program was compiled (__DATE__)
 * @param[in]  tm    time program was compiled (__TIME__)
 * @return Nothing
 ******************************************************************************/

void
FLog::init(const char* pname, const char* desc, const char* dt, const char* tm)
{
 
}


/***************************************************************************//**
 * Stop logging (should be called on exit)
 * @return Nothing
 ******************************************************************************/

void
FLog::exit(void)
{
   FLog::close();
}


/***************************************************************************//**
 * Log an error
 * @param[in]  fmt free format according to printf
 * @return Nothing
 ******************************************************************************/

void
FLog::error(const char* fmt, ...)
{


}


/***************************************************************************//**
 * Log an warning
 * @param[in]  fmt free format according to printf
 * @return Nothing
 ******************************************************************************/

void
FLog::warning(const char* fmt, ...)
{
 
}


/***************************************************************************//**
 * Log on informational message (debug or trace)
 * @param[in]  fmt free format according to printf
 * @return Nothing
 ******************************************************************************/

void
FLog::info(const char* fmt, ...)
{
  
}


/***************************************************************************//**
 * Log on system messages, called from online application code
 * @param[in]  fmt free format according to printf
 * @return Nothing
 ******************************************************************************/

void
FLog::system(const char* fmt, ...)
{
  
}


/***************************************************************************//**
 * Log on txn information, called from FForeignTxn & FTxn derived classes
 * @param[in]  fmt free format according to printf
 * @return Nothing
 ******************************************************************************/

void
FLog::txn(const char* fmt, ...)
{
  
}


/***************************************************************************//**
 * Log on informational message (debug or trace)
 * @param[in]  fmt free format according to printf
 * @return Nothing
 ******************************************************************************/

void
FLog::debug(const char* fmt, ...)
{
   
}


/***************************************************************************//**
 * Dump either ascii or hex dump to the log of the given data
 * @param[in]  txt   text describing the hex dump
 * @param[in]  pdata pointer to the data to dump
 * @param[in]  len   length of the data[in] bytes
 * @return Nothing
 ******************************************************************************/

void
FLog::dump(const char* txt, void* pdata, int len)
{
  
}


/***************************************************************************//**
 * Write an ascii-dump to the log of the given data
 * @param[in]  txt   text describing the hex dump
 * @param[in]  pdata pointer to the data to dump
 * @param[in]  len   length of the data[in] bytes
 * @return Nothing
 ******************************************************************************/

void
FLog::dumpAsc(const char* txt, void* pdata, int len)
{
   
}


/***************************************************************************//**
 * Write a hex-dump to the log of the given data
 * @param[in]  txt   text describing the hex dump
 * @param[in]  pdata pointer to the data to dump
 * @param[in]  len   length of the data[in] bytes
 * @return Nothing
 ******************************************************************************/
void
FLog::dumpHex(const char* txt, void* pdata, int len)
{
   
}

/***************************************************************************//**
 * Parse comma separated log level 
 * @param[in]  val   comma separated log options
 * @return log level in decimal, -1 on error
 ******************************************************************************/

int 
FLog::parseLevel(const char* val)
{
 

    return 0;
}


int
FLog::isLevel(int lvl)
{
    return isSet(FLog::level, lvl);
}

void
FLog::dumpLevel()
{
    if (!theFile)
        return;
  
}

void
FLog::open(void)
{
  
}

void
FLog::close(void)
{
  
}


void
FLog::msg(const char * ptext, char logSymbol)
{
   
}

void
FLog::direct(const char * ptext)
{
  
}

void
FLog::check(void)
{
   
}

void
FLog::reload(void)
{
   
}

void
FLog::changeLevel(int newlevel)
{
   
}



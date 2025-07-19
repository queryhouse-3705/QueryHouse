#ifndef __LOGGING_H__
#define __LOGGING_H__
#include <string>
#include <iostream>
#include <fstream>

// Colors
#define BLACK "\033[30m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"

#define BOLD_BLACK "\033[1m\033[30m"
#define BOLD_RED "\033[1m\033[31m"
#define BOLD_GREEN "\033[1m\033[32m"
#define BOLD_YELLOW "\033[1m\033[33m"
#define BOLD_BLUE "\033[1m\033[34m"
#define BOLD_MAGENTA "\033[1m\033[35m"
#define BOLD_CYAN "\033[1m\033[36m"
#define BOLD_WHITE "\033[1m\033[37m"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define LOG(m)            do { logfile << m << "\n"; } while (0)
#define LOG_RAW(m)        do { logfile << m; } while (0)
#define fLOG(m)           do { logfile << m << std::endl; } while (0)

#define LOGF(f,m)         do { f << m << "\n"; } while (0)
#define LOGF_RAW(f,m)     do { f << m; } while (0)
#define fLOGF(f,m)        do { f << m << std::endl; } while (0)

#endif  // __LOGGING_H__

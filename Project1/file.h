#ifndef PROJECT1_FILE_H
#define PROJECT1_FILE_H

#ifdef _WIN32

#include <direct.h>

#define mkdir_func(dir) _mkdir(dir)

#else

#include <sys/stat.h>
#include <sys/types.h>

#define mkdir_func(dir) mkdir(dir, 0755)

#endif

#endif //PROJECT1_FILE_H

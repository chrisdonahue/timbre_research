#ifndef CDSP_DEFINES
#define CDSP_DEFINES

#ifdef _WIN32
#define CDSP_WIN32
#ifdef _WIN64
#define CDSP_WIN64
#endif
#elif __APPLE__
#define CDSP_MACOS
#elif __linux
#define CDSP_LINUX
#elif __unix
#define CDSP_UNIX
#elif __posix
#define CDSP_POSIX
#endif

#define CDSP_SAMPLE_32

#endif
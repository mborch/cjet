#ifndef CJET_WINDOWS_GETOPT_H
#define CJET_WINDOWS_GETOPT_H

#ifdef __cplusplus
extern "C" {
#endif

extern int optind;
extern char *optarg;
extern int opterr;

int getopt(int argc, char *argv[], const char *optstring);

#ifdef __cplusplus
}
#endif

#endif	/* CJET_WINDOWS_GETOPT_H */
#include <getopt.h>
#include <stdbool.h>
#include <stddef.h>

static const char SHOR_FLAGS[] = "benstvAET";

struct opt_status {
  bool number;
  bool number_nonblank;
  bool show_nonprintable;
  bool show_ends;
  bool squeeze;
  bool show_tabs;
};

static struct option const LONG_FLAGS[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {"show-nonprinting", no_argument, NULL, 'v'},
    {"show-ends", no_argument, NULL, 'E'},
    {"show-tabs", no_argument, NULL, 'T'},
    {"show-all", no_argument, NULL, 'A'}};
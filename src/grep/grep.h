#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <stdbool.h>

#define MAX_LEN_PAT 10000

static const char SHORT_FLAGS[] = "e:ivclnhsf:o";

struct opt_status {
  bool pattern_e;
  bool ignor_uppercase_i;
  bool invert_v;
  bool matching_count_c;
  bool matching_files_l;
  bool count_n;
  bool without_filenames_h;
  bool suppress_errors_s;
  bool regexes_f;
  bool matching_parts_o;
  bool single_file;
};

#endif
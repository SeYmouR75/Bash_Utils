#include "grep.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool flag_parser(int argc, char **argv, struct opt_status *flag_check,
                 char *patterns_depot);

bool add_pattern_from_file(char *filename, char *patterns_depot);

bool add_pattern(const char *arg, char *patterns_depot);

bool process_files(int argc, char **argv, struct opt_status flag_check,
                   char *patterns_depot);

bool grep(FILE *file_ptr, char *filename, const char *patterns,
          struct opt_status flag_check);

bool o_only_mathces_out(const char *patterns_depot, char *line, char *filename,
                        int str_cnt, int *matches, bool *file_check,
                        struct opt_status flag_check);

bool match_check(const char *patterns, char *line, bool ignore_case);

int main(int argc, char **argv) {
  if (argc < 2) return EXIT_FAILURE;

  char patterns_depot[MAX_LEN_PAT] = {""};
  struct opt_status flag_check = {false};

  if (flag_parser(argc, argv, &flag_check, patterns_depot)) {
    process_files(argc, argv, flag_check, patterns_depot);
  }

  return 0;
}

bool flag_parser(int argc, char **argv, struct opt_status *flag_check,
                 char *patterns_depot) {
  bool err = true;
  char opt = ' ';
  while ((opt = getopt_long(argc, argv, SHORT_FLAGS, NULL, 0)) != -1) {
    switch (opt) {
      case 'e':
        flag_check->pattern_e = true;
        add_pattern(optarg, patterns_depot);
        break;
      case 'i':
        flag_check->ignor_uppercase_i = true;
        break;
      case 'v':
        flag_check->invert_v = true;
        break;
      case 'c':
        flag_check->matching_count_c = true;
        break;
      case 'l':
        flag_check->matching_files_l = true;
        break;
      case 'n':
        flag_check->count_n = true;
        break;
      case 'h':
        flag_check->without_filenames_h = true;
        break;
      case 's':
        flag_check->suppress_errors_s = true;
        break;
      case 'f':
        flag_check->regexes_f = true;
        if (!add_pattern_from_file(optarg, patterns_depot)) err = false;

        break;
      case 'o':
        flag_check->matching_parts_o = true;
        break;
      default:
        break;
    }
  }

  if (!flag_check->pattern_e && !flag_check->regexes_f &&
      (argc - (optind + 1)) == 1)
    flag_check->single_file = true;

  if ((flag_check->pattern_e || flag_check->regexes_f) &&
      ((argc - optind) == 1))
    flag_check->single_file = true;

  if (!flag_check->pattern_e && !flag_check->regexes_f) {
    flag_check->pattern_e = true;
    err = add_pattern(argv[optind], patterns_depot);
    optind++;
  }

  return err;
}

bool add_pattern_from_file(char *filename, char *patterns_depot) {
  bool err = true;

  FILE *fp = fopen(filename, "r");
  if (fp != NULL) {
    char *line = NULL;
    ssize_t lenght = 0;
    size_t size = 0;

    while (err && ((lenght = getline(&line, &size, fp)) != -1)) {
      if (line[lenght - 1] == '\n') line[lenght - 1] = '\0';
      err = add_pattern(line, patterns_depot);
    }

    if (line) free(line);
  } else {
    err = false;
  }

  if (fp) fclose(fp);

  return err;
}

bool add_pattern(const char *arg, char *patterns_depot) {
  bool err = true;

  if (strlen(arg) + strlen(patterns_depot) >= MAX_LEN_PAT) err = false;
  if (err) {
    if (strlen(patterns_depot) == 0)
      strcat(patterns_depot, arg);
    else {
      strcat(patterns_depot, "\\|");
      strcat(patterns_depot, arg);
    }
  }

  return err;
}

bool process_files(int argc, char **argv, struct opt_status flag_check,
                   char *patterns_depot) {
  bool err = true;

  for (int i = optind; i < argc; i++) {
    if (flag_check.invert_v && flag_check.matching_parts_o) break;
    FILE *file_ptr = fopen(argv[i], "r");
    if (file_ptr != NULL) {
      err = grep(file_ptr, argv[i], patterns_depot, flag_check);
      fclose(file_ptr);
    }
  }
  return err;
}

bool grep(FILE *file_ptr, char *filename, const char *patterns_depot,
          struct opt_status flag_check) {
  bool err = true;
  bool is_match = false;
  bool file_check = false;
  int last_char = 0;
  char *line = NULL;
  int matches = 0;
  int str_cnt = 0;
  ssize_t lenght = 0;
  size_t size = 0;

  while (((lenght = getline(&line, &size, file_ptr)) != -1) && !file_check) {
    str_cnt++;
    last_char = line[lenght - 1];
    if (flag_check.matching_parts_o) {
      o_only_mathces_out(patterns_depot, line, filename, str_cnt, &matches,
                         &file_check, flag_check);
    } else
      is_match =
          match_check(patterns_depot, line, flag_check.ignor_uppercase_i);

    if (flag_check.invert_v) is_match = !is_match;

    if (is_match) matches++;

    if (is_match && flag_check.matching_files_l) {
      printf("%s\n", filename);
      file_check = true;
    }

    if (is_match && !flag_check.matching_count_c &&
        !flag_check.matching_files_l) {
      if (!flag_check.single_file && !flag_check.without_filenames_h)
        printf("%s:", filename);
      if (flag_check.count_n) printf("%d:", str_cnt);
      printf("%s", line);
      if (last_char != '\n') putchar('\n');
    }
  }
  if (flag_check.matching_count_c && !flag_check.matching_files_l) {
    if (!flag_check.single_file && !flag_check.without_filenames_h)
      printf("%s:", filename);
    printf("%d\n", matches);
  }

  if (line) free(line);
  return err;
}

bool o_only_mathces_out(const char *patterns_depot, char *line, char *filename,
                        int str_cnt, int *matches, bool *file_check,
                        struct opt_status flag_check) {
  bool err = true;
  bool match_counted = false;
  int res = 1;
  regex_t regex;

  res = regcomp(&regex, patterns_depot,
                flag_check.ignor_uppercase_i ? REG_ICASE : REG_NEWLINE);

  if (res != 0)
    err = false;
  else {
    regmatch_t matchind = {0};
    bool is_match = false;

    do {
      is_match = (regexec(&regex, line, 1, &matchind, 0) == 0);

      if (is_match && !match_counted) {
        *matches += 1;
        match_counted = true;
      }
      if (is_match && flag_check.matching_files_l) {
        printf("%s\n", filename);
        *file_check = true;
      }

      if (is_match && !flag_check.matching_count_c &&
          !flag_check.matching_files_l) {
        if (!flag_check.single_file && !flag_check.without_filenames_h)
          printf("%s:", filename);
        if (flag_check.count_n) printf("%d:", str_cnt);
        printf("%.*s\n", (int)(matchind.rm_eo - matchind.rm_so),
               line + matchind.rm_so);
      }

      if (is_match) line += matchind.rm_eo;
    } while (is_match && !(*file_check));
  }

  regfree(&regex);
  return err;
}

bool match_check(const char *pattern_depot, char *line, bool ignore_case) {
  bool err = true;
  regex_t regex;
  if (regcomp(&regex, pattern_depot, ignore_case ? REG_ICASE : REG_NEWLINE) !=
      0)
    err = false;
  if (err && regexec(&regex, line, 0, NULL, 0) != 0) err = false;

  regfree(&regex);
  return err;
}

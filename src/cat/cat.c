#include "cat.h"

#include <stdio.h>

void print_text(int argc, char **argv, int index, struct opt_status flag_bool);
void flag_parser(int argc, char **argv, struct opt_status *flag_bool);

int main(int argc, char **argv) {
  struct opt_status flag_bool = {false};
  flag_parser(argc, argv, &flag_bool);
  print_text(argc, argv, optind, flag_bool);
  return 0;
}

void flag_parser(int argc, char **argv, struct opt_status *flag_bool) {
  char opt = ' ';
  while ((opt = getopt_long(argc, argv, SHOR_FLAGS, LONG_FLAGS, NULL)) != -1) {
    switch (opt) {
      case 'b':
        flag_bool->number_nonblank = true;
        break;
      case 'e':
        flag_bool->show_ends = true;
        flag_bool->show_nonprintable = true;
        break;
      case 'n':
        flag_bool->number = true;
        break;
      case 's':
        flag_bool->squeeze = true;
        break;
      case 't':
        flag_bool->show_tabs = true;
        flag_bool->show_nonprintable = true;
        break;
      case 'v':
        flag_bool->show_nonprintable = true;
        break;
      case 'A':
        flag_bool->show_nonprintable = true;
        flag_bool->show_ends = true;
        flag_bool->show_tabs = true;
        break;
      case 'E':
        flag_bool->show_ends = true;
        break;
      case 'T':
        flag_bool->show_tabs = true;
        break;
      case '?':
        printf("Unknown flag");
        break;
      default:
        break;
    }
  }
}

void print_text(int argc, char **argv, int optind,
                struct opt_status flag_bool) {
  int blank_str = 0, str_cnt = 1, cur_char = 0, prev_char = '\n';
  for (int i = optind; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp != NULL) {
      while ((cur_char = fgetc(fp)) != EOF) {
        if (cur_char != '\n') {
          blank_str = 0;
        } else {
          blank_str++;
        }

        if (flag_bool.squeeze && blank_str > 2) {
          continue;
        }

        if (flag_bool.number && !flag_bool.number_nonblank &&
            prev_char == '\n') {
          printf("%6d\t", str_cnt);
          str_cnt++;
        }

        if (flag_bool.number_nonblank && prev_char == '\n' &&
            cur_char != '\n') {
          printf("%6d\t", str_cnt);
          str_cnt++;
        }

        if (flag_bool.show_ends && cur_char == '\n') {
          printf("$");
        }

        if (flag_bool.show_tabs && cur_char == '\t') {
          printf("^I");

          prev_char = cur_char;
          continue;
        }

        if (flag_bool.show_nonprintable && (cur_char < 32 || cur_char >= 127) &&
            cur_char != '\n' && cur_char != '\t') {
          if (cur_char == 127) {
            printf("^?");
          } else if (cur_char >= 128 + 32) {
            printf("M-");
            (cur_char < 255) ? printf("%c", cur_char - 128) : printf("^?");
          } else {
            (cur_char > 32) ? printf("M-^%c", cur_char - 64)
                            : printf("^%c", cur_char + 64);
          }
          continue;
        }

        fputc(cur_char, stdout);
        prev_char = cur_char;
      }
      fclose(fp);
    }
  }
}
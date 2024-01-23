import subprocess
import sys

def add_color(text, color):
    colors_dict = {
        'GREEN': '\033[92m',
        'RED': '\033[91m',
        'RESET': '\033[0m'
    }
    return colors_dict[color] + text + colors_dict['RESET']

def run_test(args):
    original_cat = subprocess.check_output(["cat"] + args)
    my_cat = subprocess.check_output(["./s21_cat"] + args)

    if my_cat != original_cat:
        print(add_color(f"Test failed for {args}", 'RED'))
    else:
        print(add_color(f"Test passed for {args}", 'GREEN'))


args = sys.argv[1:]


run_test(args)
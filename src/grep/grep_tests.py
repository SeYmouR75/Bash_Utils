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
    original_grep = subprocess.check_output(["grep"] + args)
    my_grep = subprocess.check_output(["./s21_grep"] + args)

    if my_grep != original_grep:
        print(add_color(f"Test failed for {args}", 'RED'))
    else:
        print(add_color(f"Test passed for {args}", 'GREEN'))


args = sys.argv[1:]


run_test(args)
import os
import re
import sys
import json

from subprocess import Popen, PIPE

default_config = {
    'tests_file': 'tests.json',
    'program': '',
    'name': '',
    'stop_on_not_passed': True
}

def run_tests(tests, config):
    for action in tests:
        act_name = action['action']
        name = action.get('name', act_name)
        cases = action['cases']

        print('Tests for action "{}":'.format(name))

        if config['name'] and re.match(config['name'], act_name):
            print('\tSkipped.\n')
            continue

        is_all_passed = run_cases(act_name, cases, config)

        if not is_all_passed and config['stop_on_not_passed']:
            print('One test is not passed. Exit.')
            return

def run_cases(action, cases, config):
    case_index = 1

    is_all_passed = True
    for case in cases:
        args = case['args']
        assert_method = case['assert']

        out = exec_program(config['program'], action, args)

        passed = assert_program_out(assert_method, out)

        print('\t{}. Test {}'.format(case_index, 'passed' if passed else 'not passed'))

        if not passed:
            print('\t\tExit code: {}'.format(out['error_code']))
            print('\t\tActual: {}'.format(out['output']))

        print()

        is_all_passed = is_all_passed and passed

        if not is_all_passed and config['stop_on_not_passed']:
            break

        case_index += 1
            
    return is_all_passed

def exec_program(prog_path, action, args):
    process = Popen([prog_path, action] + args, stdout=PIPE)
    (output, err) = process.communicate()

    output = output.decode('utf-8')

    # Remove 'DEBUG mode' at first line of output and new line at end of string
    output = os.linesep.join(output.split(os.linesep)[1:-1])

    exit_code = process.wait()    
    return {
        'error_code': exit_code, 
        'output': output
    }

def assert_program_out(assert_method, prog_out):
    if prog_out['error_code'] != 0:
        if 'error_code' in assert_method:
            return assert_method['error_code'] == prog_out['error_code']
        return False

    if 'error_code' in assert_method:
            return assert_method['error_code'] == prog_out['error_code']

    if 'text' in assert_method:
        return assert_method['text'] == prog_out['output']

    return False


def parse_tests(tests_path):
    tests = {}
    with open(tests_path, 'r') as f:
        tests = json.load(f)

    return tests

def read_config_from_args():
    config = dict(default_config)

    pass_current = False
    for arg, val in zip(sys.argv[:-1], sys.argv[1:]):
        if pass_current:
            pass_current = False
            continue

        arg = arg.lstrip('-')
        if arg in config:
            config[arg] = val
            pass_current = True

    return config


def main(config):
    print('Looking for executable...', end=' ')

    exists = os.path.isfile(config['program'])
    if not exists:
        raise FileNotFoundError('program filepath is not valid')

    print('Done.')

    print('Looking for tests...', end=' ')

    exists = os.path.isfile(config['tests_file'])
    if not exists:
        raise FileNotFoundError('tests filepath is not valid')

    print('Done.')

    print('Parsing tests file...', end=' ')
    tests = parse_tests(config['tests_file'])
    print('Done.')

    print('Running tests...\n')

    run_tests(tests, config)

    print('\nDone.')

if __name__ == '__main__':
    try:
        config = read_config_from_args()

        main(config)
    except Exception as e:
        print('Error')
        print(str(e))


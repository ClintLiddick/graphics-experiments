#!/usr/bin/env python3

import argparse
import subprocess


def file_package_path_from_filename(filename):
    result = subprocess.run(
        ['bazel', 'query', filename],
        check=True,
        stdout=subprocess.PIPE,
        universal_newlines=True)
    return result.stdout.strip()


def target_from_path(file_pkg_path):
    if file_pkg_path.endswith('hh'):
        attr = 'hdrs'
    else:
        attr = 'srcs'

    package_matcher = file_pkg_path.split(':')[0] + ':*'
    result = subprocess.run(
            ['bazel', 'query', 
                'attr("{}", {}, {})'.format(attr, file_pkg_path, package_matcher)],
            check=True,
            stdout=subprocess.PIPE,
            universal_newlines=True)
    return result.stdout.splitlines()[0].strip()


def print_action(target):
    result = subprocess.run(
            ['bazel', 'print_action', '--print_action_mnemonics=CppCompile', target],
            check=True,
            stdout=subprocess.PIPE,
            universal_newlines=True)
    return result.stdout



if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('filename')
    args = parser.parse_args()

    file_pkg_path = file_package_path_from_filename(args.filename)
    target = target_from_path(file_pkg_path)
    action_proto_str = print_action(target)
    print(action_proto_str)


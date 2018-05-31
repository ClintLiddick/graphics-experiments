#!/usr/bin/env python3

import argparse
import subprocess

from third_party.bazel.proto.extra_actions_base_pb2 import ExtraActionSummary, CppCompileInfo
import google.protobuf.text_format as text_format

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

def cpp_compile_info_from_proto(extra_action_summary):
    action = extra_action_summary.action[0].action
    return action.Extensions[CppCompileInfo.cpp_compile_info]

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('filename')
    args = parser.parse_args()

    file_pkg_path = file_package_path_from_filename(args.filename)
    target = target_from_path(file_pkg_path)
    action_proto_str = print_action(target)
    extra_action_summary = ExtraActionSummary()
    text_format.Merge(action_proto_str, extra_action_summary)
    cpp_compile_info = cpp_compile_info_from_proto(extra_action_summary)
    print(cpp_compile_info.compiler_option)
    print(cpp_compile_info.sources_and_headers)

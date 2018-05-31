import os
import subprocess


def DirectoryOfThisScript():
    path = os.path.dirname(os.path.abspath(__file__))
    if not path.endswith('/'):
        path += '/'
    return path


ROOT_DIR = DirectoryOfThisScript()


def FlagsForFile(filename, **kwargs):
    filename = filename.replace(ROOT_DIR, '')
    result = subprocess.run(
        ['./bazel-bin/tools/completions', filename],
        cwd=ROOT_DIR,
        check=True,
        universal_newlines=True,
        stderr=subprocess.DEVNULL,
        stdout=subprocess.PIPE)
    compile_flags = result.stdout.splitlines()
    compile_flags = [flag.strip() for flag in compile_flags]

    if not compile_flags:
        return None

    return {
        'flags': compile_flags,
        'do_cache': False,
        'include_paths_relative_to_dir': ROOT_DIR,
    }

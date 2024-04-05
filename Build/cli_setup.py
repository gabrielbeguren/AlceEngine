from distutils.core import setup
import py2exe
import sys
import os

sys.argv.append('py2exe')

script_dir = os.path.dirname(os.path.abspath(__file__))

setup(
    options={'py2exe': {'bundle_files': 1, 'dist_dir': script_dir}},
    console=[{'script': 'cli.py', 'dest_base': 'alce'}],
    zipfile=None,
    dist_dir=script_dir
)

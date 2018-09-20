#!/bin/bash

################################################################################################################################################################

# @project        Library/Mathematics
# @file           tools/python/helpers/debug.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

gdb `which python`
# gdb `which python3`

# gdb `which python` --args /home/jovyan/notebooks/A.py

# set args /home/jovyan/notebooks/A.py
# set args /app/bindings/python/test/Library/Mathematics/Geometry.py
# set args /app/bindings/python/test/Library/Mathematics/Geometry/D2/Objects/Point.py
# set args /app/bindings/python/test/test.py

popd > /dev/null

################################################################################################################################################################
#! /bin/bash

touch origin.mips
python format_instructions.py
python mips.py
python dismips.py



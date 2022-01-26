# -*- coding: UTF-8 -*-
"""
concat mulitple output command into one json file
"""
import json
import sys
import fileinput
import argparse
p = argparse.ArgumentParser()
p.add_argument('-i', nargs='?', type=argparse.FileType(), default=sys.stdin)
p.add_argument('-o', type=str)
args = p.parse_args()

out_json = []
for input_file in args.i.readlines():
    input_file = input_file.strip()
    with open(input_file) as f:
        tmp_json = json.load(f)
        out_json.append(tmp_json)
with open(args.o, "w") as fout:
    json.dump(out_json, fout)

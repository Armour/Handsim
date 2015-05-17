#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

import re
from disassembleDict import *

command = []

def handle(target, PC):
    if target[0] == '0':
        return PC + int(target, 2) + 1
    else:
        return PC - int(bin(int(target[1:], 2) - 1).replace('1', '_').replace('0', '1').replace('_', '0')[2:], 2) + 1

def R_type(line):
    if R_dict[line[-6:]][0] == 0:
        return R_dict[line[-6:]][1] + ' ' + code[line[16:21]] + ', ' + code[line[6:11]] + ', ' + code[line[11:16]]
    elif R_dict[line[-6:]][0] == 1:
        return R_dict[line[-6:]][1] + ' ' + code[line[6:11]] + ', ' + code[line[11:16]]
    elif R_dict[line[-6:]][0] == 2:
        return R_dict[line[-6:]][1] + ' ' + code[line[6:11]]
    elif R_dict[line[-6:]][0] == 3:
        return R_dict[line[-6:]][1] + ' ' + code[line[16:21]] + ', ' + code[line[11:16]] + ', ' + code[line[6:10]]
    elif R_dict[line[-6:]][0] == 4:
        return R_dict[line[-6:]][1] + ' ' + code[line[16:21]] + ', ' + code[line[11:16]] + ', ' + str(int(line[21:26], 2))
    elif R_dict[line[-6:]][0] == 5:
        return R_dict[line[-6:]][1] + ' ' + code[line[16:21]]
    elif R_dict[line[-6:]][0] == 6:
        return R_dict[line[-6:]][1] + ' ' + code[line[16:21]] + ', ' + code[line[6:11]]
    elif R_dict[line[-6:]][0] == 7:
        return R_dict[line[-6:]][1]

def I_type(line, PC):
    if I_dict[line[0:6]][0] == 0:
        return I_dict[line[0:6]][1] + ' ' + code[line[11:16]] + ', ' + str(int(line[16:], 2)) + '(' + code[line[6:11]] + ')'
    elif I_dict[line[0:6]][0] == 1:
        return I_dict[line[0:6]][1] + ' ' + code[line[6:11]] + ', ' + 'mark_' + str(handle(line[16:], PC/4))
    elif I_dict[line[0:6]][0] == 2:
        return I_dict[line[0:6]][1] + ' ' + code[line[6:11]] + ', ' + code[line[11:16]] + ', mark_' + str(handle(line[16:], PC/4))
    elif I_dict[line[0:6]][0] == 3:
        return I_dict[line[0:6]][1] + ' ' + code[line[11:16]] + ', ' + code[line[6:11]] + ', ' + str(int(line[16:], 2))
    elif I_dict[line[0:6]][0] == 4:
        return I_dict[line[0:6]][1] + ' ' + code[line[11:16]] + ', ' + code[line[6:11]]

def J_type(line):
    return J_dict[line[0:6]] + ' mark_' + str(int(line[6:], 2))

def first_time_handle():
    PC = 0
    with open('machineCode.txt', 'r+') as data:
        for line in data:
            line = line.rstrip()
            if line[0:6] == '000000':
                res = R_type(line)
            elif line[0:6] in I_dict:
                res = I_type(line, PC)
            elif line[0:6] in J_dict:
                res = J_type(line)
            command.append(res)
            PC += 4
    return PC / 4

def second_time_handle(totalLine):
    l = []
    for i in range(totalLine):
        for cmd in command:
            if 'mark_' + str(i) in cmd:
                l.append(i)
    for i in range(totalLine):
        if (i in l):
            command[i] = 'mark_' + "{0: <4}".format(i) + ':   ' + command[i]
        else:
            command[i] = '             ' + command[i]

def print_command():
    with open('disassembleCode.txt', 'w+') as output:
        for line in command:
            output.write(line + '\n')

def main():
    totalLine = first_time_handle()
    second_time_handle(totalLine)
    print_command()

if __name__ == '__main__':
    main()

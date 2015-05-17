#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

import re
from assembleDict import *
from formatDict import addr

dict_mark = {}  # 用于map标记与内存坐标的对应关系
command = []  # 存储命令

def handle_j(target, PC): #用来处理j类里面后面的target数值，优先看是否存在于标记中
    if target in dict_mark:
        return dict_mark[target]
    else:
        return int(target, 0)

def handle_i(target, PC): #用来处理i类里面后面的target数值
    if target in dict_mark:
        tmp = dict_mark[target] - PC/4 - 1
        if tmp >= 0:
            return "{0:0>16d}".format(int(bin(tmp)[2:]))[-16:]
        else:
            return str(bin(int("1" + ("{0:0>15d}".format(int(bin(-tmp)[2:]))).replace('1', '_').replace('0', '1').replace('_', '0'),2) + 1)[2:])

def check_pseudo(cmd, PC):
    pseudo = cmd;
    arr = cmd.split();
    if arr[0] == 'move':
        pseudo = 'add ' + arr[1] + ' ' + arr[2] + ' $zero'
    elif arr[0] == 'blt':
        command.append('slt $at ' + arr[1] + ' ' + arr[2])
        pseudo = 'bne $at $zero ' + arr[3]
        PC += 4
    elif arr[0] == 'bgt':
        command.append('slt $at ' + arr[2] + ' ' + arr[1])
        pseudo = 'bne $at $zero ' + arr[3]
        PC += 4
    elif arr[0] == 'ble':
        command.append('slt $at ' + arr[2] + ' ' + arr[1])
        pseudo = 'beq $at $zero ' + arr[3]
        PC += 4
    elif arr[0] == 'bge':
        command.append('slt $at ' + arr[1] + ' ' + arr[2])
        pseudo = 'beq $at $zero ' + arr[3]
        PC += 4
    elif arr[0] == 'abs':
        command.append('sra $at ' + arr[2] + ' 31')
        command.append('xor ' + arr[1] + ' ' + arr[2] + ' $at')
        pseudo = 'sub ' + arr[1] + ' ' + arr[2] + ' $at'
        PC += 8
    return (pseudo, PC)

def first_time_handle():
    PC = 0  # 当前内存坐标
    with open('format.txt', 'r+') as test:
        for line in test:
            if line != '\n':  # 空行
                if '#' in line:  # 注释
                    tmp = line.split('#')
                    commment = tmp[-1]
                    line = tmp[0]
                if ':' in line:  # 标记
                    tmp = line.split(':')
                    mark = tmp[0]
                    body = tmp[1].strip()
                    dict_mark[mark] = PC/4  # 将标记的位置map到dict中
                else:
                    body = line.strip()

                body = re.sub(' +', ' ', body)  # 将多个空格合为一个空格
                body = re.sub('\$ +', '$', body)  # 将$后误输入的空格清空
                body = re.sub(' *\, *', ' ', body)  # 将,以及其前后的空格各位一个空格
                body = re.sub(
                    ' *\([ ]*(?P<cmd>\$[a-z0-9A-Z]+)[ ]*\)',
                    ' \g<cmd>',
                    body)  # 处理圆括号内容,将有圆括号且内开头为$的值提取出来

                PC += 4
                body = body.lower()
                body, PC = check_pseudo(body, PC)
                command.append(body)

def R_type(arr):
    if R_dict[arr[0]][0] == 0:
        return '000000' + code[arr[2]] + code[arr[3]] + code[arr[1]] + '00000' + R_dict[arr[0]][1]
    elif R_dict[arr[0]][0] == 1:
        return '000000' + code[arr[1]] + code[arr[2]] + '00000' + '00000' + R_dict[arr[0]][1]
    elif R_dict[arr[0]][0] == 2:
        return '000000' + code[arr[1]] + '00000' + '00000' + '00000' + R_dict[arr[0]][1]
    elif R_dict[arr[0]][0] == 3:
        return '000000' + code[arr[3]] + code[arr[2]] + code[arr[1]] + '00000' + R_dict[arr[0]][1]
    elif R_dict[arr[0]][0] == 4:
        return '000000' + '00000' + code[arr[2]] + code[arr[1]] + code[arr[3]] + R_dict[arr[0]][1]
    elif R_dict[arr[0]][0] == 5:
        return '000000' + '00000' + '00000' + code[arr[1]] + '00000' + R_dict[arr[0]][1]
    elif R_dict[arr[0]][0] == 6:
        return '000000' + code[arr[2]] + '00000' + code[arr[1]] + '00000' + R_dict[arr[0]][1]
    elif R_dict[arr[0]][0] == 7:
        return '000000' + '00000' + '00000' + '00000' + '00000' + R_dict[arr[0]][1]

def I_type(arr, PC):
    if I_dict[arr[0]][0] == 0:
        return I_dict[arr[0]][1] + code[arr[3]] + code[arr[1]] + "{0:0>16b}".format(int(eval(arr[2])))
    elif I_dict[arr[0]][0] == 1:
        return I_dict[arr[0]][1] + code[arr[1]] + I_dict[arr[0]][2] + str(handle_i(str(arr[3]), PC))
    elif I_dict[arr[0]][0] == 2:
        return I_dict[arr[0]][1] + code[arr[1]] + code[arr[2]] + str(handle_i(str(arr[3]), PC))
    elif I_dict[arr[0]][0] == 3:
        return I_dict[arr[0]][1] + code[arr[2]] + code[arr[1]] + "{0:0>16b}".format(int(eval(arr[3])))
    elif I_dict[arr[0]][0] == 4:
        return I_dict[arr[0]][1] + '00000' + code[arr[1]] + "{0:0>16b}".format(int(eval(arr[2])))

def J_type(arr, PC):
    return J_dict[arr[0]] + "{0:0>26b}".format(int(handle_j(str(arr[1]), PC)))

def second_time_handle():
    PC = 0  # 当前内存坐标
    with open('machineCode.txt', 'w+') as output:
        for sentence in command:
            arr = sentence.split()
            if arr[0] in R_dict.keys():
                res = R_type(arr)
            elif arr[0] in I_dict.keys():
                res = I_type(arr, PC)
            elif arr[0] in J_dict.keys():
                res = J_type(arr, PC)
            output.write(res + '\n')
            PC += 4

def main():
    first_time_handle()
    second_time_handle()

if __name__ == '__main__':
   main()

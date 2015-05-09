#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

import re
from assembleDict import *

dict_mark = {}  # 用于map标记与内存坐标的对应关系
command = []  # 存储命令

def handle_j(offset, PC): #用来处理j类里面后面的offset数值，优先看是否存在于标记中
    if (offset in dict_mark):
        return int(dict_mark[offset])
    else:
        return (int(offset, 0) << 2) + PC

def first_time_handle():
    PC = 0  # 当前内存坐标
    with open('test.txt', 'r+') as test:
        for line in test:
            if line != '\n':  # 空行
                if ('#' in line):  # 注释
                    tmp = line.split('#')
                    commment = tmp[-1]
                    line = tmp[0]
                if (':' in line):  # 标记
                    tmp = line.split(':')
                    mark = tmp[0]
                    body = tmp[1].strip()
                    dict_mark[mark] = PC  # 将标记的位置map到dict中
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
                command.append(body)

def R_type(category, arr):
    return {
        0: '000000' + code[arr[2]] + code[arr[3]] + code[arr[1]] + '00000' + R_dict[arr[0]][1],
        1: '000000' + code[arr[1]] + code[arr[2]] + '00000' + '00000' + R_dict[arr[0]][1],
        2: '000000' + code[arr[1]] + '00000' + '00000' + '00000' + R_dict[arr[0]][1],
        3: '000000' + code[arr[3]] + code[arr[2]] + code[arr[1]] + '00000' + R_dict[arr[0]][1],
        4: '000000' + '00000' + code[arr[2]] + code[arr[1]] + code[arr[3]] + R_dict[arr[0]][1],
        5: '000000' + '00000' + '00000' + code[arr[1]] + '00000' + R_dict[arr[0]][1],
        6: '000000' + code[arr[2]] + '00000' + code[arr[1]] + '00000' + R_dict[arr[0]][1],
        7: '000000' + '00000' + '00000' + '00000' + '00000' + R_dict[arr[0]][1]
    }.get(category, '')

def I_type(arr, PC):
    if I_dict[arr[0]][0] == 0:
        return I_dict[arr[0]][1] + code[arr[3]] + code[arr[1]] + "{0:0>16b}".format(int(eval(arr[2])))
    elif I_dict[arr[0]][0] == 1:
        return I_dict[arr[0]][1] + code[arr[1]] + I_dict[arr[0]][2] + "{0:0>16b}".format(handle_j(str(arr[3]), PC))
    elif I_dict[arr[0]][0] == 2:
        return I_dict[arr[0]][1] + code[arr[1]] + code[arr[2]] + "{0:0>16b}".format(handle_j(str(arr[3]), PC))
    elif I_dict[arr[0]][0] == 3:
        return I_dict[arr[0]][1] + code[arr[2]] + code[arr[1]] + "{0:0>16b}".format(int(eval(arr[3])))
    elif I_dict[arr[0]][0] == 4:
        return I_dict[arr[0]][1] + '00000' + code[arr[1]] + "{0:0>16b}".format(int(eval(arr[2])))

def J_type(arr, PC):
    return J_dict[arr[0]] + "{0:0>26b}".format(handle_j(str(arr[1]), PC))

def second_time_handle():
    PC = 0  # 当前内存坐标
    with open('out', 'w+') as output:
        for sentence in command:
            arr = sentence.split()
            if arr[0] in R_dict.keys():
                res = R_type(R_dict[arr[0]][0], arr)
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

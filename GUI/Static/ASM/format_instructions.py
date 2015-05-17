import re

def scan_txt():
    offset = 0
    PC = -4
    dotd = 0
    dott = 0
    dotg = 0
    with open('origin.txt', 'r+') as file:
        with open('format.txt', 'w+') as output:
            with open('formatDict.py', 'w+') as lists:
                lists.write('addr = {\n')
                for line in file:
                    # print '++++ ',line
                    if line != '\n':
                        line = line.strip()
                        # print '--- ',line
                        if '.' in line:
                            if line[1] == 't':
                                dotg = 0
                                dotd = 0
                                dott = 1
                                continue
                            elif line[1] == 'g':
                                dotg = 1
                                dotd = 0
                                dott = 0
                                continue
                            elif line[1] == 'd':
                                PC += 4
                                output.write('la $s7,31\n')
                                dotg = 0
                                dotd = 1
                                dott = 0
                                continue
                        if dotd == 1:
                            if '#' in line:
                                line, line_ex = line.split('#', 1)
                            if ':' in line:
                                str_def, str_ctt = line.split(':', 1)
                                # str1 get the name of the parameters
                                str_def = str_def.strip()
                                lists.write(
                                    "'" + str_def + "':'" + str(31 + offset) + "',\n")
                                str_ctt = str_ctt.strip()
                                str_typ, str_val = str_ctt.split(' ', 1)
                                str_val = str_val.strip()
                                str_val = str_val.split(',')
                                for i in range(0, len(str_val)):
                                    PC += 8
                                    # print 'addi $s0,$zero,',str_val[i].strip()
                                    # print 'sw $s0,',PC
                                    output.write(
                                        'addi $s0,$zero,' +
                                        str_val[i].strip() +
                                        '\n')
                                    output.write(
                                        'sw $s0,' +
                                        str(offset) +
                                        '($s7)\n')
                                    offset -= 1
                                # if str_typ in data_type
                                #  pass
                                # else
                                #  break
                        elif dotg == 1:
                            # print line
                            output.write(line + '\n')
                        else:
                            pass
                lists.write('}\n')

def main():
    scan_txt()

if __name__ == '__main__':
    main()

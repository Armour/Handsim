import re

def scan_mips():
  mem_addr = 32;
  dotd = 0
  dott = 0
  dotg = 0
  with open('origin.txt','r+') as file:
    with open('memory.txt','w+') as fm:
      with open('formatDict.py','w+') as lists:
        with open('format.txt','w+') as mips:
          lists.write('addr = {\n')
          for line in file:
            if line != '\n':
              line = line.strip()
              if '.' in line:
                if line[1] == 't':
                  dotg = 0
                  dott = 1
                  dotd = 0
                  continue
                elif line[1] == 'g':
                  dotg = 1
                  dott = 0
                  dotd = 0
                  continue
                elif line[1] == 'd':
                  dotg = 0
                  dott = 0
                  dotd = 1
                  continue
            if dotd == 1:
              if '#' in line:
                line, line_ex = line.split('#',1)
              if ':' in line:
                str_def, str_ctt = line.split(':',1)
                str_def = str_def.strip()
                lists.write("'"+str_def+"':'"+str(mem_addr-1)+"',\n")
                str_ctt = str_ctt.strip()
                str_typ, str_val = str_ctt.split(' ',1)
                str_val = str_val.strip()
                str_val = str_val.split(',');
                for i in range(0,len(str_val)):
                  mem_addr -= 1
                  fm.write(str(mem_addr)+' '+str_val[i].strip()+'\n')
            elif dotg == 1:
              mips.write(line+'\n')
        lists.write('}\n')

def main():
  scan_mips()

if __name__ == '__main__':
   main()

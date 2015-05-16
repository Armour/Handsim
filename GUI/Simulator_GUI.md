# Simulator GUI Specification
![alt text](Outlook.png)
## Techs:
1. The language is C++;
2. The GUI uses Qt5;

## Classes:
* MainWindow: to hold the whole GUI;
* Bash: to provide an area for MIPS code inputting;
* McCode: to provide an area to display machine code converted from MIPS instructions in bash;
* Memory: to display the memory
* RegInfo: to display the content in each register

## Usage:
### 1. Import a MIPS file
  * click the leftest button in the toolbar, select a txt file which contains MIPS instructions, and import it;
  * the MIPS code in the chosen txt file would be displayed in the bash, while the old code in the bash would be cleaned out;

### 2. Save a file
  * click the second leftest button in the toolbar, select a directory and input the filename, then save it;
  * the code in the bash would be saved into the file you designated;

### 3. Commit
  * after your coding in the bash, click the second rightest button in the toolbar;
  * the code would be assembled and executed by the simulator;
  * the result, including the condition in the memory and the result in the registers, would be displayed in the corresponding area;

### 4. Clear
  * click the rightest button in the toolbar. The bash, machine code, memory and the registers would be clean to their initial values

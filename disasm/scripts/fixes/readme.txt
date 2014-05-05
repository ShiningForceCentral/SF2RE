Those scripts were written to fix some IDA 68k module bugs which prevent the disassembly to be re-assembled properly.

Most of them have been used only once on the disassembly
But as we format new code, the same bugs can appear again. 
If the assembler displays errors about addressing mode on an instruction, just run the releated script on the disassembly again.

Be aware that the script starts analyzing the disassembly from your current cursor position.

Use the cancel button in dialog boxes to stop the script analysis.
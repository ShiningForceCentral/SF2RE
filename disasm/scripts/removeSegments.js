UltraEdit.activeDocument.findReplace.find("; end of 'ROM'");

UltraEdit.activeDocument.gotoLine(UltraEdit.activeDocument.currentLineNum + 1, 0);

UltraEdit.activeDocument.selectToBottom ();

UltraEdit.activeDocument.deleteText();

UltraEdit.activeDocument.write("\n\tEND");

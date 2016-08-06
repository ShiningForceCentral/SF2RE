SF2RE
=====

Collaborative work on reverse-engineering Shining Force II.

The main purposes of SF2RE are :
- to reverse-engineer Shining Force II with IDA Pro,
- to share disassembly content with IDA Pro IDC scripts,
- and ultimately, to produce as a result SF2DISASM's content : a split disassembly which can build back into the original game, while offering as much flexibility as possible for new games, hacks and mods based on Shining Force II. 


Naming conventions :
- Functions : DoSomethingLikeThis
- Rom Data Locations : DataChunkLikeThat
Disambiguation is made by the way they are accessed : functions are
branched or jumped into while data is pointed to, moved, etc.
- Enums : ENUM_VALUE_LIKE_THIS
- RAM locations : RAM_LOCATION_LIKE_THAT
Once again, disambiguation is obvious since enums are used as immediate
values while RAM locations are pointed to, moved, etc.


Disasm folder organization :
The main goal is to clarify the game's data organization and creation
process by reflecting them in the folder structure.
- Most data is considered as assets and are gathered by type for a
bottom-up approach : graphics, sound, scripting, etc., need to be
created first in order to use them in maps, battles, cutscenes.
- In an opposite top-down approach, battles and maps are organized in an
"entry-oriented" way, to make each entry contain all that is specific to
the entry.
Editors can then edit assets individually, and point to them while
editing battle or map entries.
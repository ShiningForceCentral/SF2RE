mkdir disasm

mkdir disasm\code
mkdir disasm\code\gameflow
mkdir disasm\code\gameflow\start
mkdir disasm\code\gameflow\exploration
mkdir disasm\code\gameflow\exploration\vints
mkdir disasm\code\gameflow\battle
mkdir disasm\code\gameflow\battle
mkdir disasm\code\gameflow\battle\vints
mkdir disasm\code\gameflow\battle\battlescenes
mkdir disasm\code\gameflow\battle\battlescenes\spells
mkdir disasm\code\gameflow\battle\specialsprites
mkdir disasm\code\gameflow\battle\ai
mkdir disasm\code\gameflow\end
mkdir disasm\code\gameflow\special
mkdir disasm\code\common
mkdir disasm\code\common\tech
mkdir disasm\code\common\tech\interrupts
mkdir disasm\code\common\tech\sram
mkdir disasm\code\common\tech\sound
mkdir disasm\code\common\tech\graphics
mkdir disasm\code\common\maps
mkdir disasm\code\common\items
mkdir disasm\code\common\stats
mkdir disasm\code\common\stats\allies
mkdir disasm\code\common\stats\enemies
mkdir disasm\code\common\menus\
mkdir disasm\code\common\menus\main
mkdir disasm\code\common\menus\shop
mkdir disasm\code\common\menus\church
mkdir disasm\code\common\menus\caravan
mkdir disasm\code\common\menus\blacksmith
mkdir disasm\code\common\windows
mkdir disasm\code\common\scripting
mkdir disasm\code\common\scripting\entity
mkdir disasm\code\common\scripting\map
mkdir disasm\code\common\scripting\text
mkdir disasm\code\specialscreens
mkdir disasm\code\specialscreens\segalogo
mkdir disasm\code\specialscreens\title
mkdir disasm\code\specialscreens\witch
mkdir disasm\code\specialscreens\suspend
mkdir disasm\code\specialscreens\endkiss
mkdir disasm\code\specialscreens\credits
mkdir disasm\code\specialscreens\witchend
mkdir disasm\code\specialscreens\jewelend

mkdir disasm\data
mkdir disasm\data\battles
mkdir disasm\data\battles\global
mkdir disasm\data\battles\entries
FOR /L %%G IN (0,1,9) DO mkdir disasm\data\battles\entries\battle0%%G
FOR /L %%G IN (10,1,44) DO mkdir disasm\data\battles\entries\battle%%G
mkdir disasm\data\maps
mkdir disasm\data\maps\global
mkdir disasm\data\maps\entries
FOR /L %%G IN (0,1,9) DO mkdir disasm\data\maps\entries\map0%%G
FOR /L %%G IN (10,1,78) DO mkdir disasm\data\maps\entries\map%%G
FOR /L %%G IN (0,1,9) DO mkdir disasm\data\maps\entries\map0%%G\mapsetups
FOR /L %%G IN (10,1,78) DO mkdir disasm\data\maps\entries\map%%G\mapsetups
mkdir disasm\data\scripting
mkdir disasm\data\scripting\text
mkdir disasm\data\scripting\entity
mkdir disasm\data\scripting\map

mkdir disasm\layout

mkdir disasm\data\stats
mkdir disasm\data\stats\allies
mkdir disasm\data\stats\allies\growths
mkdir disasm\data\graphics
mkdir disasm\data\graphics\mapsprites
mkdir disasm\data\graphics\portraits
mkdir disasm\data\graphics\battles
mkdir disasm\data\graphics\battles\grounds
mkdir disasm\data\graphics\battles\backgrounds
mkdir disasm\data\graphics\battles\weapons
mkdir disasm\data\graphics\battles\battlesprites
mkdir disasm\data\graphics\battles\battlesprites\allies
mkdir disasm\data\graphics\battles\battlesprites\allies\animations
mkdir disasm\data\graphics\battles\battlesprites\enemies
mkdir disasm\data\graphics\battles\battlesprites\enemies\animations
mkdir disasm\data\graphics\battles\spells
mkdir disasm\data\graphics\battles\spells\invocations
mkdir disasm\data\graphics\battles\spells\animations
pause
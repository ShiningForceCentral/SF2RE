mkdir battles
mkdir battles\global
mkdir battles\entries
FOR /L %%G IN (0,1,9) DO mkdir battles\entries\battle0%%G
FOR /L %%G IN (10,1,44) DO mkdir battles\entries\battle%%G
mkdir maps
mkdir maps\global
mkdir maps\entries
FOR /L %%G IN (0,1,9) DO mkdir maps\entries\map0%%G
FOR /L %%G IN (10,1,78) DO mkdir maps\entries\map%%G
FOR /L %%G IN (0,1,9) DO mkdir maps\entries\map0%%G\mapsetups
FOR /L %%G IN (10,1,78) DO mkdir maps\entries\map%%G\mapsetups
mkdir scripting
mkdir scripting\entityactscripts
mkdir scripting\mapscripts
mkdir scripting\cutscenes
pause
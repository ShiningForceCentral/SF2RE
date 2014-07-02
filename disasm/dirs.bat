mkdir asmscripts
mkdir asmscripts\battlecutscenes
FOR /L %%G IN (0,1,9) DO mkdir asmscripts\battlecutscenes\battle0%%G
FOR /L %%G IN (10,1,43) DO mkdir asmscripts\battlecutscenes\battle%%G
mkdir asmscripts\mapsetups
FOR /L %%G IN (0,1,9) DO mkdir asmscripts\mapsetups\map0%%G
FOR /L %%G IN (10,1,78) DO mkdir asmscripts\mapsetups\map%%G
pause
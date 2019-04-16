del *.sdf /s /q

rd /q /s ipch

del /s /q *.tlog
del /s /q *.obj
del /s /q *.manifest
del /s /q *.log
del /s /q *.pch
del /s /q *.res
del /s /q *.idb
del /s /q *.pdb
del /s /q *.lastbuildstate
del /s /q *.cache
del /s /q *_manifest.rc
del /s /q *.exe

CD debug
del *.* /s /q


exit
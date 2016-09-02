@echo ==================================
@echo SET VisualStudio PATH
@echo ==================================
call "%VS110COMNTOOLS%\vsvars32.bat

@echo ==================================
@echo Clean VisualStudio Solution
@echo ==================================
devenv TestDebugDll.sln /Clean Debug
devenv TestDebugDll.sln /Clean Release
rmdir Debug /s /q
rmdir Release /s /q
rmdir CreateDll\Debug /s /q
rmdir CreateDll\Release /s /q
rmdir DebugDll\Debug /s /q
rmdir DebugDll\Release /s /q
del *.sdf
del *.log
rmdir ipch /s /q

PAUSE
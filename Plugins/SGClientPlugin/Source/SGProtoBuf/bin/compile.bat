@echo off

setlocal enabledelayedexpansion

for /r %%i in (*.pb) do (
    set pbFileRealName=%%~nxi
    set pbFileNoExtension=!pbFileRealName:~0,-3!.proto
    ConvertPbToProto.exe !pbFileRealName! !pbFileNoExtension!
)

@echo on
for /r %%i in (*.proto) do (
    protoc.exe -I=./ --cpp_out=dllexport_decl=SGPROTOBUF_API:./ ./%%~nxi
)
move /Y  .\*.pb.h ..\Public
move /Y  .\*.pb.cc ..\Private


for /r %%i in (*.proto) do (
    del %%~nxi
)
echo "Finished."

pause
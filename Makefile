CPP = cl
OBJ_LIST = main.obj utils.obj

build: main.exe

main.exe: $(OBJ_LIST)
    $(CPP) /Fe$@ $**

clean:
    del *.obj main.exe

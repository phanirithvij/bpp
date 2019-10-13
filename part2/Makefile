CPP = cl
OBJ_LIST = main.obj utils.obj hasher.obj

build: main.exe

main.exe: $(OBJ_LIST)
    $(CPP) /Fe$@ $**

clean:
    del *.obj

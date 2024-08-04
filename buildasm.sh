nasm -f win64 generated.asm -o generated.obj
# ld generated.obj -o generated.exe
GoLink /console generated.obj /fo generated.exe
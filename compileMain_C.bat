:: If di kasama exe at object files then need ito para organized 
if not exist dist mkdir dist
gcc -c src/saxpy_c.c -o dist/saxpy_c.obj -m64
nasm -f win64 src/saxpy_asm.asm -o dist/saxpy_asm.obj
gcc -c src/main.c -o dist/main.obj -m64
gcc dist/main.obj dist/saxpy_c.obj dist/saxpy_asm.obj -o dist/main.exe
dist\main.exe
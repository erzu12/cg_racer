cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build

rm compile_commands.json
compdb -p build/ list > compile_commands.json

make -C build -j8

printf "\n\n=============================================================================\n\n"

./build/gl_gui
#mangohud --dlsym build/spaceracer

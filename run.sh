cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build

rm compile_commands.json
compdb -p build/ list > compile_commands.json

make -C build

printf "\n\n=============================================================================\n\n"

#./build/spaceracer
mangohud --dlsym build/spaceracer

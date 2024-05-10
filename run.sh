cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DTARGET_GROUP=test -B build

rm compile_commands.json
compdb -p build/ list > compile_commands.json

cmake --build build
# make -C build -j8

printf "\n\n=============================================================================\n\n"

cd build/test

# Run the tests
ctest --output-on-failure

if [ $? -ne 0 ]; then
    printf "\n\n=============================================================================\n\n"
    printf "Tests failed\n"
    exit 1
fi

cd ../..

printf "\n\n=============================================================================\n\n"


./build/src/spaceracer
#mangohud --dlsym build/spaceracer

SOURCE_DIR=$HOME/programs/tinyrenderer/
BUILD_DIR=$HOME/cmake_build/tinyrenderer/
mkdir -p -v "$BUILD_DIR"

cd "$BUILD_DIR"
cmake -G "CodeBlocks - Unix Makefiles" -B "$BUILD_DIR" -S "$SOURCE_DIR" -DCMAKE_BUILD_TYPE=DEBUG
clion "$BUILD_DIR"
rm -rf tmp
rm -rf output
mkdir output
rm -rf build
mkdir build
cd build
cmake .. && make -j2
cp astar ../main

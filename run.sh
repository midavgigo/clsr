cmake .
read -n1 -r -p "Press any key to continue..." key
cmake --build .
read -n1 -r -p "Press any key to continue..." key
cd target
./server
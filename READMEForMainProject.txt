 make clean && cd .. && rm -rf build &&  mkdir build && cd build && cmake .. -DLLVM_DIR=$(llvm-config --cmakedir) && make 

cd /mnt/d/myfiles/mainProject/llvm-project/sample_tests/build

./regres-tblgen < ../input.td
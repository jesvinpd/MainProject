 make clean && cd .. && rm -rf build &&  mkdir build && cd build && cmake .. -DLLVM_DIR=$(llvm-config --cmakedir) && make 

cd /mnt/d/myfiles/mainProject/llvm-project/sample_tests/

cd /mnt/d/myfiles/mainProject/GeneratedExamplesTesting/graphPlotting/nonlinearPlot
//////////////////////////////////////////////////////////////////////////////////////////////\\\\\\\\\\



used commands for version change to 17th version: 
sudo apt update
sudo apt install wget gnupg lsb-release software-properties-common libzstd-dev
wget https://apt.llvm.org/llvm.sh
sudo chmod +x llvm.shA
sudo ./llvm.sh 17

After installation(worked for Sample_tests folder's ArithmeticOps.td): 
cd .. && rm -rf build &&  mkdir build && cd build && cmake .. -DLLVM_DIR=$(llvm-config-17 --cmakedir) && make

another error: in cmakelists.txt on  2nd line language 'C' should be added 
then it become "project(ArithTblgen LANGUAGES C CXX)".

another error: Target "arith-tblgen" links to target "zstd::libzstd_shared" but the target was not found.
fix is : sudo apt install libzstd-dev

After installation:
There will be a CMakeLists.txt file which contains the neccessary backend cpp files for code generation.
Using this txt file we create a build file and by using "make"
command it will create a "tablegen" in the build folder.
Using that and .td file (as an input)  we can generate our desired code.

For generation of code run:  ./arith-tblgen < ../ArithmeticOps.td

Then we will get the C program as the terminal output corresponding to the DSL content mentionedin the ".td" file.
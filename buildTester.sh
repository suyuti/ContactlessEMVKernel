mkdir -p build
cd build
rm -rf *
cmake ..
make
make TestRunner
cd test
cd Runner3
python tester.py -itestLog.json

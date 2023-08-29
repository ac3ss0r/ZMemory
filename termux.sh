rm -rf $HOME/ZMemory
mkdir $HOME/ZMemory
echo Copying files...
cp -r "$(dirname "$0")/source" $HOME/ZMemory
cp -r "$(dirname "$0")/include" $HOME/ZMemory
cp "$(dirname "$0")/Sample.cpp" $HOME/ZMemory
cp "$(dirname "$0")/Target.cpp" $HOME/ZMemory
echo Building ZMemory...
g++ $HOME/ZMemory/Sample.cpp -o sample
g++ $HOME/ZMemory/Target.cpp -o target
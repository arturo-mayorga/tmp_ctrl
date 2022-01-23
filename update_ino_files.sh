#!/bin/bash

MonitoredFileList=(
    [0]="src/*.cpp" 
    [1]="src/*.h")

copyFileToTargetDirs() {
    sourceFileName=$1
    cp -v $sourceFileName ./src/sketch_dec18a/
    cp -v $sourceFileName ./src/TRMO_demo/
    cp -v $sourceFileName ./src/SCR_demo/
    cp -v $sourceFileName ./src/ctrl_device/
}

declare -A FileToDateMap

loadModDateByFile() {
    echo "Scanning Source Files for Monitoring:"
    for i in ${MonitoredFileList[*]}; do
        dt=$(date -r $i)
        echo $i "    -->>    " $dt
        FileToDateMap[$i]=$dt
    done

    echo
    echo "Making Fresh Copy:"
    for i in ${MonitoredFileList[*]}; do
        copyFileToTargetDirs $i
    done
}

checkModifications() {
    for i in ${MonitoredFileList[*]}; do
        dt=$(date -r $i)
        oldDt=${FileToDateMap[$i]}
        if [[ "$oldDt" != "$dt" ]];
        then
            echo
            echo $i " was modified"
            FileToDateMap[$i]=$dt
            copyFileToTargetDirs $i
        fi
    done
}

loadModDateByFile

echo
echo "Monitoring Active; Press [CTRL+C] to stop..."

while :
do
    checkModifications
	sleep 5
done

echo


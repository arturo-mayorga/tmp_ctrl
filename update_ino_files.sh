#!/bin/bash

cd src

rm -v sketch_dec18a/*.cpp
rm -v sketch_dec18a/*.h

cp -v *.cpp sketch_dec18a/
cp -v *.h sketch_dec18a/

#####################

rm -v TRMO_demo/*.cpp
rm -v TRMO_demo/*.h

cp -v *.cpp TRMO_demo/
cp -v *.h TRMO_demo/

#####################

rm -v SCR_demo/*.cpp
rm -v SCR_demo/*.h

cp -v *.cpp SCR_demo/
cp -v *.h SCR_demo/

#####################

rm -v ctrl_device/*.cpp
rm -v ctrl_device/*.h

cp -v *.cpp ctrl_device/
cp -v *.h ctrl_device/

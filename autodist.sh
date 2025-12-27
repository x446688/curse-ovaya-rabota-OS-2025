#!/bin/bash
cp build/src/c2rn package/opt/c2rn-gui  
dpkg-deb --build package 

#!/bin/bash


cd ../Rivet-2.4.0/
make clean
cd -
cd ../YODA-1.5.5/
make clean
cd -

rm /home/rivet/Rivet/boost_1_56_0.tar.gz
sudo apt-get clean -y
sudo apt-get install texlive-base -y
sudo apt-get install --no-install-recommends  texlive-latex-extra -y
sudo apt-get install imagemagick -y

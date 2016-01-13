#!/bin/bash

cd ../Rivet-2.4.0/
make clean
cd -
cd ../YODA-1.5.5/
make clean
cd -

rm /home/rivet/Rivet/boost_1_56_0.tar.gz
sudo apt-get clean -y
sudo apt-get install --no-install-recommends texlive-base -y
sudo apt-get install --no-install-recommends texlive-latex-extra -y
sudo apt-get install --no-install-recommends texlive-latex-extra -y
sudo apt-get install --no-install-recommends ps2eps -y
sudo apt-get install --no-install-recommends texlive-extra-utils -y
sudo apt-get install --no-install-recommends texlive-font-utils -y
sudo apt-get install --no-install-recommends texlive-pstricks -y
sudo apt-get install --no-install-recommends texlive-latex-extra -y
sudo apt-get install --no-install-recommends texlive-fonts-recommended -y
sudo apt-get install imagemagick -y

wget https://users.hepforge.org/~holsch/7TeVZJets_short.hepmc.bz2

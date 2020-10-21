#/usr/bin/env sh
#
# Install the software needed for a build.
#
#*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
# 
# Copyright (c) 2015 Jeroen de Bruijn
# Copyright (c) 2020 Nahuel Espinosa
# 
# This file is part of MPLABX_Travis-CI_Example which is released under the
# MIT License (MIT).
# For full license details see file "LICENSE" or go to
# https://opensource.org/licenses/MIT
#
#*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
#
# Downloads the software from Microchip and saves them in a folder outside
# of the project directory. Than extracts and installs them.
# 
# Versions:
#  MPLAB® X IDE:         v5.30
#  MPLAB® XC8 Compiler:  v2.20
#

# Save the current working directory
pushd .

# Create a folder for the installation files.
mkdir ../install-dependencies
cd ../install-dependencies

### IDE
# Install MPLAB X IDE v5.30
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
echo "- Downloading MPLAB X IDE v5.30... +"
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
wget http://ww1.microchip.com/downloads/en/DeviceDoc/MPLABX-v5.30-linux-installer.tar
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"
echo "- Download finished...                          -"
echo "- Unpacking MPLABX-v5.30-linux-installer.tar... -"
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"
tar -xvf MPLABX-v5.30-linux-installer.tar
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"
echo "- Unpack finished...              -"
echo "- Installing MPLAB X IDE v5.30... -"
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"
sudo ./MPLABX-v5.30-linux-installer.sh -- --mode unattended
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"
echo "- Installation of MPLAB X IDE v5.30 finished... -"
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"
echo 

### Compiler
# Install MPLAB XC8 Compiler v2.20
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
echo "- Downloading MPLAB XC8 Compiler v2.20 +"
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
wget http://ww1.microchip.com/downloads/en/DeviceDoc/xc8-v2.20-full-install-linux-installer.run
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"
echo "- Download finished...        -"
echo "- Adding excecution rights... -"
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"
chmod +x xc8-v2.20-full-install-linux-installer.run
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"
echo "- Installing MPLAB XC8 Compiler v2.20 -"
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-"
sudo ./xc8-v2.20-full-install-linux-installer.run --mode unattended --netservername dontknow
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
echo "- Installation of MPLAB XC8 Compiler v2.20 finished... +"
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
echo 

# Return to the saved working directory
popd

echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"
echo "- All installations finished +"
echo "-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"

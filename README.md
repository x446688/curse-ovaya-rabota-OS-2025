# Setup

## Requirements: 
make, gcc, libopenssl, check, libgtk-3, pkg-config 

## Installation:

```sh
./autogen.sh
mkdir build
cd build
../configure
make
make check
make install
```

## Distribute (DEB):
If using a second build tree (which is recommended) with the build directory run ./autodist.sh to create a deb package.   
Alternatively you can run the following commands:
```sh
cp whatever_directory_the_binary_is_in/c2rn package/opt/c2rn-gui  
dpkg-deb --build package    
```
Installing the package requires apt or dpkg (in Astra Linux it's recommended to use apt instead of dpkg)
```sh 
sudo apt install ./package.deb   
```

## Tested environments:
- Astra Linux 1.6 SE
- Mac OS Tahoe 26.2

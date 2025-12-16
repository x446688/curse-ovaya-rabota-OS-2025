# Setup

#### Requirements: 
make, gcc, libopenssl, check, libgtk-3, pkg-config 

#### Installation:

```sh
./autogen.sh
mkdir build
cd build
../configure
make
make check
make install
```

#### Distribute (DEB):
```sh
cp whatever_directory_the_binary_is_in/c2rn package/DEBIAN/opt/c2rn-gui   
dpkg-deb --build package   
sudo apt install ./package.deb   
```

#### Tested environments:
- Astra Linux 1.6 SE
- Mac OS Tahoe 26.1

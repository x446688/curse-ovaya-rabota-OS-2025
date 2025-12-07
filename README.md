# Setup

#### Requirements: 
make, gcc, libopenssl, check, libgtk-3, pkg-config 

#### Installation:

```sh
cd src
./autogen.sh
mkdir build
cd build
../configure
make
make check
make install
```

#### Tested environments:
- Astra Linux 1.6 SE
- Mac OS Tahoe 26.1

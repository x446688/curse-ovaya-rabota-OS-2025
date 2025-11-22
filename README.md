# Setup

#### Requirements: 
make, gcc, libopenssl, libgtk-4, pkg-config, xterm 

#### Installation:

```sh
cd src
./autogen.sh
mkdir build
cd build
../configure
make
```

#### Tested environments:
- macOS Tahoe 26.1, arm64 (DOCKER + XQuartz)
- Astra Linux 1.6 SE

# NeuroRobot-Brain-framework

Repository contains framework for NeuroRobot-iOS app and guidelines how to build framework's libraries.    

Framework is used to simulate how the Brain works.  

Used 3rd party libraries:
- [opencv](https://opencv.org/) library, version `v4.1.1`  (followed [this repo](https://github.com/szanni/ios-autotools) to build it, with some modifications)  
- [matio](https://github.com/tbeu/matio) library  

## OpenCV

#### iOS

Download source from [this](https://opencv.org/releases/) link.    
Go to `/opencv-<version>/platforms/ios`  
Open terminal and run `./build_framework.py <outputdir>`, error may occurs because you don't have cmake.    
If you don't have cmake, run `brew install cmake`.  
run from build folder: `lipo -create -output ./libopencv_world.a ./build/build-arm64-iphoneos/install/lib/libopencv_world.a ./build/build-armv7-iphoneos/install/lib/libopencv_world.a ./build/build-armv7s-iphoneos/install/lib/libopencv_world.a ./build/build-i386-iphonesimulator/install/lib/libopencv_world.a ./build/build-x86_64-iphonesimulator/install/lib/libopencv_world.a`    
Header files are in `./build/build-arm64-iphoneos/install/include`

#### macOS

Download source from [this](https://opencv.org/releases/) link.    
Go to `/opencv-<version>/platforms/osx`  
Open terminal and run `./build_framework.py <outputdir>`, error may occurs because you don't have cmake.  
If you don't have cmake, run `brew install cmake`.  
change `"MACOSX_DEPLOYMENT_TARGET=10.9"` to `"MACOSX_DEPLOYMENT_TARGET=10.12"` in `./build_framework.py` [maybe]  
Lib files are in `./build/build-x86_64-macosx/install/lib`  
Header files are in `./build/build-x86_64-macosx/install/include`

## Matio

#### iOS

run `git clone git://git.code.sf.net/p/matio/matio`    
run `cd matio`  
run `brew install libtool` [maybe]  
run `brew install automake` [maybe]      
run `./autogen.sh`  
download `https://github.com/szanni/ios-autotools`  
make changes in `configure` [maybe not necessary]  
Edited code around line number 15542 in `configure` to pass tests if it's cross compiling. Edit is:    
```
if test ".$ac_cv_va_copy" = .; then
if test "$cross_compiling" = yes; then :
{ 
{
ac_cv_va_copy="C99" 
}
}
```
It was:
```
if test ".$ac_cv_va_copy" = .; then
if test "$cross_compiling" = yes; then :
{ { $as_echo "$as_me:${as_lineno-$LINENO}: error: in \`$ac_pwd':" >&5
$as_echo "$as_me: error: in \`$ac_pwd':" >&2;}
as_fn_error $? "cannot run test program while cross compiling
See \`config.log' for more details" "$LINENO" 5; }
```

paste `iconfigure` and `autoframework` from `ios-autotools` to matio root folder.  
In `iconfigure` change min iOS version (search for `-miphoneos-version-min`), e.g. `-miphoneos-version-min=10.3`.        
In `iconfigure` add `-fembed-bitcode` to the end of line where assigning `CFLAGS`.  
In `autoframework` add `lipo -create -output "$PREFIX/$LIBARCHIVE" $LIPOARCHS` line bellow another `lipo` command.  
run `PREFIX="--path--to--build--folder--" ARCHS="i386 x86_64 armv7 armv7s arm64" ./autoframework Matio libmatio.a`

#### macOS

run `git clone git://git.code.sf.net/p/matio/matio`    
run `cd matio`  
run `brew install libtool` [maybe]  
run `brew install automake` [maybe]      
run `./autogen.sh`  
run `./configure --prefix=<absolute path>`  
run `make`  
run `make install`  

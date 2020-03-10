#!/bin/bash

LIBIIO_BRANCH=master
LIBAD9361_BRANCH=master
LIBM2K_BRANCH=master
GRIIO_BRANCH=upgrade-3.8
GNURADIO_FORK=analogdevicesinc
GNURADIO_BRANCH=ming-3.8-clean
GRSCOPY_BRANCH=master
GRM2K_BRANCH=master
QWT_BRANCH=qwt-6.1-multiaxes
QWTPOLAR_BRANCH=master # not used
LIBSIGROK_BRANCH=master
LIBSIGROKDECODE_BRANCH=master #not used

PYTHON="python3 python"
PACKAGES="pkg-config qt cmake fftw bison gettext autoconf automake libtool libzip glib libusb $PYTHON"
PACKAGES="$PACKAGES glibmm doxygen wget boost@1.60 gnu-sed libmatio dylibbundler libxml2"

set -e
cd ~/projects/scopy
WORKDIR=${PWD}
NUM_JOBS=4

#brew update

brew_install_or_upgrade() {
	brew install $1 || \
		brew upgrade $1 || \
		brew ls --versions $1 # check if installed last-ly
}

brew_install() {
	brew install $1 || \
		brew ls --versions $1
}

for pak in $PACKAGES ; do
	brew_install $pak
done

for pkg in qt gcc bison gettext cmake; do
	brew link --overwrite --force $pkg
done

source ./CI/appveyor/before_install_lib.sh

QT_PATH="$(brew --prefix qt)/bin"
export PATH="${QT_PATH}:$PATH"
export PATH="/usr/local/bin:$PATH"
export PATH="/usr/local/opt/bison/bin:$PATH"
#export PATH="/usr/local/opt/icu4c/bin:$PATH"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/opt/libzip/lib/pkgconfig"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/opt/libffi/lib/pkgconfig"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/opt/glibmm/lib/pkgconfig"
#export PKG_CONFIG_PATH="/usr/local/opt/icu4c/lib/pkgconfig:$PKG_CONFIG_PATH"

pip3 install cheetah3
pip install cheetah

patch_qwtpolar_mac() {
	patch_qwtpolar

	patch -p1 <<-EOF
--- a/qwtpolarconfig.pri
+++ b/qwtpolarconfig.pri
@@ -16,7 +16,9 @@ QWT_POLAR_VER_PAT      = 1
 QWT_POLAR_VERSION      = \$\${QWT_POLAR_VER_MAJ}.\$\${QWT_POLAR_VER_MIN}.\$\${QWT_POLAR_VER_PAT}
 
 unix {
-    QWT_POLAR_INSTALL_PREFIX    = /usr/local/qwtpolar-\$\$QWT_POLAR_VERSION
+    QWT_POLAR_INSTALL_PREFIX    = $STAGINGDIR
+    QMAKE_CXXFLAGS              = -I${STAGINGDIR}/include
+    QMAKE_LFLAGS                = ${STAGINGDIR}/lib/libqwt*dylib
 }
 
 win32 {
EOF


	cat qwtpolarconfig.pri
}

## Get pip if not installed ; on Travis + OS X, Python is not well supported
#if ! command -v pip ; then
#	curl https://bootstrap.pypa.io/get-pip.py > get-pip.py
#	sudo -H python get-pip.py
#fi

QMAKE="$(command -v qmake)"

#pip3 install --user cheetah
cd ~

make_build_git "libsigrok" "https://github.com/sigrokproject/libsigrok" "" "" "./autogen.sh"

make_build_wget "libsigrokdecode-0.4.1" "http://sigrok.org/download/source/libsigrokdecode/libsigrokdecode-0.4.1.tar.gz"

qmake_build_git "qwt" "https://github.com/osakared/qwt.git" "qwt-6.1-multiaxes" "qwt.pro" "patch_qwt"

qmake_build_wget "qwtpolar-1.1.1" "https://downloads.sourceforge.net/project/qwtpolar/qwtpolar/1.1.1/qwtpolar-1.1.1.tar.bz2" "qwtpolar.pro" "patch_qwtpolar_mac"

cmake_build_wget "volk-1.3" "http://libvolk.org/releases/volk-1.3.tar.gz"

cmake_build_git "gnuradio" "https://github.com/analogdevicesinc/gnuradio" "scopy" "-DENABLE_INTERNAL_VOLK:BOOL=OFF -DENABLE_GR_FEC:BOOL=OFF -DENABLE_GR_DIGITAL:BOOL=OFF -DENABLE_GR_DTV:BOOL=OFF -DENABLE_GR_ATSC:BOOL=OFF -DENABLE_GR_AUDIO:BOOL=OFF -DENABLE_GR_CHANNELS:BOOL=OFF -DENABLE_GR_NOAA:BOOL=OFF -DENABLE_GR_PAGER:BOOL=OFF -DENABLE_GR_TRELLIS:BOOL=OFF -DENABLE_GR_VOCODER:BOOL=OFF"

cmake_build_git "libiio" "https://github.com/analogdevicesinc/libiio" "" "-DINSTALL_UDEV_RULES:BOOL=OFF"

cmake_build_git "libad9361-iio" "https://github.com/analogdevicesinc/libad9361-iio"

cmake_build_git "gr-iio" "https://github.com/analogdevicesinc/gr-iio"



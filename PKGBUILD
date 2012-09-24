# Contributor: Nguyễn Hà Dương <cmpitg@gmail.com>
# Contributor: Ngô Trung <ndtrung4419@gmail.com>
# Contributor: Đàm Tiến Long <longdt90@gmail.com>

pkgname="Bogo"
pkgver=20120924
pkgrel=1
pkgdecs=" Bogo Engine for Ibus"

arch=('i686' 'x86_64')
url="https://github.com/BoGoEngine"
license=('GPL')
depends=('python2' 'glibmm' 'cmake' 'gcc')
makedepends=('git')
provides=('Ibus')

_gitroot="https://github.com/NgoHuy/bogo.git"
_gitname="bogo"
_gitpython="https://github.com/NgoHuy/ibus-bogo-python.git"
_gitpythonname="ibus-bogo-python"

build()  {
	cd ${srcdir}

	if [ -d ${_gitname} ] ; then
		cd ${_gitname} && git pull
		cd ${_gitpythonname} && git pull 
		msg "The local files are updated."
	else
		git clone ${_gitroot}
		cd ${_gitname}
		git clone ${_gitpython} ${_gitpythonname}
	fi

	msg "Starting make..."
	
	cd ${srcdir}/${_gitname}
	if [ -d build ]; then
	cd build 
        else 
		mkdir build
		cd build
	fi
	cmake ..
	make
        mkdir ${pkgdir}/usr/
	mkdir ${pkgdir}/usr/lib/
	mkdir ${pkgdir}/usr/lib/bogo/
	mkdir ${pkgdir}/usr/share
	mkdir ${pkgdir}/usr/share/ibus/
	mkdir ${pkgdir}/usr/share/ibus/component/
	mkdir ${pkgdir}/usr/share/ibus-bogo/
	mkdir ${pkgdir}/usr/share/ibus-bogo/icons/	
	install -D -m755 ${srcdir}/${_gitname}/build/src/libbogo.so ${pkgdir}/usr/lib/ || return 1
	install -D -m755 ${srcdir}/${_gitname}/build/src/libbogo.so.0 ${pkgdir}/usr/lib/ || return 1
	install -D -m755 ${srcdir}/${_gitname}/build/src/libbogo.so.0.1.0 ${pkgdir}/usr/lib/ || return 1
	
	cd ${srcdir}/${_gitname}/${_gitpythonname}
	install -D -m755 engine/ibus-engine-bogo ${pkgdir}/usr/lib/bogo/ || return 1
	install -D -m755 engine/bogo.xml ${pkgdir}/usr/share/ibus/component/ || return 1
	install -D -m755 engine/ibus-bogo.svg ${pkgdir}/usr/share/ibus-bogo/icons/ || return 1
	install -D -m755 engine/BoGoMain.py ${pkgdir}/usr/share/ibus-bogo/ || return 1
	install -D -m755 engine/BoGoEngine.py ${pkgdir}/usr/share/ibus-bogo/ || return 1
	
	}
	
	
	


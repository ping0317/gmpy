import sys, os
from distutils.core import setup, Extension

# patch distutils if it can't cope with the "classifiers" and
# "download_url" keywords
if sys.version < '2.2.3':
    from distutils.dist import DistributionMetadata
    DistributionMetadata.classifiers = None
    DistributionMetadata.download_url = None

# determine include and library dirs
incdirs = libdirs = ()
if sys.version.find('MSC') == -1:
    # Unix-like build
    incdirs = ['./src']
    if os.path.isfile('/usr/local/include/gmp.h'):
        incdirs.append('/usr/local/include')
    if os.path.isfile('/usr/local/lib/libgmp.a'):
        libdirs=['/usr/local/lib']

# decomment next line (w/gcc, only!) to support gcov
#   os.environ['CFLAGS'] = '-fprofile-arcs -ftest-coverage -O0'
# prepare the extension for building
gmpy_ext = Extension('gmpy', sources=['src/gmpy.c'],
    include_dirs=incdirs,
    library_dirs=libdirs,
    libraries=['gmp'])

setup (name = "gmpy",
       version = "1.03",
       maintainer = "Alex Martelli",
       maintainer_email = "aleaxit@gmail.com",
       url = "http://code.google.com/p/gmpy/",
       description = "GMP-4 to Python-2.{2-5} interface",
       # download_url = "http://http://prdownloads.sourceforge.net/gmpy/gmpy-sources-101.zip?download",

       classifiers = [
         'Development Status :: 4 - Beta',
         'Intended Audience :: Developers',
         'License :: OSI Approved :: GNU Library or Lesser General Public License (LGPL)',
         'Natural Language :: English',
         'Operating System :: MacOS :: MacOS X',
         'Operating System :: Microsoft :: Windows',
         'Operating System :: POSIX',
         'Programming Language :: C',
         'Programming Language :: Python',
         'Topic :: Scientific/Engineering :: Mathematics',
         'Topic :: Software Development :: Libraries :: Python Modules',
       ],

       ext_modules = [ gmpy_ext ]
)
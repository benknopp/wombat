# Try to find directories with standard headers, e.g. iostream
#
# It is needed to detect those directories to get them into the 
# include path. Otherwise, some dumb IDEs like Eclipse using CDT 
# do not know where to get those includes from :(.
#
# 2009/04 Tobias Feldmann

# typical root dirs of installations, exactly one of them is used
SET (StdMac_POSSIBLE_ROOT_DIRS
    /usr/local
    /usr
)

# typical include dirs above the root dirs
SET(StdMac_INCDIR_SUFFIXES
    include
    include/c++/4.3.3
    include/c++/4.3
    include/c++/4.2.4
    include/c++/4.2
    include/c++/4.0.0
    include/c++/3.3.0
    include/c++/3.2.0
)

# try to find at least iostream and cstring at the root dirs or
# root dir subdirectories.
FIND_PATH(StdMac_INC_DIR
    NAMES iostream cstring
    PATHS ${StdMac_POSSIBLE_ROOT_DIRS}      
    PATH_SUFFIXES ${StdMac_INCDIR_SUFFIXES}
)

# handle the QUIETLY and REQUIRED arguments and set StdMac_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(StdMac DEFAULT_MSG StdMac_INC_DIR)


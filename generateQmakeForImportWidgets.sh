#/bin/bash

function getHeaderFiles {
    #$1 folder
    #return headerFiles

    headerFiles=$(find $1 -type f | grep '\.h')
}

function getCppFiles {
    #$1 folder
    #return cppFiles

    cppFiles=$(find $1 -type f | grep '\.cpp')
}

function getDistFiles {
    #$1 folder
    #return distFiles

    distFiles=$(find $1 -type f | grep '\.gitignore\|\.clang-format\|\.md')
}

function getIncludePaths {
    #$1 folder
    #return includePaths

    includePaths=$(find $1 -type d -maxdepth 1 | grep -v '\.git' | tail -n +2)
}

function getSubdirs {
    #$1 folder
    #reurn subdirs

    subdirs=$(find $1 -type f | grep '\.pro' | grep -v '\.user')
}

function getQtModules {
    #return qtModules

    qtModules="gui opengl widgets"
}

function writeSomthingToVariable {
    #$1 filepath
    #$2 variablename
    #$3 somthing CMakeLists

    for somthing in $3
    do
        echo "$2 += ../phywidgets/$somthing" >> $1
    done
    echo >> $1
}

function writeWidgetsSpecific {
    #$1 filepath

    echo -e "include(widgets-specific.qmake)\n" >> $1
}

function generateQMake {
    #$1 folder

    local qmakePath=$1/widgets.qmake

    rm -r $qmakePath 2> /dev/null

    writeWidgetsSpecific $qmakePath

    getQtModules #return qtModules
    echo -e "QT += $qtModules\n" >> $qmakePath

    getIncludePaths $1 #return includePaths
    writeSomthingToVariable $qmakePath INCLUDEPATH "$includePaths"

    getHeaderFiles $1 #return headerFiles
    writeSomthingToVariable $qmakePath HEADERS "$headerFiles"

    getCppFiles $1 #return cppFiles
    writeSomthingToVariable $qmakePath SOURCES "$cppFiles"

    getDistFiles $1 #return distFiles
    writeSomthingToVariable $qmakePath DISTFILES "$distFiles"

    getSubdirs $1 #return subdirs
    writeSomthingToVariable $qmakePath SUBDIRS "$subdirs"
}

generateQMake .

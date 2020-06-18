#!/bin/sh
# I am the build script. Please run me and not gmake (that is if you want to
# build the documentation as well as the binarary!)


handleBuildWithArgOptions()
{
    CMD_ARG_OPT1="debug"		# For debug builds.
    CMD_ARG_OPT2="DEBUG"
    CMD_ARG_OPT3="clean"		# For make clean.
    CMD_ARG_OPT4="doc"		# For building documentation.
    
    CMD_OPT1="gmake -j8"
    CMD_OPT2="doxygen"
    CMD_OPT2_ARG="Doxyfile"

    MAKE_ARG=$1

    echo -e "${GREEN}Attempting to execute command $1 =========================\
==================="
    
    case $1 in
	$CMD_ARG_OPT1)
	    CMD=$CMD_OPT1
	    CMD_ARG0=$CMD_ARG_OPT1
	    
	    printCMDInfo $CMD $CMD_ARG0
	    $CMD_OPT1 $CMD_ARG_OPT1
	    CMD_RET=$?
	    printCMDExitStatus $? $CMD $CMD_ARG0
	    ;;
	$CMD_ARG_OPT2)
	    CMD=$CMD_OPT1
	    CMD_ARG0=$CMD_ARG_OPT1
	    
	    printCMDInfo $CMD $CMD_ARG0
	    $CMD_OPT1 $CMD_ARG_OPT1	# make file does not recognize "DEBUG"
	    CMD_RET=$?
	    printCMDExitStatus $? $CMD $CMD_ARG0
	    ;;
	$CMD_ARG_OPT3)
	    CMD=$CMD_OPT1
	    CMD_ARG0=$CMD_ARG_OPT3
	    
	    printCMDInfo $CMD $CMD_ARG0
	    $CMD_OPT1 $CMD_ARG_OPT3
	    CMD_RET=$?
	    printCMDExitStatus $? $CMD $CMD_ARG0
	    ;;
	$CMD_ARG_OPT4)
	    CMD=$CMD_OPT2
	    CMD_ARG0=$CMD_OPT2_ARG
	    
	    printCMDInfo $CMD $CMD_ARG0
	    $CMD_OPT2 $CMD_OPT2_ARG
	    CMD_RET=$?
	    printCMDExitStatus $? $CMD $CMD_ARG0
	    ;;
	*)
	    echo -e "${RED}Error argument (${1}) is not recognised! The only \
argument's recognised are ${GREEN}${CMD_ARG_OPT1}, ${CMD_ARG_OPT2}, \
${CMD_ARG_OPT3} and ${CMD_ARG_OPT4}.${NO_COLOR}"
    esac

    shift 1			# Left shift CMD args (not equivalent to rotate)
    if [ ${1:-NULL} != $NULL ]
    then
	handleBuildWithArgOptions $@
    fi
}


printCMDInfo()
{
    echo -e "${GREEN}Now running ${CMD} with argument/s \
(${CMD_ARG0}, ${CMD_ARG1})  =========================================\
${NO_COLOR}"
}


printCMDExitStatus()
{
    if [ $CMD_RET -eq 0 ]
    then
	echo -e "${GREEN}Finished running command ${CMD} with argument\s (\
${CMD_ARG0}, ${CMD_ARG1}) (without error) ==============${NO_COLOR}"
    else
	echo -e "${RED}Finished running command ${CMD} with argument\s \
(${GREEN}${CMD_ARG0}, ${CMD_ARG1}${RED}) (with error/s) ==============\
${NO_COLOR}"
    fi
}


# We found some info about the colour codes here:
# https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux
NO_COLOR='\033[0m'
RED='\033[0;31m'		# Indicates bad things :'(
GREEN='\033[0;32m'		# Indicates all is well in the world :)

NULL="NULL"

CMD_ARG_NO_OPTIONS=0
CMD_ARG_OPTIONS_MAX=3

# Check commandline argument/s ("debug" is the only command currently
# supported.)
if [ $# -eq $CMD_ARG_NO_OPTIONS ]
then
    CMD="gmake -j8"
    CMD_ARG0=""
    printCMDInfo $CMD $CMD_ARG0
    $CMD
    CMD_RET=$?
    printCMDExitStatus $? $CMD $CMD_ARG0    
else
    if [ $# -le $CMD_ARG_OPTIONS_MAX ] # -le <- less then or equal.
    then
	handleBuildWithArgOptions $@
    else
	echo -e "${RED}Error ("$#") argument's given but \
("$CMD_ARG_OPTIONS_MAX") or less argument's are allowed!${NO_COLOR}"
    fi
fi

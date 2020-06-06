#!/bin/sh
# I am the build script. Please run me and not gmake (that is if you want to
# build the documentation as well as the binarary!)


buildProper()
{
    # Note that the -e tells echo to enable backslash escapes.
    echo -e $GREEN"Running gmake ==================================================\
============== :"$NO_COLOR
    gmake $MAKE_ARG

    if [ $? -eq 0 ]			# Check exit status of gmake
    then				# Gmake exited cleanly
	echo -e $GREEN"Finished running gmake (without error) =====================\
================== ."$NO_COLOR
	if [ ${MAKE_ARG:=notDefined} != "notDefined" ]
	then
	    if [ $MAKE_ARG != $MAKE_CLEAN ]
	    then			# We are building the documentation
		echo -e $GREEN"Now building documentation with Doxygen:"$NO_COLOR
		#	doxygen Doxyfile
		if [ $? -eq 0 ]
		then
		    echo -e $GREEN"Finished running doxygen ===========================\
===========================."$NO_COLOR
		    echo -e $GREEN"Finished without error =============================\
========================== ."$NO_COLOR
		    
		else
		    echo -e $RED"Finished running doxygen (with error/s) ==============\
=========================="$NO_COLOR
		    echo -e $RED"Finished (with error/s) ==============================\
======================== ."$NO_COLOR
		fi
	    fi
	fi
	
    else
	echo -e $RED"Finished running gmake (with error/s)! omitting \
documentation build step ===== :"$NO_COLOR
	echo -e $RED"Finished with error/s ========================================\
================ ."$NO_COLOR
    fi
}


# We found some info about the colour codes here:
# https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux
NO_COLOR='\033[0m'
RED='\033[0;31m'		# Indicates bad things :'(
GREEN='\033[0;32m'		# Indicates all is well in the world :)

CMD_ARG_DEBUG_LOWER="debug"
CMD_ARG_DEBUG_UPPER="DEBUG"
CMD_ARG_CLEAN="clean"
MAKE_CLEAN=$CMD_ARG_CLEAN

# Check commandline argument/s ("debug" is the only command currently
# supported.)
if [ $# -eq 0 ]
then
    buildProper
    
else
    if [ $# -eq 1 ]
    then			# Note here that we use "=" and not -eq, -eq is
	#  for numbers and = is analagous to == in c/c++ but for strings.
	if [ \( $1 = $CMD_ARG_DEBUG_LOWER \) -o \
		\( $1 = $CMD_ARG_DEBUG_UPPER \) ]
	then
	    MAKE_ARG=$CMD_ARG_DEBUG_LOWER
	    buildProper $MAKE_ARG $MAKE_CLEAN
	    
	else
	    if [ $1 = $CMD_ARG_CLEAN ]
	    then
		MAKE_ARG=$CMD_ARG_CLEAN
		buildProper $MAKE_ARG $MAKE_CLEAN
	    else
		echo -e "${RED}Error argument ("$1") is not recognised! The \
only argument's recognised are " $GREEN $CMD_ARG_DEBUG_LOWER $RED ", " $GREEN\
		     $CMD_ARG_DEBUG_UPPER " and " $CMD_ARG_CLEAN $NO_COLOR
	    fi
	fi
	
    else
	echo -e "${RED}Error ("$#") argument's given but only 0 or 1 argument's\
 are allowed!${NO_COLOR}"
    fi
fi

    


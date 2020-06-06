#!/bin/sh
# I am the build script. Please run me and not gmake (that is if you want to
# build the documentation as well as the binarary!)


buildProper()
{
# Note that the -e tells echo to enable backslash escapes.
echo -e "${GREEN}Running gmake ================================================\
================ :${NC}"
gmake $DEBUG_BUILD

if [ $? -eq 0 ]			# Check exit status of gmake
then
    echo -e "${GREEN}Finished running gmake (without error). Now building \
documentation with Doxygen:${NC}"
    echo -e "${GREEN}Finished without error ===================================\
==================== .${NC}"
    
else
    echo -e "${RED}Finished running gmake (with error/s)! omitting \
documentation build step ===== :${NC}"
    echo -e "${RED}Finished with error/s ======================================\
================== .${NC}"
fi
}


# We found some info about the colour codes here:
# https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux
NC='\033[0m'
RED='\033[0;31m'		# Indicates bad things :'(
GREEN='\033[0;32m'		# Indicates all is well in the world :)

CMD_ARG_1_LOWER="debug"
CMD_ARG_1_UPPER="DEBUG"

# Check commandline argument/s ("debug" is the only command currently
# supported.)
if [ $# -eq 0 ]
then
    buildProper
    
else
    if [ $# -eq 1 ]
    then			# Note here that we use "=" and not -eq, -eq is
	#  for numbers and = is analagous to == in c/c++ but for strings.
	if [ \( $1 = $CMD_ARG_1_LOWER \) -o \( $1 = $CMD_ARG_1_UPPER \) ]
	then
	    DEBUG_BUILD=$CMD_ARG_1_LOWER
	    buildProper $DEBUG_BUILD
	      
	else
	    echo -e "${RED}Error argument ("$1") is not recognised! The only \
argument's recognised are " $GREEN $CMD_ARG_1_LOWER $RED " and " $GREEN\
		 $CMD_ARG_1_UPPER $NC
	fi
	
    else
	echo -e "${RED}Error ("$#") argument's given but only 0 or 1 argument's\
 are allowed!${NC}"
    fi
fi

    


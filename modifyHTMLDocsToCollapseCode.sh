#!/bin/sh
# This script is used to modify the HTML and CSS code that doxygen produces so
# that any source code included in the documentation will be automatically
# hidden in a collapsible block.
# This way we can have the source code included in the documentation as we wish
# but not have it clutter things. :)


CSS_FILE="docs/html/doxygen.css"
HTML_FILE=""
FILE_PATH="docs/html/*.html"
HTML_REPLACE_FIRST="<div class=\"memdoc\">"
HTML_REPLACE_SECOND="<\/div><!-- fragment -->"
TRUE="0"
FALSE="1"
#NEW_LINE='\033[0a'
#EMPTY=""


# FILES=`ls -1 docs/html/*.html`
# cut -d' ' -f2 "${FILES}


# The following for loop does the following
# First:
# Add wrap-collapsible after class="memdoc
# Then: Add the following...
#	<input id="collapsible" class="toggle" type="checkbox">
#	<label for="collapsible" class="lbl-toggle">See source</label>
#	<div class="collapsible-content">
#	<div class="content-inner">
# sed -i -e 's/<div class="memdoc">/<div class="memdoc wrap-collapsible">\
# <input id="collapsible" class="toggle" type="checkbox">\
# <label for="collapsible" class="lbl-toggle">See source<\/label>\
# <div class="collapsible-content"><div class="content-inner">\
# /g' docs/html/*.html
# # Now we need to add two closing tags for the two unclosed div's we've added
# sed -i -e 's/<\/div><!-- fragment -->/<\/div><!-- fragment -->\
# <\/div>\
# <\/div>/g' docs/html/*.html


# Iterate over html files in documentation directory
for iter in `ls $FILE_PATH`
do
    NEW_FILE=""
    # Iterate over each line of the file. We found the code to do this on the
    # following site:
    # https://unix.stackexchange.com/questions/7011/how-to-loop-over-the-lines-of-a-file
    while IFS='' read -r LINE || [ -n "${LINE}" ]; do # -n s <-(s has non-zero length)
	REPLACED=$FALSE
	if echo "$LINE" | grep -q "${HTML_REPLACE_FIRST}";
	then
	    NEW_FILE="${NEW_FILE}\n`echo $LINE | sed -e 's/<div class="memdoc">\
/<div class="memdoc wrap-collapsible">\
<input id="collapsible" class="toggle" type="checkbox">\
<label for="collapsible" class="lbl-toggle">See source<\/label>\
<div class="collapsible-content"><div class="content-inner">\
/g'`"
	    REPLACED=$TRUE
	fi
	
	if echo "$LINE" | grep -q "${HTML_REPLACE_SECOND}"
	then
	    NEW_FILE="${NEW_FILE}\n`echo $LINE | sed -e 's/<\/div><!-- fragment -->/<\/div><!-- fragment -->\
<\/div>\
<\/div>/g'`"
	    REPLACED=$TRUE
	fi
	 

	if [ ${REPLACED:-FALSE} == $FALSE ]
	then
	    GREEN='\033[0;32m'
	    NC='\033[0m'	 
	    NEW_FILE="${NEW_FILE}\n${LINE}"
	fi
	#echo "processing line: ${LINE}"
    done < $iter
    echo -e $NEW_FILE > $iter
#    echo -e $NEW_FILE
done


# for iter in $FILE_PATH;
# do
#     echo $iter
#     if [ "$iter" == "$FILE_PATH" ]
#     then echo "${iter}"
#     else
# 	echo "No match"
#     fi
# done


# First:
# Add wrap-collapsible after class="memdoc
# Then: Add the following...
#	<input id="collapsible" class="toggle" type="checkbox">
#	<label for="collapsible" class="lbl-toggle">See source</label>
#	<div class="collapsible-content">
#	<div class="content-inner">
# sed -i -e 's/<div class="memdoc">/<div class="memdoc wrap-collapsible">\
# <input id="collapsible" class="toggle" type="checkbox">\
# <label for="collapsible" class="lbl-toggle">See source<\/label>\
# <div class="collapsible-content"><div class="content-inner">\
# /g' docs/html/*.html
# # Now we need to add two closing tags for the two unclosed div's we've added
# sed -i -e 's/<\/div><!-- fragment -->/<\/div><!-- fragment -->\
# <\/div>\
# <\/div>/g' docs/html/*.html


# Now add the required css to doxygen.css file
echo -e "/* For collapsible box's START. ======================================\
==========
The following CSS is a modified version of the CSS found at the following page:
https://alligator.io/css/collapsible/ */
input[type='checkbox']
{
  display: none;
}

.lbl-toggle
{
  display: block;

  font-weight: bold;
/*  font-family: monospace;*/
  font-style: italic;
  font-size: 0.58rem;
/*  text-transform: uppercase;*/
  text-align: left;

  padding: 1rem;

  color: #253555; /*#A77B0E;*/
  background: #A8B8D9; /*#FAE042;*/

  cursor: pointer;

  border-radius: 6px;
  padding: 0px;
  padding-left: 10px;
  transition: all 0.25s ease-out;
}

.lbl-toggle:hover
{
  color: #2535ff; /*#7C5A0B;*/
}

.lbl-toggle::before
{
  content: ' ';
  display: inline-block;

  border-top: 5px solid transparent;
  border-bottom: 5px solid transparent;
  border-left: 5px solid currentColor;

  vertical-align: middle;
  margin-right: .7rem;
  transform: translateY(-2px);

  transition: transform .2s ease-out;
}

.collapsible-content .content-inner
{
    background: #b8c8e9;
}

.collapsible-content
{
  max-height: 0px;
  overflow: hidden;

  transition: max-height .25s ease-in-out;
}

.toggle:checked + .lbl-toggle + .collapsible-content
{
  max-height: 100vh;
}

.toggle:checked + .lbl-toggle::before
{
  transform: rotate(90deg) translateX(-3px);
}

.toggle:checked + .lbl-toggle
{
  border-bottom-right-radius: 0;
  border-bottom-left-radius: 0;
}
/* For collapsible box's END. =============================================== *\
/" >> $CSS_FILE

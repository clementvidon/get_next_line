#!/bin/bash

# @author       cvidon@42
#
# @brief        Compare get_next_line and cat output.
#
# @param[in]    A file to read.
# @return       OK if there are no difference otherwise KO plus a diff.log.


## Check if get_next_line exist.
################################

if [ ! -f get_next_line ]
then
    make;
fi

## If the number of arguments
#############################

if [ "$#" -eq 0 ] || [ "$#" -gt 1 ]
then
    echo "Usage: bash diff.sh <file_name>"
    exit 1
fi

## If the argument validity
###########################

if [ ! -f "$1" ] || [ ! -r "$1" ]
then
    echo "File error"
    exit 1
fi

## Operate a diff
#################

result=$(diff <(tr -d '\0' < "$1") <(./get_next_line "$1" 2>/dev/null) | wc -l)

#              "tr -d '\0' <
#                --------  _
#                   |      +-- built-in replacement for cat
#                   +--------- removes NULL BYTE characters

## Feedback
###########

if [ $result -eq 0 ]
then
    tput setaf 2
    echo "OK";
    tput sgr0
else
    tput setaf 1
    echo "KO";
    tput sgr0
    echo "  Press ENTER to create diff.log";
    read -p ""
    diff <(tr -d '\0' < "$1") <(./get_next_line "$1" 2>/dev/null) > diff.log
fi
exit 0

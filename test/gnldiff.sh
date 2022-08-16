#!/bin/bash

# @file         gnldiff.sh
# @author       cvidon@42
# @date         220816
#
# Make sure to use a BUFFER_SIZE of 1 if your <file> parameter contains special
# characters like those from binary file or /dev/urandom.
#
# @brief        Check get_next_line output accuracy.
#
# @param[in]    A file to read.
# @return       OK if there are no difference otherwise KO + create diff.log


## Check if get_next_line exist.
################################

if [ ! -f get_next_line ]
then
    make
fi

## If the number of arguments
#############################

if [ "$#" -eq 0 ] || [ "$#" -gt 1 ]
then
    echo "Usage: bash gnldiff.sh <file_path>"
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

#               tr -d '\0' <
#                --------  _
#                   |      +-- built-in replacement for cat
#                   +--------- removes NULL BYTE characters

## Feedback
###########

if [ $result -eq 0 ]
then
    tput setaf 2
    echo "OK"
    tput sgr0
else
    tput setaf 1
    echo "KO"
    tput sgr0
    echo -n "Press ENTER to generate log..."
    read -p ""
    diff <(tr -d '\0' < "$1") <(./get_next_line "$1" 2>/dev/null) > diff.log
    ls -l diff.log
fi
exit 0

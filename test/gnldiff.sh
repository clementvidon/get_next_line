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
#

# TODO replace 'cat' with 'getline'
#
## Check the number of arguments
################################
#
# if [ ! "$#" -eq 2 ]
# then
#     echo "Usage: bash gnldiff.sh <file_path> [ <buffer_size> ]"
#     exit 1
# fi
#
## Check arguments validity
###########################
#
# size=$2
# if [ $size -lt 0 ] || [ $size -ge 2147483647 ]
# then
#     echo "Buffer size has to be between zero and one billion"
#     exit 1
# fi

## Check if get_next_line exist
###############################

if [ ! -f get_next_line ]
then
    make
fi

## Check the number of arguments
################################

if [ ! "$#" -eq 1 ]
then
    echo "Usage: bash gnldiff.sh <file_path>"
    exit 1
fi

## Check arguments validity
###########################

file=$1
if [ ! -f "$file" ] || [ ! -r "$file" ]
then
    echo "File error"
    exit 1
fi

## Operate a diff
#################

result=$(diff <(tr -d '\0' < "$file") <(./get_next_line "$file" 2>/dev/null) | wc -l)

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
    diff <(tr -d '\0' < "$file") <(./get_next_line "$file" 2>/dev/null) > diff.log
    ls -l diff.log
fi
exit 0

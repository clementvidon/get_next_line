#!/bin/bash

# @author   cvidon@42
# @brief    Check if the number of characters returned by get_next_line call on
#           different input with different BUFFER_SIZE is correct.  Also Check
#           for leaks on its way.
# @usage    'bash runtests.sh' or simply 'make test'

testfiles="testfiles/*"
bufsizes=(0 1 2 10 100 1000 1000000)
valgrind="valgrind -q --leak-check=yes --show-leak-kinds=all"
gnltotal=0
cattotal=0

for file in $testfiles; do
    for bsize in "${bufsizes[@]}"; do
        make -j CFLAGS="-D BUFFER_SIZE=$bsize" 1>/dev/null
        if [ $bsize -eq 0 ]; then
            gnlcount=$($valgrind ./get_next_line $file | wc -m | bc)
            catcount=0
        else
            gnlcount=$($valgrind ./get_next_line $file | wc -m | bc)
            catcount=$(cat $file | wc -m | bc)
        fi
        gnltotal=$(( $gnltotal + $gnlcount ))
        cattotal=$(( $cattotal + $catcount ))
        make fclean
        clear
        echo "Read: $gnlcount/$catcount"
        echo "file=$file"
        echo "BUFFER_SIZE=$bsize"
        echo ""
        if [ $gnlcount -eq $catcount ]; then
            echo "      >>> OK <<<"
            echo ""
        else
            echo "      <<< KO >>>>"
            echo ""
            exit
        fi
    done
done

clear
echo ""
echo ""
echo "Total read: $gnltotal/$cattotal"
echo ""
echo "      >>> OK <<<"
echo ""

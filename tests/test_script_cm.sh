#!/usr/bin/env bash

ko='\e[00;31m';
wipe='\e[00m';
ok='\e[01;32m';

VALID=./tests
TEST=$VALID/input
LOG=$VALID/output/log
RET=

rm -rf $LOG
mkdir $LOG

function test_minimax_ballots {
    RET=0
    if [ -x ./scrutin ]
    then
    rm -rf $VALID/output/result/
    mkdir $VALID/output/result/

	while read i
    do
        filename=$(basename "$i" .csv) # Supprime l'extension .csv

        echo "1" | ./scrutin -i $filename -o log_$filename -m cm > /dev/null
        diff $VALID/reference/ref_cm/$filename.txt $VALID/output/result/${filename}.txt  &>/dev/null
        RET=$?
        [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$filename"
        [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$filename" && return;
    done <$VALID/file_list_ballots.txt
    else
    RET=2
    fi
}

function test_minimax_duels {
    RET=0
    if [ -x ./scrutin ]
    then

	while read i
    do
        filename=$(basename "$i" .csv) # Supprime l'extension .csv

        echo "1" | ./scrutin -d $filename -o log_$filename -m cm > /dev/null
        diff $VALID/reference/ref_cm/$filename.txt $VALID/output/result/${filename}.txt  &>/dev/null
        RET=$?
        [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$filename"
        [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$filename" && return;
    done <$VALID/file_list_duels.txt
    else
    RET=2
    fi
}

function test {
    test_$1
    [ $RET -eq 0 ] && printf "===> %-12s [${ok}OK${wipe}]\n" "$1"
    [ $RET -ne 0 ] && printf "xxx> %-12s [${ko}KO${wipe}]\n" "$1"
}

test minimax_ballots;
test minimax_duels;

exit 0

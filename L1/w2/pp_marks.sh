#!/bin/bash

SCORE=0
MAX=0
mSCORE=0
mMAX=0
for i in {1..6}; do
        if [ -a m$i ]; then
               if [ -a m$i/feedback.txt ]; then

                grade=$(cat w$i/feedback.txt | tr -d [:blank:])
                IFS='/' read -ra grArray <<< "$grade"
                mSCORE=$(($mSCORE + ${grArray[0]}))
                mMAX=$(($mMAX + ${grArray[1]}))
                echo "m$i: ${grArray[0]} / ${grArray[1]}"
        else
                echo "m$i: - / -"
        fi
        else
                echo "m$i: - / -"
        fi

done

echo

for i in {1..11}; do
        if [ -a w$i ]; then
               if [ -a w$i/feedback.txt ]; then

                grade=$(cat w$i/feedback.txt | tr -d [:blank:])
                IFS='/' read -ra grArray <<< "$grade"
                SCORE=$(($SCORE + ${grArray[0]}))
                MAX=$(($MAX + ${grArray[1]}))
                echo "w$i: ${grArray[0]} / ${grArray[1]}"
        else
                echo "w$i: - / -"
        fi
        else
                echo "w$i: - / -"
        fi

done
echo
#Add if statement that deals with if max is 0 then it should output -/- else bottom echo, do for mile and lab
if [ $mMAX -eq 0 ]; then
	echo "Milestone Total: - / -"
else
	echo "Milestone Total: $mSCORE / $mMAX"
fi


if [ $mMAX -eq 0 ]; then
        echo "Lab Total: - / -"
else
        echo "Lab Total: $SCORE / $MAX"
fi


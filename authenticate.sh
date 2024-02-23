#!/bin/bash

server="$1"
Max_client=1
DefaultPort=6667

i=0
while [ $i -lt $Max_client ]; do
    nc $server $DefaultPort
    # echo "PASS 456"
    # NICK "CLIENT$i"
    i=$(($i + 1)) 
done
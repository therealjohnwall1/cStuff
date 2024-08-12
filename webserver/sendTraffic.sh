#!/bin/bash

for N in {1..150}
do
    ./clientTraffic &
done
wait 
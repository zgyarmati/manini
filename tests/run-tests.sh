#!/bin/bash


for script in tst_*
do
    echo -e "\e[104m Calling ${script} \e[0m"
    ./${script}
done

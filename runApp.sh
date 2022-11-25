#!/bin/bash
mkdir output
mkdir build
cd build
cmake ../
make

input_folder="/home/bjit/Yokogawa/Demo/Unique-pixels/assets"
output_folder="/home/bjit/Yokogawa/Demo/Unique-pixels/output"

./app  $input_folder $output_folder
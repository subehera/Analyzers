#!/bin/bash

#./bsub.sh 7 250 400 1 250 "job7_sub1"
#./bsub.sh 0 120 150 1 120 "job0_1_sub1"
#./bsub.sh 0 150 185 1 150 "job0_2_sub1"
#./bsub.sh [1-6] 185 250 1 185 "job16_sub1"
#
#./bsub.sh 7 250 400 2 250 "job7_sub2"
#./bsub.sh 0 120 150 2 120 "job0_1_sub2"
#./bsub.sh 0 150 185 2 150 "job0_2_sub2"
#./bsub.sh [1-6] 185 250 2 185 "job16_sub2"

./bsub.sh [1-6] 2 "job_mb_sub2_c2"

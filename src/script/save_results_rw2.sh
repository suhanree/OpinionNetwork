#! /bin/bash

if (( $# != 0 ))
then
	echo "Usage: $0"
else
	cd ~/Simulations/RW2
	make -f Makeback_Results
	scp rw2_results.tgz suhan@linux10.ph.utexas.edu:backup
fi

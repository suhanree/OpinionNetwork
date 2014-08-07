#! /bin/bash

if (( $# != 1 ))
then
	echo "Usage: $0 06_24"
else
	cd $HOME/Simulations/RW2
	make -f Makeback
	mv -f rw2.tgz rw2_2011_$1.tgz
	scp rw2_2011_$1.tgz suhan@linux10.ph.utexas.edu:backup
fi

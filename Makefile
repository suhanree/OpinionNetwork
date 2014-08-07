# 
# 	Filename : Makefile
#
#	Author : Suhan Ree
#	Date   : 08-07-2003


# Main makefile for RW.
#	(There is a lot of room for improvement.)

# Options 
#	APP (=SIM,STA,VIS) default=SIM
#	COMPILER (=GCC,CC) default=GCC
#	MPI (=LAM,MPICH) : default=LAM
#	DEBUG=1 : if a user wants executables with debugging info. 
#		(the name of the executable will have '.debug' extension)
#	OPTIMIZE=N : setting the optimization level to N (default=2).


# Usage: (assuming the current directory is 'RW').
#	make buildall			: build all modules using default setting.
#		(should override COMPILER in Makefile.sim)
#	make APP=SIM MPI=MPICH		: make executables for SIM usig MPICH.
#	make APP=SIM DEBUG=1		: make executables for MOB using debugging,
#	make APP=SIM clean 		: delete all binaries and object files for SIM.
#	make cleanall	 		: delete all binaries and object files.
#	make APP=SIM depend 		: build dependency table for SIM files.
#	make dependall	 		: build dependency table for all files.


ifndef APP
   APP=SIM
endif

ifndef COMPILER
   COMPILER = GCC
endif

ifndef MPI
   MPI = none
endif

ifndef OPTIMIZE
   OPTIMIZE = 2
endif

# phony targets.
.PHONY : default buildall clean cleanall depend dependall

#exporting variables to sub-make's.
export COMPILER MPI DEBUG OPTIMIZE

default : 
	@ $(MAKE) -w -C src -f Makefile.$(APP)
buildall : 
	@ $(MAKE) -w -C src -f Makefile.SIM
	@ $(MAKE) -w -C src -f Makefile.STA
	@ $(MAKE) -w -C src -f Makefile.VIS
cleanall :		    
	@ $(MAKE) -w -C src -f Makefile.SIM clean
	@ $(MAKE) -w -C src -f Makefile.STA clean
	@ $(MAKE) -w -C src -f Makefile.VIS clean
dependall :		    
	@ $(MAKE) -w -C src -f Makefile.SIM depend
	@ $(MAKE) -w -C src -f Makefile.STA depend
	@ $(MAKE) -w -C src -f Makefile.VIS depend
clean : 
	@ $(MAKE) -w -C src -f Makefile.$(APP) clean
depend : 
	@ $(MAKE) -w -C src -f Makefile.$(APP) depend


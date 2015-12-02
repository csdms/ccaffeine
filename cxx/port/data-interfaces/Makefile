all:
	@echo done
depend:
	@echo done
clean:
	@echo done

GEN_DIRS= test-data test

CXXHDR=dec2000.h

cdoc: dclean test-data test

# note -A will kill us in the next target
doc:
	if [ ! -d test ] ; then mkdir test; fi
	-doc++ -p -b -H -j -d test $(CXXHDR)

dox:
	if [ ! -d test-dox ] ; then mkdir test-dox; fi
	-doxygen ../../doc/DoxyCollective

test-data: 
	if [ ! -d test-data ] ; then mkdir test-data; fi
	-doxygen ../../../doc/DoxyData

dclean:
	-/bin/rm -rf $(GEN_DIRS)

#=======================================================================================#
# project.mk
#=======================================================================================#
#  Created on: Oct 3, 2015
#      Author: puch
#=======================================================================================#
build_proc=setup makdirs
output_dirs=$(outdir) $(incdir) $(libdir) $(objdir) $(bindir)
build_dirs_inc=$(foreach i, $(build_incs), $(shell find $(i) -name *.h) )
export make_dirs= $(foreach i, $(build_incs),$(shell find $(i) -name *makefile.mk) )

# all : setup makdirs
$(build_list) : $(build_proc)

# host : setup makdirs

.PHONY : setup
setup : 
	-mkdir out $(output_dirs);
	$(foreach i, $(build_dirs_inc), cp -fs $(i) $(rootdir)/$(incdir);)
#  setup : out
#  	cp -fs foo.h out/inc/foo.h; 

makdirs : $(make_dirs)
	$(foreach i, $^ , $(MAKE) -f $(i) -C $(dir $(i)); )
#   makdirs : foo/foo_makefile.mk
#   make -f foo/foo_makefile.mk -C ./foo;

.PHONY : clean
clean :
	rm -rf out;
#=======================================================================================#
# project.mk
#=======================================================================================#
# Changes Log
#
#
#=======================================================================================#

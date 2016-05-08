#=======================================================================================#
# setup.mk
#=======================================================================================#
#  Created on: Oct 3, 2015
#      Author: puch
#=======================================================================================#
export rootdir=$(realpath . )
export outdir=$(addprefix $(rootdir)/out/,$(build_list))
export incdir=out/inc
export libdir=$(outdir)/lib
export objdir=$(outdir)/obj
export bindir=$(outdir)/bin
export build_dirs=reuse new process
export build_incs+=$(addprefix $(rootdir)/, $(build_dirs)) $(addprefix $(rootdir)/,$(proj_inc_dirs))
#=======================================================================================#
# setup.mk
#=======================================================================================#
# Changes Log
#
#
#=======================================================================================#
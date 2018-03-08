define $(_flavor_)_$(_feat_)_MAKE
 
$(_flavor_)_$(_feat_)_bin_objs=\
 dread_gtest \

$(_flavor_)_$(_feat_)_bin_libs=\
ccipc \
dbg_log \
gtest \

$(_flavor_)_$(_feat_)_bin=dread_gtest

endef

include $(PROJ_MAK_DIR)/epilog.mk

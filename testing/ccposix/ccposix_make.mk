define $(_flavor_)_$(_feat_)_MAKE
 
$(_flavor_)_$(_feat_)_inc=\
ccposix_ipc.h \
ccposix_thread.h\
ccposix_mutex.h\
ccposix_semaphore.h\
ccposix_cond_var.h\


$(_flavor_)_$(_feat_)_lib_objs=\
ccposix_ipc \
ccposix_thread\
ccposix_mailbox\
ccposix_mutex\

$(_flavor_)_$(_feat_)_lib=ccposix_ipc

endef

include $(PROJ_MAK_DIR)/epilog.mk

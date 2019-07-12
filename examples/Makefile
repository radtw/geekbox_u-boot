ifndef CONFIG_SANDBOX

ifdef FTRACE
subdir-ccflags-y += -finstrument-functions -DFTRACE
endif

subdir-y += standalone
#TSAI: the api example doesn't compile for arm64, comment out for now
#subdir-$(CONFIG_API) += api
endif

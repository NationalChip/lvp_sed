ifndef 3rdparty_path
CURR_DIR = .
else
CURR_DIR = $(3rdparty_path)/opencore-amr
endif

AMR_INCLUDES = $(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/amr_nb/dec/src/ \
			   $(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/amr_nb/dec/include/ \
			   $(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/amr_nb/common/src/ \
			   $(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/amr_nb/common/include/ \
			   $(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/common/dec/include \
			   $(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/amr_wb/dec/include \
			   $(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/amr_wb/dec/src \
			   $(CURR_DIR)/amrnb/ \
			   $(CURR_DIR)/amrwb/ \
			   $(CURR_DIR)/oscl/ \
			   $(CURR_DIR)/
NB_DEC_PATH=$(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/amr_nb/dec/src/
WB_DEC_PATH=$(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/amr_wb/dec/src/
COMMON_PATH=$(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/amr_nb/common/src/

-include $(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/amr_nb/common/build/make/local.mk
-include $(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/amr_nb/dec/build/make/local.mk
-include $(CURR_DIR)/opencore/codecs_v2/audio/gsm_amr/amr_wb/dec/build/make/local.mk

AMRNB_SRCS:=$(CURR_DIR)/amrnb/amrnb_wrapper.c
AMRNB_SRCS+=$(COMMON_SRCS)
AMRNB_SRCS+=$(NB_DEC_SRCS)

AMRWB_SRCS:=$(CURR_DIR)/amrwb/amrwb_wrapper.c
AMRWB_SRCS+=$(COMMON_SRCS)
AMRWB_SRCS+=$(WB_DEC_SRCS)

cflags-from-includes=$(addprefix -I ,$(1))
AMR_CFLAGS = $(call cflags-from-includes, $(AMR_INCLUDES))

OBJSUFFIX=.o
LIBSUFFIX=.a

#COMPILE.c.cmdline=$(CXX) -c $(AMR_CFLAGS) -o $@ $<
#ARCHIVE.cmdline=@$(AR) $(ARFLAGS) $@ $^ && $(RANLIB) $@
NB_COBJECTS:=$(patsubst %.c, %$(OBJSUFFIX), $(AMRNB_SRCS))
WB_COBJECTS:=$(patsubst %.c, %$(OBJSUFFIX), $(AMRWB_SRCS))

#%$(OBJSUFFIX):%.cpp
#	$(COMPILE.c.cmdline)
amr_objs:=$(CURR_DIR)/amr.o

ifeq ($(CONFIG_USE_AMR_NB),y)
amr_objs+=$(NB_COBJECTS)
endif
ifeq ($(CONFIG_USE_AMR_WB),y)
amr_objs+=$(WB_COBJECTS)
endif

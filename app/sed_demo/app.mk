#
# Voice Signal Preprocess
# Copyright (C) 2001-2023 NationalChip Co., Ltd
# ALL RIGHTS RESERVED!
#
# Makefile: source list of VSP other hook
#
#=================================================================================#

ifeq ($(CONFIG_LVP_APP_SED_DEMO), y)
app_objs += app/sed_demo/lvp_app_sed_demo.o
endif


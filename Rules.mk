CROSS_COMPILE=

CC=$(CROSS_COMPILE)gcc
AR=$(CROSS_COMPILE)ar

CFLAGS = -Wall -Werror -g
ARFLAGS = -rv

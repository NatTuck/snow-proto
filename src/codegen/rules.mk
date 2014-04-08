
CODEGEN_SRCS := $(wildcard src/codegen/*.c)
CODEGEN_OBJS := $(CODEGEN_SRCS:.c=.o)

OBJS += $(CODEGEN_OBJS)


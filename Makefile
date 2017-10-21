INCLUDES=-Iinclude/
CFLAGS=$(INCLUDES) -m64 -Wall -Werror -pedantic -masm=intel

OBJC=objs/dummy.c.o objs/bigint_mm.c.o objs/bigint_sa.c.o objs/bigint_cmp.c.o
OBJC+=objs/bigint_sd.c.o objs/bigint_bo.c.o
OBJS=
OUTPUT=libsammy.a

.PHONY: debug
default: $(OUTPUT)
debug: CFLAGS += -g -O0 -D__DEBUG
debug: $(OUTPUT)

################################################################################
#                                SOURCES STUFF                                 #
################################################################################

objs/%.o: src/%
	@mkdir -p objs/
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJS) $(OBJC)
	ar rcs $(OUTPUT) $(OBJS) $(OBJC)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(OBJC)
	-rm -f $(OUTPUT)
	-rm -f demo/demo

################################################################################
#                             COMMAND LINE STUFF                               #
################################################################################

demo: CFLAGS += -g -O0 -D__DEBUG
demo: $(OUTPUT) demo/demo.c
	$(CC) demo/demo.c -L. -lsammy -o demo/demo $(CFLAGS)

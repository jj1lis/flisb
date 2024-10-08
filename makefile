TARGET = flisb

SRCDIR = src/
# SRCS = ${wildcard ${SRCDIR}*.c}

COREDIR = $(src)core/
CORES = ${wildcard ${COREDIR}*.c}

PARSEDIR = $(src)parse/
PARSES = ${wildcard ${PARSEDIR}*.c}

OBJDIR = obj/
OBJS = main.o ${patsubst %.c,%.o,${CORES}} ${patsubst %.c,%.o,${PARSES}}
OBJECTS = ${addprefix ${OBJDIR}, ${notdir ${OBJS}}}

CC = gcc
CCFLAGS =
LD = $(CC)
LDFLAGS =
LIBS =

$(TARGET) : $(OBJS)
		$(LD) $(OBJECTS) $(LDFLAGS) -o $(TARGET) $(LIBS)

core.o: $(CORES)
		$(CC) $(CCFLAGS) -o ${patsubst ${COREDIR}%,${OBJDIR}%,$@} -c $< 
parse.o:$(PARSES)
		$(CC) $(CCFLAGS) -o ${patsubst ${PARSEDIR}%,${OBJDIR}%,$@} -c $< 
main.o: $(SRCDIR)main.c
		$(CC) $(CCFLAGS) -o $(OBJDIR)main.o -c $< 

clean :
		rm -f $(OBJECTS) $(TARGET) core *~

exe : $(TARGET)
	./$(TARGET)

all : clean $(TARGET) exe

CFLAGS = -std=c99 -ggdb

PROGRAM = spectre.out
SOURCE  = Source.c


all: $(PROGRAM) f b v
     
$(PROGRAM): $(SOURCE) ; $(CC) $(CFLAGS) -o $(PROGRAM) $(SOURCE)

f: front_end.c ; $(CC) $(CFLAGS) -o front_end.out $<

b: back_end.c ; $(CC) $(CFLAGS) -o back_end.out $<

v: victim.c ; $(CC) $(CFLAGS) -o victim.out $<
     
clean: ; rm -f $(PROGRAM)

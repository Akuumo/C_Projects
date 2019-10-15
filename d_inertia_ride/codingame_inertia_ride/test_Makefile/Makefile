# ================================================
#                 Fichier Makefile
# ================================================


EXEC = m_codingame_Inertia-Ride 
OBJS = inertia_ride.o m_codingame_Inertia-Ride.o 
SRCS = inertia_ride.c m_codingame_Inertia-Ride.c

# ------------------------------------------------
#             PARTIE A NE PAS MODIFIER
# ------------------------------------------------

CC = gcc
FLAGCOMP = -c -Wall -Wextra -O3 -g #-pg -g
FLAGLINK = -o # -pg
LIB = -lm
INCL = -I.
LDFLAS = ''
CFLAGS = ''

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(FLAGLINK) $(EXEC) $(OBJS) $(LIB)
	
.c.o:
	$(CC) $(CFLAGS) $(FLAGCOMP) $< $(INCL)

clean:
	rm -rf $(OBJS) $(EXEC) *~ .~ 

all:
	make depend
	make clean
	make

info:
	echo "make [all] [depend] [clean] [info]"

depend: $(SRCS)
	makedepend -Y -- $(FLAGCOMP) -- $?

# DO NOT DELETE

inertia_ride.o: inertia_ride.h
codingame_Inertia-Ride.o: inertia_ride.h

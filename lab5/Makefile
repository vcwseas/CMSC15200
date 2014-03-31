# Makefile
# CS152 2014 
# Lab 5

.PHONY: clean

abk: addressbook.h bst.c vcard.c main.c
	gcc -o abk -Wall bst.c vcard.c main.c

# note: type 'make clean' to remove the executable
clean:
	rm -rf abk

CC=gcc
CFLAGS=-I.

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
all:
	gcc -fPIC -Wall -c fmu.c -lpthread
	gcc -fPIC -Wall -c skeleton.c -lpthread
	gcc -fPIC -Wall -c misraC/DiscreteGrippingArm.c -lpthread -w
	gcc -shared -o DiscreteGrippingArm.so DiscreteGrippingArm.o skeleton.o fmu.o -lpthread
	rm -rf sources
	rm -rf binaries
	mkdir sources
	mkdir  binaries
	mkdir binaries/linux64
	cp fmu.h sources
	cp FmuGUID.h sources
	cp fmu.c sources
	cp skeleton.c sources
	rm -f misraC/main.c
	cp -r misraC sources
	cp -r fmi sources
	mv DiscreteGrippingArm.so binaries/linux64/
	
	zip -r dmodelFMU.fmu modelDescription.xml binaries/ resources/ sources/
	rm -rf sources
	rm -rf binaries
	

run:
	
	./fmuCheck.linux64 -h 1E-01 dmodelFMU.fmu
	
run1:
	
	./fmuCheck.linux64 -h 1E-02 dmodelFMU.fmu
	

clean:
	rm -rf  DiscreteGrippingArm.o fmu.o skeleton.o

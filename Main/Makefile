CC = gcc
EXEC = tilt
CFLAGS = -lpthread -lrt -DBB_BLACK 

all: clean $(EXEC)

$(EXEC): eqep.o gpio.o servo.o pwm.o utils.o calc.o main.o 

	$(CC) -o $(EXEC) main.o eqep.o gpio.o servo.o pwm.o utils.o calc.o -lm -lpthread
	
gpio.o:

	$(CC) -o gpio.o -c gpio.c $(CFLAGS)
	
	
calc.o:

	$(CC) -o calc.o -c calc.c $(CFLAGS)
	
servo.o:

	$(CC) -o servo.o -c servo.c $(CFLAGS)
	
pwm.o: 

	$(CC) -o pwm.o -c pwm.c $(CFLAGS)

eqep.o:

	$(CC) -o eqep.o -c eqep.c $(CFLAGS)
	
utils.o:

	$(CC) -o utils.o -c utils.c $(CFLAGS)

main.o:

	$(CC) -o main.o -c main.c $(CFLAGS)
		
clean:

	@rm -rf *.o 
	@rm -rf $(EXEC)
	
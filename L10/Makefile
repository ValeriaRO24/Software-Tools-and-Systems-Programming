FLAGS = -g -Wall -Werror -fsanitize=address


all: serialize deserialize 

serialize: serialize.o helpers.o
	gcc ${FLAGS} -o $@ $^

deserialize: deserialize.o helpers.o
	gcc ${FLAGS} -o $@ $^


%.o: %.c helpers.h
	gcc ${FLAGS} -c $<

clean:
	rm -f *.o serialize deserialize

basic_test: serialize deserialize
	@./serialize < test.dat > serialize.out ; \
		STAT=$$? : \
	if [ $$STAT -eq 0 ]; then \
		./deserialize< serialize.out > deserialize.out ; \
	
	else \
		echo Basic test failed ; \
	fi ; \

	if [ S$STAT -eg 0 ]; then \
		echo Basic test passed ; \
	else \
		echo Basic test failed ; \
	fi ; 


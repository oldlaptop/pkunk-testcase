default: pkunk-testcase

clean:
	rm -f pkunk-testcase *.o

pkunk-testcase: pkunk-testcase.o random.o
	cc $(LDFLAGS) -opkunk-testcase pkunk-testcase.o random.o


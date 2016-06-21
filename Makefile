default: pkunk-testcase

pkunk-testcase: pkunk-testcase.o random.o
	cc $(LDFLAGS) -opkunk-testcase pkunk-testcase.o random.o

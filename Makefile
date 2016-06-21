default: pkunk-testcase

pkunk-testcase: pkunk-testcase.o random.o
	cc -opkunk-testcase pkunk-testcase.o random.o

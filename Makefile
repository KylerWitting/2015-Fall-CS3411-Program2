CC       = gcc

OBJ_FILE = asort.o
EXE_FILE = asort

${EXE_FILE}: ${OBJ_FILE}
	${CC} -o ${EXE_FILE}  ${OBJ_FILE} 

asort.o: asort.c
	${CC} -c asort.c
					
clean:
	rm -f ${OBJ_FILE} ${EXE_FILE}

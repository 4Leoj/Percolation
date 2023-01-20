CXX := g++
EIGENPATH := C:\Eigen

MAIN := main.cpp
MAIN.x := $(MAIN:%.cpp=%.x)

SIMUL := simul.cpp

${MAIN.x}: ${SIMUL} ${MAIN}
	${CXX} -I ${EIGENPATH}  $^ -o ${MAIN.x}
	@echo "Successful compilation"

example: ${MAIN.x} # Compile and simulate a case with L = 4, p = 0.6.
	./${MAIN.x} 4 0.6

clean: #Borra los archivos intermedios, temporales y ejecutables, dejando limpio el repositorio para que contenga solamente los archivos fundamentales
	rm -rf *.x *.out

# %.png:  # Crear las imágenes con dos niveles diferentes de optimización del compilador.
# %.txt:  # Crear los datos para las imágenes
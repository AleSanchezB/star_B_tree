# Makefile para compilar y ejecutar un programa en C++ 

# Nombre del programa
TARGET = Tree_B

# Compilador
CXX = g++

CXXFLAGS_WARNINGS = -Wall -Wextra -Wpedantic -Werror 

CXXFLAGS_SANITIZE = -fsanitize=address -fsanitize=undefined -fsanitize=shift -fsanitize=integer-divide-by-zero -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=null -fsanitize=return -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=bounds-strict -fsanitize=alignment -fsanitize=object-size -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=nonnull-attribute -fsanitize=returns-nonnull-attribute -fsanitize=bool -fsanitize=enum -fsanitize=vptr 

# Opciones de compilación
CXXFLAGS = -std=c++20 -Wall $(CXXFLAGS_SANITIZE) $(CXXFLAGS_WARNINGS)

# Directorios
SRCDIR = src
DOCDIR = doc
BUILDDIR = build
BINDIR = bin

# Archivos fuente

SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Archivos objeto generados durante la compilación
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

# Regla principal
all: $(BINDIR)/$(TARGET)

# Regla para compilar el programa
$(BINDIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar cada archivo fuente a objeto
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Regla para limpiar archivos generados
clean:
	rm $(BUILDDIR)/* $(BINDIR)/* 

# Regla para ejecutar el programa
run: $(BINDIR)/$(TARGET)
	./$(BINDIR)/$(TARGET)
# Generar documentación
d:
	@doxygen $(DOCDIR)/Doxyfile
	@echo "Documentación generada en $(DOCDIR)/html/index.html"

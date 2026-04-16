CXX = g++
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
BIN_DIR = bin
TARGET = tablahash

# Obtener todos los archivos fuente en src/
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Convertir los archivos fuente en archivos objeto en obj/
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

DEPS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.d)

# Regla principal para compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(BIN_DIR)/$(TARGET)

# Regla para compilar cada archivo fuente en un archivo objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DIR)/%.d
	$(CXX) -c $< -o $@ -I$(INC_DIR)

# Generar las dependencias para cada archivo .cpp
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp
	$(CXX) -MM $< -MF $@ -MT $(OBJ_DIR)/$*.o -I$(INC_DIR)

-include $(DEPS)

clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d $(BIN_DIR)/$(TARGET)
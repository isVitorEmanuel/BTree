# Nome do executável
TARGET = program

# Compilador
CC = g++

# Diretórios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
ASSETS_DIR = assets

# Flags de compilação
CFLAGS = -Wall -Wextra -I$(INC_DIR) -std=c++17

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(SRCS)))

# Regra padrão
all: $(TARGET)

# Criação do executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compilar os arquivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Criar diretório de build, se não existir
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Limpar os arquivos gerados
clean:
	@rm -rf $(BUILD_DIR) $(TARGET)

# Regra para rodar o programa
run: $(TARGET)
	@./$(TARGET) $(ASSETS_DIR)/dadosB.txt

# Regra para remover apenas os arquivos objeto
clean-obj:
	@rm -rf $(BUILD_DIR)/*.o

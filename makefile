CC = gcc
CFLAGS = -Wall -Wextra -pthread
SRC_DIR = challenges
BUILD_DIR = build
TARGETS = mayorchallenge race_condition thread_creation mutex mutex2 variables_condicion variables_condicion2

# Regla principal
all: $(addprefix $(BUILD_DIR)/, $(TARGETS))

# Regla pattern para construir cualquier ejecutable en build/
$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)  # Asegurar que el directorio existe
	$(CC) $(CFLAGS) -o $@ $<

# Limpiar - solo elimina el directorio build
clean:
	rm -rf $(BUILD_DIR)

# Ayuda
help:
	@echo "Targets disponibles:"
	@echo "  all   - Compilar todos los programas en ./build/"
	@echo "  clean - Eliminar directorio build/"
	@echo "  help  - Mostrar esta ayuda"

.PHONY: all clean help

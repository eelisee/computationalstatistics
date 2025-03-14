# Compiler-Flags speichern
CFLAGS = -Wall -Wextra -O2 -arch arm64

# Definiere die Ziel-Datei
TARGET = myprogram

# Die C-Datei und die entsprechenden Zwischen-Dateien
SRC = main.c
ASM = main.s
OBJ = main.o

# Standardregel zum Erzeugen des Ziels (Binary)
$(TARGET): $(OBJ)
	@echo "Linken der Objektdatei zu einer ausführbaren Datei"
	@gcc $(OBJ) -o $(TARGET)


# Regel für das Erstellen der Objekt-Datei
$(OBJ): $(ASM)
	@echo "Assembler-Datei zu Objekt-Datei kompilieren"
	@gcc -c $(ASM) -o $(OBJ)

	
# Regel zum Erstellen der Assembler-Datei
$(ASM): $(SRC)
	@echo "C-Datei in Assembler umwandeln"
	@gcc $(CFLAGS) -S $(SRC) -o $(ASM)

# Aufräumen: Entfernen von temporären Dateien
clean:
	@echo "Aufräumen: Entfernen von temporären Dateien"
	@rm -f $(ASM) $(OBJ) $(TARGET)

# Phony-Ziele (stellen sicher, dass clean nicht mit einer Datei namens clean verwechselt wird)
.PHONY: clean


# make und make clean verwenden
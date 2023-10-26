# Nom de l'exécutable
TARGET = Suffrage

# Répertoires source
SRCDIR = src
UTILSDIR = $(SRCDIR)/utils
METHODSDIR = $(SRCDIR)/methods
VERIFYDIR = $(SRCDIR)/verify

# Répertoire de documentation
DOCDIR = documentation

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -g -Wno-unused-variable -Wno-unused-parameter
LDFLAGS = -lm

# Liste de fichiers source
SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(UTILSDIR)/*.c) $(wildcard $(VERIFYDIR)/*.c) $(wildcard $(METHODSDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

# Commandes pour générer la documentation
DOXYGEN = doxygen
DOXYFILE = Doxyfile
DOCDIR = documentation

# Commande pour Valgrind
VALGRIND = valgrind

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

doc:
	$(DOXYGEN) ./$(DOCDIR)/$(DOXYFILE)

valgrind:
	$(VALGRIND) ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)
	rm -rf $(DOCDIR)

.PHONY: all clean doc valgrind

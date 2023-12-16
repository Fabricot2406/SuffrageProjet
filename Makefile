# Nom de l'exécutable
TARGET = scrutin

# Répertoires source
SRCDIR = src
OBJDIR = obj
UTILSDIR = $(SRCDIR)/utils
DATADIR = $(UTILSDIR)/dataStructure
METHODSDIR = $(SRCDIR)/methods
VERIFYDIR = $(SRCDIR)/verify
# Répertoire de documentation
DOCDIR = documentation
# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -g 
LDFLAGS = -lm

# Liste de fichiers source
SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(UTILSDIR)/*.c) $(wildcard $(DATADIR)/*.c) $(wildcard $(VERIFYDIR)/*.c) $(wildcard $(METHODSDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Commandes pour générer la documentation
DOXYGEN = doxygen
DOXYFILE = Doxyfile
DOCDIR = documentation

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

doc:
	$(DOXYGEN) $(DOXYFILE)

clean:
	rm -f $(TARGET)
	rm -rf $(DOCDIR)
	rm -rf $(OBJDIR)

.PHONY: all clean doc valgrind

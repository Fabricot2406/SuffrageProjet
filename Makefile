# Nom de l'exécutable
TARGET = scrutin

# Répertoires source
SRCDIR = src
OBJDIR = obj
TESTDIR = tests
UTILSDIR = $(SRCDIR)/utils
DATADIR = $(UTILSDIR)/dataStructure
METHODSDIR = $(SRCDIR)/methods
VERIFYDIR = $(SRCDIR)/verify
OUTPUTDIR = $(TESTDIR)/output/result
LOGDIR = $(TESTDIR)/output/log

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
ifeq ($(TEST),cm)
	@$(BASH) ./tests/test_script_cm.sh
else ifeq ($(TEST),cp)
	@$(BASH) ./tests/test_script_cp.sh
else ifeq ($(TEST),cs)
	@$(BASH) ./tests/test_script_cs.sh
else ifeq ($(TEST),uni)
	@$(BASH) ./tests/test_script_uni.sh
else ifeq ($(TEST),jm)
	@$(BASH) ./tests/test_script_jm.sh
else ifeq ($(TEST),all)
	@$(BASH) ./tests/test_script_cp.sh
	@$(BASH) ./tests/test_script_cm.sh
	@$(BASH) ./tests/test_script_cs.sh
	@$(BASH) ./tests/test_script_uni.sh
	@$(BASH) ./tests/test_script_jm.sh
endif

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
	rm -f $(OUTPUTDIR)/*.txt
	rm -f $(LOGDIR)/*.txt

.PHONY: all clean doc valgrind

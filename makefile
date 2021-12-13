
all: 
	@echo "Veuillez choisir une cible parmi : $(TARGETS)"
	@echo "Les exécutables seront produits dans les sous-répertoires correspondants"
	@echo "Le bouton \"Run\" de l'interface de Repl.it ne doit pas etre utilisé"
	@echo "N'oubliez pas d'exécuter la commande source setup_env.sh"

.PHONY: $(TARGETS)
$(TARGETS) :
	@echo Execution de make $@ :
	@cd $@; make

$(CLEANTARGETS) : 
	@echo Execution de clean $(subst clean_,,$@) :
	@cd $(subst clean_,,$@); make clean

clean: $(CLEANTARGETS)





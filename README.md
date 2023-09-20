# meteo  
  
## Commande coté PC  
Commande pour récupérer le fichier index.html depuis le PC:  
wget 127.0.0.1:8080/index.html  
  
Compiler le programme pour PC, lcPC pour la carte lc.  
  
Le fichier index.html peut également être ouvert depuis mozilla à l'adresse:  
http://127.0.0.1:8080/index.html  
  
## Commandes du coté de la carte  
Dans le fichier /var/spool/cron/crontabs/jpm la ligne:  
* * * * * /bin/ginfos  
permet de lancer le programme pour les graphiques toutes les minutes.  
Le programme peut être lancé manuellement par la commande **ginfos**.  
  
Pour lancer le daemon httpd:  
httpd -u jpm  
  
Un fichier index.html a été crée et permet un affichage des graphiques produits depuis un navigateur.  
  
## Ressources  
Prg de base interrogeant un site distant:  
https://www.youtube.com/watch?v=QwCT7Ga4BG8  
  
## Ressources curl:  
https://curl.se/libcurl/c/libcurl-tutorial.html  

### Ressource gdlib:  
https://libgd.github.io/  
  
### Ressource json:
https://json.nlohmann.me/  


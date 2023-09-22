# meteo  
  
httpd -p 8080 -h /home/jpm  

## Installation:  
Buildroot:  
-Decompacter buildroot  
-lancer make xconfig dans le répertoire buildroot-2023.08  
-Dans librairie/Graphics coché gd puis, fenêtre de gauche gdtopng et pngtogd  
-Dans Toolchain cocher Enable C++ support  
-Dans JSON/XML cocher json for modern c++ et libjson  
-Dans Networking cocher libcurl  
-Faire un make dans le répertoire buildroot-2023.08  
Busybox:  
-Faire un make menuconfig dans le répertoire buildroot-2023.08/output/build/busybox-1.36.1  
-Dans menuconfig rechercher Networkink. Dans ce sous menu, cocher la case httpd  
Buildroot: configuration pour application.  
-Dans le repertoire buildroot-2023.08 créer les répertoire bin, usr, var, etc, home  
-Dans le répertoire buildroot-2023.08/bin sera placé l'exécutable du projet meteo **ginfos**  
-Dans le répertoire home, créer un répertoire utilisateur par exemple jpm  
-C'est dans le répertoire jpm que sera placé **index.html**.  
Configuration clavier:  
- Le fichier S10Keyboard permet de generer le fichier azerty.kmap.  
-Une fois le fichier kmap généré le placer dans overlay/etc.  
-Placer S10Keyboard dans overlay/etc/init.d.  
Configuration de crontabs:  
- 
-Revenir dans le repertoire buildroot-2023.08 et lancer la commande make  


## Commande coté PC  
Commande pour récupérer le fichier index.html depuis le PC:  
wget 127.0.0.1:8080/index.html  
  
Compiler le programme pour PC, lcPC pour la carte lc.  
  
Lancement de l'émulateur carte: go.sh  
  
Le fichier index.html peut également être ouvert depuis mozilla à l'adresse:  
http://127.0.0.1:8080/index.html  
  
## Commandes du coté de la carte  
Dans le fichier /var/spool/cron/crontabs/jpm la ligne "* * * * * /bin/ginfos" permet de lancer le programme pour les graphiques toutes les minutes.  
Le programme peut être lancé manuellement par la commande **ginfos**.  
  
Pour lancer le daemon (en root) httpd:  
httpd -u jpm  
  
Un fichier index.html a été crée et permet un affichage des graphiques produits depuis un navigateur.  
  
## Amélioration possible:  
- La longitude et la latitude pourrait être paramétrable et utiliser une api pour configurer ces paramètres en fonction du nom de la ville recherchée.  
- Certaines api reetournent un le nom d'un fichier icone représentant la météo du jour. Ce fichier peut être récupéré et affiché.  
  
## Ressources  
Prg de base interrogeant un site distant:  
https://www.youtube.com/watch?v=QwCT7Ga4BG8  
  
## Ressources curl:  
https://curl.se/libcurl/c/libcurl-tutorial.html  

### Ressource gdlib:  
https://libgd.github.io/  
  
### Ressource json:
https://json.nlohmann.me/  
  
### Ressource url pour la météo:  
api.open-meteo.com/v1/forecast?latitude=43.5283&longitude=5.4497&hourly=temperature_2m,windspeed_10m,winddirection_10m  

### Autre ressource url pour la météo:  
api.openweathermap.org/data/2.5/weather?lat=43.5283&lon=5.44973&appid=fb7ea3ac85bb67a9bdb0b4b9a51f1c72&units=metric  
  
## Bugs  
Le fichier png generé depuis la carte ne semble pas correct et provoque l'erreur "cannot be displayed because it contents errors". Ce même fichier s'il est produit coté pc s'affiche sans problème.  


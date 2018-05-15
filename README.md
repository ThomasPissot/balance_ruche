﻿# Amplificateur convertisseur HX711

# Description
le module HX711 est un amplificateur pour capteurs de force à pont de Wheatstone associé à un convertisseur analogique-numérique. Les données  sont transmises sur un bus SPI de type propriétaire qui utilise une ligne d'horloge (SCK) et de données (DOUT).  Le nombre d'impulsions d'horloge permet de configurer le gain de l'amplificateur. 

 - 25 impulsions permet de configurer un gain à 128
 - 26 impulsions gain = 64
 - 27 impulsions gain = 32
 
le driver **SPI** (Serial Peripheral Interface) du noyau linux permet seulement de créer des impulsions d'horloge par multiple de 8, pour contourner cette limitation l'idée originale consiste à utiliser la ligne de données MOSI du bus SPI pour générer les 25 impulsions d'horloge. En écrivant la valeur **10101010** (0xaa en hexadécimal), nous obtenons 4 impulsions. Il suffit donc d'envoyer 6 fois cette valeur pour obtenir 24 impulsions, puis d'écrire la valeur 0x80 pour obtenir la 25 éme impulsions.
 
# Câblage 
 ![enter image description here](https://lh3.googleusercontent.com/-mNRDYTpVxts/WtIt_MIavBI/AAAAAAAANyg/fXT3A7exa583gZPzQeLJxO3L85qElCM2QCLcBGAs/s0/schema-HX711.png "schema-HX711.png")


# Changelog

**14/04/2018 : ** Ajout du README . 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER**
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


# balance_ruche

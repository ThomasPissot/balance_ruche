/**
 *  @file     main.cpp
 *  @author   Philippe SIMIER (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     15 avril 2018
 *  @brief    programme balance
 *            compilation: g++ main.cpp hx711.cpp  spi.c  -o main

 *  @author   Thomas PISSOT (Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     10 mai 2018
 *  @brief    programme balance avec enregistrement vers MySQL
 *            compilation: g++ main.cpp hx711.cpp  spi.c -L/usr/lib/mysql -lmysqlclient -o main
 *
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include </usr/include/mysql/mysql.h>


using namespace std;

class c_Bdd
{
public:
    MYSQL Mmysql;
    MYSQL_RES *result;
    MYSQL_ROW row;

    // le constructeur
    c_Bdd();
    // le destructeur
    ~c_Bdd();
    // Méthode pour obtenir la valeur du poids
    void TareAFaire(int pTare);
    bool connecter(std::string DestServeur);
private:
};



/**
 *  @file     bdd.cpp
 *  @author   Thomas PISSOT(Touchard Wahington le Mans)
 *  @license  BSD (see license.txt)
 *  @date     15 mai 2018
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
#include "bdd.h"
#include <cstring>

const std::string ADR_SERVEUR_LOCAL = "127.0.0.1";
const std::string ADR_SERVEUR_DISTANT = "192.168.0.17";
const std::string LOGIN_MARIADB = "root";
const std::string PASSWORD_MARIADB = "touchard72";
const std::string BASE = "mysql";

using namespace std;

bool c_Bdd::connecter(std::string DestServeur)
{
    bool resultat=false;
    if (mysql_init(&Mmysql) != NULL)
    {
        mysql_options(&Mmysql,MYSQL_READ_DEFAULT_GROUP,"option");
        printf("mysql_init réussi ! ");
        if(mysql_real_connect(&Mmysql,DestServeur.c_str(),LOGIN_MARIADB.c_str(),PASSWORD_MARIADB.c_str(),BASE.c_str(),0,NULL,0))
        {
            printf("Connexion et initialisation réussie à la BDD locale!");
            resultat  =true;
         }
         else
         {
            printf("Connexion impossible à la BDD locale !");
         }
    }
    else
    {
        printf("In initialisation impossible à la BDD locale !");
    }

    return(resultat);
}


void c_Bdd::TareAFaire(int pTare)
{
    bool resultat=false;
    char *pChar;
    unsigned int i = 0;
    unsigned int num_champs = 0;
    result = NULL;
    row = NULL;

   if (mysql_init(&Mmysql) != NULL)
    {
        mysql_options(&Mmysql,MYSQL_READ_DEFAULT_GROUP,"option");
        printf("mysql_init réussi ! ");
        if(mysql_real_connect(&Mmysql,ADR_SERVEUR_LOCAL.c_str(),LOGIN_MARIADB.c_str(),PASSWORD_MARIADB.c_str(),BASE.c_str(),0,NULL,0))
        {   printf("Connexion réussie à la BDD locale!");
            //à nouveau la requête qui sélectionne tout dans ma table ex_1
            mysql_query(&Mmysql, "SELECT CmdTare FROM RUCHE.config");

            result = mysql_use_result(&Mmysql);

            while (( row =  mysql_fetch_row(result)))
              {

                pChar = new char[ strlen(row[0])+1 ];
                strcpy(pChar, row[0]);
                printf(pChar);
                printf("\n");

              }
        }
    }
/*
        //On déclare un tableau de char pour y stocker la requete

    char requete[150] = "";
    //On stock la requete dans notre tableau de char

    sprintf(requete, "insert into `RUCHE`.`Pesees` VALUES ( CURRENT_TIMESTAMP(),'%.2f','%.2f')", 2.45,2.0);

    //On execute la requete
    mysql_query(&mysql, requete);
*/
}
c_Bdd::c_Bdd()
{
}
c_Bdd::~c_Bdd()
{
}

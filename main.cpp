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
 *            compilation: g++ main.cpp hx711.cpp bdd.cpp  spi.c -L/usr/lib/mysql -lmysqlclient  -o main

*/

#include <iostream>
#include <iomanip>
#include "hx711.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include </usr/include/mysql/mysql.h>
#include "bdd.h"
#include <cstring>

void TareAFaire(int pTare);

const std::string ADR_SERVEUR_LOCAL = "127.0.0.1";
const std::string ADR_SERVEUR_DISTANT = "192.168.0.17";
const std::string LOGIN_MARIADB = "root";
const std::string PASSWORD_MARIADB = "touchard72";
const std::string BASE = "mysql";


using namespace std;

int main()
{
    //class hx711 dans hx711.h
    hx711 balance;

    float xn;
    float yn   = 0.0;
    float yn_1 = 0.0;
    char  stable;
    int offset;



//Si l'apiculteur demande la tare, on execute la fonction
    //lecture du champ CmdTare de la table config Bdd locale
    //valeur à 1 = lancement de la fonction effectuerTarage

        //connexion base locale pour savoir s'il faut faire la tare


//    ConnexionBDD.connecter(ADR_SERVEUR_LOCAL);
    c_Bdd ConnexionBDD;


    //offset = balance.effectuerTarage();
/*    if (ConnexionBDD.connecter(ADR_SERVEUR_LOCAL) == true)
    {
        ConnexionBDD.TareAFaire(balance.obtenirPoids());
        //TareAFaire(offset);
    }
*/
        ConnexionBDD.TareAFaire(balance.obtenirPoids());

    //execution de la fonction dans hx711.cpp
    //balance.effectuerTarage();

    while(1)
    {
	xn = balance.obtenirPoids();
	// Filtrage passe bas du premier ordre constante de temps 2.Te  (20ms)
        // Filtre passe bas du premier ordre constante de temps 10.Te (100ms)
        // yn = 0,091.xn + 0,91.yn-1;
	yn = 0.33 * xn + 0.66 * yn_1;

	// calcul de la dérivée
	if ((yn_1 - yn) < 0.1 && (yn_1 - yn) > - 0.1)
            stable = '*';
        else stable = ' ';
        yn_1 = yn;

        cout << stable << " " << yn << fixed << setprecision (1) << " g" << endl;


        usleep(1000000);
        //system("clear");
    }
}


void TareAFaire(int pTare)
{       char *pChar;
        MYSQL mysql;
        if (mysql_init(&mysql) != NULL)
            {
            printf("mysql_init réussi ! ");
            mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
            if(mysql_real_connect(&mysql,"127.0.0.1","root","touchard72","mysql",0,NULL,0))

                {
                                //Déclaration des pointeurs de structure
            MYSQL_RES *result = NULL;
            MYSQL_ROW row = NULL;

            unsigned int i = 0;
            unsigned int num_champs = 0;

            // Cette fois, on va lire les données
            printf("\nCette fois, on va lire les donnees :\n");
            //à nouveau la requête qui sélectionne tout dans ma table ex_1
            mysql_query(&mysql, "SELECT CmdTare FROM RUCHE.config");


            result = mysql_use_result(&mysql);


            while (( row =  mysql_fetch_row(result)))
              {

                pChar = new char[ strlen(row[0])+1 ];
                strcpy(pChar, row[0]);
                printf(pChar);

              for(i = 0; i < num_champs; i++)
                {
                printf("OK [%s]",row[i]);
                }
              printf("\n");
              }



                    //On déclare un tableau de char pour y stocker la requete
                    char requete[150] = "";
                    //On stock la requete dans notre tableau de char

                    sprintf(requete, "insert into `RUCHE`.`Pesees` VALUES ( CURRENT_TIMESTAMP(),'%.2f','%.2f')", 3.5,3.9);

                    //On execute la requete

                    mysql_query(&mysql, requete);






            mysql_close(&mysql);

                    printf("Connexion réussie et refermée à la BDD!");
                }
            else
                {
                    printf("Une erreur s'est produite lors de la connexion à la BDD!");
                }

            }
        else
        {
            printf("Une erreur s'est produite lors de mysql_init à la BDD!");
        }


}

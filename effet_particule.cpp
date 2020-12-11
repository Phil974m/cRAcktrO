/***************************************************
****************************************************
**                                                **
**                                                **
**           classe "effet_particule_3"           **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/
#include "stdafx.h"
//on inclut les entêtes
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>

const float pi = 3.14159f;

//on inclut le fichier header de cette classe
#include "effet_particule.h" //on met les guillemets car ce fichier se trouve dans le même dossier

//initialise une particule
void effet_particule_3::init_particule(int particulesz)
{
        int x_res;
        int y_res;

        //on calcule les coordonnées de départ en fonction des dimensions de l'image et des particules
        x_res = ((particulesz * m_dim_part - m_dim_part) / m_hauteur_img);
        y_res = (((particulesz * m_dim_part - m_dim_part) % m_hauteur_img) / m_dim_part);
        t_particules[particulesz].x = m_x + float(x_res * m_dim_part);
        t_particules[particulesz].y = m_y - float(y_res * m_dim_part);
        t_particules[particulesz].z = m_z;

        //on calcule les coordonnées de la texture
        t_particules[particulesz].c_tex_x = float(m_taille_tex_part_x * x_res); //(m_dim_part * x_res) / m_largeur_img;
        t_particules[particulesz].c_tex_y = 1 - float(m_taille_tex_part_y * y_res); //(m_dim_part * y_res) / m_hauteur_img;

        //direction
        //t_particules[particulesz].d_x = (double(rand()%1000)-500)/1000;
        //t_particules[particulesz].d_y = (-double(rand()%2000))/1000;
        t_particules[particulesz].d_z = (double(rand()%100)-50)/10;

        //vitesse
        t_particules[particulesz].vitesse = 1;

        //vie
        t_particules[particulesz].vie = 0.0;

        //taille
        //t_particules[particulesz].taille = 80;

        //durée
        t_particules[particulesz].temps = 0;
        t_particules[particulesz].temps_tot = 5000;

        //état
        t_particules[particulesz].etat = 1; //le début
}


//constructeur par défaut
effet_particule_3::effet_particule_3( float x, float y, float z, int temps, int vitesse , int largeur_img , int hauteur_img , int dim_part )
{
        //on initialise certaines variables
        //signifie que la classe est active (0 = morte)
        etat = 1;

        //coordonnées
        m_x = x;
        m_y = y;
        m_z = z;

        //on calcule le nombre maximum de particules à afficher en fonction des dimensions de l'image et des particules
        m_nombre_tot = (largeur_img / dim_part) * (hauteur_img / dim_part);

        //nombre de particules actives
        m_nombre_actifs = 0;

        //temps
        m_temps = 0;
        m_temps_tot = temps;

        //vitesse à lequelle le temps s'écoule
        m_vitesse = vitesse;

        //on détermine notre multiplicateur
        m_multi_sz = 360 / 100;

        //on crée le tableau de particules
        m_nombre_tot++;
        t_particules = new particules[m_nombre_tot];

        //nombre de morts
        morts = 0;

        //les dimensions de l'image à afficher
        m_largeur_img = largeur_img;
        m_hauteur_img = hauteur_img;

        //les dimensions ds particules
        m_dim_part = dim_part;

        //on calcule la taille d'un morceau de texture par rapport à la taille d'une particule
        m_taille_tex_part_x = float(m_dim_part) / float(m_largeur_img);
        m_taille_tex_part_y = float(m_dim_part) / float(m_hauteur_img);

        //on initialise les particules

        //for(int i = 1 ; m_nombre_tot > i ; i++ )
        //{
        //      init_particule(i);

        //}

        m_nombre_actifs = 0; //m_nombre_tot;
        //m_nombre_tot--;
}

//destructeur
effet_particule_3::~effet_particule_3( )
{

        //rien pour le moment

}

//on calcul la position de la particule en fonction de la vitesse
void effet_particule_3::calculer( int msec , int &test )
{
        int i = 0;

        //on incrémente la variable temps
        m_temps += m_vitesse * msec;

        //on vérifie qu'on est pas au bout
        if(m_temps >= m_temps_tot)
        {
                for(i = 1 ; i < 100 ; i++)
                {
                        //on affiche les particules petit à petit
                        if(m_nombre_actifs < m_nombre_tot)
                        {
                                //on incrémente la valeur m_nombre_actifs
                                m_nombre_actifs++;

                                //on initialise la dernière particule activée
                                init_particule(m_nombre_actifs);

                        }else{

                                break;

                        }
                }

                //on réinitialise la variable temps
                m_temps = 0;
        }

        //test = morts;

        //pourcentage
        float prct;

        //on met à jour les valeurs de chaque particules actives
        for(i = 1 ; i < m_nombre_actifs ; i++)
        {

                //test = t_particules[i].c_tex_x;

                //on effectue les différentes opération en fonction de l'état de la particule
                if(t_particules[i].etat == 1)
                {
                        //on incrémente la variable temps de la particule
                        t_particules[i].temps += (m_vitesse * msec);

                        //on vérifie si on a été jusqu'au bout
                        if(t_particules[i].temps >= t_particules[i].temps_tot)
                        {
                                //on détermine le %
                                prct = 100;

                                //on change l'état
                                t_particules[i].etat = 2;

                                //on réinitialise le temps de cette particule
                                t_particules[i].temps = 0;
                                t_particules[i].temps_tot = 2000 + (rand()%5000);

                        }else
                        {
                                //on calcule le pourcentage du rapport entre le temps courrant et le temps total
                                prct = (float(t_particules[i].temps) / float(t_particules[i].temps_tot)) * 100;
                                //prct = prct * (2 - (1 / 100 * prct));
                        }

                        //on augmente sa vie par rapport au pourcentage
                        t_particules[i].vie = 0.01f * prct;

                }else if(t_particules[i].etat == 2)
                {
                        //on diminue l'opacité de la particule

                        //on incrémente la variable temps de la particule
                        t_particules[i].temps += (m_vitesse * msec);

                        //on vérifie si on a été jusqu'au bout
                        if(t_particules[i].temps >= t_particules[i].temps_tot)
                        {
                                //on change l'état
                                t_particules[i].etat = 3;

                                //on réinitialise le temps de cette particule
                                t_particules[i].temps = 0;
                                t_particules[i].temps_tot = 2000;

                        }

                }else if(t_particules[i].etat == 3)
                {
                        //on diminue l'opacité de la particule

                        //on incrémente la variable temps de la particule
                        t_particules[i].temps += (m_vitesse * msec);

                        //on vérifie si on a été jusqu'au bout
                        if(t_particules[i].temps >= t_particules[i].temps_tot)
                        {
                                //on change l'état
                                t_particules[i].etat = 0;

                                //on augmente le nombre de particules mortes
                                morts++;

                        }else
                        {
                                //on calcule le pourcentage du rapport entre le temps courrant et le temps total
                                prct = (float(t_particules[i].temps) / float(t_particules[i].temps_tot)) * 100;
                                //prct = prct * (2 - (1 / 100 * prct));

                                //on diminue sa vie par rapport au pourcentage
                                t_particules[i].vie = 1.0f - (0.01f * prct);

                        }

                        //on déplace la particule sur l'axe z
                        t_particules[i].z = t_particules[i].z + t_particules[i].d_z;

                }

        }

        if(morts >= m_nombre_tot - 1)
        {
                m_nombre_actifs = 0;
                morts = 0;
        }
}

//on affiche la lettre
void effet_particule_3::afficher()
{

        glBegin(GL_QUADS);

        //on affiche toutes les particules actives
        for(int i = 1 ; i < m_nombre_actifs ; i++)
        {
                //on vérifie que cette particule est toujours en vie
                if(t_particules[i].etat > 0)
                {

                        //on détermine la couleur
                        glColor3d( t_particules[i].vie , t_particules[i].vie, t_particules[i].vie );

                        //glBegin(GL_QUADS);
                                glTexCoord2f( t_particules[i].c_tex_x, t_particules[i].c_tex_y );
                                //glTexCoord2f( 0.0f, 1.0f );
                                glVertex3f( t_particules[i].x , t_particules[i].y, t_particules[i].z );

                                glTexCoord2f( t_particules[i].c_tex_x , t_particules[i].c_tex_y - m_taille_tex_part_y );
                                //glTexCoord2f( 0.0f, 0.25f );
                                glVertex3f( t_particules[i].x, t_particules[i].y - m_dim_part, t_particules[i].z );

                                glTexCoord2f( t_particules[i].c_tex_x + m_taille_tex_part_x, t_particules[i].c_tex_y - m_taille_tex_part_y );
                                //glTexCoord2f( 0.75f, 0.25f );
                                glVertex3f( t_particules[i].x + m_dim_part, t_particules[i].y - m_dim_part, t_particules[i].z );

                                glTexCoord2f( t_particules[i].c_tex_x + m_taille_tex_part_x, t_particules[i].c_tex_y );
                                //glTexCoord2f( 0.75f, 1.0f );

                }
        }


        glEnd();
}
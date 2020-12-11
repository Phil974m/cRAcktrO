/***************************************************
****************************************************
**                                                **
**                                                **
**                 classe "camera"                **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/
#include "stdafx.h"
//headers
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>

//on inclut le fichier header de cette classe
#include "camera.h" //on met les guillemets car ce fichier se trouve dans le m�me dossier

//constructeur par d�faut
camera::camera( double x_t, double y_t, double z_t, double x_v, double y_v, double z_v , double distance )
{
        //on initialise certaines variables
        //le point "cible" de la cam�ra (l� o� elle regarde)
        m_x_t = x_t;
        m_y_t = y_t;
        m_z_t = z_t;

        //la position de la cam�ra
        m_x_v = x_v;
        m_y_v = y_v;
        m_z_v = z_v;

        //la distance qui s�pare la cible de la cam�ra
        m_distance = distance;

        //rot
        rot = 270;

        //l'�tat de la cam�ra (1 = active)
        etat = 1;
}

//destructeur
camera::~camera( )
{

        //rien pour le moment

}

//on calcul la position de la cam�ra
void camera::calculer( int msec )
{
        //on augmente le degr� de rotation de la cam�ra
        //rot += ((float)(msec) / 10.0f);
        //rot = 270;
        //on v�rifie qu'on ne va pas trop loin
        //if(rot > 360)
        //{
        //      rot = rot - 360;
        //}

        //on calcule les coordonn�es de la cam�ra
        m_x_v = cos((rot / 360) * 2 * 3.141) * m_distance + m_x_t;
	    m_z_v = sin((rot / 360) * 2 * 3.141) * m_distance + m_z_t;

        //m_x_v = m_distance;
        //m_z_v = m_distance;
        //m_y_v = y_v;
        //m_y_v = sin((rot / 360) * 2 * 3.141) * m_distance + m_z_t;

        gluLookAt ( m_x_v , m_y_v , m_z_v , m_x_t , m_y_t , m_z_t , 0 , 1 , 0 );
}

/***************************************************
****************************************************
**                                                **
**                                                **
**        ent�te classe "effet_particule_3"       **
**                                                **
**             simulation d'un nuage              **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

//ceci sert � ce qu'on ne charge pas deux fois le m�me header
#ifndef C_EFFET_PARTICULE_3_H

	#define C_EFFET_PARTICULE_3_H

	class effet_particule_3

	{
		
		//les donn�es "priv�es" (variables, fonctions...)
		private:
						
			//structure qui va contenir les informations de chaque particules
			struct particules {
				//coordonn�es
				float x;
				float y;
				float z;
				//vitesse
				int vitesse;
				//direction
				float d_x;
				float d_y;
				float d_z;
				//coordonn�es de la texture
				float c_tex_x;
				float c_tex_y;
				//vie
				float vie;
				//�tat
				int etat;
				//dur�e (permet d'avoir une mesure du temps)
				int temps;
				int temps_tot;
			};

			//on cr�e notre tableau
			particules* t_particules;

			//multiplicateur
			float m_multi_sz;

			//permet d'avoir une mesure du temps
			int m_temps;
			int m_temps_tot;

			//permet de savoir combien de particules sont mortes
			int morts;
			
			//taille d'une particule relative aux coordonn�es d'une texture
			float m_taille_tex_part_x;
			float m_taille_tex_part_y;
		
		//les donn�es publiques
		public:
			
			//�tat de la classe
			int etat;

			//les coordonn�es (x, y, z)
			float m_x;
			float m_y;
			float m_z;

			//le nombre max de particules � afficher
			int m_nombre_tot;

			//le nombre de particules couramment affich�es
			int m_nombre_actifs;

			//vitesse � laquelle le temps s'�coule
			int m_vitesse;

			//les dimensions de l'images � afficher
			int m_largeur_img;
			int m_hauteur_img;

			//les dimensions des particules
			int m_dim_part;

			//***********
			//FONCTIONS
			//***********

			//le constructeur par d�faut
			effet_particule_3( float x, float y, float z, int temps, int vitesse , int largeur_img , int hauteur_img , int dim_part );

			//le destructeur
			~effet_particule_3( );
			
			//calcul de la position des particules
			void calculer( int msec , int &test );
		
			//affichage des particules
			void afficher();

			//fonction d'initialisation d'une particule
			void init_particule( int particulesz );
	};


#endif
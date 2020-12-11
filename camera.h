/***************************************************
****************************************************
**                                                **
**                                                **
**             ent�te classe "camera"             **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

//ceci sert � ce qu'on ne charge pas deux fois le m�me header
#ifndef C_CAMERA_H

	#define C_CAMERA_H

	class camera

	{
		
		//les donn�es "priv�es" (variables, fonctions...)
		private:
		
		//les donn�es publiques
		public:
			
			//�tat de la classe
			int etat;
			
			//les coordonn�es du point vers lequel la cam�ra "regarde"
			double m_x_t;
			double m_y_t;
			double m_z_t;

			//les coordonn�es de la cam�ra
			double m_x_v;
			double m_y_v;
			double m_z_v;

			//la distance qui s�pare la cible de la cam�ra
			double m_distance;

			//la rotation en �
			double rot;

			//le constructeur par d�faut
			camera( double x_t, double y_t, double z_t, double x_v, double y_v, double z_v , double distance );

			//le destructeur
			~camera( );
			
			//calcul de la position des particules
			void calculer( int msec );

	};


#endif
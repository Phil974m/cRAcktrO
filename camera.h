/***************************************************
****************************************************
**                                                **
**                                                **
**             entête classe "camera"             **
**                                                **
**                  Thomas John                   **
**           thomas.john@open-design.be           **
**                                                **
**                                                **
****************************************************
***************************************************/

//ceci sert à ce qu'on ne charge pas deux fois le même header
#ifndef C_CAMERA_H

	#define C_CAMERA_H

	class camera

	{
		
		//les données "privées" (variables, fonctions...)
		private:
		
		//les données publiques
		public:
			
			//état de la classe
			int etat;
			
			//les coordonnées du point vers lequel la caméra "regarde"
			double m_x_t;
			double m_y_t;
			double m_z_t;

			//les coordonnées de la caméra
			double m_x_v;
			double m_y_v;
			double m_z_v;

			//la distance qui sépare la cible de la caméra
			double m_distance;

			//la rotation en °
			double rot;

			//le constructeur par défaut
			camera( double x_t, double y_t, double z_t, double x_v, double y_v, double z_v , double distance );

			//le destructeur
			~camera( );
			
			//calcul de la position des particules
			void calculer( int msec );

	};


#endif
// OpenGLAnim.cpp : implementation file
//

#include "stdafx.h"
#include "time.h"
#include "CraCktrO_test.h"
#include "OpenGLAnim.h"
#include <gl\glaux.h>		// Header File For The Glaux Library
#include <GL/glut.h>
#include "starfield.h"

//entête de la classe "effet_particule_3"
#include "effet_particule.h"
//entête de la classe "camera"
#include "camera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Timer
void TimerInit();
void TimerUpdate();

extern float Timer_T;

LARGE_INTEGER TimerFreq;	// Timer Frequency.
LARGE_INTEGER TimeStart;	// Time of start.
LARGE_INTEGER TimeCur;		// Current time.
float Timer_T;
int T_Time;

void TimerInit()
{
	QueryPerformanceFrequency(&TimerFreq);
	QueryPerformanceCounter(&TimeStart);
}

void TimerUpdate()
{
	QueryPerformanceCounter(&TimeCur);
	Timer_T = (float)((double)(TimeCur.QuadPart - TimeStart.QuadPart) / (double)TimerFreq.QuadPart);
}

//tableau représentant les différentes touches du clavier
bool touche[256];

GLuint	texture[7];			// Storage For Our Five Textures
GLuint	loop;				// Generic Loop Variable
GLfloat	roll;				// Rolling Texture
bool	scene;				// Which Scene To Draw
bool	masking=TRUE;		// Masking On/Off



GLfloat xrot; // Paramêtre  x pour la rotation
GLfloat yrot; // Paramêtre  y    "		" 
GLfloat zrot;

#ifndef M_PI            // Défini PI
#define M_PI 3.14159265
#endif
GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f }; //
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f }; // Lumière diffuse
GLfloat LightPosition[]=	{ 0.0f, 0.0f, -5.0f, 1.0f };// Position de la lumière
GLuint  texture_a[6];     // Tableau contenant 7 textures
///////////////////////////////////////////////////////////////////////////////////
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = {1.3, 1.2, 1.2, 0.0};

float LightPos[] = { 0.0f, 5.0f,-4.0f, 1.0f};			// Light Position
float LightAmb[] = { 0.2f, 0.2f, 0.2f, 1.0f};			// Ambient Light Values
float LightDif[] = { 1.0f, 1.0f, 1.0f, 1.0f};			// Diffuse Light Values
float LightSpc[] = {-0.2f, -0.2f, -0.2f, 1.0f};			// Specular Light Values
///////////////////////////////////////////////////////////////////////////////////
static float v1;
static float v2[2];

//contient l'hwnd de la fenêtre
HWND hWnd;

//contient l'hdc
HDC	DC;
HGLRC RC;

HINSTANCE hInstance;

//spécifie si on est en mode Fullscreen ou en mode fenêtre (par défaut -> fenêtre)
bool fullscreen=FALSE;

//spécifie que le programme est actif (la boucle se termine quand b_actif est à false)
bool b_actif=FALSE;

//ces tableaux vont contenir les coordonnées z de chaque particules afin de les afficher
//dans l'ordre
float ordre_z[100000];
int ordre_type[100000];
int ordre_index[100000];

//cette variable contient le nombre maximum de particules à afficher
int ordre_max=0;

//===============
// les textures
//===============

//une image quelconque
unsigned tex_image;

//===============

//l'effet de particule n°3
/*
############################################################################################

	le dernier paramètre correspond à la taille des particules
	pour que l'effet soit bien rendu, il est nécessaire d'utiliser des puissances de 2 :
	1 , 2 , 4 , 8 , 16 , 32 , 64 , 128 ...
	ici la taille de l'image est de 256, donc 128 est la valeur minimale à utiliser.
	Au plus cette valeur est petite, au plus de particules seront nécessaires pour
	afficher la totalité de l'image

############################################################################################
*/
effet_particule_3 *particules_9 = new effet_particule_3( 0 , 0 , 0 , 1 , 1 , 256 , 256 , 1);


//on crée une instance de la classe "camera"
camera *camera_1 = new camera( 128 , -128 , 0 , 128 , -128 , 0 , -750 );


//permet de calculer le nombre de millisecondes écoulées entre chaque rendu de scène
char images_sec[256];
int temps_1;
int temps_2;
int temps_x;

int fps_1;
int fps_2;
int fps_img_1;
int fps_img_2;

double rot_tmp;
double rot_tmp_2;

int test;

star* stars = NULL;
int num_stars = 150;


void starsfield()
{
	int i;
	int cy;
for (i = 0; i < num_stars; i++) {
        stars[i].x += stars[i].vx;
      if (stars[i].x < glutGet(GLUT_WINDOW_WIDTH)) {
		//	glPushMatrix();
            glBegin(GL_LINE_STRIP);
            glColor3ub(0, 0, 0);
            glVertex2i(stars[i].x-stars[i].vx*4, stars[i].y);
            glColor3ub(255, 255, 255);
            glVertex2i(stars[i].x, stars[i].y);
            glEnd();
		//	glPopMatrix();
      } else {
            stars[i].x = 0;
        }
    }

}
//charge une texture dans la variable indiquée dans le paramètre "texturesz"
int LoadTexture( unsigned &texture_sz , char * fichier_sz)
{
	
	AUX_RGBImageRec *texture_tmp;
    texture_tmp = auxDIBImageLoad(fichier_sz);
	
    glGenTextures (1, &texture_sz);

	glBindTexture(GL_TEXTURE_2D, texture_sz);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture_tmp->sizeX, texture_tmp->sizeY, 0,
	GL_RGB, GL_UNSIGNED_BYTE, texture_tmp->data);
	
	//on retourne TRUE si tout s'est bien passé
	return TRUE;

}

GLvoid LoadGLTexture() // Fonction qui traite la texture 
{
    // Charge la texture 1
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad("z.dat");
	// Créer la texture
	glGenTextures(1,&texture_a[0]);
	glBindTexture(GL_TEXTURE_2D,texture_a[0]);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D,0,3,texture1->sizeX,
	                               texture1->sizeY,
								   0,GL_RGB,GL_UNSIGNED_BYTE,
								   texture1->data);
}

AUX_RGBImageRec *LoadBMP(char *Filename)                // Loads A Bitmap Image
{
        FILE *File=NULL;                                // File Handle
        if (!Filename)                                  // Make Sure A Filename Was Given
        {
                return NULL;                            // If Not Return NULL
        }
        File=fopen(Filename,"r");                       // Check To See If The File Exists
        if (File)                                       // Does The File Exist?
        {
                fclose(File);                           // Close The Handle
                return auxDIBImageLoad(Filename);       // Load The Bitmap And Return A Pointer
        }
        return NULL;                                    // If Load Failed Return NULL
}

int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
{
        int Status=FALSE;                               // Status Indicator
        AUX_RGBImageRec *TextureImage[6];               // Create Storage Space For The Textures
        memset(TextureImage,0,sizeof(void *)*6);        // Set The Pointer To NULL //*5

        if ((TextureImage[0]=LoadBMP("Data/GRNCIRCL.bmp")) &&	// Logo Texture
			(TextureImage[1]=LoadBMP("Data/mask1.bmp")) &&	// First Mask
			(TextureImage[2]=LoadBMP("Data/image1.bmp")) &&	// First Image
			(TextureImage[3]=LoadBMP("Data/mask2.bmp")) &&	// Second Mask
			(TextureImage[4]=LoadBMP("Data/image2.bmp")) &&	// Second Image
			(TextureImage[5]=LoadBMP("Data/Earth.bmp")) )	// Earth
        {
                Status=TRUE;                            // Set The Status To TRUE
                glGenTextures(6, &texture[0]);          // Create Five Textures

				for (loop=0; loop<6; loop++)			// Loop Through All 5 Textures
				{
	                glBindTexture(GL_TEXTURE_2D, texture[loop]);
				//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
			        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
					glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[loop]->sizeX, TextureImage[loop]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop]->data);
				}
        }
		for (loop=0; loop<6; loop++)						// Loop Through All 5 Textures
		{
	        if (TextureImage[loop])							// If Texture Exists
		    {
			        if (TextureImage[loop]->data)			// If Texture Image Exists
				    {
					        free(TextureImage[loop]->data);	// Free The Texture Image Memory
					}
					free(TextureImage[loop]);				// Free The Image Structure
			}
		}
        return Status;                                  // Return The Status
}


int sliding_blend(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glEnable( GL_TEXTURE_2D );
	glLoadIdentity();									// Reset The Modelview Matrix
	glTranslatef(0.0f,0.0f,-1.0f);						// Move Into The Screen 5 Units

	glBindTexture(GL_TEXTURE_2D, texture[0]);			// Select Our Logo Texture
	glBegin(GL_QUADS);
	glColor3f (0.6f, 0.6f, 0.0f);// Start Drawing A Textured Quad
		glTexCoord2f(0.0f, -roll+0.0f); glVertex3f(-2.1f, -1.1f,  0.0f);	// Bottom Left
		glTexCoord2f(15.0f, -roll+0.0f); glVertex3f( 2.1f, -1.1f,  0.0f);	// Bottom Right	
		glTexCoord2f(15.0f, -roll+15.0f); glVertex3f( 2.1f,  1.1f,  0.0f);	// Top Right
		glTexCoord2f(0.0f, -roll+15.0f); glVertex3f(-2.1f,  1.1f,  0.0f);	// Top Left
	glEnd();											// Done Drawing The Quad

    glEnable(GL_BLEND);									// Enable Blending
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing


	if (masking)										// Is Masking Enabled?
	{
		glBlendFunc(GL_DST_COLOR,GL_ZERO);				// Blend Screen Color With Zero (Black)
	}

	if (scene)											// Are We Drawing The Second Scene?
	{
		glTranslatef(0.0f,0.0f,-1.0f);					// Translate Into The Screen One Unit
		glRotatef(roll*360,0.0f,0.0f,1.0f);				// Rotate On The Z Axis 360 Degrees.
		if (masking)									// Is Masking On?
		{
			glBindTexture(GL_TEXTURE_2D, texture[3]);	// Select The Second Mask Texture
			glBegin(GL_QUADS);							// Start Drawing A Textured Quad
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f);	// Bottom Left
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f);	// Bottom Right
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.1f,  1.1f,  0.0f);	// Top Right
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.1f,  1.1f,  0.0f);	// Top Left
			glEnd();									// Done Drawing The Quad
		}

		glBlendFunc(GL_ONE, GL_ONE);					// Copy Image 2 Color To The Screen
		glBindTexture(GL_TEXTURE_2D, texture[4]);		// Select The Second Image Texture
		glBegin(GL_QUADS);								// Start Drawing A Textured Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.1f, -1.1f,  0.0f);	// Bottom Left
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.1f, -1.1f,  0.0f);	// Bottom Right
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.1f,  1.1f,  0.0f);	// Top Right
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.1f,  1.1f,  0.0f);	// Top Left
		glEnd();										// Done Drawing The Quad
	}
	else												// Otherwise
	{
		if (masking)									// Is Masking On?
		{
			glBindTexture(GL_TEXTURE_2D, texture[1]);	// Select The First Mask Texture
			glBegin(GL_QUADS); // Start Drawing A Textured Quad
				glTexCoord2f(sin(roll)+0.0f, cos(roll)); glVertex3f(-2.1f, -1.1f,  0.0f);	// Bottom Left
				glTexCoord2f(cos(roll)+15.0f, sin(roll)); glVertex3f( 2.1f, -1.1f,  0.0f);	// Bottom Right
				glTexCoord2f(roll+15.0f, 15.0f); glVertex3f( 2.1f,  1.1f,  0.0f);	// Top Right
				glTexCoord2f(roll+0.0f, 15.0f); glVertex3f(-2.1f,  1.1f,  0.0f);	// Top Left
			glEnd();									// Done Drawing The Quad
		}

		glBlendFunc(GL_ONE, GL_ONE);					// Copy Image 1 Color To The Screen
		glBindTexture(GL_TEXTURE_2D, texture[2]);		// Select The First Image Texture
		glBegin(GL_QUADS);								// Start Drawing A Textured Quad
			glTexCoord2f(sin(roll)+0.0f, cos(roll)); glVertex3f(-2.1f, -1.1f,  0.0f);	// Bottom Left
			glTexCoord2f(cos(roll)+15.0f, sin(roll)); glVertex3f( 2.1f, -1.1f,  0.0f);	// Bottom Right
			glTexCoord2f(roll+15.0f, 15.0f); glVertex3f( 2.1f,  1.1f,  0.0f);	// Top Right
			glTexCoord2f(roll+0.0f, 15.0f); glVertex3f(-2.1f,  1.1f,  0.0f);	// Top Left

		glEnd();										// Done Drawing The Quad
	}


	roll+=0.002f;
	/*// Increase Our Texture Roll Variable
	if (roll>10.0f)										// Is Roll Greater Than One
	{
	//	roll-=1.0f;										// Subtract 1 From Roll
	   roll-=0.002f; 
	}*/
    glDisable( GL_TEXTURE_2D );
	return TRUE;
}

int spot(double a, double b, double c, double d, double e, double f){

    /*
    a, b and c -- x, y and z co-ordinates for light position
    d, e and f -- x, y and z co-ordinates for spot light position
    */

    GLfloat mat_specular[] = { 0.3, 1.0, 1.3, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { a,b,c, 1.0 };
    GLfloat spotDir[] = { d,e,f };
//  glClearColor (0.5, 0.5, 0.5, 0.0);
	glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glLightfv(GL_LIGHT0,GL_SPECULAR,mat_specular); 
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);    
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Definig spotlight attributes
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,95.0);
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,2.0);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDir);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    return 0;

}
// #### Une Sphère ####

GLvoid Sphere(double numMajor, double numMinor, double radius)
{
  glLoadIdentity();

  glDisable(GL_BLEND);
  glTranslatef(0.0f,0.0f,-1.0f);
 
  glRotatef(yrot,0.0f,0.0f,-1.0f);
  glRotatef(xrot,0.0f,1.0f,0.0f);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[5]);
  double majorStep = (M_PI / numMajor);
  double minorStep = (2.0 * M_PI / numMinor);
  int i, j;

  for (i = 0; i < numMajor; ++i) {
    double a   = i * majorStep;
    double b   = a + majorStep;
    double r0  = radius * sin(a);
    double r1  = radius * sin(b);
    double z0  = radius * cos(a);
    double z1  = radius * cos(b);

    glBegin(GL_TRIANGLE_STRIP);
    for (j = 0; j <= numMinor; ++j) {
      double c = j * minorStep;
      double x = cos(c);
      double y = sin(c);

      glNormal3f((x * r0) / radius, (y * r0) / radius, z0 / radius);
      glTexCoord2f(j / (GLfloat) numMinor, i / (GLfloat) numMajor);
      glVertex3f(x * r0, y * r0, z0);

      glNormal3f((x * r1) / radius, (y * r1) / radius, z1 / radius);
      glTexCoord2f(j / (GLfloat) numMinor, (i + 1) / (GLfloat) numMajor);
      glVertex3f(x * r1, y * r1, z1);
    }
    glEnd();
  }

 glEnable(GL_BLEND);
}


int RePaint()
{		
	//on initialise notre premier compteur qui va nous permettre de connaître le temps écoulé entre chaque scène
	temps_1 = GetTickCount();

	//ceci est la différence entr le moment où la dernière scène a été rendue et maintenant
	temps_x = temps_1 - temps_2;
	
		//on efface notre écran
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//on remet à zéro
	
		glLoadIdentity();

		//on calcule le nombre d'images par seconde affichées
		if(GetTickCount() - fps_2 >= 1000)
		{
			fps_2 = GetTickCount();

			fps_img_2 = fps_img_1;

			fps_img_1 = 0;
			
			rot_tmp = camera_1->rot - rot_tmp_2;
			rot_tmp_2 = camera_1->rot;
		}
		
		//on affiche les infos dans la barre des titres
		sprintf(images_sec, "fps = %d , rot = %d , test = %d , ms = %d", fps_img_2 , int(rot_tmp) , test , temps_x);
		SetWindowText(hWnd, images_sec);
		
		//on augmente le nombre d'images qui ont été affichées
		fps_img_1++;

		//on calcule la position de la caméra
		camera_1->calculer( temps_x );

		//on spécifie la texture à utiliser
		glBindTexture(GL_TEXTURE_2D, tex_image);
	
		//on calcule les différents paramètres de chaque particules
		particules_9->calculer( temps_x , test );


		//on affiche ces particules
		particules_9->afficher();
 
		SwapBuffers(DC);

		//on réinitialise notre compteur
		temps_2 = temps_1;
		return TRUE;
}


//comme son nom l'indique, elle permet de fermer correctement le programme en vidant de la mémoire les différents
//éléments qu'il a fallu créer
void Shutdown()
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE);
	}

	wglMakeCurrent(NULL,NULL);
	
	wglDeleteContext(RC);
	RC=NULL;

	ReleaseDC(hWnd,DC);
	DC=NULL;
	
	DestroyWindow(hWnd);
	hWnd=NULL;

	UnregisterClass("zOrRo", hInstance);
	hInstance=NULL;
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLAnim

COpenGLAnim::COpenGLAnim()
{
	dc = NULL;
	rotation = 0.0f;
}

COpenGLAnim::~COpenGLAnim()
{
   if (dc) //Only delete dc when really allocated
   {
      delete dc;
   }
}

BEGIN_MESSAGE_MAP(COpenGLAnim, CWnd)
	//{{AFX_MSG_MAP(COpenGLAnim)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int COpenGLAnim::InitGL()
{
//on charge les textures
	if(!LoadTexture( tex_image , "x.dat" ))
		return FALSE;
	LoadTexture( tex_image , "x.dat" );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glDisable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		//si on arrive jusqu'ici, on retourne TRUE (tout s'est bien passé)
		return TRUE;
}

void COpenGLAnim::TriangleGL()
{
	glRotatef(rotation,0.0f,1.0f,0.0f);
	glBegin(GL_QUADS);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(1.0f,-1.0f,0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,1.0f,0.0f);
	glEnd();
}

void atmos()
{
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glGetFloatv(GL_LINE_WIDTH_GRANULARITY,&v1);
    glGetFloatv(GL_LINE_WIDTH_RANGE,v2);
    /* define the viewing transformation */
    glMatrixMode(GL_MODELVIEW);	

	// Enable 2D Texture Mapping
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Stencil Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glLightfv(GL_LIGHT1, GL_POSITION, LightPos);		// Set Light1 Position
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);			// Set Light1 Ambience
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDif);			// Set Light1 Diffuse
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpc);		// Set Light1 Specular
									// Enable Light1
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);// Enable Lighting  
    glEnable(GL_LIGHT0);
	glCullFace(GL_BACK);								// Set Culling Face To Back Face
	glEnable(GL_CULL_FACE);								// Enable Culling
		//////////////////////////////////////////
	
}
void COpenGLAnim::DrawGLScene()
{
      // Loop

	  Timer t ;

	  LoadGLTextures();
	  glEnable(GL_TEXTURE_2D);	
	  do{

		if (t.getTime() >= 0.0 && t.getTime() <= 14) 
		{
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.000f, 0.0f);
		RePaint();
		SwapBuffers(dc->m_hDC);
		}

		if (t.getTime() >= 14 && t.getTime() < 18) 
		{	
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glClearColor(0.000f, 0.002f, 0.030f, 0.0f);
		//////////////////////////////////////////
		atmos();
		sliding_blend();
//		spot(0, 2, 5, 0, 0, 0);
		glRotatef(xrot,1.0,0.0,0.0);
		Sphere(120.0f, 120.0f, 0.25f);
		SwapBuffers(dc->m_hDC);
		}

		if (t.getTime() >= 18.0 && t.getTime() <= 22)
		{
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glClearColor(0.010f, 0.002f, 0.004f, 0.1f);
		glTranslatef(0.0f,0.0f,-0.5f);
		sliding_blend();
		
		Sphere(120.0f, 120.0f, 0.15f);
		glTranslatef(0.0f,0.0f,-1.0f);
//		TriangleGL();
		SwapBuffers(dc->m_hDC);
		}

		if (t.getTime() >= 22.0 && t.getTime() <= 200)
		{
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		glClearColor(0.010f, 0.002f, 0.004f, 0.1f);
		glTranslatef(-1.0f,2.0f,-0.5f);
		sliding_blend();
//		spot(0, cos(xrot), 5, 0, 0, 0);
		atmos();
//		Sphere(200.0f, 200.0f, cos(zrot)/3);
		Sphere(120.0f, 120.0f, 0.15);
//		starsfield();
		glTranslatef(-1.0f,2.0f,-1.0f);
//		TriangleGL();
		SwapBuffers(dc->m_hDC);
		}
		if (t.getTime() >= 215) break;
	 yrot+=1.5f;
	 xrot+=1.5f;
     zrot+=0.001f;

	} while(!GetAsyncKeyState(VK_ESCAPE));
	 

	Shutdown();
	t.reset();
//	Sleep(1000);
	exit(0);
	
}


//////////////////////////////////////////////////

void COpenGLAnim::Create(CRect rect, CWnd *parent)
{
   //Register window class
   CString className = AfxRegisterWndClass(
      CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
      NULL,
      (HBRUSH)GetStockObject(BLACK_BRUSH),
      NULL);
  
   //Finally create the window
   CreateEx(
      0,
      className,
      "cRAcKtrO",
      WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
      rect,
      parent,
      0);
} 

void COpenGLAnim::OnPaint() 
{
	rotation += 0.45f;

	if (rotation >= 360.0f)
	{
		rotation -= 360.0f;
	}
	ShowCursor(0);
	/** OpenGL section **/
	openGLDevice.makeCurrent();
  DrawGLScene();	
}

void COpenGLAnim::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
 	if (cy == 0)								
	{
		cy = 1;						
	}
	glViewport(0,0,cx,cy);	
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();
	glOrtho(-1.0f,1.0f,-1.0f,1.0f,1.0f,-2.0f);
	gluPerspective(45.0f,cx/cy,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLAnim message handlers

int COpenGLAnim::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
   dc = new CClientDC(this); //Get device context of window
   openGLDevice.create(dc->m_hDC); //Create opengl rendering context

   InitGL();
  
   return 0;
}



BOOL COpenGLAnim::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default	
	Shutdown();
	return TRUE;
}

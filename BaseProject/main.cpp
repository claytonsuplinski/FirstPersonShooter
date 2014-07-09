/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include <iostream>
#include <time.h>       
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "shader_utils.h"

#include "cube2.h"
#include "globals.h"
#include "soldier.h"
#include "menu.h"
#include "precip.h"
#include "gameMode1.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;using namespace glm;

//The projection and modelview matrices. 
mat4 projection, modelview;

//x (0=Normal, 1=night, 2=twilight), y(0=normal, 1=underwater, 2=fog)
ivec2 tod = ivec2(0, 2);

//Perspective viewpoints (set to specific values later)
vec3 lookAtCenter;
vec3 lookAtEye;

//Creates a class for maintaining the window information for easy access.
class Window
{
public:
	Window()
	{
		this->time_last_pause_began = this->total_time_paused = 0;
		this->wireframe = this->paused = false;
		this->interval = 8;this->window_handle = -1;
	}
	float time_last_pause_began;float total_time_paused;bool paused , wireframe;
	int window_handle;int interval;ivec2 size;float window_aspect;
} window;

/////////////////////////////////////VARIABLE DECLARATIONS/////////////////////////////
int viewPerspective = 0; //Select amongst 1st and 3rd person views
int weatherType = 0; //Select amongst the weather types

//Keeps track of the time
float current_timeDisplay;

Cylinder healthBar;
Soldier tSoldier;
Precip precip;
Cube2 skybox;Menu menu;
AI ai;

bool stadiumLoaded = false;

//If the menu for selecting a soldier class is on or not
bool soldierSelectMenu = false;

Team * userTeam, * greenTeam, * blueTeam, * redTeam;

GameMode1 gm1;

float velocity2 = 0;float maxUserVelocity = 1.0;

//Used for following the remaining living soldiers
vector<Soldier*> remainingSoldiers;
bool * followCpuSoldier;
int * soldierToFollowIndex, * stadiumSelect;

//Used to calculate the user's distance from buildings for optimization
float * gmTransX, * gmTransY, * gmTransZ;
double * gmRotatedX, * gmRotatedY;

//Variables to determine if the game is over and manage the end-of-game menu
bool gameOver;int winningTeam = 0;string winningTeamName = "";vec4 winningTeamFontColor;
int endMenuPage = 0;int totYellow=0;int totGreen=0;int totBlue=0;int totRed=0;

//Keyboard flags
bool ePressed, wPressed, rPressed, zPressed, qPressed, aPressed, sPressed, dPressed;

//Values defining the position/rotation of the camera.
double RotatedX = 0;double RotatedY = 0;
float transX = 490;float transY = 0;float transZ = -490;

//Used to provide an angle for the snow falling when the user is moving
float movingWRTSnow = 0;

//Used to prevent shots and grenades from firing insanely fast
float lastShot = 0;float lastGrenade = 0;

//Reset the game back to the main menu
void reset(){
	menu.reset();
	
	gameOver=false;stadiumLoaded = false;
	winningTeam = 0;endMenuPage = 0;totYellow=0;totGreen=0;totBlue=0;totRed=0;

	RotatedX = 0;RotatedY = 0;
	transX = 490;transY = 0;transZ = -490;movingWRTSnow = 0;
	lastShot = 0;lastGrenade = 0;
	*followCpuSoldier = false;
	velocity2 = 0;

	ePressed=false; wPressed=false; rPressed=false; zPressed=false; qPressed=false; aPressed=false; sPressed=false; dPressed=false;

	userTeam->reset();greenTeam->reset();redTeam->reset();blueTeam->reset();
}

//////////////////////////////////////TEXT RENDERING/////////////////////////////////////////////
////////Font variables//////////
GLuint program;GLint attribute_coord;GLint uniform_tex;GLint uniform_color;
struct point {GLfloat x;GLfloat y;GLfloat s;GLfloat t;};
GLuint vbo;FT_Library ft;FT_Face face;const char *fontfilename;
int init_resources()
{        /* Initialize the FreeType2 library */
        if(FT_Init_FreeType(&ft)){fprintf(stderr, "Could not init freetype library\n");return 0;}
        /* Load a font */
        if(FT_New_Face(ft, fontfilename, 0, &face)){fprintf(stderr, "Could not open font %s\n", fontfilename);return 0;}
        /* Compile and link the shader program */
        GLint link_ok = GL_FALSE;GLuint vs, fs;
        if ((vs = create_shader("text.vert", GL_VERTEX_SHADER))        == 0) return 0;
        if ((fs = create_shader("text.frag", GL_FRAGMENT_SHADER)) == 0) return 0;

        program = glCreateProgram();glAttachShader(program, vs);glAttachShader(program, fs);
        glLinkProgram(program);glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
        if (!link_ok) {fprintf(stderr, "glLinkProgram:");print_log(program);return 0;}

        const char* attribute_name;attribute_name = "coord";
        attribute_coord = glGetAttribLocation(program, attribute_name);
        if (attribute_coord == -1) {fprintf(stderr, "Could not bind attribute %s\n", attribute_name);return 0;}

        const char* uniform_name;uniform_name = "tex";
        uniform_tex = glGetUniformLocation(program, uniform_name);
        if (uniform_tex == -1){fprintf(stderr, "Could not bind uniform %s\n", uniform_name);return 0;}

        uniform_name = "color";uniform_color = glGetUniformLocation(program, uniform_name);
        if (uniform_color == -1){fprintf(stderr, "Could not bind uniform %s\n", uniform_name);return 0;}

        // Create the vertex buffer object
        glGenBuffers(1, &vbo);
        return 1;
}

/**
 * Render text using the currently loaded font and currently set font size.
 * Rendering starts at coordinates (x, y), z is always 0.
 * The pixel coordinates that the FreeType2 library uses are scaled by (sx, sy).
 */
void render_text(const char *text, float x, float y, float sx, float sy) {
        const char *p;FT_GlyphSlot g = face->glyph;

        /* Create a texture that will be used to hold one "glyph" */
        GLuint tex;glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &tex);glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(uniform_tex, 0);
        /* We require 1 byte alignment when uploading texture data */
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        /* Clamping to edges is important to prevent artifacts when scaling */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        /* Linear filtering usually looks best for text */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        /* Set up the VBO for our vertex data */
        glEnableVertexAttribArray(attribute_coord);glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
        /* Loop through all characters */
        for(p = text; *p; p++) {
                /* Try to load and render the character */
                if(FT_Load_Char(face, *p, FT_LOAD_RENDER))
                        continue;

                /* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
                glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);
                /* Calculate the vertex and texture coordinates */
                float x2 = x + g->bitmap_left * sx;float y2 = -y - g->bitmap_top * sy;
                float w = g->bitmap.width * sx;float h = g->bitmap.rows * sy;

                point box[4] = {
                        {x2,     -y2    , 0, 0}, {x2 + w, -y2    , 1, 0},
                        {x2,     -y2 - h, 0, 1}, {x2 + w, -y2 - h, 1, 1},
                };

                /* Draw the character on the screen */
                glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

                /* Advance the cursor to the start of the next character */
                x += (g->advance.x >> 6) * sx;y += (g->advance.y >> 6) * sy;
        }
        glDisableVertexAttribArray(attribute_coord);glDeleteTextures(1, &tex);
}

void activeTextDisplay(const char* words, float x, float y, FT_UInt size, vec4 color)
{
		glDisable(GL_CULL_FACE);
        float sx = (float)(2.0/glutGet(GLUT_WINDOW_WIDTH));
        float sy = (float)(2.0/glutGet(GLUT_WINDOW_HEIGHT));

		/* Enable blending, necessary for our alpha texture */
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glUseProgram(program);

		/* Set font size to 48 pixels, color to black */
        FT_Set_Pixel_Sizes(face, 0, size);

		GLfloat black[4] = {color.x,color.y,color.z,color.w};glUniform4fv(uniform_color, 1, black);
		
		render_text(words,x,y,sx,sy); 
		
		glUseProgram(0);
		glEnable(GL_CULL_FACE);
}

////////////////////////////////////MOUSE DETECTION & MANAGEMENT/////////////////////////
//Mouse value/identification variables.
float mouseX = 0;float mouseY = 0;
float prevMouseY = (float)(window.size.y/2);
void mouseMovement(int x, int y) {
    mouseX=(float)x; //set lastx to the current x position
    mouseY=(float)y; //set lasty to the current y position
}

void mouseRotations(int stadium, int person){
	if(person == 1 || person == 3){
		//Turning controls
		if(mouseX < window.size.x/2){RotatedY -= abs((mouseX - window.size.x/2)/75);}
		else if(mouseX > window.size.x/2){RotatedY += abs((mouseX - window.size.x/2)/75);}
	}
	prevMouseY = mouseY;
}

/////////////////////////////////////CAMERA CONTROLS//////////////////////////////////////////
//Moves the camera according to user inputs -Draws things fitted to the environment
glm::mat4 render(mat4 Model){		
	Model = rotate(Model, (GLfloat) RotatedX, vec3(1,0,0));
	Model = rotate(Model, (GLfloat) RotatedY, vec3(0,1,0));
	Model = translate(Model, vec3(transX,0,0));    
	Model = translate(Model, vec3(0,0,transZ));    
	Model = translate(Model, vec3(0,-transY,0));	
	glLoadMatrixf(value_ptr(Model));
    return Model;
}

//Undoes the render function. -Use to draw independent of the environment (e.g. the user) 
glm::mat4 endRender(mat4 Model){	
	Model = translate(Model, vec3(0,transY,0));	
	Model = translate(Model, vec3(0,0,-transZ));
	Model = translate(Model, vec3(-transX,0,0));
	Model = rotate(Model, (GLfloat) -RotatedY, vec3(0,1,0));
	Model = rotate(Model, (GLfloat) -RotatedX, vec3(1,0,0));			
	glLoadMatrixf(value_ptr(Model));
    return Model;
}

//Changes the value of the angle in which the camera should be rotated vertically.
void rotateX(double angle){
    if(!(RotatedX>=89 && angle>0) && !(RotatedX<=-89 && angle<0)){RotatedX += angle;}
}

//Changes the value of the angle in which the camera should be rotated horizontally.
void rotateY(double angle){RotatedY += angle;}

//Deletes all of the created objects here.
void CloseFunc(){
	window.window_handle = -1;
	healthBar.TakeDown();
	skybox.TakeDown();
	tSoldier.TakeDown();
	gm1.TakeDown();
}

//Maintains aspect ratio when window is resized.
void ReshapeFunc(int w, int h){
	if (h > 0){window.size = ivec2(w, h);window.window_aspect = float(w) / float(h);}
}

//When a key is pressed down
void KeyboardFunc(unsigned char c, int x, int y){
	float current_time = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;

	switch (c){
	case 'e':if(!userTeam->soldiers[0].dead){ePressed = true;}break;
	case 'r':if(!userTeam->soldiers[0].dead){rPressed = true;}break;
		case 'z':zPressed = true;break;
		case 'q':qPressed = true;break;
		case 'w':wPressed = true;break;
		case 's':sPressed = true;break;
		case 'a':aPressed = true;break;
		case 'd':dPressed = true;break;
		case 'k': //Automatically kill user
			userTeam->soldiers[0].health = 0;
			userTeam->soldiers[0].dead = true;
			userTeam->numRemaining--;
			break;
		case 'n': //Reset back to main menu
			if(!menu.menuOn){
				reset();
			}
			break;

		case 'p': // Pause/unpause
			if(!menu.menuOn){
				if (window.paused == true){
					window.total_time_paused += (current_time - window.time_last_pause_began);
				}
				else{
					window.time_last_pause_began = current_time;
				}
				window.paused = !window.paused;
			}
			break;

		case 'i':  //Toggles wireframe mode
			window.wireframe = !window.wireframe;
			break;

		case 'c': //Follow other soldiers after the user died
			if(userTeam->soldiers[0].dead){
				*followCpuSoldier = !(*followCpuSoldier);
				if(*followCpuSoldier){
					*soldierToFollowIndex = 0;
					remainingSoldiers.clear();
					for(int i=1; i<userTeam->NUM_SOLDIERS; i++){
						if(!userTeam->soldiers[i].dead){
							remainingSoldiers.push_back(&userTeam->soldiers[i]);
						}
					}
					for(int i=0; i<userTeam->NUM_SOLDIERS; i++){
						if(!greenTeam->soldiers[i].dead){
							remainingSoldiers.push_back(&greenTeam->soldiers[i]);
						}
						if(!blueTeam->soldiers[i].dead){
							remainingSoldiers.push_back(&blueTeam->soldiers[i]);
						}
						if(!redTeam->soldiers[i].dead){
							remainingSoldiers.push_back(&redTeam->soldiers[i]);
						}
					}
				}
			}
			break;

		case 'v': //If following another soldier, switch which one you are following
			if(userTeam->soldiers[0].dead && *followCpuSoldier){
				(*soldierToFollowIndex)++;
				(*soldierToFollowIndex) %= remainingSoldiers.size();
			}
			break;

		case 'x': //If following another soldier, switch which one you are following (reverse direction)
			if(userTeam->soldiers[0].dead && *followCpuSoldier){
				(*soldierToFollowIndex)--;
				if((*soldierToFollowIndex) < 0){
					*soldierToFollowIndex = remainingSoldiers.size()-1;
				}				
			}
			break;

		case '1': 	
			if(menu.menuOn){menu.Update(1);}
			return;
		case '2':  
			if(menu.menuOn){menu.Update(2);}
			return;
		case '3':
			if(menu.menuOn){menu.Update(3);}
			return;
		case '4':
			if(menu.menuOn){menu.Update(4);}
			return;
		case '5':
			if(menu.menuOn){menu.Update(5);}
			return;

		case 13: //Enter key
			if(soldierSelectMenu){
				soldierSelectMenu = false;
			}
			return;

		case 27: //ESC key
			glutLeaveMainLoop();
			return;
	}	
}

void KeyboardUpFunc(unsigned char c, int x, int y){
	switch (c){
		case 'e':ePressed = false;break;
		case 'r':rPressed = false;break;
		case 'z':zPressed = false;break;
		case 'q':qPressed = false;break;
		case 'w':wPressed = false;break;
		case 's':sPressed = false;break;
		case 'a':aPressed = false;break;
		case 'd':dPressed = false;break;
	}	
}

void SpecialFunc(int c, int x, int y)
{
	switch(c){
        case GLUT_KEY_UP:
			if(!gameOver){rotateX(1);}
			else{
				if(endMenuPage > 0){
					endMenuPage -= 10;
				}
			}
			return;
        case GLUT_KEY_DOWN:
			if(!gameOver){rotateX(-1);}
			else{
				if(endMenuPage < userTeam->NUM_SOLDIERS - 10){
					endMenuPage += 10;
				}
			}
			return;
        case GLUT_KEY_RIGHT:rotateY(-1);return;
        case GLUT_KEY_LEFT:rotateY(1);return;
		case GLUT_KEY_F1:	
			weatherType = (weatherType + 1)%4;
			return;
		case GLUT_KEY_F2:
			tod.x  = (tod.x + 1)%3;
			return;
    }
}

void makeSkybox(){
	modelview = endRender(modelview);
	modelview = rotate(modelview, (GLfloat) RotatedX, vec3(1,0,0));
	modelview = rotate(modelview, (GLfloat) RotatedY, vec3(0,1,0));
	modelview = scale(modelview, vec3(2,2,2));
	skybox.Draw(projection, modelview, tod, current_timeDisplay/2);	
	modelview = scale(modelview, vec3(0.5,0.5,0.5));
	modelview = rotate(modelview, (GLfloat) -RotatedY, vec3(0,1,0));
	modelview = rotate(modelview, (GLfloat) -RotatedX, vec3(1,0,0));
	modelview = render(modelview);
}

void drawPrecipitationWithRadar(){
		modelview = endRender(modelview);

		modelview = rotate(modelview, (GLfloat) RotatedX, vec3(1,0,0));
		modelview = rotate(modelview, (GLfloat) RotatedY, vec3(0,1,0));
		
		precip.RotatedY = (float)(RotatedY);
		precip.movingWRTSnow = movingWRTSnow;
		precip.weatherType = weatherType;

		precip.Draw(projection, modelview, tod, 0);	
			
		modelview = rotate(modelview, (GLfloat) -RotatedY, vec3(0,1,0));
		modelview = rotate(modelview, (GLfloat) -RotatedX, vec3(1,0,0));

		gm1.DrawOrthographic(projection, modelview, tod, (viewPerspective == 1), 0);

		modelview = render(modelview);
}

//Sorts each team's soldiers by number of kills (used after the game is over)
void sortSoldiers(){
	Soldier tempSoldier;
	for(int j=0; j<userTeam->NUM_SOLDIERS; j++){
		for(int i=0; i<userTeam->NUM_SOLDIERS-1; i++){
			if(userTeam->soldiers[i].kills < userTeam->soldiers[i+1].kills){
				tempSoldier = userTeam->soldiers[i];
				userTeam->soldiers[i] = userTeam->soldiers[i+1];
				userTeam->soldiers[i+1] = tempSoldier;
			}
		}
	}
	for(int j=0; j<greenTeam->NUM_SOLDIERS; j++){
		for(int i=0; i<greenTeam->NUM_SOLDIERS-1; i++){
			if(greenTeam->soldiers[i].kills < greenTeam->soldiers[i+1].kills){
				tempSoldier = greenTeam->soldiers[i];
				greenTeam->soldiers[i] = greenTeam->soldiers[i+1];
				greenTeam->soldiers[i+1] = tempSoldier;
			}
		}
	}
	for(int j=0; j<blueTeam->NUM_SOLDIERS; j++){
		for(int i=0; i<blueTeam->NUM_SOLDIERS-1; i++){
			if(blueTeam->soldiers[i].kills < blueTeam->soldiers[i+1].kills){
				tempSoldier = blueTeam->soldiers[i];
				blueTeam->soldiers[i] = blueTeam->soldiers[i+1];
				blueTeam->soldiers[i+1] = tempSoldier;
			}
		}
	}
	for(int j=0; j<redTeam->NUM_SOLDIERS; j++){
		for(int i=0; i<redTeam->NUM_SOLDIERS-1; i++){
			if(redTeam->soldiers[i].kills < redTeam->soldiers[i+1].kills){
				tempSoldier = redTeam->soldiers[i];
				redTeam->soldiers[i] = redTeam->soldiers[i+1];
				redTeam->soldiers[i+1] = tempSoldier;
			}
		}
	}
	
	for(int i=0; i<userTeam->NUM_SOLDIERS; i++){
		totYellow += userTeam->soldiers[i].kills;
		totGreen += greenTeam->soldiers[i].kills;
		totBlue += blueTeam->soldiers[i].kills;
		totRed += redTeam->soldiers[i].kills;
	}
}

//Response to a particular key being held down
void keyPress(){
	if(ePressed){
		if(current_timeDisplay - lastShot > 0.25){
			userTeam->firedBullet(0);
			lastShot = current_timeDisplay;
		}
	}	
	if(rPressed){
		if(current_timeDisplay - lastGrenade > 0.5){
			userTeam->threwGrenade(0);
			lastGrenade = current_timeDisplay;
		}			
	}

	if(wPressed){
		if(userTeam->soldiers[0].dead){maxUserVelocity = 5;}
		else{maxUserVelocity = 5.f;} //set to 0.6f

		if(velocity2 < maxUserVelocity){velocity2 += 0.1f;}
		if(movingWRTSnow < 1){movingWRTSnow = movingWRTSnow + 0.2f;}
		transZ = (float)(transZ + velocity2*cos(-RotatedY*3.14/180));
		if(abs(transZ) > 500.0f || (!userTeam->soldiers[0].dead && userTeam->ranIntoBuilding(vec3(-transX, 0, -transZ), 0.5))){
			transZ = (float)(transZ - velocity2*cos(-RotatedY*3.14/180));
		}
		transX = (float)(transX + velocity2*sin(-RotatedY*3.14/180));			
		if(abs(transX) > 500.0f || (!userTeam->soldiers[0].dead && userTeam->ranIntoBuilding(vec3(-transX, 0, -transZ), 0.5))){
			transX = (float)(transX - velocity2*sin(-RotatedY*3.14/180));
		}
	}
	else{
		if(velocity2 > 0){velocity2 -= 0.1f;}
		if(velocity2 < 0){velocity2 = 0;}
	}

	userTeam->soldiers[0].person.velocity = velocity2;

	if(zPressed && userTeam->soldiers[0].dead){transY = transY - 1;}
	if(qPressed && userTeam->soldiers[0].dead){transY = transY + 1;}
	if(sPressed && userTeam->soldiers[0].dead){transZ = (float)(transZ - 1*cos(-RotatedY*3.14/180));transX = (float)(transX - 1*sin(-RotatedY*3.14/180));}
	if(aPressed && userTeam->soldiers[0].dead){transX = (float)(transX + 1*cos(RotatedY*3.14/180));transZ = (float)(transZ + 1*sin(RotatedY*3.14/180));}
	if(dPressed && userTeam->soldiers[0].dead){transX = (float)(transX - 1*cos(RotatedY*3.14/180));transZ = (float)(transZ - 1*sin(RotatedY*3.14/180));}
}

//Set up the environment for game play after selected in the menu
void initArena(){
	tod.y = menu.s.stadiumSelect;
	//ADD_STADIUM//
	switch(menu.s.stadiumSelect){
	case 1:
		gm1.stadium->Initialize(0);
		userTeam->buildings = gm1.stadium->rectangularObstacles;
		greenTeam->buildings = gm1.stadium->rectangularObstacles;
		blueTeam->buildings = gm1.stadium->rectangularObstacles;
		redTeam->buildings = gm1.stadium->rectangularObstacles;
		break;
	case 2:
		gm1.forest->Initialize();
		userTeam->buildings = gm1.forest->rectangularObstacles;
		greenTeam->buildings = gm1.forest->rectangularObstacles;
		blueTeam->buildings = gm1.forest->rectangularObstacles;
		redTeam->buildings = gm1.forest->rectangularObstacles;
		break;
	case 3:
		gm1.desert->Initialize();
		userTeam->buildings.clear();
		greenTeam->buildings.clear();
		blueTeam->buildings.clear();
		redTeam->buildings.clear();
		break;
	case 4:
		gm1.volcano->Initialize();
		userTeam->buildings.clear();
		greenTeam->buildings.clear();
		blueTeam->buildings.clear();
		redTeam->buildings.clear();
		break;
	case 5:
		gm1.cave->Initialize();
		userTeam->buildings.clear();
		greenTeam->buildings.clear();
		blueTeam->buildings.clear();
		redTeam->buildings.clear();
		break;
	}
}

//Orchestrates all the objects and variables into a playable game
void GameDisplay(){
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	projection = perspective(25.0f, window.window_aspect, 0.01f, 2000.0f);
	modelview = lookAt(lookAtEye, lookAtCenter, vec3(0.0f, 1.0f, 0.0f));
	modelview = render(modelview);
	glLoadMatrixf(value_ptr(modelview));
	glPolygonMode(GL_FRONT_AND_BACK, window.wireframe ? GL_LINE : GL_FILL);	

	lookAtEye = menu.s.lookAtEye;
	lookAtCenter = menu.s.lookAtCenter;
	viewPerspective = 3;
	if(lookAtEye == menu.FIRST_PERSON_EYE){
		viewPerspective = 1;
	}
	*stadiumSelect = menu.s.stadiumSelect;
	/////////////////////////////Menu Display////////////////////////////////
	if(menu.menuOn){
		soldierSelectMenu = true;
		//3P - eye = vec3(0.0f, 1, 10);center = vec3(0.0f, 0.0f, 0.0f);
		//1P - eye = vec3(0.0f, 1, -2);center = vec3(0.0f, 1.0f, -3.0f);
		viewPerspective = 3;
		lookAtEye = vec3(0.0f, 2, 10);
		lookAtCenter = vec3(0.0f, 1.0f, -10.0f);		

		glDepthMask(GL_FALSE);
		for(unsigned int i=0; i<menu.titles.size(); i++){
			activeTextDisplay(menu.titles.at(i).c_str(), -0.5f, 0.8f - i*0.25f, 32 - i*4, vec4(1,1,1,1));
		}
		for(unsigned int i=0; i<menu.lines.size(); i++){
			activeTextDisplay(menu.lines.at(i).c_str(), -0.5f, 0.25f-i*0.15f, 20, vec4(1,1,1,1));
		}
		glDepthMask(GL_TRUE);

	}
	//The menu just before playing the game - Select which soldier class you want to use
	else if(soldierSelectMenu){

		if(!stadiumLoaded){
			initArena();
			stadiumLoaded = true;
		}	

		mat4 scaler1 = rotate(modelview, 90.0f, vec3(0,1,0));
		gm1.userTeam.drawUser = false;
		gm1.userTeam.Draw(projection, scaler1, tod, 0);

		gm1.DrawStadium(projection, modelview, tod, 0);

		activeTextDisplay("Select Soldier", -0.5f, 0.75f, 32, vec4(1,1,1,1));
		activeTextDisplay("Standard Trooper", -0.5f, 0.25f, 20, vec4(1,1,1,1));

		activeTextDisplay("Hit Enter to Continue", -0.5f, -0.65f, 16, vec4(1,1,1,1));

	}

	///////////////////////Game Display///////////////////////////
	else if(!gameOver){
		
		current_timeDisplay = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;
		current_timeDisplay = (window.paused ? window.time_last_pause_began : current_timeDisplay) - window.total_time_paused;

		gm1.AfterDeath(remainingSoldiers, transX, transY, transZ);

		keyPress();		
		
		//Mouse movement
		mouseRotations(1, viewPerspective);		

		makeSkybox();

		modelview = endRender(modelview);

		*gmTransX = transX;*gmTransY = transY;*gmTransZ = transZ;
		*gmRotatedX = RotatedX;*gmRotatedY = RotatedY;

		gm1.DrawUser(projection, modelview, tod, 0);

		modelview = render(modelview);

		gm1.DrawTeams(projection, modelview, tod, 0);
		
		glDepthMask(GL_FALSE);
		drawPrecipitationWithRadar();

		//Display the relevant text on the screen
		stringstream yS (stringstream::in | stringstream::out);stringstream rS (stringstream::in | stringstream::out);
		stringstream bS (stringstream::in | stringstream::out);stringstream gS (stringstream::in | stringstream::out);
		stringstream ammo (stringstream::in | stringstream::out);stringstream grenades (stringstream::in | stringstream::out);
		stringstream kills (stringstream::in | stringstream::out);
		
		ammo << userTeam->soldiers[0].ammo;yS << userTeam->numRemaining;gS << greenTeam->numRemaining;
		kills << userTeam->soldiers[0].kills;
		bS << blueTeam->numRemaining;rS << redTeam->numRemaining;grenades << userTeam->soldiers[0].grenades;

		activeTextDisplay((yS.str()).c_str(), 0.3f, 0.85f, 32, vec4(1,1,0,1));
		activeTextDisplay((gS.str()).c_str(), 0.45f, 0.85f, 32, vec4(0,1,0,1));
		activeTextDisplay((bS.str()).c_str(), 0.6f, 0.85f, 32, vec4(0,0,1,1));
		activeTextDisplay((rS.str()).c_str(), 0.75f, 0.85f, 32, vec4(1,0,0,1));
		activeTextDisplay((kills.str()).c_str(), -0.94f, -0.85f, 16, vec4(1,1,1,1));
		activeTextDisplay((ammo.str()).c_str(), -0.85f, -0.85f, 16, vec4(1,1,1,1));
		activeTextDisplay((grenades.str()).c_str(), -0.74f, -0.85f, 16, vec4(1,1,1,1));
		glDepthMask(GL_TRUE);

		gameOver = gm1.checkGameOver(winningTeam, winningTeamName, winningTeamFontColor);
		if(gameOver){sortSoldiers();}
	}
	else{ //The game is over - Display end-of-game menu
		glDepthMask(GL_FALSE);
		activeTextDisplay((winningTeamName + " Team Wins!").c_str(), -0.85f, 0.75f, 64, winningTeamFontColor);

		if(endMenuPage > 0){
			activeTextDisplay("^", 0.85f, 0.7f, 64, vec4(1,1,1,1));
		}
		if(endMenuPage < userTeam->NUM_SOLDIERS-10){
			activeTextDisplay("v", 0.85f, -0.8f, 32, vec4(1,1,1,1));
		}

		for(int i=endMenuPage; i<(endMenuPage+10 < userTeam->NUM_SOLDIERS ? endMenuPage+10 : userTeam->NUM_SOLDIERS); i++){
			stringstream numKills (stringstream::in | stringstream::out);
			numKills << userTeam->soldiers[i].kills;

			float vertPos = 0.5f - (i-endMenuPage)*0.1f;

			activeTextDisplay((userTeam->soldiers[i].name + " : " + numKills.str() + (userTeam->soldiers[i].kills == 1 ? " kill" : " kills")).c_str(), -0.85f, vertPos, 16, vec4(1,1,0,1));
		}
		stringstream numKills1 (stringstream::in | stringstream::out);
		numKills1 << totYellow;
		activeTextDisplay(("Total: " + numKills1.str() + (totYellow == 1 ? " kill" : " kills")).c_str(), -0.85f, -0.75, 16, vec4(1,1,0,1));

		for(int i=endMenuPage; i<(endMenuPage+10 < userTeam->NUM_SOLDIERS ? endMenuPage+10 : userTeam->NUM_SOLDIERS); i++){
			stringstream numKills (stringstream::in | stringstream::out);
			numKills << greenTeam->soldiers[i].kills;

			float vertPos = 0.5f - (i-endMenuPage)*0.1f;

			activeTextDisplay((greenTeam->soldiers[i].name + " : " + numKills.str() + (greenTeam->soldiers[i].kills == 1 ? " kill" : " kills")).c_str(), -0.45f, vertPos, 16, vec4(0,1,0,1));
		}
		stringstream numKills2 (stringstream::in | stringstream::out);
		numKills2 << totGreen;
		activeTextDisplay(("Total: " + numKills2.str() + (totGreen == 1 ? " kill" : " kills")).c_str(), -0.45f, -0.75, 16, vec4(0,1,0,1));

		for(int i=endMenuPage; i<(endMenuPage+10 < userTeam->NUM_SOLDIERS ? endMenuPage+10 : userTeam->NUM_SOLDIERS); i++){
			stringstream numKills (stringstream::in | stringstream::out);
			numKills << blueTeam->soldiers[i].kills;

			float vertPos = 0.5f - (i-endMenuPage)*0.1f;

			activeTextDisplay((blueTeam->soldiers[i].name + " : " + numKills.str() + (blueTeam->soldiers[i].kills == 1 ? " kill" : " kills")).c_str(), -0.05f, vertPos, 16, vec4(0,0,1,1));
		}
		stringstream numKills3 (stringstream::in | stringstream::out);
		numKills3 << totBlue;
		activeTextDisplay(("Total: " + numKills3.str() + (totBlue == 1 ? " kill" : " kills")).c_str(), -0.05f, -0.75, 16, vec4(0,0,1,1));

		for(int i=endMenuPage; i<(endMenuPage+10 < userTeam->NUM_SOLDIERS ? endMenuPage+10 : userTeam->NUM_SOLDIERS); i++){
			stringstream numKills (stringstream::in | stringstream::out);
			numKills << redTeam->soldiers[i].kills;

			float vertPos = 0.5f - (i-endMenuPage)*0.1f;

			activeTextDisplay((redTeam->soldiers[i].name + " : " + numKills.str() + (redTeam->soldiers[i].kills == 1 ? " kill" : " kills")).c_str(), 0.35f, vertPos, 16, vec4(1,0,0,1));
		}
		stringstream numKills4 (stringstream::in | stringstream::out);
		numKills4 << totRed;
		activeTextDisplay(("Total: " + numKills4.str() + (totRed == 1 ? " kill" : " kills")).c_str(), 0.35f, -0.75, 16, vec4(1,0,0,1));
		glDepthMask(GL_TRUE);
		
	}

	//Calculations for moving while it's snowing
	if(movingWRTSnow > 0){movingWRTSnow = movingWRTSnow - 0.1f;}
	if(movingWRTSnow < 0){movingWRTSnow = 0.0;}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFlush();
	
}

//Manage pausing and when to display the game / jumbotrons
void DisplayFunc(){
	glViewport(0, 0, window.size.x, window.size.y);
	if(!window.paused){
		GameDisplay();	
		glViewport(0, 0, (GLsizei)(512.0), (GLsizei)(512.0));

		if(!gameOver && !menu.menuOn){
			glm::mat4 Projection2 = glm::ortho( -10.0f, 10.0f, -10.0f, 10.0f,1.0f, 10.0f);
			glm::mat4 View       = glm::lookAt(
				glm::vec3(0,0,5), // Camera is at (0,0,5), in World Space
				glm::vec3(0,0,0), // and looks at the origin
				glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
			);  

		}
		glutSwapBuffers();
	}	
}

void TimerFunc(int value){
	if (window.window_handle != -1){glutTimerFunc(window.interval, TimerFunc, value);glutPostRedisplay();}
}

int main(int argc, char * argv[])
{
	/* Enable blending, necessary for our alpha texture */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glewInit();
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 512);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	srand ((unsigned int)(time(NULL)));

	//Initialize everything
	fontfilename = "Motorwerk.ttf";

	window.window_handle = glutCreateWindow("Base Project");
	glutReshapeFunc(ReshapeFunc);
	glutCloseFunc(CloseFunc);
	
	glutMotionFunc(mouseMovement);
	glutPassiveMotionFunc(mouseMovement); //check for mouse movement
	glutKeyboardFunc(KeyboardFunc);
	glutKeyboardUpFunc(KeyboardUpFunc);
	glutSpecialFunc(SpecialFunc);
	glutTimerFunc(window.interval, TimerFunc, 0);
	
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	menu.Initialize();

	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW failed to initialize." << endl;
		return 0;
	}

	init_resources();
	glutDisplayFunc(DisplayFunc);

	if (!skybox.Initialize(0, 5000, "basic_skybox_shader.vert", "basic_skybox_shader.frag")){return 0;}
	
	if (!precip.Initialize()){return 0;}
	if(!tSoldier.Initialize()){return 0;}

	gm1.tSoldier = tSoldier;

	if(!gm1.Initialize()){return 0;}

	userTeam = &gm1.userTeam;
	greenTeam = &gm1.greenTeam;
	blueTeam = &gm1.blueTeam;
	redTeam = &gm1.redTeam;

	*&gmTransX = &gm1.transX;
	*&gmTransY = &gm1.transY;
	*&gmTransZ = &gm1.transZ;
	*&gmRotatedX = &gm1.RotatedX;
	*&gmRotatedY = &gm1.RotatedY;
	*&followCpuSoldier = &gm1.followCpuSoldier;
	*&soldierToFollowIndex = &gm1.soldierToFollowIndex;
	*&stadiumSelect = &gm1.stadiumSelect;

	gm1.stadium = new SquareStadium();
	gm1.forest = new Forest();
	gm1.desert = new Desert();
	gm1.volcano = new Volcano();
	gm1.cave = new Cave();

	glutMainLoop();
}










	/*  //For positioning elements of the soldier
		case '1': 	
			for(int i=0; i<userTeam.NUM_SOLDIERS; i++){
				userTeam.soldiers[i].person.tmpZoom-=0.001;
			}
			cout << "tmpZoom = " << userTeam.soldiers[1].person.tmpZoom << endl;
			return;
		case '2':  
			for(int i=0; i<userTeam.NUM_SOLDIERS; i++){
				userTeam.soldiers[i].person.tmpZoom+=0.001;
			}
			cout << "tmpZoom = " << userTeam.soldiers[1].person.tmpZoom << endl;
			return;
		case '3':
			for(int i=0; i<userTeam.NUM_SOLDIERS; i++){
				userTeam.soldiers[i].person.tmpX-=0.5;
			}
			cout << "tmpX = " << userTeam.soldiers[1].person.tmpX << endl;
			return;
		case '4':
			for(int i=0; i<userTeam.NUM_SOLDIERS; i++){
				userTeam.soldiers[i].person.tmpX+=0.5;
			}
			cout << "tmpX = " << userTeam.soldiers[1].person.tmpX << endl;
			return;
		case '5':
			for(int i=0; i<userTeam.NUM_SOLDIERS; i++){
				userTeam.soldiers[i].person.tmpY-=0.005;
			}			
			cout << "tmpY = " << userTeam.soldiers[0].person.tmpY << endl;
			cout << "tmpY1 = " << userTeam.soldiers[1].person.tmpY << endl;
			return;
		case '6':
			for(int i=0; i<userTeam.NUM_SOLDIERS; i++){
				userTeam.soldiers[i].person.tmpY+=0.005;
			}
			cout << "tmpY = " << userTeam.soldiers[0].person.tmpY << endl;
			cout << "tmpY1 = " << userTeam.soldiers[1].person.tmpY << endl;
			return;
		case '7':
			for(int i=0; i<userTeam.NUM_SOLDIERS; i++){
				userTeam.soldiers[i].person.tmpZ-=0.005;
			}
			cout << "tmpZ = " << userTeam.soldiers[1].person.tmpZ << endl;
			return;
		case '8':
			for(int i=0; i<userTeam.NUM_SOLDIERS; i++){
				userTeam.soldiers[i].person.tmpZ+=0.005;
			}
			cout << "tmpZ = " << userTeam.soldiers[1].person.tmpZ << endl;
			return;
			*/



/*	// For placing roads
		case '1': 	
			//if(menu.menuOn){menu.Update(1);}
			stadium.tmpX--;
			return;
		case '2':  
			//if(menu.menuOn){menu.Update(2);}
			stadium.tmpX++;
			return;
		case '3':
			//if(menu.menuOn){menu.Update(3);}
			stadium.tmpZ--;
			return;
		case '4':
			//if(menu.menuOn){menu.Update(4);}
			stadium.tmpZ++;
			return;
		case '5':
			//cout << "user pos = (" << transX << ", " << transY << ", " << transZ << ")" << endl;
			stadium.tmpR-=90;
			return;
		case '6':
			stadium.tmpR+=90;
			return;
		case '7':
			stadium.tmpS-=0.5;
			return;
		case '8':
			stadium.tmpS+=0.5;
			return;
		case '9':
			stadium.saveBuildingVertices();
			return;
		case 32:
			stadium.roadStraightXZRS.push_back(vec4(stadium.tmpX, stadium.tmpZ, stadium.tmpR, stadium.tmpS));
			return;*/
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
#include <list>
#include "plane.h"
#include "Reload.h"
#include "bullet.h"
#include "rocket.h"
#include "bomb.h"
//#include "AiGround.h"
#include "AiPilot.h"

 
extern const float FPS = 60;
extern const int SCREEN_W = 640;
extern const int SCREEN_H = 480;

extern const int WORLD_W = 10000;


extern const int WORLD_H = 480;

extern int BOUNCER_SIZE = 32;

float bouncer_x = SCREEN_W / 10.0 - BOUNCER_SIZE / 10.0;
float bouncer_y = SCREEN_H / 10.0 - BOUNCER_SIZE / 10.0;
extern float ANGLE_TO_RADIANS = PI/180;
extern float RADIAN_TO_ANGLE = 180/PI;

static int CAMERACOORD_X;
static int CAMERACOORD_Y;

ALLEGRO_BITMAP *bouncer = NULL;
ALLEGRO_BITMAP* background = NULL;
ALLEGRO_BITMAP* background2 = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_TIMER *timer = NULL;
/** extern bitmaps that will be referenced by an airborne object **/
extern ALLEGRO_BITMAP* bulletBitmap = NULL;
extern ALLEGRO_BITMAP* rocketBitmap = NULL;
extern ALLEGRO_BITMAP* bombBitmap = NULL;
ALLEGRO_BITMAP* smoketrail = NULL;

ALLEGRO_FONT* font = NULL;
ALLEGRO_FONT* font2 = NULL;

extern Plane* playerPlane = NULL;

std::list<Bullet*> allProjectiles;
std::list<Bullet*>::iterator it;
std::vector<std::pair<float,float>>::iterator it2 ;
//std::vector<AiGround*> groundAi;
std::vector<AiPilot*> airAi;

int mapOriginX = 0;


enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, SPACEBAR, ONE_KEY, TWO_KEY, THREE_KEY, FOUR_KEY
};

void draw(void){
	/** get the camera translation values for a player fixed camera
	(subtract these from objects world coordinates = screen coord) **/
	int cameraXOffset = playerPlane->x - SCREEN_W / 2;
	int cameraYOffset = playerPlane->y - SCREEN_H / 2; 
	
	/** draw background image only whats visible **/
	if(mapOriginX + al_get_bitmap_width(background) < playerPlane->x - SCREEN_W)
		mapOriginX = playerPlane->x - SCREEN_W;
	al_draw_bitmap(background, mapOriginX - cameraXOffset, 0 - playerPlane->y,0);
	
	if(playerPlane->x + SCREEN_W/2 > mapOriginX + al_get_bitmap_width(background)){
		al_draw_bitmap(background2, mapOriginX + al_get_bitmap_width(background) - cameraXOffset, 0 - playerPlane->y,0);
	}
	
	/** draw players plane **/
	int bitmapCenterX = al_get_bitmap_width(playerPlane->bitmapObject) /2;
	int bitmapCenterY = al_get_bitmap_height(playerPlane->bitmapObject) /2;

	al_draw_rotated_bitmap(playerPlane->bitmapObject, bitmapCenterX, bitmapCenterY, playerPlane->x - cameraXOffset , playerPlane->y - cameraYOffset, -(playerPlane->noseRotation) * ANGLE_TO_RADIANS, 0);
	/** now draw the plane's exhaust **/
	if(playerPlane->trailList && playerPlane->showTrail){
		for(int i = playerPlane->trailList->size()-1; i >= 0; i--){
			float first = playerPlane->trailList->at(i).first;
			float second = playerPlane->trailList->at(i).second;
			int smokeXOffset = (int)(first - cameraXOffset);
			int smokeYOffset = (int)(second - cameraYOffset);
			if(smokeXOffset < SCREEN_W && smokeYOffset < SCREEN_H)
				al_draw_bitmap(smoketrail, smokeXOffset, smokeYOffset, 0);
		}
	}

	/** now draw ai players **/
	/*for(unsigned int i = 0; i < groundAi.size(); i++){
		if((groundAi.at(i)->getX() > playerPlane->x - SCREEN_W/2) && (groundAi.at(i)->getY() < playerPlane->y + SCREEN_W/2)){
			int AIScreenCoordX = groundAi.at(i)->getX() - cameraXOffset;
			int AIScreenCoordY = groundAi.at(i)->getY() - cameraYOffset;
			al_draw_bitmap(airAi.at(i)->bitmapObject, AIScreenCoordX, AIScreenCoordY, 0);
		}
	}*/

	for(unsigned int i = 0; i < airAi.size(); i++){
		if((airAi.at(i)->x > playerPlane->x - SCREEN_W/2) && (airAi.at(i)->y < playerPlane->y + SCREEN_W/2)){ 
			int AIScreenCoordX = airAi.at(i)->x - cameraXOffset;
			int AIScreenCoordY = airAi.at(i)->y - cameraYOffset;
			al_draw_bitmap(airAi.at(i)->bitmapObject, AIScreenCoordX, AIScreenCoordY, 0);
		}
	}
	
	/** now draw projectiles only if theyre within viewport **/
	for(it = allProjectiles.begin(); it != allProjectiles.end(); ++it){
		int projectileXOffset = (int)((**it).x) - cameraXOffset;
		int projectileYOffset =	(int)((**it).y) - cameraYOffset;
		
		if(projectileXOffset < SCREEN_W && projectileYOffset < SCREEN_H){
			al_draw_bitmap((**it).bitmapObject, projectileXOffset, projectileYOffset, 0);
			
			if((**it).trailShow){
				for(it2 = (**it).trailList->begin(); it2 != (**it).trailList->end(); ++it2){
					int smokeXOffset = (int)((*it2).first) - cameraXOffset;
					int smokeYOffset = (int)((*it2).second) - cameraYOffset;
					if(smokeXOffset < SCREEN_W && smokeYOffset < SCREEN_H)
						al_draw_bitmap(smoketrail, smokeXOffset, smokeYOffset, 0);
				}
			}
		}
	}

}
/**
	Process updates to ai objects
**/
void processAI(void){
	//for(unsigned int i = 0; i < groundAi.size(); i++){
	//	//groundAi.at(i)->processUpdate();
	//}

	for(unsigned int i = 0; i < airAi.size(); i++){
		airAi.at(i)->processUpdate();
	}
}

/** 
	Set number of enemies that can show up at once on screen

**/
void initializeAI(int groundNumOnScreen, int airNumOnScreen){
	
	/** initialize number of ground enemies on screen at once **/
	//for(int i = 0; i < groundNumOnScreen; i++){
	//	//groundAi.push_back(new AiGround(*bouncer));	
	//}

	/** initialize number of air enemies on screen at one time **/
	for(int i = 0; i < airNumOnScreen; i++){
		airAi.push_back(new AiPilot(*bouncer));	
	}

}
 

void run(void){
	
	bool redraw = true;
	bool doexit = false;
	bool key[9] = { false, false, false, false, false, false, false, false, false };

	while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
		if(key[KEY_UP]) {
            /** turn flaps up **/
			 playerPlane->adjustPitch(true);
         }
 
         if(key[KEY_DOWN] && playerPlane->y <= SCREEN_H - BOUNCER_SIZE - 4.0) {
			/** turn flaps down **/
            playerPlane->adjustPitch(false);
         }
 
         if(key[KEY_LEFT] && playerPlane->x >= 4.0) {
			 /** increase thrusters **/
			 float tmpthrottle = playerPlane->throttle - 0.02;
			 if(tmpthrottle < 0.0)
				 playerPlane->throttle = 0.0;
			 else
				 playerPlane->throttle = tmpthrottle;
         }
 
         if(key[KEY_RIGHT]) {
			/** decrease thrusters **/
			float tmpthrottle = playerPlane->throttle + 0.02;
			if(tmpthrottle > 1.0)
				playerPlane->throttle = 1.0;
			else
				playerPlane->throttle = tmpthrottle;
         }
		 if(key[SPACEBAR]){
			if(!playerPlane->flying)
				playerPlane->vely = 15.0;
		 }
		
		 /** fire bullets **/
		 if(key[ONE_KEY]){
			allProjectiles.push_back(playerPlane->fireBullets());
		 }
		  /**fire cannons basically bullets slower and more dmg **/
		 if(key[TWO_KEY]){
			//allProjectiles.push_back(playerPlane->fireBullets())
		 }
		 /** fire rockets **/
		 if(key[THREE_KEY]){
			allProjectiles.push_back(playerPlane->fireRockets());
		 }
		 /** drop bombs **/
		 if(key[FOUR_KEY]){
			allProjectiles.push_back(playerPlane->dropBombs());
		 }

	  /** update data structures **/
	  playerPlane->update();
	  for(it = allProjectiles.begin(); it != allProjectiles.end(); ++it){
		(**it).update();	
	  }
	  processAI();
	  /*for(int i = 0; i < groundAi.size(); i++){
		  if(groundAi.at(i)->getReload()->checkIfReady()){
			  Bullet* newBullet = groundAi.at(i)->firedShots();
			  newBullet->setSourceObject(*groundAi.at(i));
			  allProjectiles.push_back(newBullet);
		  }
	  }*/


         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
		 case ALLEGRO_KEY_W:
               key[KEY_UP] = true;
               break;
 
            case ALLEGRO_KEY_S:
               key[KEY_DOWN] = true;
               break;
 
            case ALLEGRO_KEY_A: 
               key[KEY_LEFT] = true;
               break;
 
            case ALLEGRO_KEY_D:
               key[KEY_RIGHT] = true;
               break;
			case ALLEGRO_KEY_SPACE:
				key[SPACEBAR] = true;
				break;
			case ALLEGRO_KEY_1:
				key[ONE_KEY] = true;
				break;
			case ALLEGRO_KEY_2:
				key[TWO_KEY] = true;
				break;
			case ALLEGRO_KEY_3:
				key[THREE_KEY] = true;
				break;
			case ALLEGRO_KEY_4:
				key[FOUR_KEY] = true;
				break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_W:
               key[KEY_UP] = false;
               break;
 
            case ALLEGRO_KEY_S:
               key[KEY_DOWN] = false;
               break;
 
            case ALLEGRO_KEY_A: 
               key[KEY_LEFT] = false;
               break;
 
            case ALLEGRO_KEY_D:
               key[KEY_RIGHT] = false;
               break;
 
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
			
			case ALLEGRO_KEY_SPACE:
			   key[SPACEBAR] = false;
			   break;
			/** handle abilities **/
			case ALLEGRO_KEY_1:
			   key[ONE_KEY] = false;
			   break;
			case ALLEGRO_KEY_2:
				key[TWO_KEY] = false;
				break;
			case ALLEGRO_KEY_3:
				key[THREE_KEY] = false;
				break;
			case ALLEGRO_KEY_4:
				key[FOUR_KEY] = false;
				break;
         }
		 playerPlane->resetPitch();
		 
	  }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
		 /** draws background **/
		
         al_clear_to_color(al_map_rgb(0,0,0));
		
         draw();
		 al_draw_textf(font, al_map_rgb(255,255,255), 640/2, (480/4), ALLEGRO_ALIGN_CENTRE, "planeX : %f planeY: %f planeRotation: %f planePitch: %f", playerPlane->x, playerPlane->y,  playerPlane->noseRotation,  playerPlane->pitch);
		 al_draw_textf(font2, al_map_rgb(255,255,255), 640/2, (480-(480/4)), ALLEGRO_ALIGN_CENTRE, "throttle : %f flyingBool: %i accelX = %f accelY: %f", playerPlane->throttle, playerPlane->flying, playerPlane->accelx, playerPlane->accely);
         
		 al_flip_display();

      }
   }

}

int initializeBitmaps(){
   bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   if(!bouncer) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   bulletBitmap = al_create_bitmap(BOUNCER_SIZE/4, BOUNCER_SIZE/4);
   if(!bulletBitmap) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   smoketrail = al_create_bitmap(BOUNCER_SIZE/6, BOUNCER_SIZE/6);
   if(!smoketrail) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   rocketBitmap = al_create_bitmap(BOUNCER_SIZE/4, BOUNCER_SIZE/4);
   if(!smoketrail) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   bombBitmap = al_create_bitmap(BOUNCER_SIZE/4, BOUNCER_SIZE/4);
   if(!smoketrail) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   background = al_load_bitmap("background_city.png");
   if(!background){
	  fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   background2 = al_load_bitmap("background_city2.png");
   if(!background2){
	  fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   al_set_target_bitmap(bouncer);
   al_clear_to_color(al_map_rgb(255, 0, 255));
   al_set_target_bitmap(bulletBitmap);
   al_clear_to_color(al_map_rgb(0, 255, 0));
   al_set_target_bitmap(smoketrail);
   al_clear_to_color(al_map_rgb(150,150,150));
   al_set_target_bitmap(rocketBitmap);
   al_clear_to_color(al_map_rgb(0, 0, 255));
   al_set_target_bitmap(bombBitmap);
   al_clear_to_color(al_map_rgb(255, 0, 0));

   return 0;
}


int main(int argc, char **argv)
{

     
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   if(!al_init_image_addon()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }

   al_init_font_addon(); // initialize the font addon
   al_init_ttf_addon();// initialize the ttf (True Type Font) addon
   font = al_load_ttf_font("Arcade.ttf", 16, 0 );
   font2 = al_load_ttf_font("Arcade.ttf", 16, 0 );

   int init_bitmap = initializeBitmaps();
   if(init_bitmap != 0){
	   return -1;
   }
   
   al_set_target_bitmap(al_get_backbuffer(display));

 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(bouncer);
	  al_destroy_bitmap(bulletBitmap);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
   al_start_timer(timer);
 
   playerPlane = new Plane(*bouncer);
   initializeAI(0,1);
   run();
   
   delete playerPlane;
   for(it = allProjectiles.begin(); it != allProjectiles.end(); ++it){
		delete (*it);
	}
   al_destroy_bitmap(bouncer);
   al_destroy_bitmap(bulletBitmap);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}


#include <stdio.h>
#include <allegro5/allegro.h>
#include "plane.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include <list>
#include "projectile.h"

 
extern const float FPS = 60;
extern const int SCREEN_W = 640;
extern const int SCREEN_H = 480;
extern int BOUNCER_SIZE = 32;

float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;

static int CAMERA_X;
static int CAMERA_Y;

ALLEGRO_BITMAP *bouncer = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
extern ALLEGRO_BITMAP* bulletBitmap = NULL;

ALLEGRO_FONT* font;
ALLEGRO_FONT* font2;

Plane* playerPlane;
std::list<Projectile*> allProjectiles;
std::list<Projectile*>::iterator it;

enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, SPACEBAR, ONE_KEY, TWO_KEY, THREE_KEY, FOUR_KEY
};

void draw(void){
	/** CENTER THE CAMERA ON THE PLAYERPLANE **/
	int cameraXOffset = playerPlane->x - SCREEN_W / 2;
	int cameraYOffset = playerPlane->y - SCREEN_H / 2; 
	CAMERA_X = playerPlane->x - cameraXOffset;
	CAMERA_Y = playerPlane->y - cameraYOffset;

	al_draw_bitmap(playerPlane->bitmapObject, CAMERA_X , CAMERA_Y, 0);
	for(it = allProjectiles.begin(); it != allProjectiles.end(); ++it){
		al_draw_bitmap((*it)->bitmapObject, (*it)->x, (*it)->y, 0);
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
			 float tmpthrottle = playerPlane->throttle - 0.1;
			 if(tmpthrottle < 0.0)
				 playerPlane->throttle = 0.0;
			 else
				 playerPlane->throttle = tmpthrottle;
         }
 
         if(key[KEY_RIGHT]) {
			/** decrease thrusters **/
			float tmpthrottle = playerPlane->throttle + 0.1;
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


		 playerPlane->update();
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
			
			case ALLEGRO_KEY_1:
			   key[ONE_KEY] = true;
			   break;
         }
		 playerPlane->resetPitch();
		 
	  }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
 
         al_clear_to_color(al_map_rgb(0,0,0));
		
         draw();
		 al_draw_textf(font, al_map_rgb(255,255,255), 640/2, (480/4), ALLEGRO_ALIGN_CENTRE, "planeX : %f planeY: %f planeRotation: %f planePitch: %f", playerPlane->x, playerPlane->y,  playerPlane->noseRotation,  playerPlane->pitch);
		 al_draw_textf(font2, al_map_rgb(255,255,255), 640/2, (480-(480/4)), ALLEGRO_ALIGN_CENTRE, "throttle : %f flyingBool: %i accelX = %f accelY: %f ", playerPlane->throttle, playerPlane->flying, playerPlane->accelx, playerPlane->accely);
         al_flip_display();
      }
   }

}
 
int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_TIMER *timer = NULL;
     
   if(!al_init()) {
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

   al_set_target_bitmap(bulletBitmap);
   al_set_target_bitmap(bouncer);
   al_clear_to_color(al_map_rgb(255, 0, 255));
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

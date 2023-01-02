//project.c
// Daniel Shields Fund Comp Lab 11
// This code greates a user-interface game in the X11 graphics window that requires the user to jump over obstacles as they approach the player's character.

#include <stdio.h>
#include "gfx.h"
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define PI M_PI
typedef struct{
	float xc;
	float yc;
	float r;
	float vx;
	float vy;
	int past;
}box;
void grav(box *, int);
void drawBird(float, float, float, int);
int obstacles(box *, box *, box *, box *, int, int, int, int *, int *);
void obglide(box *);
void makeob(box *, int, int);
void scorecheck(box *, box *, int *);
void endscreen(int, int);
void startscreen(int, int);
void gamemain(int, int);

int main(){
	int wd = 600, ht = 700;
	gfx_open(wd, ht, "Bird Flap Jawn");
	gamemain(wd, ht);
	return 0;
}

void gamemain(int wd, int ht){	
	startscreen(wd, ht);
	srand(time(0));
	box player;
	player.xc = 200;
	player.yc = ht/2;
	player.r = 25;
	player.vx = 0;
	player.vy = 0;
	box *user = &player;
	box foe1;
	box *f1 = &foe1;
	f1->xc = wd; // xc initialized at wd to avoid starting with a score of 2
	box foe2;
	box *f2 = &foe2;
	f2->xc = wd;
	box foe3;
	box *f3 = &foe3;
	f3->xc = wd;
	
	int pausetime = 10000;
	int game = 1;
	int ntime = 0;

	char showscore[20];
	int count = 0;
	int *cp = &count;
	int score = 0;
	int *points = &score;
	while (game){
		gfx_clear();
		gfx_clear_color(50, 50, 50);
		drawBird(user->xc, user->yc, user->r, 1);
		grav(user, ht);// controls the falling of the box and the jumps
		game = obstacles(user, f1, f2, f3, wd, ht, ntime, cp, points);//creates obstacles and checks if the user has collided with any of them
		sprintf(showscore, "Score: %8d", *points);
		gfx_text(20, 20, showscore);
		gfx_flush();
		usleep(pausetime);
		ntime++;
	}
}

void drawBird(float xc, float yc, float r, int color){
	float theta = PI/4, dt = PI/2;
	int i;
	if(color == 1){ // because they are both squares the same function is used for both the user and the obstacles with a condition that changes the color
	gfx_color(0, 255, 20);
	} else { gfx_color(255, 0, 0); }
	for(i = 0; i < 4; i++){
		gfx_line(xc + r*cos(theta), yc + r*sin(theta), xc + r*cos(theta+dt), yc + r*sin(theta+dt));
		theta += dt;
	}
	if(color == 1){//draws eyes on the user
		gfx_color(0, 255, 255);
		gfx_circle(xc + r/4, yc - r/4, r/8);
		gfx_circle(xc - r/4, yc - r/4, r/8);
	}
}

void grav(box *user, int ht){
	float g = .098;
	char u = 0;
	user->yc += user->vy; // changes position over time
	user->vy += g; // changes velocity over time
	if(user->yc >= ht-(user->r)){ // when bird reaches the bottom
		user->yc = ht-(user->r); // place flat on the bottom
		user->vy = 0; // doesn't bounce
	}
	if(gfx_event_waiting()){
		u = gfx_wait();
	}
	if(u == ' '){
		user->vy = -4;
	}
}

int obstacles(box *user, box *f1, box *f2, box *f3, int wd, int ht, int ntime, int *count, int *score){	
	int a= 0, b =0, c =0;
	if(ntime == 0 || (ntime%200) == 0){
		if(*count == 0){
			makeob(f1, wd, ht);
			*count += 1;
		} else if(*count == 1){
			makeob(f2, wd, ht);
			*count += 1;
		} else {
			makeob(f3, wd, ht);
			*count = 0;
		}
	}	
	drawBird(f1->xc, f1->yc, f1->r, 0);
	drawBird(f2->xc, f2->yc, f2->r, 0);
	drawBird(f3->xc, f3->yc, f3->r, 0);
	obglide(f1);
	obglide(f2);
	obglide(f3);
	scorecheck(user, f1, score);
	scorecheck(user, f2, score);
	scorecheck(user, f3, score);
	a = deathcheck(user, f1);
	b = deathcheck(user, f2);
	c = deathcheck(user, f3);
	if(a == 0 || b == 0 || c == 0){
		endscreen(wd, ht);
		return 0;
	}
	
	return 1;	
}

void obglide(box *ob){
	ob->xc += ob->vx;
}

void makeob(box *ob, int wd, int ht){
		ob->xc = wd;
		ob->yc = 50.0 + 1.0*(rand()%ht);
		ob->r = (rand()%(ht/4));
		ob->vx = -3.5;
		ob->vy = 0.0;
		ob->past = 0;
}

void scorecheck(box *user, box *ob, int *score){
	float checkpoint = ob->xc + ob->r;
	float useredge = user->xc - user->r;
	char showscore[30];
	if(useredge > checkpoint && ob->past == 0){
		*score += 1;
		ob->past = 1;
		printf("%d\n", *score);
	}
	sprintf(showscore, "Score: %8d", *score);
	gfx_text(20, 20, showscore);
}

int deathcheck(box *user, box *f){
	float dx = abs(f->xc - user->xc), dy = abs(f->yc - user->yc);
	if((dx < user->r && dy < user->r) || (dx < f->r && dy < f->r)) {
		return 0;
	}
	
	return 1;
}

void endscreen(int wd, int ht){
	gfx_clear_color(255, 0, 0);
	gfx_clear();
	gfx_color(0, 0, 0);
	char endmessage[80];
	char c;
	sprintf(endmessage, "You died...Press 'q' to quit.");
	while(1){
		gfx_clear_color(200, 0, 0);
		gfx_text(wd/2 -100, ht/2, endmessage);
		gfx_flush();
		if(gfx_event_waiting()) c = gfx_wait();
		if(c == 'q') break;
	}
}

void startscreen(int wd, int ht){
	char c = 0;
	char open[50];
	sprintf(open, "JUMP & DODGE Press 'p' to play");
	while(1){
		gfx_clear_color(0, 200, 200);
		gfx_clear();
		gfx_text(wd/2 - 100, ht/2 -10, open);
		gfx_flush();
		if(gfx_event_waiting()){
			c = gfx_wait();
		}
		if(c == 'p') break;
	}
}

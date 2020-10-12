#include "ex1_stars.h"
#include "../core/renderer.h"

#define MAX_RECTS 10000
#include <stdio.h>
#include <stdlib.h>

struct velocity {
  float dx;
  float dy;
} velocity;

int rect_count = 0;
int rect_add_count = 10;
quad_desc recs[MAX_RECTS];
struct velocity recs_dxy[MAX_RECTS];
spritebatch_desc sprt;

void event(const sapp_event *e);
void update(void);
void draw(void);

void ex1_start(void) {
  printf("Starting Game\n");
  sprt = (spritebatch_desc){.max_quads = MAX_RECTS,
                            .texture = {.path = "assets/flare.png"}};
  spritebatch_create(&sprt);
}

int ex1_frame(const sapp_event *e) {
  if (e != NULL) {
    event(e);
  }
  update();
  draw();
  return rect_count;
}

void ex1_end(void) {
  printf("Ending Game\n");
  spritebatch_destroy(&sprt);
}

void event(const sapp_event *e) {
  if (e->type == SAPP_EVENTTYPE_MOUSE_MOVE) {
    if (rect_count < MAX_RECTS) {
      float w = sprt.texture.width / 2.0f;
      float h = sprt.texture.height / 2.0f;

      for (int i = 0; i < rect_add_count; ++i) {
        recs[rect_count] = (quad_desc){
            .x = e->mouse_x - (w / 2.0f),
            .y = e->mouse_y - (h / 2.0f),
            .w = w,
            .h = h,
            .r = (float)rand() / (float)(RAND_MAX),
            .g = (float)rand() / (float)(RAND_MAX),
            .b = (float)rand() / (float)(RAND_MAX),
            .a = 1.0f,
            .type = EZY_QUAD_TEXTURE_COLOR,
        };

        recs_dxy[rect_count] = (struct velocity){
            .dx = (float)rand() / (float)(RAND_MAX)-0.5f,
            .dy = (float)rand() / (float)(RAND_MAX)-0.5f,
        };

        rect_count += 1;
      }
    }
    printf("Total Stars: %d\n", rect_count);
  }
}

void update(void) {
  for (int i = 0; i < rect_count; i++) {
    recs[i].x += recs_dxy[i].dx;
    recs[i].y += recs_dxy[i].dy;
    if (recs[i].x < 0 || recs[i].x + recs[i].w > 1280.0) {
      recs_dxy[i].dx *= -1;
    }
    if (recs[i].y < 0 || recs[i].y + recs[i].h > 720.0) {
      recs_dxy[i].dy *= -1;
    }
  }
}

void draw(void) {
  for (int i = 0; i < rect_count; i++) {
    spritebatch_draw(&sprt, recs[i]);
  }
  spritebatch_commit(&sprt);
}

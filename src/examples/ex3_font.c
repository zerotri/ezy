#include "ex3_font.h"
#include "../core/renderer.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "../../libs/stb/stb_image_write.h"

#define MAX_RECTS 10000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

font_texture font;
spritebatch_desc sprt3;
int fps = 0;
uint64_t last_time = 0;
double elapsed_time = 0.0;
int frame_count = 0;

void ex3_start(void) {
  printf("Starting Game\n");
  font = spritefont_create((font_texture_desc){
      .filepath = "assets/monogram_extended.ttf", .line_height = 48});

  sprt3 = (spritebatch_desc){.max_quads = MAX_RECTS,
                             .texture = {.type = EZY_TEXTURE_FONT, .font = font}};
  spritebatch_create(&sprt3);

  stm_setup();

  /*
  unsigned int sz = font.width * font.height;
  unsigned char bitmap2[sz*4];
  for (unsigned int i = 0; i < sz; ++i) {
    bitmap2[i*4+0] = 255;
    bitmap2[i*4+1] = 255;
    bitmap2[i*4+2] = 255;
    bitmap2[i*4+3] = font.bitmap[i];
  }
  stbi_write_png("out.png", font.width, font.height, 4, bitmap2, font.width *
  4);
  */
}

void ex3_frame(const sapp_event *e, int rects) {
  const double delta = stm_ms(stm_laptime(&last_time));
  elapsed_time += delta;
  if (elapsed_time > 1000.0) {
    elapsed_time = 0.0;
    fps = frame_count;
    frame_count = 0;
  } else {
    frame_count += 1;
  }

  char fps_str[10];
  char rects_str[10];
  sprintf(fps_str, "FPS: %d", fps);
  sprintf(rects_str, "%d", rects);
  spritefont_draw(&sprt3, "Hello World", 50.0, 100.0f, 1.0f);
  spritefont_draw(&sprt3, fps_str, 0.0, 0.0f, 1.0f);
  spritefont_draw(&sprt3, rects_str, 0.0, 48.0f, 1.0f);
  spritebatch_commit(&sprt3);
}

void ex3_end(void) {
  printf("Ending Game\n");
  spritebatch_destroy(&sprt3);
}

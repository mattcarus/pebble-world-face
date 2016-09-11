#include <pebble.h>
#include "main.h"

Window *my_window;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;
TextLayer *s_num_layer, *s_day_layer;
static Layer *s_hands_layer;
static GPath *s_minute_arrow, *s_hour_arrow;

static void hands_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  GRect frame = grect_inset(bounds, GEdgeInsets(0));
  GPoint center = grect_center_point(&bounds);

  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  
  // minute/hour hand
  graphics_context_set_fill_color(ctx, GColorOxfordBlue);
  graphics_context_set_stroke_color(ctx, GColorClear);
  graphics_context_set_stroke_width(ctx, 1);  // must be odd

  gpath_rotate_to(s_minute_arrow, TRIG_MAX_ANGLE * t->tm_min / 60);
  gpath_draw_filled(ctx, s_minute_arrow);
  gpath_draw_outline(ctx, s_minute_arrow);

  gpath_rotate_to(s_hour_arrow, (TRIG_MAX_ANGLE * (((t->tm_hour % 12) * 6) + (t->tm_min / 10))) / (12 * 6));
  gpath_draw_filled(ctx, s_hour_arrow);
  gpath_draw_outline(ctx, s_hour_arrow);

  // dot in the middle
  graphics_fill_circle(ctx, center, 5);
  graphics_draw_circle(ctx, center, 5);
  
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  // Create GBitmap
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMG_WORLD);

  // Create BitmapLayer to display the GBitmap
  s_background_layer = bitmap_layer_create(bounds);

  // Set the bitmap onto the layer and add to the window
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));
  
  s_hands_layer = layer_create(bounds);
  layer_set_update_proc(s_hands_layer, hands_update_proc);
  layer_add_child(window_layer, s_hands_layer);
}

static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
  layer_mark_dirty(window_get_root_layer(my_window));
}

static void window_unload(Window *window) {
  layer_destroy(s_hands_layer);
}

void handle_init(void) {
  my_window = window_create();
  window_set_background_color(my_window, GColorWhite);
  window_set_window_handlers(my_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(my_window, true);

  // init hand paths
  s_minute_arrow = gpath_create(&MINUTE_HAND_POINTS);
  s_hour_arrow = gpath_create(&HOUR_HAND_POINTS);
  
  Layer *window_layer = window_get_root_layer(my_window);
  GRect bounds = layer_get_bounds(window_layer);
  GPoint center = grect_center_point(&bounds);
  gpath_move_to(s_minute_arrow, center);
  gpath_move_to(s_hour_arrow, center);
  
  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
  
  // Force a refresh to position the hands correctly
  layer_mark_dirty(window_get_root_layer(my_window));
}

void handle_deinit(void) {
  gpath_destroy(s_minute_arrow);
  gpath_destroy(s_hour_arrow);
  
  tick_timer_service_unsubscribe();
  
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
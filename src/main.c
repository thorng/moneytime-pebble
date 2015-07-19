#include <pebble.h>
#include "menu_window.h"
 
//---pointers to the Window and TextLayer---
static Window *window;
static TextLayer *text_layer;
 
//---the click event handler for the SELECT button---
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  menu_window_push();
}
 
//---the click event handler for the UP button---
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Buy?");
}
 
//---the click event handler for the DOWN button---
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Sell?");
}
 
//---the click configuration provider function---
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}
 
//---called when the user enters the window---
static void window_load(Window *window) {
 
  //---gets the root layer of the window---
  Layer *window_layer = window_get_root_layer(window);
 
  //---gets the bound of the layer---
  GRect bounds = layer_get_bounds(window_layer);
 
  //---creates a new text TextLayer on the heap and init with default 
  // values---
  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
 
  //---sets the text to display in the TextLayer---
  text_layer_set_text(text_layer, "HP");
 
  //---sets the alignment of the TextLayer---
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
 
  //---adds the TextLayer onto the Window layer---
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}
 
//---called when the user leaves the window---
static void window_unload(Window *window) {
  //---destroys the TextLayer---
  text_layer_destroy(text_layer);
}
 
static void init(void) {
 
  //---creates a new Window on the heap and initialize with the default 
  // values---
  window = window_create();
 
  //---sets the click configuration provider callback function on the 
  // window---
  window_set_click_config_provider(window, click_config_provider);
 
  //---sets the window handlers of the Window---
  window_set_window_handlers(window, (WindowHandlers) {
  	.load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
 
  //---push the window onto the navigation stack using sliding animation---
  window_stack_push(window, animated);
}
 
static void deinit(void) {
  //---destroys the window---
  window_destroy(window);
}
 
//---the starting point for your app---
int main(void) {
 
  //---call this when the app is started---
  init();
 
  //---enters the app event loop; blocking call---
  app_event_loop();
 
  //---call this when the app gets killed---
  deinit();
}
#include <pebble.h>
	
#include "menu_window.h"
	
#define NUM_WINDOWS 3
	
static Window *s_main_window;
static MenuLayer *s_menu_layer;

uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return NUM_WINDOWS;
}

void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *context) {
  switch(cell_index->row) {
    case 0:
      menu_cell_basic_draw(ctx, cell_layer, "Buy", NULL, NULL);
      break;
    case 1:
      menu_cell_basic_draw(ctx, cell_layer, "Ignore", NULL, NULL);
      break;
    case 2:
      menu_cell_basic_draw(ctx, cell_layer, "Sell", NULL, NULL);
      break;
		default:
			break;
	}
}

void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  switch(cell_index->row) {
    case 0:
      //push buy window
      break;
    case 1:
			//ignore window?
			break;
    case 2:
      //push sell window
      break;
		default:
			break;
	}
}

void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_menu_layer = menu_layer_create(bounds);
  menu_layer_set_click_config_onto_window(s_menu_layer, window);
//   menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks) {
//       .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)get_num_rows_callback,
//       .draw_row = (MenuLayerDrawRowCallback)draw_row_callback,
//       .get_cell_height = (MenuLayerGetCellHeightCallback)get_cell_height_callback,
//       .select_click = (MenuLayerSelectCallback)select_callback,
//       .draw_header = (MenuLayerDrawHeaderCallback)draw_header_callback,
//       .get_header_height = (MenuLayerGetHeaderHeightCallback)get_header_height_callback,
//       .get_num_sections = (MenuLayerGetNumberOfSectionsCallback)get_num_sections_callback,
//   });
  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

void window_unload(Window *window) {
  menu_layer_destroy(s_menu_layer);
	s_main_window = NULL;
}

void menu_window_push() {
	if(!s_main_window) {
		s_main_window = window_create();
		window_set_window_handlers(s_main_window, (WindowHandlers) {
			.load = window_load,
			.unload = window_unload,
		});
	}
	window_stack_push(s_main_window, true);
}
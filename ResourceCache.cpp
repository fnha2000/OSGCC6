#include "ResourceCache.h"

ResourceCache::ResourceCache() {
	PHYSFS_init(NULL);
	PHYSFS_addToSearchPath("data/images.zip", 1);
	PHYSFS_addToSearchPath("data/sounds.zip", 1);
	al_init_image_addon();
	al_init_acodec_addon();
	al_set_physfs_file_interface();
}

ResourceCache::~ResourceCache() {
	PHYSFS_deinit();
	al_shutdown_image_addon();
}

ALLEGRO_BITMAP *ResourceCache::get_image(std::string file) {
	ALLEGRO_BITMAP *img;
	std::string filepath = "images/" + file;
	img = al_load_bitmap(filepath.c_str());
	if (!img) return NULL;
	else return img;
}

ALLEGRO_SAMPLE *ResourceCache::get_sound(std::string file) {
	ALLEGRO_SAMPLE *snd;
	std::string filepath = "sounds/" + file;
	snd = al_load_sample(filepath.c_str());
	if (!snd) return NULL;
	else return snd;
}
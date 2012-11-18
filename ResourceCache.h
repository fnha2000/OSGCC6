#ifndef RESOURCECACHE
#define RESOURCECACHE

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_physfs.h>
#include <physfs.h>
#include <string>

class ResourceCache {
public:
	ResourceCache();
	virtual ~ResourceCache();
	ALLEGRO_BITMAP *get_image(std::string file);
	ALLEGRO_SAMPLE *get_sound(std::string file);
};

#endif